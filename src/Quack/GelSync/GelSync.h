// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELSYNC_H__
#define __GEL_GELSYNC_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelNet.h"
// - ------------------------------------------------------------------------------------------ - //
class GelSync {
	typedef GelSync thistype;
public:
//	GelNet Net;
	
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
	
	//inline void OnPacket( GelPacketData& 
	
//	inline void Start( const bool Server ) {
//		Net.Start( Server );
//	}
//	
//	inline void Stop() {
//		Net.Stop();
//	}
	
	inline void Step() {
//		Net.Step();
	}
	
	inline void SendSync( GelNet* Net ) {
		Log("Send Sync");
		if ( !Net->IsServer() ) {
			LocalTime = get_ms_GelTime();

			GelPacket Packet;
			Packet.Add( Gel::PACKET_SYNC_REQUEST, &LocalTime, sizeof(LocalTime) );

			Net->SendPeer(Packet,0);
		}
	}
	
	// NOTE: Sending my TimeStamp, once we're in sync, we can determine the speed of each way by //
	// taking the difference. Can probably converge on it.
	
	// TODO: Need to rig this up as hook functions (signals?). Need to recieve a call upon packets arriving.
	
	// TODO: Need to rig up some sort of delayed action queue. Or callbacks once we know we've connected.
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELSYNC_H__ //
// - ------------------------------------------------------------------------------------------ - //
