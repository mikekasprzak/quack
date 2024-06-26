// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "../QuackLib/QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
using namespace QK;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_camera_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QCamera* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	// Construct Data //
//	new(Info) QK::QCamera();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_camera_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QCamera* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);
	
//	// Get the requested member //
//	const char* MemberName;
//	sq_getstring(v,2,&MemberName);
//
//	if ( strcmp(MemberName,"Art") == 0 ) {
//		sq_pushobject(vm,DummySkelAnimator);
//		sq_setinstanceup(vm,-1,Ob->GetArt());
//		return SQ_RETURN;		
//	}

//	// Return different data depending on requested member //
//	if ( MemberName[0] == 'r' ) {
//		sq_pushinteger(v,GEL_GET_R(*Color));	// +1 //
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

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_camera_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QCamera* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);
	
//	// Get the requested member //
//	const char* MemberName;
//	sq_getstring(v,2,&MemberName);
//
//	// Get the value //
//	float Value;
//	sq_getfloat(v,3,&Value);
//	
//	// Return different data depending on requested member //
//	if ( MemberName[0] == 'x' ) {
//		Ob->AddForce( Vector2D(Value,0) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}

//	else if ( MemberName[0] == 'g' ) {
//		*Color = GEL_SET_G( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'b' ) {
//		*Color = GEL_SET_B( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'a' ) {
//		*Color = GEL_SET_A( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_camera_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QCamera* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);
	
	char Text[128];
	sprintf(Text,"[QkCamera:0x%x,?,?]", (int)(st)Info );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_camera_cloned( HSQUIRRELVM v ) {
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
_FUNC_TYPEOF(QCamera,qk_camera_typeof,"QkCamera",8);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_camera_GetView( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QCamera* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	// Create a Matrix Instance //	
	sq_pushroottable(v);
	sq_pushstring(v,"rect2",-1);
	sq_get(v,-2);
	sq_createinstance(vm,-1);
	
	QK::QRect* Rect;
	sq_getinstanceup(v,-1,(void**)&Rect,0);

	int Width = Gel::LastBoundTarget->Width;
	int Height = Gel::LastBoundTarget->Height;

	*Rect = Info->GetView(Width,Height);

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_camera_GetMatrix( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QCamera* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	// Create a Matrix Instance //	
	sq_pushroottable(v);
	sq_pushstring(v,"mat4",-1);
	sq_get(v,-2);
	sq_createinstance(vm,-1);
	
	QK::QMat* Mat;
	sq_getinstanceup(v,-1,(void**)&Mat,0);

	int Width = Gel::LastBoundTarget->Width;
	int Height = Gel::LastBoundTarget->Height;

	*Mat = Info->GetMatrix(Width,Height);

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkCamera_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_camera_constructor,-1,NULL),
	_DECL_FUNC(qk_camera_get,2,NULL),
	_DECL_FUNC(qk_camera_set,3,NULL),
	_DECL_FUNC(qk_camera_typeof,0,NULL),
	_DECL_FUNC(qk_camera_tostring,1,NULL),
//	_DECL_FUNC(qk_camera_cloned,2,NULL),

	_DECL_FUNC(qk_camera_GetView,1,NULL),
	_DECL_FUNC(qk_camera_GetMatrix,1,NULL),
		
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkCamera(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkCamera_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	// NOTE: NEVER CREATED! ALWAYS RETURNED BY ENGINE METHODS! //
	int Root = sq_gettop(v); // root table pos //
	{
		_ADD_PTRCLASS_START(QCamera,"QkCamera",QK_TAG_CAMERA);
		_CLASS_ADDFUNC(qk_camera_constructor,constructor);
		_CLASS_ADDFUNC(qk_camera_get,_get);
		_CLASS_ADDFUNC(qk_camera_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_camera_typeof,_typeof);
		_CLASS_ADDFUNC(qk_camera_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_camera_cloned,_cloned);

		_CLASS_ADDFUNC(qk_camera_GetView,GetView);
		_CLASS_ADDFUNC(qk_camera_GetMatrix,GetMatrix);

		_ADD_CLASS_END(QCamera);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
