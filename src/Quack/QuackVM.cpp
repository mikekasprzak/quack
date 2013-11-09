// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Asset/Asset.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
#include "QuackLib/qkSystem.h"
#include "QuackLib/qkScreen.h"
#include "QuackLib/qkInput.h"
#include "QuackLib/qkColor.h"
#include "QuackLib/qkVector.h"
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
HSQUIRRELVM vm;
// - ------------------------------------------------------------------------------------------ - //
void QuackLog() {
	Log( "-=- Squirrel VM -=-" );
	Log( SQUIRREL_VERSION );
	Log( SQUIRREL_COPYRIGHT );
		
	#ifdef _SQ64
	Log( "* _SQ64 Enabled." );
	#endif // _SQ64 //
	
	#ifdef SQUSEDOUBLE
	Log( "* SQUSEDOUBLE Enabled." );
	#endif // SQUSEDOUBLE //
	
	#ifdef SQUNICODE
	Log( "* SQUNICODE Enabled." );
	#endif // SQUNICODE //

	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void QuackVMInit() {
	QuackLog();
	
	// Initialize VM //
	Log( "Creating VM..." );
	vm = sq_open( 32 );		// Start VM (Stack Size) //
	sq_setprintfunc_Log( vm );	// Set 'Log' to be the print function //

	atexit( QuackVMExit );
	Log( "VM Created." );
	Log( "" );
	
	// Load Standard Libraries //
	Log( "Loading System Libraries..." );
	sq_pushroottable( vm );
		//Log("* sqIO"); sqstd_register_iolib( vm );			// FileIO (dofile, loadfile, writeclosuretofile)
		//Log("* sqBlob"); sqstd_register_bloblib( vm );		// Binary File Blobs (unnecessary?)
		Log("* sqMath"); sqstd_register_mathlib( vm );			// Math (abs, fabs, sin, cos, log, rand, srand, sqrt, PI, ...)
		//Log("* sqSystem"); sqstd_register_systemlib( vm );	// System (clock [time], getenv, remove [file], system [cmd], ...)
		Log("* sqString"); sqstd_register_stringlib( vm );		// String (format [sprintf], regexp, l/r/strip, split [tokens])
	sq_pop( vm, 1 );
	Log( "" );
	
	// Load My Libraries //
	Log( "Loading Quack Libraries..." );
	sq_pushroottable( vm );
		Log("* qkSystem"); register_qkSystem( vm );
		Log("* qkLib (nut)"); sqext_load_nut( vm, "qkLib.nut" );
		Log("* qkVector (nut)"); sqext_load_nut( vm, "qkVector.nut" );
		Log("* qkScreen"); register_qkScreen( vm );
		Log("* qkInput"); register_qkInput( vm );
		//Log("* qkJson"); register_qkJson( vm );
		Log("* qkColor"); register_qkColor( vm );
		Log("* qkVector"); register_qkVector( vm );
//		Log("* qkMatrix"); register_qkMatrix( vm );
	sq_pop( vm, 1 );
	Log( "" );
	
	// Load the startup file //
	const char* StartupFile = "main.nut";
	Log( "Loading Startup File (%s)...", StartupFile );
	sqext_load_nut( vm, StartupFile );
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void QuackVMExit() {
	sq_close( vm );		// Shutdown VM //
}
// - ------------------------------------------------------------------------------------------ - //
	
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallSetup() {
	// Do the Init function //
	if ( sqext_exists( vm, "main" ) ) {
		Log( "Calling main() function..." );
		sqext_call( vm, "main" );
		App::SetMode( App::AM_MAIN );
	}
	else if ( sqext_exists( vm, "Init" ) || sqext_exists( vm, "Setup" ) || sqext_exists( vm, "Step" ) || sqext_exists( vm, "Draw" ) ) {
		// Check for Step and Draw //
		if ( !sqext_exists( vm, "Step" ) ) {
			Log( "! ERROR: GameLoop Mode detected, but no Step(). Aborting..." );
			App::SetMode( App::AM_ERROR );
			return false;
		}
		if ( !sqext_exists( vm, "Draw" ) ) {
			Log( "! ERROR: GameLoop Mode detected, but no Draw(). Aborting..." );
			App::SetMode( App::AM_ERROR );
			return false;
		}

		App::SetMode( App::AM_GAMELOOP );

		if ( sqext_exists( vm, "Setup" ) ) {
			Log( "Calling user Setup() function..." );
			sqext_call( vm, "Setup" );
		}
		else if ( sqext_exists( vm, "_DefaultSetup" ) ) {
			Log( "Calling _DefaultSetup() function..." );
			sqext_call( vm, "_DefaultSetup" );
		}
	}
	else {
		Log( "! ERROR: No startup function found (Init, Setup or main). Aborting..." );
		App::SetMode( App::AM_ERROR );
		return false;
	}
	Log( "" );
	
	return true;			
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallInit() {
	if ( sqext_exists( vm, "Init" ) ) {
		return sqext_call( vm, "Init" );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallExit() {
	if ( sqext_exists( vm, "Exit" ) ) {
		return sqext_call( vm, "Exit" );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallStep() {
	if ( sqext_exists( vm, "Step" ) ) {
		return sqext_call( vm, "Step" );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallDraw() {
	if ( sqext_exists( vm, "Draw" ) ) {
		return sqext_call( vm, "Draw" );
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallGainFocus() {
	return sqext_call( vm, "GainFocus" );
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallLoseFocus() {
	return sqext_call( vm, "LoseFocus" );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallRequestExit() {
	return sqext_call( vm, "RequestExit" );
}
// - ------------------------------------------------------------------------------------------ - //
