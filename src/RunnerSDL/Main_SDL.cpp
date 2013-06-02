// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL2.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <Timer/Timer.h>
#include <DrMinGW/DrMinGW.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
//#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Main/Main_Product.h>
#include <Main/Main_HgVersion.h>
#include "Main_SDL_InitLog.h"

#include <System/System.h>
#include <Screen/Screen.h>
#include <Search/Search.h>
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern int FramesPerSecond;
int FramesPerSecond = 0;

TIMEVALUE WorkTime;
void SkipTime() {
	WorkTime = GetTimeNow();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <System/Path.h>

//extern char AppBaseDir[];
//char AppBaseDir[2048];
//
//extern char AppSaveDir[];
//char AppSaveDir[2048] = "";
// - ------------------------------------------------------------------------------------------ - //
// TODO: Rename this. ArgInit? SystemInit? Only non arg is the PID
void ArgInit( int argc, char* argv[] ) {
	Log( "-=- Application Execution Info -=-" );
	
	// Show Command Line //
	{
		Log( "Command Line Arguments: %i", argc );
		for ( int idx = 0; idx < argc; idx++ ) {
			Log( "argv[%i]: \"%s\"", idx, argv[idx] );	
		}
	}

	// Get Base Directory //
	{	
		// TODO: Add Arg Decomposer //
		if ( argc > 1 ) {
			// HACK: if more than 1 args, assume higher Log Level //
			LogLevel = 3;
		}

		bool DetermineContentPath = true;
		if ( argc > 2 ) {
			if ( strcmp( argv[1], "-DIR" ) == 0 ) {
				strcpy( System::BaseDir, argv[2] );
				DetermineContentPath = false;
			}
		}

		bool DetermineSavePath = true;
		if ( argc > 4 ) {
			if ( strcmp( argv[3], "-SAVE" ) == 0 ) {
				strcpy( System::SaveDir, argv[4] );
				DetermineSavePath = false;
			}
		}
		
		if ( DetermineContentPath )
			gelGetContentPath( System::BaseDir, sizeof(System::BaseDir) );

		if ( DetermineSavePath )
			gelGetStoragePath( System::SaveDir, sizeof(System::SaveDir) );
		
		Log( "Base Directory: %s", System::BaseDir );
		Log( "Save Directory: %s", System::SaveDir );
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
extern bool __UpKey;
extern bool __DownKey;
extern bool __LeftKey;
extern bool __RightKey;
extern bool __TabKey;
extern bool __EscKey;
extern bool __F1Key;
extern bool __F2Key;
extern bool __F3Key;
extern bool __F4Key;
extern bool __1Key;
extern bool __2Key;
// - ------------------------------------------------------------------------------------------ - //
bool __UpKey = false;
bool __DownKey = false;
bool __LeftKey = false;
bool __RightKey = false;
bool __TabKey = false;
bool __EscKey = false;
bool __F1Key = false;
bool __F2Key = false;
bool __F3Key = false;
bool __F4Key = false;
bool __1Key = false;
bool __2Key = false;
// - ------------------------------------------------------------------------------------------ - //
bool KillSignal = false;
// - ------------------------------------------------------------------------------------------ - //
int EventHandler( void* /*UserData*/, SDL_Event* Event ) {
	extern bool KillSignal;
	
	if ( Event->type == SDL_QUIT ) {
		Log( "> SDL_QUIT Signal Recieved" );
		KillSignal = true;
		return true;
	}
	else if ( Event->type == SDL_KEYUP ) {
//		if ( Event->key.keysym.keycode == SDLK_TAB ) { // Key on current keyboard //
//		if ( Event->key.keysym.scancode == SDL_SCANCODE_TAB ) { // Key on all keyboards //

		if ( (Event->key.keysym.scancode == SDL_SCANCODE_RETURN) && (Event->key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			Screen::ToggleScreens();
		}
		else if ( (Event->key.keysym.scancode == SDL_SCANCODE_F4) && (Event->key.keysym.mod & (KMOD_LALT | KMOD_RALT)) ) {
			Log( "> ALT+F4 Kill Signal Recieved" );
			KillSignal = true;
			return true;
		}
		#ifndef ndebug
			// Only I use F10 as a standard exit key, so remove it when a release build //
			else if ( Event->key.keysym.scancode == SDL_SCANCODE_F10 ) {
				Log( "> F10 Kill Signal Recieved" );
				KillSignal = true;
				return true;
			}
		#endif // ndebug //
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F12 ) {
			if ( Screen::Native.Size() > 1 ) {
				if ( Screen::Native[1].HasWindow() ) {
					Screen::RemoveScreens();
				}
				else {
					Screen::AddScreens();
				}
			}
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_UP ) {
			__UpKey = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_DOWN ) {
			__DownKey = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_LEFT ) {
			__LeftKey = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_RIGHT ) {
			__RightKey = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_TAB ) {
			__TabKey = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
			__EscKey = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F1 ) {
			__F1Key = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F2 ) {
			__F2Key = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F3 ) {
			__F3Key = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F4 ) {
			__F4Key = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_1 ) {
			__1Key = false;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_2 ) {
			__2Key = false;
		}
	}
	else if ( Event->type == SDL_KEYDOWN ) {
		if ( Event->key.keysym.scancode == SDL_SCANCODE_UP ) {
			__UpKey = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_DOWN ) {
			__DownKey = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_LEFT ) {
			__LeftKey = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_RIGHT ) {
			__RightKey = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_TAB ) {
			__TabKey = true;
		}
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
			__EscKey = true;
		}		
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F1 ) {
			__F1Key = true;
		}		
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F2 ) {
			__F2Key = true;
		}		
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F3 ) {
			__F3Key = true;
		}		
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_F4 ) {
			__F4Key = true;
		}		
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_1 ) {
			__1Key = true;
		}		
		else if ( Event->key.keysym.scancode == SDL_SCANCODE_2 ) {
			__2Key = true;
		}		
	}
	else if ( Event->type == SDL_WINDOWEVENT ) {
		VVLog( "**** [%i] %s [%i,%i]", Event->window.windowID, SDL_WindowEventName( Event->window.event ), Event->window.data1, Event->window.data2 );
		
		int WindowIndex = Screen::GetIndexByWindowID( Event->window.windowID );
			
		if ( WindowIndex >= 0 ) {
			if ( Event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED ) {
				System::GainFocus();
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_FOCUS_LOST ) {
				System::LoseFocus();
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_MOVED ) {
				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_SIZE_CHANGED ) {	// Preferred //
				Screen::Update( WindowIndex );
			}
			else if ( Event->window.event == SDL_WINDOWEVENT_CLOSE )  {
				Log( "> SDL_WINDOWEVENT_CLOSE Signal Recieved from Window %i", Event->window.windowID );
				KillSignal = true;
				return true;		
			}
		}
	}
	return false;
}
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
#include <Node/GelList.h>
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();
	
	signal( SIGTERM, term_func );
	signal( SIGINT, int_func );
	
	// *** //

	Log( "-=======- GEL2 Application Started -- SDL2 Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2013 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "Hg Revision: %i:%s", HG_VERSION, HG_HASH );
	Log( "Compiled on: %s %s", __DATE__, __TIME__ );
	
	ReportCompilerVersion();
	#ifdef USES_MINGW
	Log( "Using DrMinGW: %s", (InitDrMinGW() ? "No" : "Yes") );
	#endif // USES_MINGW //
	ReportSDLVersion();
	
	ArgInit( argc, argv );

	// **** //

//	gelNetInit();
		
	// **** //
	
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK );
	SDL_GL_LoadLibrary( NULL );
	SDL_DisableScreenSaver();
	atexit(SDL_Quit);
	atexit(SDL_GL_UnloadLibrary);
	atexit(SDL_EnableScreenSaver);
	
	ReportSDLSystemInfo();
	ReportSDLGraphicsInfo();
	
	// **** //
	
	Log( "+ Creating Primary Window..." );
	Screen::InitNative();
	Log( "- Primary Window Created.\n" );

	// **** //

	System::Init();
	Search::Init();
	Input::Init();
	Render::Init();
	
	// **** //

	{
//		cApp* App = new cApp();
		SDL_SetEventFilter( EventHandler, 0 );
		
		Log( "Mem: %i", System::GetMemoryUsage() );

		int FPS_Step = 0;
		int FPS_Draw = 0;

		SetFramesPerSecond( 60 );
		WorkTime = GetTimeNow();
		
		extern bool KillSignal;
		while ( !KillSignal ) {
			TIMEVALUE TimeDiff = SubtractTime( GetTimeNow(), WorkTime );
			int FramesOfWork = GetFrames( &TimeDiff );

			if ( FramesOfWork >= 30 ) {
				Log("! WARNING: FramesOfWork is high (%i)! Skipping Work...", FramesOfWork );
				FramesOfWork = 1;
			}
			
//			if ( __EscKey ) {
//				delete App;
//				App = new cApp();
//			}

			for ( int Frame = 0; Frame < (FramesOfWork); Frame++ ) {
				Input::Poll();
				SDL_PumpEvents();
//				App->Step();

				AddFrame( &WorkTime );
			}
			FPS_Step += FramesOfWork;

			if ( (FramesOfWork > 0) ) {
				// For All Screens //
				for ( size_t idx = 0; idx < Screen::Native.Size(); idx++ ) {
					if ( Screen::Native[idx].pWindow ) {
						Screen::Native[idx].MakeCurrent(); // Memory Leak //
						
//						App->Draw( Screen::Native[idx] );
						
						Screen::Native[idx].Swap(); // Memory Leak //
					}
				}
				FPS_Draw++;

				// ** WEIRD ** //			
				{
					static int MemDrop = 0;
					static int OldMemory = 0;
					int Memory = System::GetMemoryUsage();
					MemDrop++;
					if ( (MemDrop & 255) == 255 ) {
						char MemoryState[] = " ";
						if ( Memory > OldMemory )
							MemoryState[0] = '+';
						else if ( Memory < OldMemory )
							MemoryState[0] = '-';
						Log( "Mem[%s]: %i [%ik -- %iM] -- %s", MemoryState, Memory, Memory / 1024, Memory / 1024 / 1000, System::GetClockShortString() );
						OldMemory = Memory;
					}
				}
			}

			if ( FPS_Step > 60 ) {
				FPS_Step -= 60;
				FramesPerSecond = FPS_Draw;
				FPS_Draw = 0;
			}
			
			Wait(5);
		}
	}

	// **** //
	
	Log( "+ Shutdown Started..." );
	Screen::DestroyNative();
	Log( "- Shutdown Complete." );
	
	// **** //

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
