// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QuackVM.h"
#include <Asset/Asset.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
HSQUIRRELVM vm;
// - ------------------------------------------------------------------------------------------ - //
// GelScript will be the primary Script type. If I ever add Lua, call it GelLuaScript.
// - ------------------------------------------------------------------------------------------ - //
class GelScript {
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
class GelScriptPool {
	std::vector<GelScript> Script;
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
GelScriptPool ScriptPool;
// - ------------------------------------------------------------------------------------------ - //
void CallSqFunction( HSQUIRRELVM vm, const char* fname ) {
	sq_pushroottable(vm);
	
	sq_pushstring(vm,fname,-1);
	sq_get(vm,-2);
	sq_pushroottable(vm);			// this //
	// Push Other Arguments Here //
	
	sq_call(vm,1,SQFalse,SQFalse);	// VM, Arg Count (including this), Push RetVal on Stack, On Error Call Handlers //
	
	sq_pop(vm,2);					// Root Table and Function //
}
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
	//Log("* IO lib"); sqstd_register_iolib( vm );			// FileIO (dofile, loadfile, writeclosuretofile)
	//Log("* Blob lib"); sqstd_register_bloblib( vm );		// Binary File Blobs (unnecessary?)
	Log("* Math lib"); sqstd_register_mathlib( vm );		// Math (abs, fabs, sin, cos, log, rand, srand, sqrt, PI, ...)
	//Log("* System lib"); sqstd_register_systemlib( vm );	// System (clock [time], getenv, remove [file], system [cmd], ...)
	Log("* String lib"); sqstd_register_stringlib( vm );	// String (format [sprintf], regexp, l/r/strip, split [tokens])
	
	// Load My Libraries //
	Log( "Loading Quack Libraries..." );
	//Log("* qkJson"); register_qkJson( vm );
	
	// Load the startup file //
	const char* StartupFile = "main.nut";
	Log( "Loading Startup File (%s)...", StartupFile );
	const char* StartupFileResult = Gel::Search(StartupFile);
	GelAssetPool::UID MainNut = Gel::AssetPool.Load(StartupFileResult);
	if ( !Gel::AssetPool[MainNut].IsBad() ) {
		if ( SQ_SUCCEEDED( sq_compilebuffer(vm, Gel::AssetPool[MainNut].Get(), Gel::AssetPool[MainNut].GetSize(), StartupFileResult, true) ) ) {
			sq_push(vm,-2);
			if ( SQ_SUCCEEDED( sq_call(vm,1,false,SQTrue) ) ) {
				Log( "Finished Running Script." );
			}
			sq_pop(vm,1); //removes the closure
		}
	}
	else {
		Log( "! ERROR! %s not found! No program to start!", StartupFile );
		//TODO: Do Shutdown //
	}

	{
		// Do the Init function //
		Log( "Calling User Init Function..." );
		CallSqFunction( vm, "Init" );
	}
			
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void QuackVMExit() {
	sq_pop( vm, 1 ); 	// Pop the Root Table //
	sq_close( vm );		// Shutdown VM //
}
// - ------------------------------------------------------------------------------------------ - //
