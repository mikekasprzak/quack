// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <Lib/Lib.h>
#include <System/System.h>
#include <System/GelScreen/GelScreens_Internal_SDL.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelSystemInit() {
	Log( "* SDL GelSystem Init()..." );
	
	// Populate List of Screens //
	for( int idx = 0; idx < SDL_GetNumVideoDisplays(); idx++ ) {
		// Common Screens //
		SDL_DisplayMode Mode;
		SDL_GetDesktopDisplayMode( idx, &Mode );

		SDL_Rect Rect;
		SDL_GetDisplayBounds( idx, &Rect );
		
		GelScreen Screen;
		Screen.w = Mode.w;
		Screen.h = Mode.h;
		Screen.SetFlags( GelScreen::SF_TV | GelScreen::SF_WINDOW );
		
		Gel::Screen.Add( Screen );

		// Internal Screens //
		Gel::Native.push_back( GelNativeScreen() );
	}
	
	// Clear the Screen Scalar //
	Gel::ScreenScalar = 1.0f;
}
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//namespace Gel {
//// - ------------------------------------------------------------------------------------------ - //
//bool HasFixedSizedScreens() { return false; }
//bool HasTV() { return true; } // TODO: #ifdef Android, OUYA
//bool AreAllScreensRequired() { return false; }
//// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
