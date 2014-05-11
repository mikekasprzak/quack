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
		MaxClients( 32 ),
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
	
			{		
				char IpText[256];
//				char NameText[4096];
//				enet_address_get_host_ip(&Host->address, IpText, sizeof(IpText));
//				enet_address_get_host(&Host->address, NameText, sizeof(NameText));
				enet_address_get_host_ip(&Addr, IpText, sizeof(IpText));
//				enet_address_get_host(&Addr, NameText, sizeof(NameText));
	
//				printf("Server Created: %s [%s]\n", IpText, NameText);
				Log("* Server Created: %s", IpText);
			}
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
		}
	}
	
	inline void Stop() {
		if ( Peer ) {
			enet_peer_reset(Peer);
		}
		if ( Host ) {
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
				case ENET_EVENT_TYPE_CONNECT:
					Log("A new client connected from %x:%u.", 
						Event.peer -> address.host,
						Event.peer -> address.port
					);
					
					/* Store any relevant client information here. */
					Event.peer -> data = (void*)"Client information";
				break;
				case ENET_EVENT_TYPE_RECEIVE:
					Log("A packet of length %lu containing \"%s\" was received from %s on channel %u.",
						Event.packet -> dataLength,
						Event.packet -> data,
						(char*)Event.peer -> data,
						Event.channelID
					);
						
					/* Clean up the packet now that we're done using it. */
					enet_packet_destroy( Event.packet );
				
					break;
				
				case ENET_EVENT_TYPE_DISCONNECT: {
					Log( "%s disconnected.", (char*)Event.peer->data );
					/* Reset the peer's client information. */
					Event.peer -> data = NULL;

					break;
				default:
					Log("other\n");
				}
			}
		}		
		
	}
	
	inline void ClientStep() {
		//ENetEvent Event;
		ServerStep();
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
		Peer = enet_host_connect( Host, &Addr, Channels, 0 /* DATA */ );
		
		if ( Peer == NULL ) {
			Log("* Peer not found");
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ENET //
#endif // USES_GELNET //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELNET_H__ //
// - ------------------------------------------------------------------------------------------ - //
