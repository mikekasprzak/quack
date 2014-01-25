// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include "Input.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
//#include <System/System.h>
#include <App.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
namespace SDLInput {
// - ------------------------------------------------------------------------------------------ - //
enum { 
	MAX_GAMEPADS = 32
};
// - ------------------------------------------------------------------------------------------ - //
st32 IndexBase;
SDLGamePad GamePad[MAX_GAMEPADS];
// - ------------------------------------------------------------------------------------------ - //
SDL_Joystick* State[MAX_GAMEPADS];
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	// Close All Joysticks //
	for ( st32 idx = 0; idx < DevicesConnected(); idx++ ) {
		SDL_JoystickClose( State[idx] );
	}	
	
	SDL_QuitSubSystem( SDL_INIT_JOYSTICK );
}
// - ------------------------------------------------------------------------------------------ - //
void ExitEvent( void* ) {
	Exit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Init() {
	SDL_InitSubSystem( SDL_INIT_JOYSTICK );
	
	// Open All Joysticks //
	for ( st32 idx = 0; idx < DevicesConnected(); idx++ ) {
		State[idx] = SDL_JoystickOpen( idx );
		GamePad[idx].NumAxis = SDL_JoystickNumAxes(State[idx]);
	}
	
	// Connect Signals (Functions to be called) //		
	Gel::Input::Poll.Connect( PollEvent );
}
// - ------------------------------------------------------------------------------------------ - //
void InitEvent( void* _IndexBase ) {
	IndexBase = (st)_IndexBase;

	Init();
	Poll();
	
	Log( "" );
	Log( "-=- SDLInput -- %i Device(s) Connected [%i] -=-", DevicesConnected(), Size() );
	for ( st32 idx = 0; idx < DevicesConnected(); idx++ ) {
        Log( "%i - %s", idx, SDL_JoystickName(State[idx]) );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void Poll() {
	SDL_JoystickUpdate();
	
	int NumJoysticks = SDL_NumJoysticks();
	for ( int idx = 0; idx < NumJoysticks; idx++ ) {
		SDL_Joystick* Joy = State[idx];
		
		// Buttons //
		GamePad[idx].Button = 0;
		for ( int idx2 = 0; idx2 < SDL_JoystickNumButtons(Joy); idx2++ ) {
			GamePad[idx].Button |= SDL_JoystickGetButton( Joy, idx2 ) << idx2;
		}
		
		// Axis //
		for ( int idx2 = 0; idx2 < SDL_JoystickNumAxes(Joy); idx2++ ) {
			GamePad[idx].Axis[idx2] = SDL_JoystickGetAxis( Joy, idx2 ) / 32768.0f;
		}
		
		// Hat //
		if ( SDL_JoystickNumHats(Joy) ) {
			GamePad[idx].Hat = SDL_JoystickGetHat( Joy, 0 );
		}
		else {
			GamePad[idx].Hat = 0;
		}
		
		// DPad (Modified Hat) //
		GamePad[idx].DPad.x = 0.0f;
		GamePad[idx].DPad.y = 0.0f;
		if ( GamePad[idx].Hat & SDL_HAT_LEFT ) {
			GamePad[idx].DPad.x = -1.0f;
		}
		else if ( GamePad[idx].Hat & SDL_HAT_RIGHT ) {
			GamePad[idx].DPad.x = +1.0f;
		}

		if ( GamePad[idx].Hat & SDL_HAT_UP ) {
			GamePad[idx].DPad.y = +1.0f;
		}
		else if ( GamePad[idx].Hat & SDL_HAT_DOWN ) {
			GamePad[idx].DPad.y = -1.0f;
		}			
	}
}
// - ------------------------------------------------------------------------------------------ - //
void PollEvent( void* ) {
	Poll();
}
// - ------------------------------------------------------------------------------------------ - //
st32 Size() {
	return MAX_GAMEPADS;
}
// - ------------------------------------------------------------------------------------------ - //
st32 DevicesConnected() {
	return SDL_NumJoysticks();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Pulse( const int /*Index*/, const int /*Motor*/, const int /*Amount*/ ) {
}
// - ------------------------------------------------------------------------------------------ - //
void Vibrate( const int /*Index*/, const int /*Motor*/, const int /*Amount*/ ) {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Controller Detection - We really don't have much to go on, except button/axis counts //
// - ------------------------------------------------------------------------------------------ - //
bool Is360( int Index ) {
	if ( SDL_JoystickNumButtons(State[Index]) == 12 )
#ifdef USES_WINDOWS
		if ( SDL_JoystickNumAxes(State[Index]) == 5 )
#else // USES_WINDOWS //
		if ( SDL_JoystickNumAxes(State[Index]) == 6 )
#endif // USES_WINDOWS //
			if ( SDL_JoystickNumHats(State[Index]) == 1 )
				if ( SDL_JoystickNumBalls(State[Index]) == 0 )
					return true;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool IsPS4( int Index ) {
	if ( SDL_JoystickNumButtons(State[Index]) == 14 )
		if ( SDL_JoystickNumAxes(State[Index]) == 6 )
			if ( SDL_JoystickNumHats(State[Index]) == 1 )
				if ( SDL_JoystickNumBalls(State[Index]) == 0 )
					return true;
	return false;	
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace SDLInput //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
