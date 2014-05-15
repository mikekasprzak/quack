// - ------------------------------------------------------------------------------------------ - //
#include "GelNet.h"
// - ------------------------------------------------------------------------------------------ - //
int GelNet::ReadChunk( const void* Data, const ENetEvent& Event ) {
	const GelPacketChunk* Chunk = (GelPacketChunk*)Data;
	const GelNetClient* Client = (const GelNetClient*)Event.peer->data;

	//	roundTripTime
	
	st Ret = 0;

	switch ( Chunk->Type ) {
		case Gel::PACKET_TEST: {
			Log("! I GOT YOUR MESSAGE: \"%s\"", (const char*)Chunk->Data );
			Ret = true;
			break;
		}
	}
	
	GelPacketData PacketData;
	PacketData.Chunk = Chunk;
	PacketData.Net = this;
	PacketData.Event = &Event;
	
	Ret = (st)OnPacket( &PacketData, (void*)Ret );
	if ( Ret == 0 ) {
		Log("! PACKET WAS UNHANDLED !");
	}
	
	return Chunk->GetTotalSize();
}
// - ------------------------------------------------------------------------------------------ - //
