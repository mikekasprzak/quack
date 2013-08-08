// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
#include <App.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <signal.h>
// - ------------------------------------------------------------------------------------------ - //
void term_func( int Signal ) {
	LogAlways( "\nGEL3: SIGTERM (Terminate) recieved -- %i", Signal );
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //
void int_func( int Signal ) {
	LogAlways( "\nGEL3: SIGINT (Interrupt) recieved (CTRL+C) -- %i", Signal );
	exit(1);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int EventHandler( void* /*UserData*/, SDL_Event* Event ) {
	if ( Event->type == SDL_QUIT ) {
		Log( "> SDL_QUIT Signal Recieved" );
		App::Exit = true;
		return true;
	}
	else if ( Event->type == SDL_KEYUP ) {
	}
	else if ( Event->type == SDL_KEYDOWN ) {	
		if ( Event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
			Log( "> ESC Signal Recieved" );
		}
		if ( Event->key.keysym.scancode == SDL_SCANCODE_F10 ) {
			Log( "> F10 Kill Signal Recieved" );
			App::Exit = true;
			return true;
		}
	}
	return false;	
}
// - ------------------------------------------------------------------------------------------ - //
void MainInput() {
	// TODO: Poll Input Devices here //	
	SDL_PumpEvents();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern "C" int main( int argc, char* argv[] ) {
	LogInit();
	
	// Install C/Unix Signals //
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );

	// **** //
	
	gelLogCompilerDetails();

	// **** //
	
	// Initialize System //
	SDL_Init( SDL_INIT_VIDEO /*| SDL_INIT_JOYSTICK*/ );
	SDL_GL_LoadLibrary( NULL );
	SDL_DisableScreenSaver();
	atexit(SDL_Quit);
	atexit(SDL_GL_UnloadLibrary);
	atexit(SDL_EnableScreenSaver);
	SDL_SetEventFilter( EventHandler, 0 );

	gelLogSystemAPIDetails();

	// *** //
	
	// Initialize App //
	AppInit();

	// If the Mode is AM_MAIN, then we're already done //
	if ( App::Mode == App::AM_MAIN )
		return 0;	// TODO: return App::Error; //
	else if ( App::Mode == App::AM_NULL ) {
		return 1;	// TODO: return App::Error; //
	}

	// Otherwise, we're a Game Loop //
	Log( "-=- Game Loop Begins -=-" );
	App::FrameTime = 0;
	MainInput();	// Poll Input Devices //
	AppStep();		// Do an initial Step, beacuse we're going to do a Draw,Step,Flip loop //
	
	// A Draw, Step, Flip loop. Optimal for GPUs because good GPU code executes in parallel to the CPU. //
	while ( !App::Exit ) {
		AppDraw();				// *** DRAW *** //
		if ( !App::Exit ) {
			App::FrameTime++;
			MainInput();		// Poll Input Devices //
			AppStep();			// *** STEP *** //
		}
		gelSwapScreens();		// *** FLIP *** //
		gelSysYield();
	}
	

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

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
