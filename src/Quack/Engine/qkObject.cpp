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
HSQOBJECT DummySkelAnimator;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_object_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Obj;
	sq_getinstanceup(v,1,(void**)&Obj,0);

	// Construct Data //
//	new(Obj) QK::QObj();

	// HEY! THIS SHOULD NOT BE CALLED! //
	Log("! THIS SHOULD NOT BE CALLED !");

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_object_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);

	if ( strcmp(MemberName,"Art") == 0 ) {
		sq_pushobject(vm,DummySkelAnimator);
		sq_setinstanceup(vm,-1,Ob->GetArt());
		return SQ_RETURN;		
	}

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
SQInteger qk_object_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);

	// Get the value //
	float Value;
	sq_getfloat(v,3,&Value);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'x' ) {
		Ob->AddForce( Vector2D(Value,0) );
		sq_pushinteger( v, Value );
		return SQ_RETURN;
	}
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
SQInteger qk_object_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	char Text[128];
	sprintf(Text,"[QkObject:0x%x (%i),?,?]", (int)(st)Ob, Ob->MyIndex );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_object_cloned( HSQUIRRELVM v ) {
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
_FUNC_TYPEOF(QObj,qk_object_typeof,"QkObj",5);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_SetArt( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	// Get the requested member //
	const char* ArtFile;
	sq_getstring(v,2,&ArtFile);
	
	Ob->SetArt(ArtFile);

	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_SetArtScale( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	Vector2D Vec(1,1);
	_SQ_GET_VEC2_ARG(Vec,2);	
	
	Ob->SetArtScale( Vec );

	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_SetMass( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	SQFloat Mass = 1.0f;
	sq_getfloat(v,2,&Mass);
	
	Ob->SetMass( Real(Mass) );

	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_SetShape( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	Vector2D Vec(1,1);
	_SQ_GET_VEC2_ARG(Vec,2);	
	
	Ob->SetShape( Vec );

	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_AddForce( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	Vector2D Vec;
	_SQ_GET_VEC2_ARG(Vec,2);	

	Ob->AddForce( Vec );

	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_GetVelocity( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	// Create a Vector Instance //	
	sq_pushroottable(v);
	sq_pushstring(v,"vec2",-1);
	sq_get(v,-2);
	sq_createinstance(vm,-1);
	// TODO: OPTIMIZE! store a vec2 class, retrieve it, push it //
	
	QK::QVec* Vec;
	sq_getinstanceup(v,-1,(void**)&Vec,0);

	*Vec = Ob->GetVelocity();

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_GetPos( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	// Create a Vector Instance //	
	sq_pushroottable(v);
	sq_pushstring(v,"vec2",-1);
	sq_get(v,-2);
	sq_createinstance(vm,-1);
	// TODO: OPTIMIZE! store a vec2 class, retrieve it, push it //
	
	QK::QVec* Vec;
	sq_getinstanceup(v,-1,(void**)&Vec,0);

	*Vec = Ob->GetPos();

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_object_Notify( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QObj* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	QK::QObj* Vs;
	sq_getinstanceup(v,2,(void**)&Vs,0);

	SQInteger Message;
	sq_getinteger(v,3,&Message);

	Ob->Notify(*Vs,Message);

	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkObject_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_object_constructor,-1,NULL),
	_DECL_FUNC(qk_object_get,2,NULL),
	_DECL_FUNC(qk_object_set,3,NULL),
	_DECL_FUNC(qk_object_typeof,0,NULL),
	_DECL_FUNC(qk_object_tostring,1,NULL),
//	_DECL_FUNC(qk_object_cloned,2,NULL),

	_DECL_FUNC(qk_object_SetArt,2,NULL),
	_DECL_FUNC(qk_object_SetArtScale,3,NULL),
	
	_DECL_FUNC(qk_object_SetMass,2,NULL),
	_DECL_FUNC(qk_object_SetShape,3,NULL),
	_DECL_FUNC(qk_object_AddForce,-2,NULL),

	_DECL_FUNC(qk_object_Notify,3,NULL),
	
	_DECL_FUNC(qk_object_GetPos,1,NULL),
	_DECL_FUNC(qk_object_GetVelocity,1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkObject(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkObject_funcs;
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
		_ADD_PTRCLASS_START(QObj,"QkObj",QK_TAG_OBJECT);
		_CLASS_ADDFUNC(qk_object_constructor,constructor);
		_CLASS_ADDFUNC(qk_object_get,_get);
		_CLASS_ADDFUNC(qk_object_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_object_typeof,_typeof);
		_CLASS_ADDFUNC(qk_object_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_object_cloned,_cloned);

		_CLASS_ADDFUNC(qk_object_SetArt,SetArt);
		_CLASS_ADDFUNC(qk_object_SetArtScale,SetArtScale);

		_CLASS_ADDFUNC(qk_object_SetMass,SetMass);
		_CLASS_ADDFUNC(qk_object_SetShape,SetShape);
		_CLASS_ADDFUNC(qk_object_AddForce,AddForce);

		_CLASS_ADDFUNC(qk_object_GetPos,GetPos);
		_CLASS_ADDFUNC(qk_object_GetVelocity,GetVelocity);

		_CLASS_ADDFUNC(qk_object_Notify,Notify);

		_ADD_CLASS_END(QObj);
	}
	
	// ** SqObj Holder (Pointer is assigned before calls) ** //
	sq_resetobject(&DummySkelAnimator);
	// Instance the Class //		
	sq_pushroottable(vm);
	sq_pushstring(vm,_SC("QkSkelAnimatorPtr"),-1);
	sq_get(vm,-2);
	sq_createinstance(vm,-1);
	// Store the Instance, add a reference //
	sq_getstackobj(vm,-1,&DummySkelAnimator);
	sq_addref(vm,&DummySkelAnimator);
	sq_pop(vm,3);

	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
