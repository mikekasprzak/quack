// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
HSQUIRRELVM vm;
// - ------------------------------------------------------------------------------------------ - //
void QuackVMInit() {
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
	
	// Initialize VM //
	Log( "Creating VM..." );
	vm = sq_open( 1024 );		// Start VM (Stack Size) //
	sq_setprintfunc_Log( vm );	// Set 'Log' to be the print function //
	sq_pushroottable( vm );		// Push the Root Table //

	atexit( QuackVMExit );
	
	// Load Standard Libraries //
	Log( "Loading System Libraries..." );
//	Log("* IO lib"); sqstd_register_iolib( vm );			// FileIO (dofile, loadfile, writeclosuretofile)
//	Log("* Blob lib"); sqstd_register_bloblib( vm );		// Binary File Blobs (unnecessary?)
	Log("* Math lib"); sqstd_register_mathlib( vm );		// Math (abs, fabs, sin, cos, log, rand, srand, sqrt, PI, ...)
//	Log("* System lib"); sqstd_register_systemlib( vm );	// System (clock [time], getenv, remove [file], system [cmd], ...)
	Log("* String lib"); sqstd_register_stringlib( vm );	// String (format [sprintf], regexp, l/r/strip, split [tokens])
	
	// Load My Libraries //
	Log( "Loading Quack Libraries..." );
	//Log("* qkJson"); register_qkJson( vm );
	
	// Load the startup file //
	Log( "Loading Startup File (???.nut)..." );
	
	// Do the Init function //
	Log( "Calling User Init Function..." );
	
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void QuackVMExit() {
	sq_pop( vm, 1 ); 	// Pop the Root Table //
	sq_close( vm );		// Shutdown VM //
}
// - ------------------------------------------------------------------------------------------ - //
