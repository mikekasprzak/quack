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
SQInteger qk_sky_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	// Construct Data //
	new(Ob) QK::QSky();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_sky_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
//	QK::QObjHandle* ObjHandle;
//	sq_getinstanceup(v,1,(void**)&ObjHandle,0);
//	QK::QObj* Ob = ObjHandle->Get();

//	QK::QObj* Ob;
//	sq_getinstanceup(v,1,(void**)&Ob,0);
//	
//	// Get the requested member //
//	const char* MemberName;
//	sq_getstring(v,2,&MemberName);
//
//	if ( strcmp(MemberName,"Art") == 0 ) {
//		sq_pushobject(vm,DummySkelAnimator);
//		sq_setinstanceup(vm,-1,Ob->GetArt());
//		return SQ_RETURN;		
//	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_sky_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
//	QK::QObjHandle* ObjHandle;
//	sq_getinstanceup(v,1,(void**)&ObjHandle,0);
//	QK::QObj* Ob = ObjHandle->Get();

//	QK::QObj* Ob;
//	sq_getinstanceup(v,1,(void**)&Ob,0);
//	
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
////	else if ( MemberName[0] == 'g' ) {
////		*Color = GEL_SET_G( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
////		sq_pushinteger( v, Value );
////		return SQ_RETURN;
////	}
////	else if ( MemberName[0] == 'b' ) {
////		*Color = GEL_SET_B( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
////		sq_pushinteger( v, Value );
////		return SQ_RETURN;
////	}
////	else if ( MemberName[0] == 'a' ) {
////		*Color = GEL_SET_A( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
////		sq_pushinteger( v, Value );
////		return SQ_RETURN;
////	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_sky_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
//	QK::QObjHandle* ObjHandle;
//	sq_getinstanceup(v,1,(void**)&ObjHandle,0);
//	QK::QObj* Ob = ObjHandle->Get();

	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);
	
	char Text[128];
	// NOTE: When we switch UID to be 64bit, make sure to update this printf!! //
	sprintf(Text,"[QkSky:0x%x ?,?]", (int)(st)Ob );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_sky_cloned( HSQUIRRELVM v ) {
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
_FUNC_TYPEOF(QSky,qk_sky_typeof,"QkSky",5);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sky_Add( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	SQInteger Bands;
	sq_getinteger(v,2,&Bands);
	
	GelColor* Color;
	sq_getinstanceup(v,3,(void**)&Color,NULL);

	Ob->Add( Bands, *Color );
	
	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sky_SetBandPos( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	SQFloat Pos;
	sq_getfloat(v,2,&Pos);
	
	Ob->SetBandPos( Real(Pos) );
	
	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sky_SetBandSize( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	SQFloat Pos;
	sq_getfloat(v,2,&Pos);
	
	Ob->SetBandSize( Real(Pos) );
	
	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sky_step( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	// Do Step //	
	Ob->Step();	
	
	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_sky_draw( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	QK::QSky* Ob;
	sq_getinstanceup(v,1,(void**)&Ob,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);
	
	// Need a View and a Matrix //
	Rect2D* View;
	sq_getinstanceup(v,2,(void**)&View,NULL);
	
	Matrix4x4* Mat;
	sq_getinstanceup(v,3,(void**)&Mat,NULL);

	// Do Draw //	
	Ob->Draw(*View,*Mat);	
		
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkSky_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_sky_constructor,-1,NULL),
	_DECL_FUNC(qk_sky_get,2,NULL),
	_DECL_FUNC(qk_sky_set,3,NULL),
	_DECL_FUNC(qk_sky_typeof,0,NULL),
	_DECL_FUNC(qk_sky_tostring,1,NULL),
//	_DECL_FUNC(qk_sky_cloned,2,NULL),

	_DECL_FUNC(qk_sky_Add,3,NULL),

	_DECL_FUNC(qk_sky_SetBandPos,2,NULL),
	_DECL_FUNC(qk_sky_SetBandSize,2,NULL),

	_DECL_FUNC(qk_sky_step,1,NULL),
	_DECL_FUNC(qk_sky_draw,3,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkSky(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkSky_funcs;
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
		_ADD_CLASS_START(QSky,"QkSky",QK_TAG_SKY);
		_CLASS_ADDFUNC(qk_sky_constructor,constructor);
		_CLASS_ADDFUNC(qk_sky_get,_get);
		_CLASS_ADDFUNC(qk_sky_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_sky_typeof,_typeof);
		_CLASS_ADDFUNC(qk_sky_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_sky_cloned,_cloned);

		_CLASS_ADDFUNC(qk_sky_Add,Add);
		_CLASS_ADDFUNC(qk_sky_SetBandPos,SetBandPos);
		_CLASS_ADDFUNC(qk_sky_SetBandSize,SetBandSize);

		_CLASS_ADDFUNC(qk_sky_step,Step);
		_CLASS_ADDFUNC(qk_sky_draw,Draw);

		_ADD_CLASS_END(QSky);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
