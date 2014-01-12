// - ------------------------------------------------------------------------------------------ - //
// TODO: Timer Code
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Graphics/Graphics.h>
#include <Input/Input.h>
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
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //	
bool KeyESC = false;
bool KeyRefresh = false;

int KeyFakeLStick = 0;
int KeyFakeRStick = 0;
int KeyFakeButtons = 0;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int EventHandler( void* /*UserData*/, SDL_Event* Event ) {
	if ( Event->type == SDL_QUIT ) {
		Log( "> SDL_QUIT Signal Recieved" );
		AppRequestExit();
		return true;
	}
	else if ( Event->type == SDL_WINDOWEVENT ) {
		VVLog( "**** [%i] %s [%i,%i]", Event->window.windowID, SDL_WindowEventName( Event->window.event ), Event->window.data1, Event->window.data2 );

		int WindowIndex = Event->window.windowID;// Screen::GetIndexByWindowID( Event->window.windowID );
		if ( WindowIndex >= 0 ) {
			if ( Event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED ) {
				AppGainFocus();
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_FOCUS_LOST ) {
				AppLoseFocus();
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_MOVED ) {
//				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED ) {	// Preferred //
//				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_CLOSE )  {
				Log( "> SDL_WINDOWEVENT_CLOSE Signal Recieved from Window %i", Event->window.windowID );
				AppRequestExit();
				return true;		
			}
		}
	}
	else if ( Event->type == SDL_KEYUP ) {
		if ( Event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
			Gel::KeyESC = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F2 ) {
			Gel::KeyRefresh = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_UP )
			Gel::KeyFakeLStick &= ~(Gel::KeyFakeLStick & Gel::KEY_UP);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_DOWN )
			Gel::KeyFakeLStick &= ~(Gel::KeyFakeLStick & Gel::KEY_DOWN);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_LEFT )
			Gel::KeyFakeLStick &= ~(Gel::KeyFakeLStick & Gel::KEY_LEFT);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_RIGHT )
			Gel::KeyFakeLStick &= ~(Gel::KeyFakeLStick & Gel::KEY_RIGHT);

		else if ( Event->key.keysym.scancode == SDL_SCANCODE_W )
			Gel::KeyFakeRStick &= ~(Gel::KeyFakeRStick & Gel::KEY_UP);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_S )
			Gel::KeyFakeRStick &= ~(Gel::KeyFakeRStick & Gel::KEY_DOWN);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_A )
			Gel::KeyFakeRStick &= ~(Gel::KeyFakeRStick & Gel::KEY_LEFT);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_D )
			Gel::KeyFakeRStick &= ~(Gel::KeyFakeRStick & Gel::KEY_RIGHT);

		else if ( Event->key.keysym.scancode == SDL_SCANCODE_Z )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & 0x1);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_X )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & 0x2);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_C )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & 0x4);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_V )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & 0x8);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_Q )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & Gel::KEY_L);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_E )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & Gel::KEY_R);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_RETURN )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & Gel::KEY_MENU);
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_TAB )
			Gel::KeyFakeButtons &= ~(Gel::KeyFakeButtons & Gel::KEY_EXTRA);
	}
	else if ( Event->type == SDL_KEYDOWN ) {
		if ( (Event->key.keysym.scancode == SDL_SCANCODE_F4) && (Event->key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			Log( "> ALT+F4 Kill Signal Recieved" );
			AppRequestExit();
			return true;
		}
		
		if ( Event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
			Log( "> ESC Signal Recieved" );
			Gel::KeyESC = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F2 ) {
			Log( "> Refresh Signal Recieved (F2)" );
			Gel::KeyRefresh = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F10 ) {
			#ifdef PRODUCT_DEV_MODE
				// This *ALWAYS* kills the app if available, without bothering with a request. //
				// After all, it's for debugging anyways, and only in the Windows/Linux Builds. //
				Log( "> F10 Kill Signal Recieved. Forcing Exit." );
				AppRequestExit();	// Do this anyway, just in case we can exit. //
				App::Exit = true;	// Always forcefully exit. //
			#endif // PRODUCT_DEV_MODE //
			return true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_UP )
			Gel::KeyFakeLStick |= Gel::KEY_UP;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_DOWN )
			Gel::KeyFakeLStick |= Gel::KEY_DOWN;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_LEFT )
			Gel::KeyFakeLStick |= Gel::KEY_LEFT;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_RIGHT )
			Gel::KeyFakeLStick |= Gel::KEY_RIGHT;

		else if ( Event->key.keysym.scancode == SDL_SCANCODE_W )
			Gel::KeyFakeRStick |= Gel::KEY_UP;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_S )
			Gel::KeyFakeRStick |= Gel::KEY_DOWN;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_A )
			Gel::KeyFakeRStick |= Gel::KEY_LEFT;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_D )
			Gel::KeyFakeRStick |= Gel::KEY_RIGHT;

		else if ( Event->key.keysym.scancode == SDL_SCANCODE_Z )
			Gel::KeyFakeButtons |= 0x1;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_X )
			Gel::KeyFakeButtons |= 0x2;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_C )
			Gel::KeyFakeButtons |= 0x4;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_V )
			Gel::KeyFakeButtons |= 0x8;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_Q )
			Gel::KeyFakeButtons |= Gel::KEY_L;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_E )
			Gel::KeyFakeButtons |= Gel::KEY_R;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_RETURN )
			Gel::KeyFakeButtons |= Gel::KEY_MENU;
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_TAB )
			Gel::KeyFakeButtons |= Gel::KEY_EXTRA;
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


	// *** //
		
	// Initialize System //
	SDL_Init( SDL_INIT_VIDEO );

	// **** //

