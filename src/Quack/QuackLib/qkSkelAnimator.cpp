// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Skel/Skel.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_skelanimator_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);
	
	// Check the number of arguments //
	int Top = sq_gettop(v);

	//new(GelSkelAnimator,SkelAnimator);
	SkelAnimator->_Constructor();

	if ( Top > 1 ) {
		const char* SkelFile;
		sq_getstring(v,2,&SkelFile);
	
		SkelAnimator->Load( Gel::SkelPool.Load( SkelFile ) );
	}
	
	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
//SQInteger qk_skelanimator_get( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelSkelAnimator* SkelAnimator;
//	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);
//	
//	// Get the requested member //
//	const char* MemberName;
//	sq_getstring(v,2,&MemberName);
//	
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
//
//	// Throw null on member not found //
//	sq_pushnull(v);				// +1 //
//	return sq_throwobject(v);	// -1 //
//}
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
//	// Get the value //
//	SQInteger Value;
//	sq_getinteger(v,3,&Value);
//	
//	// Return different data depending on requested member //
//	if ( MemberName[0] == 'r' ) {
//		*Color = GEL_SET_R( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
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
//
//	// Throw null on member not found //
//	sq_pushnull(v);				// +1 //
//	return sq_throwobject(v);	// -1 //
//}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_skelanimator_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);
	
	// (RRR,GGG,BBB,AAA) //
