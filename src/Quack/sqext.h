// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_SQEXT_H__
#define __GEL_WTF_SQEXT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Asset/Asset.h>
// - ------------------------------------------------------------------------------------------ - //
// The function we use to subscribe to AssetPool changes //
void sqext_reload_subscriber( const st UserData );
// - ------------------------------------------------------------------------------------------ - //
inline SQBool sqext_compile_nut( HSQUIRRELVM v, const char* Text, const st TextSize, const char* Name = "?" ) {
	VVLog( "+ Compiling Script File (%s)...", Name );

	// Compile and push a closure on to the stack //
	if ( SQ_SUCCEEDED( sq_compilebuffer(v, Text, TextSize, Name, true) ) ) {
		VVVLog( "* Executing Script File (%s)...", Name );
		sq_pushroottable(v);	// Push the root table (first argument) //
		if ( SQ_SUCCEEDED( sq_call(v,1,false,SQTrue) ) ) {
			sq_remove(v,-1); 	// Remove the closure
			VVLog( "- Script File Compiled and Executed successfully (%s).", Name );
			return SQTrue;
		}
		sq_pop(v,1);			// Pop the root table //
	}
	
	VVLog( "- Error using Script File (%s).", Name );
	
	return SQFalse;
}
// - ------------------------------------------------------------------------------------------ - //
inline SQBool sqext_load_nut( HSQUIRRELVM v, const char* NutFile ) {
	VLog( "+ Loading Script File (%s)...", NutFile );

	const char* NutFileResult = Gel::Search(NutFile);
	VVVLog( "* Full Name: %s", NutFileResult );
	GelAssetPool::UID Nut = Gel::AssetPool.Load(NutFileResult);
		
	GelAsset& MyAsset = Gel::AssetPool[Nut];
	VVVLog( "* NUT: %i", Nut );

	if ( !MyAsset.IsBad() ) {
		MyAsset.SubscribeToChanges( sqext_reload_subscriber, Nut );
		
		return_if_VLog( 
			sqext_compile_nut( v, MyAsset.Get(), MyAsset.GetSize(), NutFileResult ), 
			"- Script File Loaded Successfully (%s).", NutFile 
		);
	}
	
	VLog( "- Unable to load Script File (%s).", NutFile );
	
	return SQFalse;
}
//inline const char* sqext_gettypename( HSQUIRRELVM v, SQInteger Index ) {
//	switch( sq_gettype(v,Index) ) {
inline const char* sqext_gettypename( SQInteger Index ) {
	switch( Index ) {
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
inline void sqext_stackdump( HSQUIRRELVM v ) {
	SQInteger Top = sq_gettop(v);
	
	Log("Stack Dump (%i):", Top);
	for ( int idx = Top; idx > 0; --idx ) {
		const char* ToString;
		sq_tostring(v,idx); 				// +1 //
		sq_getstring(v,-1,&ToString);
		sq_poptop(v);						// -1 //
		const char* TypeOf;
		sq_typeof(v,idx);					// +1 //
		sq_getstring(v,-1,&TypeOf);
		sq_poptop(v);						// -1 //
		Log( "%i - [size: %04i] %s: %s", idx, sq_getsize(v,idx), TypeOf, ToString );
	}
	Log("End of Stack Dump (%i).", sq_gettop(v));
}
// - ------------------------------------------------------------------------------------------ - //
// Whether an object exists or not in the root table //
inline bool sqext_exists( HSQUIRRELVM v, const char* name ) {
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
inline bool sqext_call( HSQUIRRELVM v, const char* name ) {
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
inline void sqslot_bool(HSQUIRRELVM vm, const char* name, SQBool value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushbool(vm,value);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
inline void sqslot_int(HSQUIRRELVM vm, const char* name, SQInteger value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushinteger(vm,value);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
inline void sqslot_float(HSQUIRRELVM vm, const char* name, SQFloat value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushfloat(vm,value);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
inline void sqslot_string(HSQUIRRELVM vm, const char* name, const char* value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushstring(vm,value,-1);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_SQEXT_H__ //
// - ------------------------------------------------------------------------------------------ - //
