// - ------------------------------------------------------------------------------------------ - //
#include "GelNet.h"
// - ------------------------------------------------------------------------------------------ - //
int GelNet::ReadChunk( const void* Data, const ENetEvent& Event ) {
	const GelPacketChunk* Chunk = (GelPacketChunk*)Data;
	const GelNetClient* Client = (const GelNetClient*)Event.peer->data;

	//	roundTripTime

	switch ( Chunk->Type ) {
		case Gel::PACKET_TEST: {
			Log("! I GOT YOUR MESSAGE: \"%s\"", (const char*)Chunk->Data );
			break;
		}
		case Gel::PACKET_SYNC_REQUEST: {
			GelTime LocalTime;
			LocalTime = get_ms_GelTime();

			Log("Must Respond... %lli", LocalTime );
			
			GelPacket Packet;
			Packet.Add( Gel::PACKET_SYNC_RESPONSE, &LocalTime, sizeof(LocalTime) );

			Send(Packet,Event.peer,0);
			
			break;	
		}
		case Gel::PACKET_SYNC_RESPONSE: {
			GelTime* RemoteTime = (GelTime*)Chunk->Data;
			Log("Response! %lli", *RemoteTime );
			break;
		}
	}
	
	return Chunk->GetTotalSize();
}
// - ------------------------------------------------------------------------------------------ - //
