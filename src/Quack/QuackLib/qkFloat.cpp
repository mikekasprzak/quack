// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
#include "QuackLib.h"
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_float_toscalar( HSQUIRRELVM v ) {
	sq_pushroottable(v);
	sq_pushstring(v,"scalar",6);			/* +1 */
	sq_get(v,-2);							/* =0 */
	sq_createinstance(v,-1);				/* +1 */
	/* NOTE: Contructor not called! */

	float Me;
	sq_getfloat(v,1,&Me);
	
	float* Ret;
	sq_getinstanceup(v,-1,(void**)&Ret,0);

	*Ret = Me;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkFloat_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_float_toscalar,1,NULL),	

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkFloat(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkFloat_funcs;
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
		// NOTE: The Float and Integer delegates are the same //
		sq_getdefaultdelegate( v, OT_FLOAT );	// +1 //
		int CPos = sq_gettop(v);
		
		_CLASS_ADDFUNC(qk_float_toscalar,toscalar);
		
		sq_poptop(v);							// -1 //
	}

	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
