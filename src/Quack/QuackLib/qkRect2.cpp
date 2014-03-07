// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_rect2_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Rect2D* Rect;
	sq_getinstanceup(v,1,(void**)&Rect,0);
	
	// Check the number of arguments //
	int Top = sq_gettop(v);
	
	SQFloat x,y,w,h;
	sq_getfloat(v,2,&x);
	sq_getfloat(v,3,&y);
	sq_getfloat(v,4,&w);
	sq_getfloat(v,5,&h);
	
	// Write Data //
	new (Rect) Rect2D(x,y,w,h);

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_rect2_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Rect2D* Rect;
	sq_getinstanceup(v,1,(void**)&Rect,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
	// Return different data depending on requested member //
	if ( MemberName[1] == 0 ) {
		if ( MemberName[0] == 'x' ) {
			sq_pushfloat(v,Rect->P1().x.ToFloat());		// +1 //
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'y' ) {
			sq_pushfloat(v,Rect->P1().y.ToFloat());		// +1 //
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'w' ) {
			sq_pushfloat(v,Rect->Shape().x.ToFloat());		// +1 //
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'h' ) {
			sq_pushfloat(v,Rect->Shape().y.ToFloat());		// +1 //
			return SQ_RETURN;
		}
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_rect2_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Rect2D* Rect;
	sq_getinstanceup(v,1,(void**)&Rect,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);

	// Get the value //
	SQFloat Value;
	sq_getfloat(v,3,&Value);
	
	// Return different data depending on requested member //
	if ( MemberName[1] == 0 ) {
		if ( MemberName[0] == 'x' ) {
			Rect->P1().x = Real(Value);
			sq_pushfloat( v, Value );
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'y' ) {
			Rect->P1().y = Real(Value);
			sq_pushfloat( v, Value );
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'w' ) {
			Rect->Shape().x = Real(Value);
			sq_pushfloat( v, Value );
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'h' ) {
			Rect->Shape().y = Real(Value);
			sq_pushfloat( v, Value );
			return SQ_RETURN;
		}
	}
	// P1 and P2 //
	else if ( MemberName[0] == 'p' ) {
		if ( MemberName[1] == '1' ) {
		}
		else if ( MemberName[1] == '2' ) {
		}
	}
	// Shape //
	else if ( MemberName[0] == 's' ) {
	}
	// HalfShape //
	else if ( MemberName[0] == 'h' ) {
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_rect2_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	Rect2D* Rect;
	sq_getinstanceup(v,1,(void**)&Rect,0);
	
	char Text[256];
	sprintf(Text,"[(%f,%f) (%f,%f)]", Rect->P1().x.ToFloat(),Rect->P1().y.ToFloat(), Rect->Shape().x.ToFloat(),Rect->Shape().y.ToFloat() );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_rect2_cloned( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelColor* Color;
//	sq_getinstanceup(v,1,(void**)&Color,0);
//
//	// Retrieve Other Data (Pointer) //
//	GelColor* OtherColor;
//	sq_getinstanceup(v,2,(void**)&OtherColor,0);
//	
//	*Color = *OtherColor;
//
//	return SQ_VOID;
//}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(Rect2D,qk_rect2_typeof,"rect2",5);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkRect2_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_rect2_constructor,-1,NULL),
	_DECL_FUNC(qk_rect2_get,2,NULL),
	_DECL_FUNC(qk_rect2_set,3,NULL),
	_DECL_FUNC(qk_rect2_typeof,0,NULL),
	_DECL_FUNC(qk_rect2_tostring,1,NULL),
//	_DECL_FUNC(qk_rect2_cloned,2,NULL),	

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkRect2(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkRect2_funcs;
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
		_ADD_CLASS_START(Rect2D,"rect2",QK_TAG_RECT2);
		_CLASS_ADDFUNC(qk_rect2_constructor,constructor);
		_CLASS_ADDFUNC(qk_rect2_get,_get);
		_CLASS_ADDFUNC(qk_rect2_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_rect2_typeof,_typeof);
		_CLASS_ADDFUNC(qk_rect2_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_rect2_cloned,_cloned);
		_ADD_CLASS_END(Rect2D);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
