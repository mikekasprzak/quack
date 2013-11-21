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
SQInteger qk_float_len( HSQUIRRELVM v ) {
	sq_pushinteger( v, 1 );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_float_flipx( HSQUIRRELVM v ) {
	float Me;
	sq_getfloat(v,1,&Me);
	sq_pushfloat( v, -Me );
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_float_xaxis( HSQUIRRELVM v ) {
	float Me;
	sq_getfloat(v,1,&Me);
	sq_pushfloat( v, Me );
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
	_DECL_FUNC(qk_float_len,0,NULL),
	_DECL_FUNC(qk_float_flipx,1,NULL),
	_DECL_FUNC(qk_float_xaxis,1,NULL),

//	_DECL_FUNC(qk_scalar_normal,1,NULL),
//	_DECL_FUNC(qk_scalar_normalize,1,NULL),
//	_DECL_FUNC(qk_scalar_normalizeret,1,NULL),
//	_DECL_FUNC(qk_scalar_magnitude,1,NULL),
//	_DECL_FUNC(qk_scalar_magnitudesquared,1,NULL),
//	_DECL_FUNC(qk_scalar_manhattan,1,NULL),
//	_DECL_FUNC(qk_scalar_mix,3,NULL),
//	_DECL_FUNC(qk_scalar_tofloat,1,NULL),
//	_DECL_FUNC(qk_scalar_tovec2,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_tohvec2,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_toivec2,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_tovec3,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_tohvec3,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_toivec3,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_tovec4,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_tohvec4,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_toivec4,1,NULL),	// + //
//	_DECL_FUNC(qk_scalar_tomat2,1,NULL),
//	_DECL_FUNC(qk_scalar_tomat3,1,NULL),
//	_DECL_FUNC(qk_scalar_tomat4,1,NULL),
	
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
		_CLASS_ADDFUNC_STATIC(qk_float_len,len);
		_CLASS_ADDFUNC(qk_float_flipx,flipx);
		_CLASS_ADDFUNC(qk_float_xaxis,xaxis);

//		_CLASS_ADDFUNC(qk_float_normal,normal);
//		_CLASS_ADDFUNC(qk_float_normalize,normalize);
//		_CLASS_ADDFUNC(qk_float_normalizeret,normalizeret);
//		_CLASS_ADDFUNC(qk_float_magnitude,magnitude);
//		_CLASS_ADDFUNC(qk_float_magnitudesquared,magnitudesquared);
//		_CLASS_ADDFUNC(qk_float_manhattan,manhattan);
//		_CLASS_ADDFUNC(qk_float_mix,mix);
//		_CLASS_ADDFUNC(qk_float_tofloat,tofloat);
//		_CLASS_ADDFUNC(qk_float_tovec2,tovec2);
//		_CLASS_ADDFUNC(qk_float_tovec3,tovec3);
//		_CLASS_ADDFUNC(qk_float_tovec4,tovec4);
//		_CLASS_ADDFUNC(qk_float_tohvec2,tohvec2);
//		_CLASS_ADDFUNC(qk_float_tohvec3,tohvec3);
//		_CLASS_ADDFUNC(qk_float_tohvec4,tohvec4);
//		_CLASS_ADDFUNC(qk_float_toivec2,toivec2);
//		_CLASS_ADDFUNC(qk_float_toivec3,toivec3);
//		_CLASS_ADDFUNC(qk_float_toivec4,toivec4);
//		_CLASS_ADDFUNC(qk_float_tomat2,tomat2);
//		_CLASS_ADDFUNC(qk_float_tomat3,tomat3);
//		_CLASS_ADDFUNC(qk_float_tomat4,tomat4);
		
		sq_poptop(v);							// -1 //
	}

	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
