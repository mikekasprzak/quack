// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELNET_H__
#define __GEL_GELNET_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_GELNET
#ifdef USES_ENET
// - ------------------------------------------------------------------------------------------ - //
#include <enet/enet.h>
// - ------------------------------------------------------------------------------------------ - //
// Packet Header - 16 Bit Alignment //
// [pt][sz] - pt: Packet Type.  sz: Size in 2-bytes.
// Exception: if pt=0 (Null), then sz is size in bytes.
// - ------------------------------------------------------------------------------------------ - //
enum {
	GPT_NULL = 0,			// Null/Padding ** SIZE IN BYTES! NOT 2 BYTES!//
	
	GPT_PACKET_ID = 1,		//
	GPT_CONFIRM_ID,
	
	GPT_FRAME_ID = 4,		//
	
//	// Inputs (GamePads, etc) //
//	GPT_INPUT_START = 32,
//	GPT_INPUT_END = 63,
//	
//	// Engine Messages //
//	GPT_ENGINE_START = 64,
//	GPT_ENGINE_END = 254,
//
//	GPT_RAW = 255,			// Stream of Raw Data
};
// - ------------------------------------------------------------------------------------------ - //
struct GelNetChunk {
	typedef GelNetChunk thistype;
	
	unsigned char Type;		// Chunk Type (was Packet Type) //
	unsigned char Size;		// Size of Chunk in 2-Bytes, or larger if 255 is used //
	
	unsigned short Data[0];
	
	inline int GetSize() const {
		if ( Type == GPT_NULL )
			return Size;
		// Special Code: 255 (means use next short as size) //
		if ( Size == 255u )
			// Special Code: 65535 (means use next-next int as size) //
			if ( Data[0] == 65535u )
				// I give up, a whole integer for size. Forget the unsigned. //
				return *((int*)&Data[1]);
			else
				// 2-Shorts (+2), or values from 2 to 131070 //
				return 2+(Data[0]<<1);
		// 2-Bytes, or even values from 0-508 (510 [255] is a Special Code)
		return (Size<<1);
	}
	
	inline int GetTotalSize() const {
		if ( Type == GPT_NULL )
			return Size + sizeof(thistype);
		
		return (Size<<1) + sizeof(thistype);
	}
		
	
	inline void* GetData() {
		// 
		if ( Size == 255u )
			if ( Data[0] == 65535u )
				return &Data[3];
			else
				return &Data[1];
		return &Data[0];
	}
	
	inline const void* GetNextChunk() const {
		if ( Size == 255u )
			if ( Data[0] == 65535u )
				return &Data[3];
			else
				return &Data[1];
		return &Data[0];	
	}
	
//	inline bool IsInput() const {
//		return (PacketType >= GPT_INPUT_START) && (PacketType <= GPT_INPUT_END);
//	}
};
// - ------------------------------------------------------------------------------------------ - //
class GelNetClient {
	typedef GelNetClient thistype;
public:
	ENetAddress Address;

	char IpText[256];
	char NameText[256];
	char NiceText[512];
public:
	inline GelNetClient( const ENetAddress& _Address ) :
		Address( _Address )
	{
		IpText[0] = 0;
		NameText[0] = 0;
		NiceText[0] = 0;
		
		UpdateText();
	}
	
	inline void UpdateText() {
		enet_address_get_host_ip(&Address, IpText, sizeof(IpText));
				
		if ( NameText[0] == 0 ) {
			sprintf(NiceText, "%s:%i", IpText, Address.port );
		}
		else {
			sprintf(NiceText, "%s (%s:%i)", (NameText[0] == 0) ? "??" : NameText, IpText, Address.port );
		}
	}

	// This should be done in a thread, as it can sometimes take a while (to fail) //	
	inline void FetchName() {
		enet_address_get_host(&Address, NameText, sizeof(NameText));
		UpdateText();
	}
	
