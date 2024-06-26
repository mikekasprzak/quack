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
SQInteger qk_sensorinfo_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	// Construct Data //
	new(Info) QK::QSensorInfo();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_sensorinfo_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
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
SQInteger qk_sensorinfo_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
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
SQInteger qk_sensorinfo_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);
	
	char Text[128];
	sprintf(Text,"[QkSensorInfo:0x%x,?,?]", (int)(st)Info );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_sensorinfo_cloned( HSQUIRRELVM v ) {
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
_FUNC_TYPEOF(QSensorInfo,qk_sensorinfo_typeof,"QkSensorInfo",12);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//SQInteger qk_sensorinfo_SetMass( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	QK::QObj* Ob;
//	sq_getinstanceup(v,1,(void**)&Ob,0);
//	
//	SQFloat Mass = 1.0f;
//	sq_getfloat(v,2,&Mass);
//	
//	Ob->SetMass( Real(Mass) );
//
//	return SQ_VOID;	
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//SQInteger qk_sensorinfo_GetPoint( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	QK::QSensorInfo* Info;
//	sq_getinstanceup(v,1,(void**)&Info,0);
//
//	// Create a Vector Instance //	
//	sq_pushroottable(v);
//	sq_pushstring(v,"vec2",-1);
//	sq_get(v,-2);
//	sq_createinstance(vm,-1);
//	// TODO: OPTIMIZE! store a vec2 class, retrieve it, push it //
//	
//	QK::QVec* Vec;
//	sq_getinstanceup(v,-1,(void**)&Vec,0);
//
//	*Vec = Info->Sensor.Point;
//
//	return SQ_RETURN;	
//}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sensorinfo_GetA( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	sq_pushinteger(v,Info->A.Message);

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sensorinfo_GetB( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	sq_pushinteger(v,Info->B.Message);

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sensorinfo_GetNameA( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	sq_pushstring(v,Info->A.Name,-1);

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sensorinfo_GetNameB( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSensorInfo* Info;
	sq_getinstanceup(v,1,(void**)&Info,0);

	sq_pushstring(v,Info->B.Name,-1);

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkSensorInfo_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_sensorinfo_constructor,-1,NULL),
	_DECL_FUNC(qk_sensorinfo_get,2,NULL),
	_DECL_FUNC(qk_sensorinfo_set,3,NULL),
	_DECL_FUNC(qk_sensorinfo_typeof,0,NULL),
	_DECL_FUNC(qk_sensorinfo_tostring,1,NULL),
//	_DECL_FUNC(qk_sensorinfo_cloned,2,NULL),
	
	_DECL_FUNC(qk_sensorinfo_GetA,1,NULL),
	_DECL_FUNC(qk_sensorinfo_GetB,1,NULL),
	_DECL_FUNC(qk_sensorinfo_GetNameA,1,NULL),
	_DECL_FUNC(qk_sensorinfo_GetNameB,1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkSensorInfo(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkSensorInfo_funcs;
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
		_ADD_PTRCLASS_START(QSensorInfo,"QkSensorInfo",QK_TAG_CONTACTINFO);
		_CLASS_ADDFUNC(qk_sensorinfo_constructor,constructor);
		_CLASS_ADDFUNC(qk_sensorinfo_get,_get);
		_CLASS_ADDFUNC(qk_sensorinfo_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_sensorinfo_typeof,_typeof);
		_CLASS_ADDFUNC(qk_sensorinfo_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_sensorinfo_cloned,_cloned);

		_CLASS_ADDFUNC(qk_sensorinfo_GetA,GetA);
		_CLASS_ADDFUNC(qk_sensorinfo_GetB,GetB);
		_CLASS_ADDFUNC(qk_sensorinfo_GetNameA,GetNameA);
		_CLASS_ADDFUNC(qk_sensorinfo_GetNameB,GetNameB);

		_ADD_CLASS_END(QSensorInfo);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
