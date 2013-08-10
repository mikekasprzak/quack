// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
#include <App.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Check if the project is built in Development Mode (Desktop OS's Only) //
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
// Queue up a file for the Asset Pool //
SQInteger qkRequireFile( HSQUIRRELVM v ) {
	const char* File;
	if( SQ_FAILED( sq_getstring(v,2,&File) ) ) {
		return sq_throwerror(v,_SC("invalid param"));
	}
	
	Log( "> %s", File );
	
	bool Success = true;
	
	sq_pushbool( v, Success ? SQTrue : SQFalse );
	
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
