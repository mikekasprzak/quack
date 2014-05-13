// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELSYNC_H__
#define __GEL_GELSYNC_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelNet.h"
// - ------------------------------------------------------------------------------------------ - //
class GelSync {
	typedef GelSync thistype;
public:
	GelNet Net;
	
	GelTime LocalTime;
	GelTime RemoteTime;
	GelTime TimeDiff;
	
	inline GelSync() :
		TimeDiff( 0 )
	{
	}
	
public:
	inline void Start( const bool Server ) {
		Net.Start( Server );
	}
	
	inline void Stop() {
		Net.Stop();
	}
	
	inline void Step() {
//		if ( Net.IsServer() ) {
//			LocalTime = get_ms_GelTime();
//		}
		Net.Step();
	}
	
	inline void SendSync() {
		Log("Send Sync");
		if ( !Net.IsServer() ) {
			LocalTime = get_ms_GelTime();

			GelPacket Packet;
			Packet.Add( Gel::PACKET_SYNC_REQUEST, &LocalTime, sizeof(LocalTime) );

			Net.SendPeer(Packet,0);
		}		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELSYNC_H__ //
// - ------------------------------------------------------------------------------------------ - //
