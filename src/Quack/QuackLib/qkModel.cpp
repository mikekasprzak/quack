// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a ".Draw" function.
// TODO: Add a ".tostring" function. Returns "[QkModel:content/Cube.pod]"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Model/Model.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Constructor argument (bool) that enables/disables Smoothing. //
_FUNC_POOL_CONSTRUCTOR(GelModelPool,qk_model_constructor,ModelPool);
_FUNC_LOAD_POOL(qkModelLoad,"QkModel",7,"qk_model_constructor");

_FUNC_TYPEOF(GelModelPool::UID,qk_model_typeof,"QkModel",7);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkModel_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_model_constructor,-1,NULL),
	_DECL_FUNC(qk_model_typeof,1,NULL),

	_DECL_FUNC(qkModelLoad,-1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkModel(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkModel_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	int Root = sq_gettop(v); // root table pos //
	{
		_ADD_CLASS_START(GelModelPool::UID,"QkModel",QK_TAG_MODEL);
		_CLASS_ADDFUNC(qk_model_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_model_typeof,_typeof);
//		_CLASS_ADDFUNC(qk_model_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_model_cloned,_cloned);
		_ADD_CLASS_END(GelModelPool::UID);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