//	char Text[2 + 3+1 + 3+1 + 3+1 + 3 + 1];
//	sprintf(Text,"(%i,%i,%i,%i)", GEL_GET_R(*Color), GEL_GET_G(*Color), GEL_GET_B(*Color), GEL_GET_A(*Color) );
//	
//	sq_pushstring(v,Text,-1);

	sq_pushstring(v,"SkelAnimator (TODO: this)",-1);
		
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
SQInteger qk_skelanimator_cloned( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Retrieve Other Data (Pointer) //
	GelSkelAnimator* OtherSkelAnimator;
	sq_getinstanceup(v,2,(void**)&OtherSkelAnimator,0);
	
	*SkelAnimator = *OtherSkelAnimator;

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(GelSkelAnimator,qk_skelanimator_typeof,"QkSkelAnimator",14);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_Step( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	//int Top = sq_gettop(v);
	
	SkelAnimator->Step();

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_Draw( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	//int Top = sq_gettop(v);

	Matrix4x4* Matrix;
	sq_getinstanceup(v,2,(void**)&Matrix,0);
	
//	Log( "MAT: %x", Matrix );
	
	SkelAnimator->Draw( *Matrix );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_Set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	SQInteger TrackIndex = 0;
	sq_getinteger(v,2,&TrackIndex);

	const char* AnimName;
	sq_getstring(v,3,&AnimName);
	
	SQBool Loop = SQTrue;
	if ( Top >= 4 ) {
		sq_getbool(v,4,&Loop);
	}
	
	SkelAnimator->Set( TrackIndex, AnimName, Loop );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_Force( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	SQInteger TrackIndex = 0;
	sq_getinteger(v,2,&TrackIndex);

	const char* AnimName;
	sq_getstring(v,3,&AnimName);

	SQBool Loop = SQTrue;
	if ( Top >= 4 ) {
		sq_getbool(v,4,&Loop);
	}
	
	SkelAnimator->Force( TrackIndex, AnimName, Loop );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_Add( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	SQInteger TrackIndex = 0;
	sq_getinteger(v,2,&TrackIndex);

	const char* AnimName;
	sq_getstring(v,3,&AnimName);

	SQBool Loop = SQTrue;
	if ( Top >= 4 ) {
		sq_getbool(v,4,&Loop);
	}

	SQFloat Delay = 0.0f;
	if ( Top >= 5 ) {
		sq_getfloat(v,5,&Delay);
	}
	
	SkelAnimator->Add( TrackIndex, AnimName, Loop, Delay );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_SetFlips( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	SQBool XFlip = SQFalse;
	SQBool YFlip = SQFalse;
	
	if ( Top >= 2 ) {
		sq_getbool(v,2,&XFlip);
	}
	if ( Top >= 3 ) {
		sq_getbool(v,3,&YFlip);
	}
	
	SkelAnimator->SetFlips( XFlip, YFlip );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_SetColor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	GelColor* Color;
	sq_getinstanceup(v,2,(void**)&Color,0);
	
	SkelAnimator->SetColor( *Color );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_skelanimator_Clear( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelSkelAnimator* SkelAnimator;
	sq_getinstanceup(v,1,(void**)&SkelAnimator,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	if ( Top >= 2 ) {
		SQInteger TrackIndex = 0;
		sq_getinteger(v,2,&TrackIndex);
	
		SkelAnimator->Clear( TrackIndex );
	}
	else {
		SkelAnimator->Clear();
	}		

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkSkelAnimator_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_skelanimator_constructor,-1,NULL),
//	_DECL_FUNC(qk_skelanimator_get,2,NULL),
//	_DECL_FUNC(qk_skelanimator_set,3,NULL),
	_DECL_FUNC(qk_skelanimator_typeof,0,NULL),
	_DECL_FUNC(qk_skelanimator_tostring,1,NULL),
	_DECL_FUNC(qk_skelanimator_cloned,2,NULL),
	
	_DECL_FUNC(qk_skelanimator_Step,1,NULL),
	_DECL_FUNC(qk_skelanimator_Draw,2,NULL),

	_DECL_FUNC(qk_skelanimator_Set,-3,NULL),
	_DECL_FUNC(qk_skelanimator_Force,-3,NULL),
	_DECL_FUNC(qk_skelanimator_Add,-3,NULL),
	_DECL_FUNC(qk_skelanimator_SetFlips,-2,NULL),
	_DECL_FUNC(qk_skelanimator_SetColor,2,NULL),
	_DECL_FUNC(qk_skelanimator_Clear,-1,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkSkelAnimator(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkSkelAnimator_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	// Regular Version //
	int Root = sq_gettop(v); // root table pos //
	{
		_ADD_CLASS_START(GelSkelAnimator,"QkSkelAnimator",QK_TAG_SKELANIMATOR);
		_CLASS_ADDFUNC(qk_skelanimator_constructor,constructor);
//		_CLASS_ADDFUNC(qk_skelanimator_get,_get);
//		_CLASS_ADDFUNC(qk_skelanimator_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_skelanimator_typeof,_typeof);
		_CLASS_ADDFUNC(qk_skelanimator_tostring,_tostring);
		_CLASS_ADDFUNC(qk_skelanimator_cloned,_cloned);
		_CLASS_ADDFUNC(qk_skelanimator_Step,Step);
		_CLASS_ADDFUNC(qk_skelanimator_Draw,Draw);

		_CLASS_ADDFUNC(qk_skelanimator_Set,Set);
		_CLASS_ADDFUNC(qk_skelanimator_Force,Force);
		_CLASS_ADDFUNC(qk_skelanimator_Add,Add);
		_CLASS_ADDFUNC(qk_skelanimator_SetFlips,SetFlips);
		_CLASS_ADDFUNC(qk_skelanimator_SetColor,SetColor);
		_CLASS_ADDFUNC(qk_skelanimator_Clear,Clear);
		_ADD_CLASS_END(GelSkelAnimator);
	}

	// Pointer Version //
	{
		_ADD_PTRCLASS_START(GelSkelAnimator,"QkSkelAnimatorPtr",QK_TAG_SKELANIMATOR);
		_CLASS_ADDFUNC(qk_skelanimator_constructor,constructor);
//		_CLASS_ADDFUNC(qk_skelanimator_get,_get);
//		_CLASS_ADDFUNC(qk_skelanimator_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_skelanimator_typeof,_typeof);
		_CLASS_ADDFUNC(qk_skelanimator_tostring,_tostring);
		_CLASS_ADDFUNC(qk_skelanimator_cloned,_cloned);
		_CLASS_ADDFUNC(qk_skelanimator_Step,Step);
		_CLASS_ADDFUNC(qk_skelanimator_Draw,Draw);

		_CLASS_ADDFUNC(qk_skelanimator_Set,Set);
		_CLASS_ADDFUNC(qk_skelanimator_Force,Force);
		_CLASS_ADDFUNC(qk_skelanimator_Add,Add);
		_CLASS_ADDFUNC(qk_skelanimator_SetFlips,SetFlips);
		_CLASS_ADDFUNC(qk_skelanimator_SetColor,SetColor);
		_CLASS_ADDFUNC(qk_skelanimator_Clear,Clear);
		_ADD_CLASS_END(GelSkelAnimator);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
