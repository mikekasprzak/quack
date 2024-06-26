// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_GELSCREEN_GELSCREEN_H__
#define __GEL_SYSTEM_GELSCREEN_GELSCREEN_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
class GelScreen {
public:
	int w, h;
	int Flags;

	enum /* Screen Flags */ {
		// A Television attached to a console may be variable, meaning developer has choice of resolution (720p). //
		// Overscan is a seperate property. The Wii U's Gamepad may be considered a TV without Overscan. EDIT: No. //
		// There isn't much significance to being a TV, just FYI. A Computer Monitor is a TV. //
		// A TV is a non-integrated screen (as opposed to an integrated LCD). //
		SF_VARIABLE			= 0x1,		// This screen can vary in size and shape at runtime.
		SF_OVERSCAN			= 0x2,		// This screen is affected by overscan (TV's only... typically).
		SF_TV				= 0x4,		// This screen is a television/monitor attached to a Console/PC.
		SF_WINDOW			= 0x8,		// This screen is a window (PC, Web).
		
		SF_SCREEN_TYPE		= 0xFF,		// Screen Types. TV, LCD, etc //
		
		SF_REQUIRED			= 0x100,	// This screen is required (i.e. #0 on PC, #0 & #1 on 3DS)
	};
public:
	inline bool IsVariable() const {
		return Flags & SF_VARIABLE;
	}
	inline bool IsOverscan() const {
		return Flags & SF_OVERSCAN;
	}
	inline bool IsTV() const {
		return Flags & SF_TV;
	}
	inline bool IsWindow() const {
		return Flags & SF_WINDOW;
	}
	inline bool IsRequired() const {
		return Flags & SF_REQUIRED;
	}

public:
	inline void SetFlags( const int _Flags ) {
		Flags = _Flags;
	}
	inline void SetFlag( const int _Flags ) {
		Flags |= _Flags;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSCREEN_GELSCREEN_H__ //
// - ------------------------------------------------------------------------------------------ - //
