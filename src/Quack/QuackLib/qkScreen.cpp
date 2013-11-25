// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Graphics/Graphics.h>
#include <App.h>

#include <Graphics/GelColor.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Render/Render.h>

#include <Generate/Vertex.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkScreensSetScalar( HSQUIRRELVM v ) {
	float Scale;
	if(SQ_FAILED(sq_getfloat(v,2,&Scale)))
		return sq_throwerror(v,_SC("invalid param"));
	
	gelSetScreenScalar( Scale );
	
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkScreensInit( HSQUIRRELVM v ) {
	gelInitScreens();

	gelLogGraphicsAPIDetails();
	gelGraphicsInit();

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkScreenGetAspectRatio(HSQUIRRELVM vm) {
	sq_pushfloat( vm, (float)Gel::Native[0].GetWidth() / (float)Gel::Native[0].GetHeight() );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkScreenClear(HSQUIRRELVM vm) {
	//gelClear( true, true );
	glClearColor(0.2,0,0,1);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkScreen_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	// Screen Plural //
	_DECL_FUNC(qkScreensInit,1,NULL),
	_DECL_FUNC(qkScreensSetScalar,2,_SC(".n")),
	// Screen Singular //
	_DECL_FUNC(qkScreenGetAspectRatio,1,NULL),
	_DECL_FUNC(qkScreenClear,1,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkScreen(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkScreen_funcs;
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
