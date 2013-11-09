// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _VEC_CONSTRUCTOR_START(_TYPE_) \
	_TYPE_* Vec; \
	sq_getinstanceup(v,1,(void**)&Vec,0);
// - ------------------------------------------------------------------------------------------ - //
#define _VEC_CONSTRUCTOR_END(_TYPE_) \
	return SQ_VOID;
// - ------------------------------------------------------------------------------------------ - //
#define _VEC_GET_START(_TYPE_) \
	_TYPE_* Vec; \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	const char* MemberName; \
	sq_getstring(v,2,&MemberName);
// - ------------------------------------------------------------------------------------------ - //
#define _VEC_GET_END(_TYPE_) \
	sq_pushnull(v);		/* +1 */ \
	sq_throwobject(v);	/* -1 */ \
	\
	return SQ_VOID;
// - ------------------------------------------------------------------------------------------ - //
#define _VEC_SET_START(_TYPE_) \
	_TYPE_* Vec; \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	const char* MemberName; \
	sq_getstring(v,2,&MemberName); \
	\
	float Value; \
	sq_getfloat(v,3,&Value);
// - ------------------------------------------------------------------------------------------ - //
#define _VEC_SET_END(_TYPE_) \
	sq_pushnull(v);		/* +1 */ \
	sq_throwobject(v);	/* -1 */ \
	\
	return SQ_VOID;
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_vec2_constructor( HSQUIRRELVM v ) {
	_VEC_CONSTRUCTOR_START(Vector2D);
	
	float x,y;
	sq_getfloat(v,2,&x);
	sq_getfloat(v,3,&y);
		
	// Write Data //
	*Vec = Vector2D(x,y);

	_VEC_CONSTRUCTOR_END(Vector2D);
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_vec2_get( HSQUIRRELVM v ) {
	_VEC_GET_START(Vector2D);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'x' ) {
		sq_pushfloat(v,Vec->x.ToFloat());	// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'y' ) {
		sq_pushfloat(v,Vec->y.ToFloat());	// +1 //
		return SQ_RETURN;
	}

	_VEC_GET_END(Vector2D);
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_vec2_set( HSQUIRRELVM v ) {
	_VEC_SET_START(Vector2D);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'x' ) {
		Vec->x = Value;
		sq_pushfloat( v, Value );
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'y' ) {
		Vec->y = Value;
		sq_pushfloat( v, Value );
		return SQ_RETURN;
	}

	_VEC_SET_END(Vector2D);
}
// - ------------------------------------------------------------------------------------------ - //
// _typeof metamethod //
//SQInteger qk_vec2_typeof( HSQUIRRELVM v ) {
//	sq_pushstring(v,"vec2",4); // 4 characters long //
//	return SQ_RETURN;
//}
// - ------------------------------------------------------------------------------------------ - //
//// _tostring metamethod //
//SQInteger qk_vec2_tostring( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelColor* Color;
//	sq_getinstanceup(v,1,(void**)&Color,0);
//	
//	// (RRR,GGG,BBB,AAA) //
//	char Text[2 + 3+1 + 3+1 + 3+1 + 3 + 1];
//	sprintf(Text,"(%i,%i,%i,%i)", GEL_GET_R(*Color), GEL_GET_G(*Color), GEL_GET_B(*Color), GEL_GET_A(*Color) );
//	
//	sq_pushstring(v,Text,-1);
//	
//	return SQ_RETURN;
//}

// - ------------------------------------------------------------------------------------------ - //
#define _VEC_TYPEOF_METAMETHOD(_TYPE_,_NAME_,_TYPENAME_,_STRLEN_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_pushstring(v,#_TYPENAME_,_STRLEN_); \
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned //
#define _VEC_CLONED_METAMETHOD(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Vec; /* +1 */ \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	*Vec = *Vs; \
	\
	return SQ_VOID; \
}
// - ------------------------------------------------------------------------------------------ - //
// _add, _sub, _mul, _div //
#define _VEC_MATH_METAMETHOD(_TYPE_,_NAME_,_OP_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	*Vec = (*Vec) _OP_ (*Vs); \
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// _unm (i.e. negative) //
#define _VEC_UNM_METAMETHOD(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	*Vec = -(*Vec);\
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
#define _CLASS_ADDFUNC(_FUNC_,_METHOD_) \
	sq_pushstring(v,#_METHOD_,-1);				/* +1 */ \
	sq_pushstring(v,#_FUNC_,-1);				/* +1 */ \
	sq_get(v,Root); /* lookup function */		/* =0 */ \
	sq_newslot(v,CPos,false);					/* -2 */
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
_VEC_TYPEOF_METAMETHOD(Vector2D,qk_vec2_typeof,vec2,4);
_VEC_CLONED_METAMETHOD(Vector2D,qk_vec2_cloned);
_VEC_MATH_METAMETHOD(Vector2D,qk_vec2_add,+);
_VEC_MATH_METAMETHOD(Vector2D,qk_vec2_sub,-);
_VEC_UNM_METAMETHOD(Vector2D,qk_vec2_unm);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkVector_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qk_vec2_constructor,3,NULL),
	_DECL_FUNC(qk_vec2_get,2,NULL),
	_DECL_FUNC(qk_vec2_set,3,NULL),
	_DECL_FUNC(qk_vec2_typeof,1,NULL),
//	_DECL_FUNC(qk_vec2_tostring,1,NULL),
	_DECL_FUNC(qk_vec2_cloned,2,NULL),

	_DECL_FUNC(qk_vec2_add,2,NULL),
	_DECL_FUNC(qk_vec2_sub,2,NULL),
//	_DECL_FUNC(qk_vec2_mul,2,NULL),
//	_DECL_FUNC(qk_vec2_div,2,NULL),

	_DECL_FUNC(qk_vec2_unm,1,NULL),
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkVector(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkVector_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	int Root = sq_gettop(v); // root table pos	
	
	sq_pushstring(v,"vec2",-1);							// +1 //
	sq_newclass(v,false); 								// +1 //
	int CPos = sq_gettop(v); // class pos
	sq_setclassudsize(v,CPos,sizeof(Vector2D));

	_CLASS_ADDFUNC(qk_vec2_constructor,constructor);
	_CLASS_ADDFUNC(qk_vec2_get,_get);
	_CLASS_ADDFUNC(qk_vec2_set,_set);
	_CLASS_ADDFUNC(qk_vec2_typeof,_typeof);
	_CLASS_ADDFUNC(qk_vec2_cloned,_cloned);
	_CLASS_ADDFUNC(qk_vec2_add,_add);
	_CLASS_ADDFUNC(qk_vec2_sub,_sub);

	sq_newslot(v,Root,false); // Add Class to Root		// -2 //
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
