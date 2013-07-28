// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_GELSYSTEM_H__
#define __GEL_SYSTEM_GELSYSTEM_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
void gelSystemInit();
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
		
		SF_SCREEN_TYPE		= 0xF,		// Screen Types. TV, LCD, etc //
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

public:
	inline void SetFlags( const int _Flags ) {
		Flags |= _Flags;
	}
};
// - ------------------------------------------------------------------------------------------ - //
class GelScreens {
	std::vector<GelScreen> Screens;
public:
	inline GelScreens() {
	}
	
	inline void Add( const GelScreen& _Screen ) {
		Screens.push_back( _Screen );
	}
	
	inline const GelScreen& operator[]( const st Index ) const {
		return Screens[Index];
	}
	
	inline st Count() const {
		return Screens.size();
	}
};
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
// System Information Functions //
inline bool HasScreen() {return true;}	// Does it have a screen (duh)? //
bool HasFixedSizedScreens();			// True if one or more screens have a fixed size (3DS, WiiU, Android, PS Vita, ...)
bool HasTV();							// True if one or more screens are TVs (Wii U, PS3, PS4)
bool AreAllScreensRequired();			// True on a Multiscreen devices (3DS, Wii U) //
// - ------------------------------------------------------------------------------------------ - //
extern GelScreens Screen;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSYSTEM_H__ //
// - ------------------------------------------------------------------------------------------ - //
