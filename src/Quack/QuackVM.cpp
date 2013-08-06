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
void sqext_log( HSQUIRRELVM v ) {
	Log( "! STACK: %i", sq_gettop(v) );	
}
// - ------------------------------------------------------------------------------------------ - //
const char* sqext_gettypename( HSQUIRRELVM v, SQInteger Index ) {
	switch( sq_gettype(v,Index) ) {
		case OT_NULL:
			return "null";
			break;
		case OT_INTEGER:
			return "integer";
			break;
		case OT_FLOAT:
			return "float";
			break;
		case OT_BOOL:
			return "bool";
			break;
		case OT_STRING:
			return "string";
			break;
		case OT_TABLE:
			return "table";
			break;
		case OT_ARRAY:
			return "array";
			break;
		case OT_USERDATA:
			return "userdata";
			break;
		case OT_CLOSURE:
			return "closure (function)";
			break;
		case OT_NATIVECLOSURE:
			return "native closure (C function)";
			break;
		case OT_FUNCPROTO:
			return "?? func proto ??";
			break;
		case OT_OUTER:
			return "?? outer ??";
			break;
		case OT_GENERATOR:
			return "generator";
			break;
		case OT_THREAD:
			return "thread";
			break;
		case OT_USERPOINTER:
			return "userpointer";
			break;
		case OT_CLASS:
			return "class";
			break;
		case OT_INSTANCE:
			return "instance";
			break;
		case OT_WEAKREF:
			return "weak reference";
			break;
	};

	return "invalid type";
}
// - ------------------------------------------------------------------------------------------ - //
// Whether an object existis or not in the root table //
bool sqext_exists( HSQUIRRELVM v, const char* name ) {
	sq_pushroottable(v);							// ST1 - Push the Root Table //

	SQInteger Top = sq_gettop(v);

	sq_pushstring(v,name,-1);						// ST2 - Push a string, the name of the function (-1 is length) //
	sq_get(v,-2);									// ST2 - Pop an element, and lookup the object at the specified index (usually a function) //

	// There should be 1 more element on the stack, otherwise sq_get failed to find the function //
	if ( Top == sq_gettop(v) ) {
		sq_pop(v,1);	// Remove the Root Table //
		return SQFalse;
	}

	sq_pop(v,2);									// ST0 - Remove Root Table and Function //
	
	return SQTrue;
}
// - ------------------------------------------------------------------------------------------ - //
// Call a function (that takes no arguments, such as a compiled source file) //
bool sqext_call( HSQUIRRELVM v, const char* name ) {
	sq_pushroottable(v);							// ST1 - Push the Root Table //

	SQInteger Top = sq_gettop(v);

	sq_pushstring(v,name,-1);						// ST2 - Push a string, the name of the function (-1 is length) //
	sq_get(v,-2);									// ST2 - Pop an element, and lookup the object at the specified index (usually a function) //

	// There should be 1 more element on the stack, otherwise sq_get failed to find the function //
	if ( Top == sq_gettop(v) ) {
		sq_pop(v,1);	// Remove the Root Table //
		return SQFalse;
	}

	sq_pushroottable(v);							// ST3 - first argument: this //
	// Push Other Arguments Here //
	
	sq_call(v,1,SQFalse,SQTrue);					// ST2 - VM, Arg Count (including this), Push RetVal on Stack, On Error Call Handlers //
	
	sq_pop(v,2);									// ST0 - Remove Root Table and Function //
	
	return SQTrue;
}
// - ------------------------------------------------------------------------------------------ - //
bool sqext_load_nut( HSQUIRRELVM v, const char* NutFile ) {
	Log( "Loading Script File (%s)...", NutFile );

	const char* NutFileResult = Gel::Search(NutFile);
	GelAssetPool::UID Nut = Gel::AssetPool.Load(NutFileResult);
		
	GelAsset& MyAsset = Gel::AssetPool[Nut];

	if ( !MyAsset.IsBad() ) {
		// Compile and push a closure on to the stack //
		if ( SQ_SUCCEEDED( sq_compilebuffer(v, MyAsset.Get(), MyAsset.GetSize(), NutFileResult, true) ) ) {
			//sq_push(v,-2); // Grab the root table (because it's typically already pushed) //
			sq_pushroottable(v);	// Push the root table (first argument) //
			if ( SQ_SUCCEEDED( sq_call(v,1,false,SQTrue) ) ) {
				sq_remove(v,-1); 	// Remove the closure
				return true;
			}
			sq_pop(v,1);			// Pop the root table //
		}
	}
	
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

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

	atexit( QuackVMExit );
	
	// Load Standard Libraries //
	Log( "Loading System Libraries..." );
	sq_pushroottable( vm );
	//Log("* IO lib"); sqstd_register_iolib( vm );			// FileIO (dofile, loadfile, writeclosuretofile)
	//Log("* Blob lib"); sqstd_register_bloblib( vm );		// Binary File Blobs (unnecessary?)
	Log("* Math lib"); sqstd_register_mathlib( vm );		// Math (abs, fabs, sin, cos, log, rand, srand, sqrt, PI, ...)
	//Log("* System lib"); sqstd_register_systemlib( vm );	// System (clock [time], getenv, remove [file], system [cmd], ...)
	Log("* String lib"); sqstd_register_stringlib( vm );	// String (format [sprintf], regexp, l/r/strip, split [tokens])
	sq_pop( vm, 1 );
	
	// Load My Libraries //
	Log( "Loading Quack Libraries..." );
	Log("* qkLib"); sqext_load_nut( vm, "qkLib.nut" );
	//Log("* qkJson"); register_qkJson( vm );
	
	// Load the startup file //
	const char* StartupFile = "main.nut";
	Log( "Loading Startup File (%s)...", StartupFile );
	sqext_load_nut( vm, StartupFile );

	// Do the Init function //
	if ( sqext_exists( vm, "Init" ) ) {
		Log( "Calling user Init() function..." );
		sqext_call( vm, "Init" );
		// TODO: Set mode to Engine/GameLoop
	}
	else if ( sqext_exists( vm, "main" ) ) {
		Log( "Calling main() function..." );
		sqext_call( vm, "main" );
		// TODO: Set mode to oneshot
	}
	else {
		Log( "! ERROR: No startup function found (Init or main). Aborting..." );
	}
			
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
void QuackVMExit() {
	sq_close( vm );		// Shutdown VM //
}
// - ------------------------------------------------------------------------------------------ - //
