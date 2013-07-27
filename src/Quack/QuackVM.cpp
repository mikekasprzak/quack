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
	// Initialize VM //
	Log( "-=- Squirrel VM -=-" );
	
	Log( "Creating VM..." );
	vm = sq_open(1024);			// Stack Size //
	sq_setprintfunc_Log( vm );	// Set 'Log' to be the print function //
	sq_pushroottable(vm);
	
	// Load Standard Libraries //
	Log( "Loading System Libraries..." );
//	sqstd_register_iolib( vm );			// No FileIO //
	sqstd_register_bloblib( vm );
	sqstd_register_mathlib( vm );
//	sqstd_register_systemlib( vm );		// No System Time //
	sqstd_register_stringlib( vm );
	
	// Load My Libraries //
	Log( "Loading Quack Libraries..." );
	
	// 
	Log( "Loading Startup File (???.nut)..." );
	
	// Do the Init function //
	Log( "Calling User Init Function..." );
	
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