//#ifdef USES_MOBILE
//	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	
//	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
//	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
//	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
//	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
//
//	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
//	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

//#ifndef USES_MOBILE
	// Currently not safe on Tegra, so Desktop Only (for now) //
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);	// 4x //
//#endif // USES_MOBILE //

//#endif // USES_MOBILE //

	// **** //

	//SDL_GL_LoadLibrary( NULL );
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

	// *** //

	// Otherwise, we're a Game Loop //
	Log( "-=- Game Loop Begins -=-" );
	App::FrameTime = 0;
	App::WorkTime = get_us_GelTime();
	int FramesOfWorkComplete = 1; 		// We're beginning with 1 frame of work (Steps) complete //
	GelTime FrameOfWork = 1000000 / 60;	// A single unit of work, as a GelTime //

	Log("Start Time: %llu -- Work %i", App::WorkTime, FramesOfWorkComplete);

	// First Step //
	MainInput();	// Poll Input Devices //
	AppStep();		// Do an initial Step, beacuse we're going to do a Draw,Step,Flip loop //
	App::FrameTime++;
	App::WorkTime += FrameOfWork;
		
	int FPS_Step = 0;
	int FPS_Draw = 0;
	
	// A Draw, Step, Flip loop. Optimal for GPUs because good GPU code executes in parallel to the CPU. //
	while ( !App::Exit ) {
		bool DrawCalled = false;
		if ( FramesOfWorkComplete > 0 ) {
			AppDraw();				// *** DRAW *** //
			DrawCalled = true;
			FPS_Draw++;
		}

		GelTime TimeDiff = 0;
		GelTime TimeStamp = get_us_GelTime();
		if ( TimeStamp > App::WorkTime ) {
			TimeDiff = TimeStamp - App::WorkTime;
			FramesOfWorkComplete = TimeDiff / FrameOfWork;
		}
		else {
			FramesOfWorkComplete = 0;
		}
		
		//Log("%i Time: %llu (%llu - %llu) -- Work %i", App::FrameTime, TimeDiff, App::WorkTime, get_us_GelTime(), FramesOfWorkComplete);
		
		for ( int Frame = 0; Frame < FramesOfWorkComplete; Frame++ ) {
			if ( !App::Exit ) {
				MainInput();		// Poll Input Devices //
				AppStep();			// *** STEP *** //
				App::FrameTime++;
				App::WorkTime += FrameOfWork;
			}
			else {
				break;
			}
		}
		FPS_Step += FramesOfWorkComplete;

		bool Slept = false;
		
		if ( DrawCalled ) {
//			GelTime YeildTime = get_us_GelTime();
//			TimeDiff = FrameOfWork - (YeildTime - App::WorkTime);
//			TimeDiff -= 1000;
//			if ( TimeDiff < FrameOfWork ) {
//				gelSysUSleep(TimeDiff);
//				Slept = true;
//			}
//			Log("%i Time: %llu (%llu - %llu) -- Work %i", App::FrameTime, TimeDiff, App::WorkTime, get_us_GelTime(), FramesOfWorkComplete);

			gelSwapScreens();		// *** FLIP *** //
		}

		if ( FPS_Step > 60 ) {
			FPS_Step -= 60;
			App::FPS = FPS_Draw;
			FPS_Draw = 0;
		}

		if ( !Slept ) {
//			gelSysYield();
			gelSysMSleep(3);
		}
	}

	// *** //
	
	AppExit();		// Do Shutdown //
	
	// *** //

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
