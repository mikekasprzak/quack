// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_SDL2.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelSystem.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelSystemInit() {
	Log( "* SDL GelSystem Init()..." );
	
	// Populate List of Screens //
	for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {
		SDL_DisplayMode Mode;
		SDL_GetDesktopDisplayMode( idx, &Mode );

		SDL_Rect Rect;
		SDL_GetDisplayBounds( idx, &Rect );
		
		GelScreen Screen;
		Screen.w = Mode.w;
		Screen.h = Mode.h;
		Screen.SetFlags( GelScreen::SF_TV | GelScreen::SF_WINDOW );
		
		Gel::Screen.Add( Screen );
		
//		Log( "%i - %i, %i at %i Hz [%x] -- Location: %i, %i (%i,%i)", 
//			idx, 
//			Mode.w, Mode.h, Mode.refresh_rate, Mode.format, 
//			Rect.x, Rect.y, Rect.w, Rect.h 
//			);
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
bool HasFixedSizedScreens() { return false; }
bool HasTV() { return true; } // TODO: #ifdef Android, OUYA
bool AreAllScreensRequired() { return false; }
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
