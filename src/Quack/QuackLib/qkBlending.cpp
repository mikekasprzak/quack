// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkBlendingEnablePremultipliedAlpha( HSQUIRRELVM vm ) {
	gelBlendingEnablePremultipliedAlpha();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkBlendingEnableSourceAlpha( HSQUIRRELVM vm ) {
	gelBlendingEnableSourceAlpha();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkBlendingEnableAddative( HSQUIRRELVM vm ) {
	gelBlendingEnableAddative();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkBlendingEnableModulation( HSQUIRRELVM vm ) {
	gelBlendingEnableModulation();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkBlendingEnable( HSQUIRRELVM vm ) {
	gelBlendingEnable();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkBlendingDisable( HSQUIRRELVM vm ) {
	gelBlendingDisable();
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkBlending_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qkBlendingEnablePremultipliedAlpha,1,NULL),
	_DECL_FUNC(qkBlendingEnableSourceAlpha,1,NULL),
	_DECL_FUNC(qkBlendingEnableAddative,1,NULL),
	_DECL_FUNC(qkBlendingEnableModulation,1,NULL),

	_DECL_FUNC(qkBlendingEnable,1,NULL), // Internally: Premultiplied Alpha //
	_DECL_FUNC(qkBlendingDisable,1,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkBlending(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkBlending_funcs;
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
