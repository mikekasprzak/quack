// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_vec2_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Vector2D* Vec;
	sq_getinstanceup(v,1,(void**)&Vec,0);
	
	// Check the number of arguments //
//	int Top = sq_gettop(v);
	
	float x,y;
	sq_getfloat(v,2,&x);
	sq_getfloat(v,3,&y);
		
	// Write Data //
	*Vec = Vector2D(x,y);

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_vec2_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Vector2D* Vec;
	sq_getinstanceup(v,1,(void**)&Vec,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'x' ) {
		sq_pushfloat(v,Vec->x.ToFloat());	// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'y' ) {
		sq_pushfloat(v,Vec->y.ToFloat());	// +1 //
		return SQ_RETURN;
	}

	// Throw null on member not found //
	sq_pushnull(v);		// +1 //
	sq_throwobject(v);	// -1 //
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_vec2_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Vector2D* Vec;
	sq_getinstanceup(v,1,(void**)&Vec,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);

	// Get the value //
	float Value;
	sq_getfloat(v,3,&Value);
	
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

	// Throw null on member not found //
	sq_pushnull(v);		// +1 //
	sq_throwobject(v);	// -1 //
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _typeof metamethod //
SQInteger qk_vec2_typeof( HSQUIRRELVM v ) {
	sq_pushstring(v,"vec2",4); // 4 characters long //
	return SQ_RETURN;
}
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
// _cloned metamethod //
SQInteger qk_vec2_cloned( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Vector2D* Vec;
	sq_getinstanceup(v,1,(void**)&Vec,0);

	// Retrieve Other Data (Pointer) //
	Vector2D* Vs;
	sq_getinstanceup(v,2,(void**)&Vs,0);
	
	*Vec = *Vs;

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _add metamethod //
SQInteger qk_vec2_add( HSQUIRRELVM v ) {
	sq_clone(v,1);
	
	// Retrieve Clone Data (Pointer) //
	Vector2D* Vec;
	sq_getinstanceup(v,-1,(void**)&Vec,0);

	// Retrieve Other Data (Pointer) //
	Vector2D* Vs;
	sq_getinstanceup(v,2,(void**)&Vs,0);
	
	*Vec += *Vs;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _sub metamethod //
SQInteger qk_vec2_sub( HSQUIRRELVM v ) {
	sq_clone(v,1);
	
	// Retrieve Clone Data (Pointer) //
	Vector2D* Vec;
	sq_getinstanceup(v,-1,(void**)&Vec,0);

	// Retrieve Other Data (Pointer) //
	Vector2D* Vs;
	sq_getinstanceup(v,2,(void**)&Vs,0);
	
	*Vec -= *Vs;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _mul metamethod //
//SQInteger qk_vec2_mul( HSQUIRRELVM v ) {
//	sq_clone(v,1);
//	
//	// Retrieve Clone Data (Pointer) //
//	Vector2D* Vec;
//	sq_getinstanceup(v,-1,(void**)&Vec,0);
//
//	// Retrieve Other Data (Pointer) //
//	Vector2D* Vs;
//	sq_getinstanceup(v,2,(void**)&Vs,0);
//	
//	(*Vec) *= (*Vs);
//
//	return SQ_RETURN;
//}
// - ------------------------------------------------------------------------------------------ - //
// _div metamethod //
//SQInteger qk_vec2_div( HSQUIRRELVM v ) {
//	sq_clone(v,1);
//	
//	// Retrieve Clone Data (Pointer) //
//	Vector2D* Vec;
//	sq_getinstanceup(v,-1,(void**)&Vec,0);
//
//	// Retrieve Other Data (Pointer) //
//	Vector2D* Vs;
//	sq_getinstanceup(v,2,(void**)&Vs,0);
//	
//	*Vec /= *Vs;
//
//	return SQ_RETURN;
//}
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

	// constructor //
	sq_pushstring(v,"constructor",-1);					// +1 //
	sq_pushstring(v,"qk_vec2_constructor",-1);			// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// get metamethod //
	sq_pushstring(v,"_get",-1);							// +1 //
	sq_pushstring(v,"qk_vec2_get",-1);					// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// set metamethod //
	sq_pushstring(v,"_set",-1);							// +1 //
	sq_pushstring(v,"qk_vec2_set",-1);					// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// typeof metamethod //
	sq_pushstring(v,"_typeof",-1);						// +1 //
	sq_pushstring(v,"qk_vec2_typeof",-1);				// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

//	// tostring metamethod //
//	sq_pushstring(v,"_tostring",-1);					// +1 //
//	sq_pushstring(v,"qk_vec2_tostring",-1);			// +1 //
//	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
//	sq_newslot(v,CPos,false);							// -2 //

	// cloned metamethod //
	sq_pushstring(v,"_cloned",-1);						// +1 //
	sq_pushstring(v,"qk_vec2_cloned",-1);				// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// add metamethod //
	sq_pushstring(v,"_add",-1);							// +1 //
	sq_pushstring(v,"qk_vec2_add",-1);					// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// sub metamethod //
	sq_pushstring(v,"_sub",-1);							// +1 //
	sq_pushstring(v,"qk_vec2_sub",-1);					// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

//	// mul metamethod //
//	sq_pushstring(v,"_mul",-1);							// +1 //
//	sq_pushstring(v,"qk_vec2_mul",-1);					// +1 //
//	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
//	sq_newslot(v,CPos,false);							// -2 //
//
//	// div metamethod //
//	sq_pushstring(v,"_div",-1);							// +1 //
//	sq_pushstring(v,"qk_vec2_div",-1);					// +1 //
//	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
//	sq_newslot(v,CPos,false);							// -2 //
	
	sq_newslot(v,Root,false); // Add Class to Root		// -2 //
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
