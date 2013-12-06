// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/GelColor.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_color_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelColor* Color;
	sq_getinstanceup(v,1,(void**)&Color,0);
	
	// Check the number of arguments //
	int Top = sq_gettop(v);
	
	// Build our color channels //
	int r,g,b;
	int a = 255;
	sq_getinteger(v,2,&r);
	sq_getinteger(v,3,&g);
	sq_getinteger(v,4,&b);
	if ( Top > 4 )
		sq_getinteger(v,5,&a);
	
	// Clamp Colors to 0-255 range //
	r = GEL_CLAMP_COLOR_COMPONENT(r);
	g = GEL_CLAMP_COLOR_COMPONENT(g);
	b = GEL_CLAMP_COLOR_COMPONENT(b);
	a = GEL_CLAMP_COLOR_COMPONENT(a);
	
	// Write Data //
	*Color = GEL_RGBA(r,g,b,a);

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_color_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelColor* Color;
	sq_getinstanceup(v,1,(void**)&Color,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'r' ) {
		sq_pushinteger(v,GEL_GET_R(*Color));	// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'g' ) {
		sq_pushinteger(v,GEL_GET_G(*Color));	// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'b' ) {
		sq_pushinteger(v,GEL_GET_B(*Color));	// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'a' ) {
		sq_pushinteger(v,GEL_GET_A(*Color));	// +1 //
		return SQ_RETURN;
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_color_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelColor* Color;
	sq_getinstanceup(v,1,(void**)&Color,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);

	// Get the value //
	int Value;
	sq_getinteger(v,3,&Value);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'r' ) {
		*Color = GEL_SET_R( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
		sq_pushinteger( v, Value );
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'g' ) {
		*Color = GEL_SET_G( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
		sq_pushinteger( v, Value );
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'b' ) {
		*Color = GEL_SET_B( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
		sq_pushinteger( v, Value );
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'a' ) {
		*Color = GEL_SET_A( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
		sq_pushinteger( v, Value );
		return SQ_RETURN;
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_color_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelColor* Color;
	sq_getinstanceup(v,1,(void**)&Color,0);
	
	// (RRR,GGG,BBB,AAA) //
	char Text[2 + 3+1 + 3+1 + 3+1 + 3 + 1];
	sprintf(Text,"(%i,%i,%i,%i)", GEL_GET_R(*Color), GEL_GET_G(*Color), GEL_GET_B(*Color), GEL_GET_A(*Color) );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
SQInteger qk_color_cloned( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelColor* Color;
	sq_getinstanceup(v,1,(void**)&Color,0);

	// Retrieve Other Data (Pointer) //
	GelColor* OtherColor;
	sq_getinstanceup(v,2,(void**)&OtherColor,0);
	
	*Color = *OtherColor;

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(GelColor,qk_color_typeof,"QkColor",7);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_color_RGB( HSQUIRRELVM v ) {
	// Check the number of arguments //
	int Top = sq_gettop(v);

	// Create an instance of the QkColor Class //
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"QkColor",7);		// +1 //
	sq_get(v,-2);						// =0 //
	sq_createinstance(v,-1);			// +1 //

	// Retrieve Data (Pointer) //
	GelColor* Color;
	sq_getinstanceup(v,-1,(void**)&Color,0);
	
	// Build our color channels //
	int r,g,b;
	int a = 255;
	sq_getinteger(v,2,&r);
	sq_getinteger(v,3,&g);
	sq_getinteger(v,4,&b);
	if ( Top > 4 )
		sq_getinteger(v,5,&a);
	
	// Clamp Colors to 0-255 range //
	r = GEL_CLAMP_COLOR_COMPONENT(r);
	g = GEL_CLAMP_COLOR_COMPONENT(g);
	b = GEL_CLAMP_COLOR_COMPONENT(b);
	a = GEL_CLAMP_COLOR_COMPONENT(a);
	
	// Write Data //
	*Color = GEL_RGBA(r,g,b,a);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkColor_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_color_constructor,-1,NULL),
	_DECL_FUNC(qk_color_get,2,NULL),
	_DECL_FUNC(qk_color_set,3,NULL),
	_DECL_FUNC(qk_color_typeof,0,NULL),
	_DECL_FUNC(qk_color_tostring,1,NULL),
	_DECL_FUNC(qk_color_cloned,2,NULL),	

	_DECL_FUNC_ALT("RGB",qk_color_RGB,-4,NULL),
	_DECL_FUNC_ALT("RGBA",qk_color_RGB,5,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkColor(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkColor_funcs;
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
		_ADD_CLASS_START(GelColor,"QkColor",QK_TAG_COLOR);
		_CLASS_ADDFUNC(qk_color_constructor,constructor);
		_CLASS_ADDFUNC(qk_color_get,_get);
		_CLASS_ADDFUNC(qk_color_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_color_typeof,_typeof);
		_CLASS_ADDFUNC(qk_color_tostring,_tostring);
		_CLASS_ADDFUNC(qk_color_cloned,_cloned);
		_ADD_CLASS_END(GelColor);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
