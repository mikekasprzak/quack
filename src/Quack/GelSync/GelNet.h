// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELNET_H__
#define __GEL_GELNET_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_GELNET
#ifdef USES_ENET
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

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_ENET //
#endif // USES_GELNET //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELNET_H__ //
// - ------------------------------------------------------------------------------------------ - //
