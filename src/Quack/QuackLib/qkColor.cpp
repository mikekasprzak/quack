// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Graphics/GelColor.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
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
	sq_pushnull(v);		// +1 //
	sq_throwobject(v);	// -1 //
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
//SQInteger qk_color_set( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelColor* Color;
//	sq_getinstanceup(v,1,(void**)&Color,0);
//	
//	// Get the requested member //
//	const char* MemberName;
//	sq_getstring(v,2,&MemberName);
//	
//	// Return different data depending on requested member //
//	if ( MemberName[0] == 'r' ) {
//		GEL_SET_R(*Color));	// +1 //
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'g' ) {
//		sq_pushinteger(v,GEL_GET_G(*Color));	// +1 //
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'b' ) {
//		sq_pushinteger(v,GEL_GET_B(*Color));	// +1 //
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'a' ) {
//		sq_pushinteger(v,GEL_GET_A(*Color));	// +1 //
//		return SQ_RETURN;
//	}
//
//	// Throw null on member not found //
//	sq_pushnull(v);		// +1 //
//	sq_throwobject(v);	// -1 //
//	
//	return SQ_VOID;
//}
// - ------------------------------------------------------------------------------------------ - //
// _typeof metamethod //
SQInteger qk_color_typeof( HSQUIRRELVM v ) {
	sq_pushstring(v,"color",5); // 5 characters long //
	return SQ_RETURN;
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

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkColor_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qk_color_constructor,-1,NULL),
	_DECL_FUNC(qk_color_get,2,NULL),
	_DECL_FUNC(qk_color_typeof,1,NULL),
	_DECL_FUNC(qk_color_tostring,1,NULL),
	_DECL_FUNC(qk_color_cloned,2,NULL),	
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
	
	int Root = sq_gettop(v); // root table pos
	sq_pushstring(v,"color",-1);						// +1 //
	sq_newclass(v,false); 								// +1 //
	int CPos = sq_gettop(v); // class pos
	sq_setclassudsize(v,CPos,sizeof(GelColor));

	// constructor //
	sq_pushstring(v,"constructor",-1);					// +1 //
	sq_pushstring(v,"qk_color_constructor",-1);			// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// get metamethod //
	sq_pushstring(v,"_get",-1);							// +1 //
	sq_pushstring(v,"qk_color_get",-1);					// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// typeof metamethod //
	sq_pushstring(v,"_typeof",-1);						// +1 //
	sq_pushstring(v,"qk_color_typeof",-1);				// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// tostring metamethod //
	sq_pushstring(v,"_tostring",-1);					// +1 //
	sq_pushstring(v,"qk_color_tostring",-1);			// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //

	// cloned metamethod //
	sq_pushstring(v,"_cloned",-1);						// +1 //
	sq_pushstring(v,"qk_color_cloned",-1);				// +1 //
	sq_get(v,Root); // lookup function 					// =0 // (-1,+1?)
	sq_newslot(v,CPos,false);							// -2 //
	
	sq_newslot(v,Root,false); // Add Class to Root		// -2 //
	sqext_stackdump(v);
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
