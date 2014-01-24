// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_STEAM
// - ------------------------------------------------------------------------------------------ - //
#include "steam/steam_api.h"
#include "Input_Core.h"
#include "Input_Device_Controller_SteamController.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
	extern bool IsSteamRunning;
// - ------------------------------------------------------------------------------------------ - //	
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
namespace Steam {
// - ------------------------------------------------------------------------------------------ - //
bool Connected[MAX_STEAM_CONTROLLERS];
bool OldConnected[MAX_STEAM_CONTROLLERS];
// - ------------------------------------------------------------------------------------------ - //
SteamControllerState_t State[MAX_STEAM_CONTROLLERS];
// - ------------------------------------------------------------------------------------------ - //
GelSteamPad SteamPad[16];
// - ------------------------------------------------------------------------------------------ - //
#include <unistd.h>
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	for ( size_t idx = 0; idx < Size(); idx++ ) {
		Connected[idx] = false;
		OldConnected[idx] = false;
	}

// DIRTY //
#define MAX_PATH PATH_MAX
#define _getcwd getcwd

	char rgchCWD[1024];
	_getcwd( rgchCWD, sizeof( rgchCWD ) );

	char rgchFullPath[1024];
#if defined(_WIN32)
	_snprintf( rgchFullPath, sizeof( rgchFullPath ), "%s\\%s", rgchCWD, "null_controller.vdf" );
#else
	_snprintf( rgchFullPath, sizeof( rgchFullPath ), "%s/%s", rgchCWD, "null_controller.vdf" );
#endif
	SteamController()->Init( rgchFullPath );
// DIRTY //
	
	Gel::Input::Poll.Connect( PollEvent );
}
// - ------------------------------------------------------------------------------------------ - //
void InitEvent( void* ) {
	if ( IsSteamRunning ) {
		Init();
		Poll();
		
		Log( "" );
		Log( "-=- SteamController -- %i Device(s) Connected -=-", DevicesConnected() );
		for ( size_t idx = 0; idx < Size(); idx++ ) {
	        if ( IsConnected(idx) ) {
	        	Log( "%i - Connected", idx );
			}
		}
		Log( "" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void Poll() {
	// Copy connection state //
	for ( size_t idx = 0; idx < MAX_STEAM_CONTROLLERS; idx++ ) {
		OldConnected[idx] = Connected[idx];
	}
	
//	Log(" Steam %x", SteamController() );
	
	// Retrieve Controller State //
	for ( size_t idx = 0; idx < MAX_STEAM_CONTROLLERS; idx++ ) {
//		Log(" TOM %x", SteamController() );
		Connected[idx] = SteamController()->GetControllerState( idx, &(State[idx]) );
//		Log(" TOM %x", SteamController() );
		// Populate SteamPad data //
		SteamPad[idx].LStick = Vector2D( State[idx].sLeftPadX / 32767.0f, State[idx].sLeftPadY / 32767.0f );
		SteamPad[idx].RStick = Vector2D( State[idx].sRightPadX / 32767.0f, State[idx].sRightPadY / 32767.0f );
		SteamPad[idx].Button = State[idx].ulButtons;
	}
}
// - ------------------------------------------------------------------------------------------ - //
void PollEvent( void* ) {
	if ( IsSteamRunning ) {
		Poll();
		if ( HasConnectionChanged() ) {
			for ( size_t idx = 0; idx < Size(); idx++ ) {
				if ( HasConnectionChanged(idx) ) {
					Log( "** Steam Controller %i %s", idx, IsConnected(idx) ? "Connected" : "Disconnected" );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	SteamController()->Shutdown();
}
// - ------------------------------------------------------------------------------------------ - //
void ExitEvent( void* ) {
	if ( IsSteamRunning ) {
		Exit();
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//void LoseFocusEvent( void* ) {
//}
// - ------------------------------------------------------------------------------------------ - //
//void GainFocusEvent( void* ) {
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
size_t Size() {
	return MAX_STEAM_CONTROLLERS;
}
// - ------------------------------------------------------------------------------------------ - //
size_t DevicesConnected() {
	size_t Count = 0;
	for ( size_t idx = 0; idx < MAX_STEAM_CONTROLLERS; idx++ ) {
		if( IsConnected(idx) ) {
			Count++;
		}
	}
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //
bool IsConnected( const int Index ) {
	if ( Index > MAX_STEAM_CONTROLLERS )
		return false;
	return Connected[Index];
}
bool IsConnected() {
	for ( int idx = 0; idx < MAX_STEAM_CONTROLLERS; idx++ ) {
		return_if( IsConnected(idx) );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool HasConnectionChanged( const int Index ) {
	if ( Index > MAX_STEAM_CONTROLLERS )
		return false;
	return OldConnected[Index] != Connected[Index];
}
bool HasConnectionChanged() {
	for ( int idx = 0; idx < MAX_STEAM_CONTROLLERS; idx++ ) {
		return_if( HasConnectionChanged(idx) );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Steam //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STEAM //
// - ------------------------------------------------------------------------------------------ - //
