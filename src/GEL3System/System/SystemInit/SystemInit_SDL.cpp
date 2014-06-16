// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <Lib/Lib.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelSystemInit() {
	Log( "* SDL GelSystem Init()..." );
	
	// Populate List of Screens //
	int NumDisplays = SDL_GetNumVideoDisplays();
	for( int idx = 0; idx < NumDisplays; idx++ ) {
		// Common Screens //
		SDL_DisplayMode Mode;
		SDL_GetDesktopDisplayMode( idx, &Mode );

		SDL_Rect Rect;
		SDL_GetDisplayBounds( idx, &Rect );
		
		GelScreen Screen;
		Screen.w = Mode.w;
		Screen.h = Mode.h;

		int Flags = 0;

		#ifdef PRODUCT_DESKTOP
		Flags |= GelScreen::SF_WINDOW | GelScreen::SF_VARIABLE;
		#endif // PRODUCT_DESKTOP //
		
		#ifdef PRODUCT_CONSOLE
		Flags |= GelScreen::SF_TV | GelScreen::SF_VARIABLE | GelScreen::SF_OVERSCAN;
		#endif // PRODUCT_DESKTOP //

		#ifdef PRODUCT_MOBILE
		Flags |= 0;
		#endif // PRODUCT_DESKTOP //
		
		// In the case of Development Mode, if there's a 2nd screen, make it the default //
//		#ifdef PRODUCT_DEV_MODE
//		if ( NumDisplays > 1 ) {
//			if ( idx == 1 ) {
//				Flags |= GelScreen::SF_REQUIRED;
//			}
//		}
//		else
//		#endif // PRODUCT_DEV_MODE //

		if ( idx == 0 ) {
			Flags |= GelScreen::SF_REQUIRED;
		}

		Screen.SetFlags( Flags );

		// Finally, add the screen //
		Gel::Screen.Add( Screen );

		// Internal Screens //
		Gel::Native.push_back( GelNativeScreen() );
	}
	
	// Clear the Screen Scalar //
	Gel::ScreenScalar = 1.0f;

	Log( "* SDL GelSystem Init() done." );
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
