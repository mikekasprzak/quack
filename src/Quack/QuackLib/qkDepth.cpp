// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthEnableTest( HSQUIRRELVM vm ) {
	gelDepthEnableTest();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthDisableTest( HSQUIRRELVM vm ) {
	gelDepthDisableTest();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthEnableWrite( HSQUIRRELVM vm ) {
	gelDepthEnableWrite();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthDisableWrite( HSQUIRRELVM vm ) {
	gelDepthDisableWrite();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthEnable( HSQUIRRELVM vm ) {
	gelDepthEnable();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthDisable( HSQUIRRELVM vm ) {
	gelDepthDisable();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDepthClear( HSQUIRRELVM vm ) {
	gelDepthClear();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkDepth_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qkDepthEnableTest,1,NULL),
	_DECL_FUNC(qkDepthDisableTest,1,NULL),
	_DECL_FUNC(qkDepthEnableWrite,1,NULL),
	_DECL_FUNC(qkDepthDisableWrite,1,NULL),

	_DECL_FUNC(qkDepthEnable,1,NULL),	// Internally: Both //
	_DECL_FUNC(qkDepthDisable,1,NULL),	// Internally: Both //
	
	_DECL_FUNC(qkDepthClear,1,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkDepth(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkDepth_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