	inline bool operator == ( const GelNetClient& Vs ) const {
		if ( Address.host == Vs.Address.host )
			return Address.port == Vs.Address.port;
		return false;
	}
};
// - ------------------------------------------------------------------------------------------ - //
class GelNet {
	typedef GelNet thistype;
	
	bool Server;
	int Port;
	int Channels;
	int MaxClients;
	
	// ENET VARS //
	ENetHost* Host;
	ENetPeer* Peer;
public:	
	inline GelNet( const bool _Server = false, const int _Port = 10240 ) :
		Server( _Server ),
		Port( _Port ),
		Channels( 2 ),
		MaxClients( 8 ),
		Host( 0 ),
		Peer( 0 )
	{
		if ( enet_initialize() != 0 ) {
			Log("! An error occurred while initializing ENet.");
			return;
		}
	}
	
	inline ~GelNet() {
		Stop();
		enet_deinitialize();
	}

public:
	inline void Start() {
		Start(Server);
	}
	inline void Start( const bool _Server ) {
		Server = _Server;

		// Stop any old Servers/Clients //
		Stop();

		if ( Server ) {
			// NOTE: I think this is where we'd bind one of multiple Network interfaces. //
			ENetAddress Addr;
			Addr.host = ENET_HOST_ANY;
			Addr.port = Port;
	
			Host = enet_host_create( 
				&Addr,		// Bound Address //
				MaxClients,	// Outgoing Connections //
				Channels,	// Channels (0, 1, ...) //
				0,			// Incoming (Download) Bandwidth (0 for unlimited) //
				0			// Outgoing (Upload) Bandwidth (0 for unlimited)
			);
			
			if ( Host == NULL ) {
				printf("! Server Create Failed");
				return;
			}
	
			char IpText[256];
			enet_address_get_host_ip(&Addr, IpText, sizeof(IpText));
			Log("* Server Created [%s]", IpText);
		}
		else /* ClientMode */ {
			Host = enet_host_create( 
				NULL,		// No bound address (clients) are null //
				1, 			// Outgoing Connections //
				Channels,	// Channels (0, 1) //
				0,			// Incoming (Download) Bandwidth (0 for unlimited) //
				0			// Outgoing (Upload) Bandwidth (0 for unlimited)
			);
				
			if ( Host == NULL ) {
				printf("! Client Create Failed");
				return;
			}

			char IpText[256];
			enet_address_get_host_ip(&Host->address, IpText, sizeof(IpText));
	
			Log("* Client Created [%s]", IpText);
		}
	}
	
	inline void Stop() {
		if ( Peer ) {
			enet_peer_disconnect_now(Peer, 2 /* DATA */ );
		}
		if ( Host ) {
			int PeersDeleted = 0;
			// Delete all the Peers //
			for ( int idx = 0; idx < Host->peerCount; idx++ ) {
				if ( Host->peers[idx].data ) {
					delete (GelNetClient*)Host->peers[idx].data;
					PeersDeleted++;
				}
			}
			Log( "* Deleted %i of %i Peers.", PeersDeleted, Host->peerCount );
			
			enet_host_destroy(Host);
		}
	}

public:
	inline void Step() {
		if ( Host ) {
			if ( Server )
				ServerStep();
			else
				ClientStep();
		}
	}
	
