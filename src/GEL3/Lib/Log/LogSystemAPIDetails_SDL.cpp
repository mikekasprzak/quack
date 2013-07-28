// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
void gelLogSystemAPIDetails() {
	// Report SDL Version //
	Log( "-=- SDL Information -=-" );
	SDL_version ver;
	SDL_VERSION(&ver);
	Log( "SDL (core) - v%u.%u.%u -- Compiled Version", ver.major, ver.minor, ver.patch );

	SDL_version pver;
	SDL_GetVersion(&pver);
	Log( "SDL (core) - v%u.%u.%u -- Linked Version (DLL or Shared Library)", pver.major, pver.minor, pver.patch );
	Log( "" );

	int LinkVer = (ver.major << 16) | (ver.minor << 8) | (ver.patch << 0);
	int DLLVer = (pver.major << 16) | (pver.minor << 8) | (pver.patch << 0);

	if ( LinkVer > DLLVer ) {
		Log( "* WARNING: Linked version is older than Compiled version!!" );
		Log( "  If you have problems starting the game, this may be why." );
		Log( "  Upgrade to a newer SDL version to resolve this." );
		Log( "" );
	}
	
	// System Info //
	Log( "-=- SDL System Information -=-" );
	Log( "Platform: %s", SDL_GetPlatform() );
	Log( "CPU Cores: %i", SDL_GetCPUCount() );
	Log( "L1 Cache Line Size: %i", SDL_GetCPUCacheLineSize() );
	Log( "Has MMX: %s", SDL_HasMMX() ? "Yes" : "No" );
	Log( "Has 3DNow: %s", SDL_Has3DNow() ? "Yes" : "No" );
	Log( "Has SSE: %s", SDL_HasSSE() ? "Yes" : "No" );
	Log( "Has SSE 2: %s", SDL_HasSSE2() ? "Yes" : "No" );
	Log( "Has SSE 3: %s", SDL_HasSSE3() ? "Yes" : "No" );
	Log( "Has SSE 4.1: %s", SDL_HasSSE41() ? "Yes" : "No" );
	Log( "Has SSE 4.2: %s", SDL_HasSSE42() ? "Yes" : "No" );
	Log( "Has RDTSC Instruction: %s", SDL_HasRDTSC() ? "Yes" : "No" );
	Log( "Has AltiVec: %s", SDL_HasAltiVec() ? "Yes" : "No" );
	Log("");

	// NOTE: Not very useful. Number of drivers compiled in to SDL. //
	VLog( "-=- SDL Video Drivers (not very useful) -=-" );
	for( int idx = 0; idx < SDL_GetNumVideoDrivers(); idx++ ) {			
		VLog( "%i - %s", idx, SDL_GetVideoDriver( idx ) );
	}
	VLog("");
	
	// Displays Info //
	Log( "-=- Video Displays -- %i Device(s) Connected -=-", SDL_GetNumVideoDisplays() );
	for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {
		SDL_DisplayMode Mode;
		SDL_GetDesktopDisplayMode( idx, &Mode );

		SDL_Rect Rect;
		SDL_GetDisplayBounds( idx, &Rect );
		
		Log( "%i - %i, %i at %i Hz [%x] -- Location: %i, %i (%i,%i)", 
			idx, 
			Mode.w, Mode.h, Mode.refresh_rate, Mode.format, 
			Rect.x, Rect.y, Rect.w, Rect.h 
			);
	}
	Log("");
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
