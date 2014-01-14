// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a ".Draw" function.
// TODO: Add a ".tostring" function. Returns "[QkSkel:content/Cube.pod]"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Skel/Skel.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Constructor argument (bool) that enables/disables Smoothing. //
_FUNC_POOL_CONSTRUCTOR(GelSkelPool,qk_skel_constructor,SkelPool);
_FUNC_LOAD_POOL(qkSkelLoad,"QkSkel",6,"qk_skel_constructor");

_FUNC_TYPEOF(GelSkelPool::UID,qk_skel_typeof,"QkSkel",6);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkSkel_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_skel_constructor,-1,NULL),
	_DECL_FUNC(qk_skel_typeof,1,NULL),

	_DECL_FUNC(qkSkelLoad,-1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkSkel(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkSkel_funcs;
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
		_ADD_CLASS_START(GelSkelPool::UID,"QkSkel",QK_TAG_SKEL);
		_CLASS_ADDFUNC(qk_skel_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_skel_typeof,_typeof);
//		_CLASS_ADDFUNC(qk_skel_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_skel_cloned,_cloned);
		_ADD_CLASS_END(GelSkelPool::UID);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