	inline void ServerStep() {
		ENetEvent Event;

		while( enet_host_service(Host, &Event, 0) > 0 ) {
			switch( Event.type ) {					
				case ENET_EVENT_TYPE_CONNECT: {
					Event.peer->data = new GelNetClient( Event.peer->address );
					GelNetClient* Client = (GelNetClient*)Event.peer->data;

					Log("* A new client connected from %s [%i].", 
						Client->NiceText,
						Event.data
					);
					
					break;
				}
				case ENET_EVENT_TYPE_RECEIVE: {
					GelNetClient* Client = (GelNetClient*)Event.peer->data;

					Log("A packet of length %lu containing \"%s\" was received from %s on channel %u [%i].",
						Event.packet -> dataLength,
						Event.packet -> data,
						Client->NiceText,
						Event.channelID,
						Event.data
					);
						
					/* Clean up the packet now that we're done using it. */
					enet_packet_destroy( Event.packet );
				
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT: {
					GelNetClient* Client = (GelNetClient*)Event.peer->data;

					Log( "* %s disconnected [%i].", 
						Client->NiceText,
						Event.data
					);
					
					if ( Event.peer->data )
						delete (GelNetClient*)Event.peer->data;

					/* Reset the peer's client information. */
					Event.peer->data = NULL;

					break;
				}
			}
		}
		
	}
	
	inline void ClientStep() {
		ENetEvent Event;

		while( enet_host_service(Host, &Event, 0) > 0 ) {
			switch( Event.type ) {					
				case ENET_EVENT_TYPE_CONNECT: {
					Event.peer->data = new GelNetClient( Event.peer->address );
					GelNetClient* Client = (GelNetClient*)Event.peer->data;

					Log("* Connected to %s [%i].", 
						Client->NiceText,
						Event.data
					);

					break;
				}
				case ENET_EVENT_TYPE_RECEIVE: {
					GelNetClient* Client = (GelNetClient*)Event.peer->data;
					
					Log("A packet of length %lu containing \"%s\" was received from %s on channel %u.",
						Event.packet -> dataLength,
						Event.packet -> data,
						//(char*)Event.peer -> data,
						Client->NiceText,
						Event.channelID
					);
						
					/* Clean up the packet now that we're done using it. */
					enet_packet_destroy( Event.packet );
				
					break;
				}
				case ENET_EVENT_TYPE_DISCONNECT: {
					GelNetClient* Client = (GelNetClient*)Event.peer->data;
					
					Log( "%s disconnected [%i].", 
						Client->IpText,
						Event.data
					);

					if ( Event.peer->data )
						delete (GelNetClient*)Event.peer->data;
					Event.peer->data = NULL;

					break;
				}
			}
		}		
	}
	
public:
	// Connect to a specific client (by IP or Name) //
	inline void Connect( const char* Address ) {
		ENetAddress Addr;
		enet_address_set_host(&Addr, Address);
		Addr.port = Port;

		Connect( Addr );
	}	
	// Connect to whomever is recieving on the Broadcast Address //
	// NOTE: A better solution would be to create a list of all clients who respond to a broadcast //
	inline void ConnectLocal() {
		ENetAddress Addr;
		Addr.host = ENET_HOST_BROADCAST;
		Addr.port = Port;
		
		Connect( Addr );
	}
	
	inline void Connect( ENetAddress& Addr ) {
		Peer = enet_host_connect( Host, &Addr, Channels, 7 /* DATA */ );
		
		if ( Peer == NULL ) {
			Log("* Peer not found");
		}
	}
	
	inline void Disconnect() {
		if ( Peer ) {
			enet_peer_disconnect( Peer, 1 /* DATA */ );
		}
	}
	
	inline void LogPeers() {
		const char* States[] = {
			"ENET_PEER_STATE_DISCONNECTED",
			"ENET_PEER_STATE_CONNECTING",
			"ENET_PEER_STATE_ACKNOWLEDGING_CONNECT",
			"ENET_PEER_STATE_CONNECTION_PENDING",
			"ENET_PEER_STATE_CONNECTION_SUCCEEDED",
			"ENET_PEER_STATE_CONNECTED",
			"ENET_PEER_STATE_DISCONNECT_LATER",
			"ENET_PEER_STATE_DISCONNECTING",
			"ENET_PEER_STATE_ACKNOWLEDGING_DISCONNECT",
			"ENET_PEER_STATE_ZOMBIE",
			"" 
		};

		for ( int idx = 0; idx < Host->peerCount; idx++ ) {
			Log("* %x [%s]", Host->peers[idx].address.host, Host->peers[idx].address.host ? States[Host->peers[idx].state] : "-" );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ENET //
#endif // USES_GELNET //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELNET_H__ //
// - ------------------------------------------------------------------------------------------ - //
