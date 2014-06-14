// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELSYNC_H__
#define __GEL_GELSYNC_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelNet.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_GELNET
#ifdef USES_ENET
// - ------------------------------------------------------------------------------------------ - //
class GelSync {
	typedef GelSync thistype;
public:
	GelTime LocalTime;
	GelTime RemoteTime;
	GelTime TimeDiff;
	
	inline GelSync() :
		TimeDiff( 0 )
	{
	}
	
	// Bind my functions to the active GelNet //
	inline void Bind( GelNet* Net ) {
		Net->OnConnect.Connect( _OnConnect, this );
		Net->OnDisconnect.Connect( _OnDisconnect, this );
		Net->OnPacket.Connect( _OnPacket, this, GelSignal::FF_RETURN_IF_NON_ZERO );
	}
	
public:
	static void _OnConnect( thistype* Me, GelNet* Net ) {
		Me->OnConnect( Net );
	}
	inline void OnConnect( GelNet* Net ) {
		Log("SYNC CONNECT");
		SendSync(Net);
	}
	
	static void _OnDisconnect( thistype* Me, GelNet* Net ) {
		Me->OnDisconnect( Net );
	}
	inline void OnDisconnect( GelNet* Net ) {
		Log("SYNC DISCONNECT");
	}
	
	static st _OnPacket( thistype* Me, GelPacketData* Data, st Ret ) {
		return Me->OnPacket( Data, Ret );
	}
	inline st OnPacket( GelPacketData* Data, st Ret ) {
//		return_if( Ret );	// Now handled by FF_RETURN_IF_NON_ZERO //
		
		const GelPacketChunk* Chunk = Data->Chunk;

		switch ( Chunk->Type ) {
			case Gel::PACKET_SYNC_REQUEST: {
				GelTime LocalTime;
				LocalTime = get_ms_GelTime();
	
				Log("Must Respond... %lli", LocalTime );
				
				GelPacket Packet;
				Packet.Add( Gel::PACKET_SYNC_RESPONSE, &LocalTime, sizeof(LocalTime) );
	
				Data->SendResponse(Packet,0);
				
				return true;
				break;	
			}
			case Gel::PACKET_SYNC_RESPONSE: {
				GelTime* RemoteTime = (GelTime*)Chunk->Data;
				Log("Response! %lli", *RemoteTime );
				
				return true;
				break;
			}
		}
		
		return Ret;
	}

	inline void Step() {
	}
	
	inline void SendSync( GelNet* Net ) {
		if ( !Net->IsServer() ) {
			Log("Send Sync");
			LocalTime = get_ms_GelTime();

			GelPacket Packet;
			Packet.Add( Gel::PACKET_SYNC_REQUEST, &LocalTime, sizeof(LocalTime) );

			Net->SendPeer(Packet,0);
		}
	}
	
	// NOTE: Sending my TimeStamp, once we're in sync, we can determine the speed of each way by //
	// taking the difference. Can probably converge on it.
	
	// TODO: Need to rig up some sort of delayed action queue. Or callbacks once we know we've connected.
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ENET //
#endif // USES_GELNET //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELSYNC_H__ //
// - ------------------------------------------------------------------------------------------ - //
