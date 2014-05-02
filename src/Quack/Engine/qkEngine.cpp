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
SQInteger qk_engine_constructor( HSQUIRRELVM v ) {
	// HACK! Until fixed (see notes at bottom of file in class creation) //
	extern SQInteger qk_engine_destructor( SQUserPointer Engine, SQInteger Size );
	sq_setreleasehook(v,1,qk_engine_destructor);
	
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// Construct Data //
	new(Engine) QK::QEngine();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// the destructor //
SQInteger qk_engine_destructor( SQUserPointer Engine, SQInteger Size ) {
	((QK::QEngine*)Engine)->~QEngine();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_engine_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
	// Return different data depending on requested member //
	if ( strcmp(MemberName,"Debug") == 0 ) {
		sq_pushbool(v,Engine->Prop.Debug);			// +1 //
		return SQ_RETURN;
	}
	else if ( strcmp(MemberName,"NumObj") == 0 ) {
		sq_pushinteger(v,Engine->Obj.size());		// +1 //
		return SQ_RETURN;
	}
	else if ( strcmp(MemberName,"NumCamera") == 0 ) {
		sq_pushinteger(v,Engine->Camera.size());	// +1 //
		return SQ_RETURN;
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
namespace App {
	extern bool Debug;
};
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_engine_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
	// Return different data depending on requested member //
	if ( strcmp(MemberName,"Debug") == 0 ) {
		SQBool Value;
		sq_getbool(v,3,&Value);

		Engine->Prop.Debug = Value;
		App::Debug = Value;
		sq_pushbool( v, Value );
		return SQ_RETURN;
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_engine_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);
	
	char Text[128];
	sprintf(Text,"[QkEngine Obj:%i Camera:%i]", (int)Engine->Obj.size(), (int)Engine->Camera.size() );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_engine_cloned( HSQUIRRELVM v ) {
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
_FUNC_TYPEOF(QEngine,qk_engine_typeof,"QkEngine",8);
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//SQInteger qk_engine_ShowRects( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	QK::QEngine* Engine;
//	sq_getinstanceup(v,1,(void**)&Engine,0);
//	
//	// Get the requested member //
//	SQBool Show;
//	sq_getbool(v,2,&Show);
//	
//	Engine->Prop.ShowRects = Show;
//
//	return SQ_VOID;	
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddDummy( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos;
	sq_getinstanceup(v,2,(void**)&Pos,NULL);
	
	QK::AddDummy_QEngine( *Engine, *Pos );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddBoxy( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos;
	sq_getinstanceup(v,2,(void**)&Pos,NULL);
	Vector2D* Shape;
	sq_getinstanceup(v,3,(void**)&Shape,NULL);
	
	QK::AddBoxy_QEngine( *Engine, *Pos, *Shape );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddBoxyStatic( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos;
	sq_getinstanceup(v,2,(void**)&Pos,NULL);
	Vector2D* Shape;
	sq_getinstanceup(v,3,(void**)&Shape,NULL);
	
	QK::AddBoxyStatic_QEngine( *Engine, *Pos, *Shape );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddBally( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos;
	sq_getinstanceup(v,2,(void**)&Pos,NULL);
	float Radius;
	sq_getfloat(v,3,&Radius);
	
	QK::AddBally_QEngine( *Engine, *Pos, Real(Radius) );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddCappy( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos1;
	sq_getinstanceup(v,2,(void**)&Pos1,NULL);
	float Radius1;
	sq_getfloat(v,3,&Radius1);
	Vector2D* Pos2;
	sq_getinstanceup(v,4,(void**)&Pos2,NULL);
	float Radius2;
	sq_getfloat(v,5,&Radius2);
	
	QK::AddCappy_QEngine( *Engine, *Pos1, Real(Radius1), *Pos2, Real(Radius2) );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddCappyStatic( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos1;
	sq_getinstanceup(v,2,(void**)&Pos1,NULL);
	float Radius1;
	sq_getfloat(v,3,&Radius1);
	Vector2D* Pos2;
	sq_getinstanceup(v,4,(void**)&Pos2,NULL);
	float Radius2;
	sq_getfloat(v,5,&Radius2);
	
	QK::AddCappyStatic_QEngine( *Engine, *Pos1, Real(Radius1), *Pos2, Real(Radius2) );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddBoxObj( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	Vector2D* Pos;
	sq_getinstanceup(v,2,(void**)&Pos,NULL);	
	const char* ClassName;
	sq_getstring(v,3,&ClassName);
	
	QK::AddBoxObj_QEngine( *Engine, *Pos, ClassName );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_AddCamera( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// TODO: Fancy interpretation //	
	QK::QObj* Ob;
	sq_getinstanceup(v,2,(void**)&Ob,NULL);
//	float Radius;
//	sq_getfloat(v,3,&Radius);
	
	QK::AddCamera_QEngine( *Engine, *Ob );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_step( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// Do Step //	
	Engine->Step();	
	
	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_draw( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);
	
	// Need a View and a Matrix //
	Rect2D* View;
	sq_getinstanceup(v,2,(void**)&View,NULL);
	
	Matrix4x4* Mat;
	sq_getinstanceup(v,3,(void**)&Mat,NULL);

	// Do Step //	
	Engine->Draw(*View,*Mat);	
		
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_engine_DrawCamera( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QEngine* Engine;
	sq_getinstanceup(v,1,(void**)&Engine,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);
	
	// Need a View and a Matrix //
	SQInteger CameraIndex;
	sq_getinteger(v,2,&CameraIndex);

//	Rect2D* View;
//	sq_getinstanceup(v,2,(void**)&View,NULL);
	
//	Matrix4x4* Mat;
//	sq_getinstanceup(v,3,(void**)&Mat,NULL);

	// Do Step //	
//	Engine->Draw(*View,*Mat);	
	Engine->DrawCamera( CameraIndex );	
		
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkEngine_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_engine_constructor,-1,NULL),
	_DECL_FUNC(qk_engine_get,2,NULL),
	_DECL_FUNC(qk_engine_set,3,NULL),
	_DECL_FUNC(qk_engine_typeof,0,NULL),
	_DECL_FUNC(qk_engine_tostring,1,NULL),
//	_DECL_FUNC(qk_engine_cloned,2,NULL),	

	_DECL_FUNC(qk_engine_AddDummy,2,NULL),
	_DECL_FUNC(qk_engine_AddBoxy,3,NULL),
	_DECL_FUNC(qk_engine_AddBoxyStatic,3,NULL),
	_DECL_FUNC(qk_engine_AddBally,3,NULL),
	_DECL_FUNC(qk_engine_AddCappy,5,NULL),
	_DECL_FUNC(qk_engine_AddCappyStatic,5,NULL),
	
	_DECL_FUNC(qk_engine_AddBoxObj,3,NULL),
	
//	_DECL_FUNC(qk_engine_ShowRects,2,NULL),

	_DECL_FUNC(qk_engine_AddCamera,2,NULL),

	_DECL_FUNC(qk_engine_step,1,NULL),
	_DECL_FUNC(qk_engine_draw,3,NULL),
	_DECL_FUNC(qk_engine_DrawCamera,2,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkEngine(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkEngine_funcs;
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
		_ADD_CLASS_START(QEngine,"QkEngine",QK_TAG_ENGINE);
		// There's a bug/design flaw. This will not propagate to the instances (as of 3.4) //
		// Instead, I've added a workaround to the constructor itself //
//		_CLASS_DESTRUCTOR(qk_engine_destructor);
		_CLASS_ADDFUNC(qk_engine_constructor,constructor);
		_CLASS_ADDFUNC(qk_engine_get,_get);
		_CLASS_ADDFUNC(qk_engine_set,_set);
//		_CLASS_ADDFUNC(qk_engine_step,Step);
//		_CLASS_ADDFUNC(qk_engine_draw,Draw);
		_CLASS_ADDFUNC_STATIC(qk_engine_typeof,_typeof);
		_CLASS_ADDFUNC(qk_engine_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_engine_cloned,_cloned);

		_CLASS_ADDFUNC(qk_engine_AddDummy,AddDummy);
		_CLASS_ADDFUNC(qk_engine_AddBoxy,AddBoxy);
		_CLASS_ADDFUNC(qk_engine_AddBoxyStatic,AddBoxyStatic);
		_CLASS_ADDFUNC(qk_engine_AddBally,AddBally);
		_CLASS_ADDFUNC(qk_engine_AddCappy,AddCappy);
		_CLASS_ADDFUNC(qk_engine_AddCappyStatic,AddCappyStatic);
		
		_CLASS_ADDFUNC(qk_engine_AddBoxObj,AddBoxObj);
		
//		_CLASS_ADDFUNC(qk_engine_ShowRects,ShowRects);

		_CLASS_ADDFUNC(qk_engine_AddCamera,AddCamera);

		_CLASS_ADDFUNC(qk_engine_step,Step);
		_CLASS_ADDFUNC(qk_engine_draw,Draw);
		_CLASS_ADDFUNC(qk_engine_DrawCamera,DrawCamera);

		_ADD_CLASS_END(QEngine);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
