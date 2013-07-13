// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Main/Main_HgVersion.h>
#include <Main/Main_Product.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <signal.h>
// - ------------------------------------------------------------------------------------------ - //
void term_func( int Signal ) {
	Log( "\nSIGTERM (Terminate) recieved -- %i", Signal );
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
void int_func( int Signal ) {
	Log( "\nSIGINT (Interrupt) recieved (CTRL+C) -- %i", Signal );
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern "C" int main( int argc, char* argv[] ) {
	LogInit();
	
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );
	
	// *** //

	Log( "-=======- GEL3 Application Started -- SDL2 Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2014 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "Hg Revision: %i [%s]", HG_VERSION, HG_HASH );
	Log( "Compiled on: %s %s", __DATE__, __TIME__ );

//	{
//		GelFileInfo_Core Finf;
//		stat_GelFileInfo_Core( &Finf, "shugar" );
//		Log("> shugar %x", Finf.Flags );
//		stat_GelFileInfo_Core( &Finf, "output" );
//		Log("> output %x", Finf.Flags );
//		stat_GelFileInfo_Core( &Finf, "makefile" );
//		Log("> makefile %x", Finf.Flags );
//	}

		
//	ReportCompilerVersion();
//	#ifdef USES_MINGW
//	Log( "Using DrMinGW: %s", (InitDrMinGW() ? "No" : "Yes") );
//	#endif // USES_MINGW //
//	ReportSDLVersion();
	
//	ArgInit( argc, argv );
//
//	// **** //
//
////	gelNetInit();
//		
//	// **** //
//
//	LogMemoryUsage();
//
//	//return 0;
//	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
//	SDL_GL_LoadLibrary( NULL );
//	SDL_DisableScreenSaver();
//	atexit(SDL_Quit);
//	atexit(SDL_GL_UnloadLibrary);
//	atexit(SDL_EnableScreenSaver);
//	
//	ReportSDLSystemInfo();
//	ReportSDLGraphicsInfo();
//
//	LogMemoryUsage();
//	
//	// **** //
//	
//	Log( "+ Creating Primary Window..." );
//	Screen::InitNative();
//	Log( "- Primary Window Created.\n" );
//
//	// **** //
//
//	System::Init();
//	Search::Init();
//	Input::Init();
//	Render::Init();
//	
//	// **** //
//
//	LogMemoryUsage();
//
//	{
//		cApp* App = new cApp();
//		SDL_SetEventFilter( EventHandler, 0 );
//		
//		LogMemoryUsage();
//
//		int FPS_Step = 0;
//		int FPS_Draw = 0;
//
//		SetFramesPerSecond( 60 );
//		WorkTime = GetTimeNow();
//		
//		extern bool KillSignal;
//		while ( !KillSignal ) {
//			TIMEVALUE TimeDiff = SubtractTime( GetTimeNow(), WorkTime );
//			int FramesOfWork = GetFrames( &TimeDiff );
//
//			if ( FramesOfWork >= 30 ) {
//				Log("! WARNING: FramesOfWork is high (%i)! Skipping Work...", FramesOfWork );
//				AddFrames( &WorkTime, FramesOfWork-1 );
//				FramesOfWork = 1;
//			}
//			
//			if ( __EscKey ) {
//				delete App;
//				App = new cApp();
//			}
//
//			for ( int Frame = 0; Frame < (FramesOfWork); Frame++ ) {
//				Input::Poll();
//				SDL_PumpEvents();
//				App->Step();
//
//				AddFrame( &WorkTime );
//			}
//			FPS_Step += FramesOfWork;
//
//			if ( (FramesOfWork > 0) ) {
//				// For All Screens //
//				for ( size_t idx = 0; idx < Screen::Native.Size(); idx++ ) {
//					if ( Screen::Native[idx].pWindow ) {
//						Screen::Native[idx].MakeCurrent(); // Memory Leak //
//						
//						App->Draw( Screen::Native[idx] );
//						
//						Screen::Native[idx].Swap(); // Memory Leak //
//					}
//				}
//				FPS_Draw++;
//
//				{
//					static int MemDrop = 0;
//					MemDrop++;
//					if ( (MemDrop & 255) == 255 ) {
//						LogMemoryUsage();
//					}
//				}
//			}
//
//			if ( FPS_Step > 60 ) {
//				FPS_Step -= 60;
//				FramesPerSecond = FPS_Draw;
//				FPS_Draw = 0;
//			}
//			
//			Wait(5);
//		}
//	}
//
//	// **** //
//	
//	Log( "+ Shutdown Started..." );
//	Screen::DestroyNative();
//	Log( "- Shutdown Complete." );
//	
	// **** //

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
