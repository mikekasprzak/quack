// - ------------------------------------------------------------------------------------------ - //
#include <stdarg.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Asset/Asset.h>
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
#include "sqext.h"
// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
#include "QuackLib/QuackLib.h"
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
HSQUIRRELVM vm;
bool vmError;
// - ------------------------------------------------------------------------------------------ - //
void QuackVMPrintFunc( HSQUIRRELVM v, const SQChar *s, ... ) {
	va_list arglist; 
	va_start(arglist, s); 
	vLogAlways(s,arglist);
	va_end(arglist);
	LogFlush();
} 
// - ------------------------------------------------------------------------------------------ - //
void QuackVMErrorFunc( HSQUIRRELVM v, const SQChar *s, ... ) {
	va_list arglist; 
	va_start(arglist, s); 
	_vLogAlways(s,arglist);
	va_end(arglist);
	LogFlush();
	vmError = true;
}
// - ------------------------------------------------------------------------------------------ - //
void QuackVMClearError() {
	vmError = false;;
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMGetError() {
	return vmError;
}
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
	// Set the Functions for Printed output and Errors //
	sq_setprintfunc( vm, QuackVMPrintFunc, QuackVMErrorFunc );
	// Use the above functions for Squirrel Error Printing //
	sqstd_seterrorhandlers(vm);
	
	QuackVMClearError();	// Clear our error status (because no files have compiled) //

	atexit( QuackVMExit );
	Log( "VM Created." );
	Log( "" );
	
	// Load Standard Libraries //
	Log( "Loading System Libraries..." );
	sq_pushroottable( vm );	// +1 //
		//Log("* sqIO"); sqstd_register_iolib( vm );			// FileIO (dofile, loadfile, writeclosuretofile)
		//Log("* sqBlob"); sqstd_register_bloblib( vm );		// Binary File Blobs (unnecessary?)
		Log("* sqMath"); sqstd_register_mathlib( vm );			// Math (abs, fabs, sin, cos, log, rand, srand, sqrt, PI, ...)
		//Log("* sqSystem"); sqstd_register_systemlib( vm );	// System (clock [time], getenv, remove [file], system [cmd], ...)
		Log("* sqString"); sqstd_register_stringlib( vm );		// String (format [sprintf], regexp, l/r/strip, split [tokens])
	sq_pop( vm, 1 );		// -1 //
	Log( "" );
	
	// Load My Libraries //
	Log( "Loading Quack Libraries..." );
	sq_pushroottable( vm );	// +1 //
		Log("* qkSystem"); register_qkSystem( vm );
		Log("* qkLib (nut)"); sqext_load_nut( vm, "qkLib.nut" );
		Log("* qkScreen"); register_qkScreen( vm );
		Log("* qkBlending"); register_qkBlending( vm );
		Log("* qkDepth"); register_qkDepth( vm );
		Log("* qkDraw"); register_qkDraw( vm );
		Log("* qkTexture"); register_qkTexture( vm );
		Log("* qkFont"); register_qkFont( vm );
		Log("* qkModel"); register_qkModel( vm );
		Log("* qkInput"); register_qkInput( vm );
		Log("* qkInput (nut)"); sqext_load_nut( vm, "qkInput.nut" );
		Log("* qkColor"); register_qkColor( vm );
		Log("* qkVector"); register_qkVector( vm );
		Log("* qkVector (nut)"); sqext_load_nut( vm, "qkVector.nut" );
		Log("* qkMatrix"); register_qkMatrix( vm );
		Log("* qkFloat"); register_qkFloat( vm );
		Log("* qkGrid"); register_qkGrid( vm );
	sq_pop( vm, 1 );		// -1 //
	Log( "" );
	
	// Load the setup file (if available) //
	const char* SetupFile = "setup.nut";
	Log( "Loading Setup File (%s)...", SetupFile );
	sqext_load_nut( vm, SetupFile );
	Log( "" );
	
	// TODO: --nosetup command-line argument
	if ( sqext_exists( vm, "Setup" ) ) {
		Log( "Calling user Setup() function..." );
		sqext_call( vm, "Setup" );
	}
	else if ( sqext_exists( vm, "_DefaultSetup" ) ) {
		Log( "Calling _DefaultSetup() function..." );
		sqext_call( vm, "_DefaultSetup" );
	}
			
	// Load the startup file //
	const char* StartupFile = "main.nut";
	Log( "Loading Startup File (%s)...", StartupFile );
	sqext_load_nut( vm, StartupFile );
	Log( "" );
	
	QuackVMCallSetup();
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
	else if ( sqext_exists( vm, "Init" ) || sqext_exists( vm, "Step" ) || sqext_exists( vm, "Draw" ) ) {
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
	}
	else {
		Log( "! ERROR: No startup function found (Init or main). Aborting..." );
		App::SetMode( App::AM_ERROR );
		return false;
	}
	Log( "" );

//	//glEnable( GL_LINE_SMOOTH );
//	glLineWidth( 1 );
//	//glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

	return true;			
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallInit() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "Init" ) ) {
			return sqext_call( vm, "Init" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallExit() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "Exit" ) ) {
			return sqext_call( vm, "Exit" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallStep() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "Step" ) ) {
			return sqext_call( vm, "Step" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallDraw() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "Draw" ) ) {
			return sqext_call( vm, "Draw" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallGainFocus() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "GainFocus" ) ) {
			return sqext_call( vm, "GainFocus" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallLoseFocus() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "LoseFocus" ) ) {
			return sqext_call( vm, "LoseFocus" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool QuackVMCallRequestExit() {
	if ( !vmError ) {
		if ( sqext_exists( vm, "RequestExit" ) ) {
			return sqext_call( vm, "RequestExit" );
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
