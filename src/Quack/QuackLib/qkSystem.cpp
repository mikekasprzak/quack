// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Asset/Asset.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <App.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// We needed these because getting access to the default delegates isn't exposed to Squirrel. //
// - ------------------------------------------------------------------------------------------ - //
// NOTE: The Float and Integer delegates are the same //
SQInteger sqext_getfloatdelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_FLOAT );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getstringdelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_STRING );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_gettabledelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_TABLE );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getarraydelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_ARRAY );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: The Closure and NativeClosure delegates are the same //
SQInteger sqext_getclosuredelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_CLOSURE );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getgeneratordelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_GENERATOR );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getthreaddelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_THREAD );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getclassdelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_CLASS );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getinstancedelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_INSTANCE );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger sqext_getweakrefdelegate( HSQUIRRELVM v ) {
	sq_getdefaultdelegate( v, OT_WEAKREF );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This doesn't seem to work, yet it sort-of does. Returned refcount is incorrect. //
SQInteger sqext_getrefcount( HSQUIRRELVM v ) {
	HSQOBJECT obj;
	sq_resetobject(&obj);	// Initialize the Handle //
		
//	Log( "type: %s", sqext_gettypename(sq_gettype(v,2)) );

//	SQObjectType Tag;
//	sq_gettypetag(v,2,(void**)&Tag);
//	Log( "type: %s", sqext_gettypename(Tag) );

	sq_getstackobj(v,2,&obj);
	sq_addref(v,&obj);
	
//	sq_getobjtypetag( &obj, (void**)&Tag );
//	Log( "Type: %s", sqext_gettypename(obj._type) );
	
	SQUnsignedInteger Refs = sq_getrefcount(v,&obj);
//	Log( "Refs: %i", Refs );
	
	sq_pushinteger(v, Refs);
	
	sq_release(v,&obj);

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Check if the project is built in Development Mode (Desktop OS's Only... Please) //
SQInteger qkIsDevMode( HSQUIRRELVM v ) {
	#ifdef PRODUCT_DEV_MODE
		sq_pushbool( v, SQTrue );
	#else // !PRODUCT_DEV_MODE //
		sq_pushbool( v, SQFalse );
	#endif // PRODUCT_DEV_MODE //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Set the flag that forces exit //
SQInteger qkRequestExit( HSQUIRRELVM v ) {
	App::Exit = true;

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// Dummy //
SQInteger qkOnKey( HSQUIRRELVM v ) {
	sq_pushbool( v, Gel::KeyESC ? SQTrue : SQFalse );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkGetTop( HSQUIRRELVM v ) {
	sq_pushinteger( v, sq_gettop(v) );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Queue up a file for the Asset Pool //
SQInteger qkRequireFile( HSQUIRRELVM v ) {
	const char* File;
	if( SQ_FAILED( sq_getstring(v,2,&File) ) ) {
		return sq_throwerror(v,_SC("invalid param"));
	}
	
	// * * * //
	// NOTE: Old Suggestions //
	// TODO: Support wildcards (*.nut) (**.nut for all recursively) //
	// TODO: Track dependencies (which files requested a file, which files a file requseted).
	//       Note in the logs if a refcount ever becomes zero. //
	// * * * //
	
	Log( "+ Requirement Found: %s", File );
	
	SQBool SearchSuccess = SQFalse;
	const char* Requirement = Gel::Search( File );
		
	if ( Requirement ) {
		GelAssetPool::UID ReqUID = Gel::AssetPool.Find(Requirement);
		if ( !ReqUID ) {
			// Asset was not found in the Pool, lets load it //
			ReqUID = Gel::AssetPool.Load(Requirement);
			GelAsset& MyAsset = Gel::AssetPool[ReqUID];
			
			// Compile //
			if ( !MyAsset.IsBad() ) {
				MyAsset.SubscribeToChanges( sqext_reload_subscriber, ReqUID );
				
				sqext_compile_nut( v, MyAsset.Get(), MyAsset.GetSize(), Requirement );
			}
		}		
		else {
			Log( "** Requirement already loaded (%s)", Requirement );
		}
			
//		Log( "> %s (%s)", Requirement, File );
		
		SearchSuccess = SQTrue;
	}
	
	sq_pushbool( v, SearchSuccess );

	Log( "- Done with Requirement (%s).", File );
	
	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkSystem_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qkIsDevMode,1,NULL),
	_DECL_FUNC(qkRequestExit,1,NULL),
	_DECL_FUNC(qkRequireFile,2,_SC(".s")),
	_DECL_FUNC(qkOnKey,1,NULL),
	_DECL_FUNC(qkGetTop,1,NULL),
	
	_DECL_FUNC(sqext_getfloatdelegate,1,NULL),
	_DECL_FUNC(sqext_getstringdelegate,1,NULL),
	_DECL_FUNC(sqext_gettabledelegate,1,NULL),
	_DECL_FUNC(sqext_getarraydelegate,1,NULL),
	_DECL_FUNC(sqext_getclosuredelegate,1,NULL),
	_DECL_FUNC(sqext_getgeneratordelegate,1,NULL),
	_DECL_FUNC(sqext_getthreaddelegate,1,NULL),
	_DECL_FUNC(sqext_getclassdelegate,1,NULL),
	_DECL_FUNC(sqext_getinstancedelegate,1,NULL),
	_DECL_FUNC(sqext_getweakrefdelegate,1,NULL),
	
	_DECL_FUNC(sqext_getrefcount,2,NULL),
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkSystem(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* qklib_funcs = qkSystem_funcs;
	while(qklib_funcs[i].name!=0) {
		sq_pushstring(v,qklib_funcs[i].name,-1);
		sq_newclosure(v,qklib_funcs[i].f,0);
		sq_setparamscheck(v,qklib_funcs[i].nparamscheck,qklib_funcs[i].typemask);
		sq_setnativeclosurename(v,-1,qklib_funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
