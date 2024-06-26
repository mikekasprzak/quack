// - ------------------------------------------------------------------------------------------ - //
// Typically, any QkTarget's instantiated from Squirrel will be Render Targets. QkTarget.
// Native Targets will usually be requested via some "tell me the screen" call. QkTargetPtr.
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Render/GelTarget.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_target_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);
	
	// Check the number of arguments //
	int Top = sq_gettop(v);

	// Get the Dimensions of the Render Target //
	SQInteger w,h;
	sq_getinteger(v,2,&w);
	sq_getinteger(v,3,&h);

	// Write Data //
	placement_Render_GelTarget( Target, w, h );

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_target_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
	// Return different data depending on requested member //
	if ( MemberName[0] == 'x' ) {
		sq_pushinteger(v,Target->x);			// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'y' ) {
		sq_pushinteger(v,Target->y);			// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'w' ) {
		sq_pushinteger(v,Target->Width);		// +1 //
		return SQ_RETURN;
	}
	else if ( MemberName[0] == 'h' ) {
		sq_pushinteger(v,Target->Height);		// +1 //
		return SQ_RETURN;
	}

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _set metamethod //
SQInteger qk_target_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_target_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);
	
	char Text[128];
	sprintf(Text,"(%i,%i,%i,%i): %f", Target->x,Target->y, Target->Width,Target->Height, Target->GetAspectRatio().ToFloat() );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_target_cloned( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelTarget* Target;
//	sq_getinstanceup(v,1,(void**)&Target,0);
////
////	// Retrieve Other Data (Pointer) //
////	GelColor* OtherColor;
////	sq_getinstanceup(v,2,(void**)&OtherColor,0);
////	
////	*Color = *OtherColor;
//
//	return SQ_VOID;
//}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(GelTarget,qk_target_typeof,"QkTarget",8);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_target_GetAspectRatio( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);
		
	sq_pushfloat(v,Target->GetAspectRatio().ToFloat());
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_target_Bind( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);
	
	Target->Bind( 0 );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_target_BindAsTexture( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Target;
	sq_getinstanceup(v,1,(void**)&Target,0);
	
	// TODO: Allow Layer and Texture Unit Selection //
	Target->BindAsTexture( 0, 0 );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_target_GetRegion( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelTarget* Parent;
	sq_getinstanceup(v,1,(void**)&Parent,0);

	SQInteger x,y,w,h;
	sq_getinteger(v,2,&x);
	sq_getinteger(v,3,&y);
	sq_getinteger(v,4,&w);
	sq_getinteger(v,5,&h);
	
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"QkTarget",-1);		// +1 //
	sq_get(v,-2);						// =0 (-1 then +1) //
	sq_createinstance(v,-1);			// +1 //

	//sq_setinstanceup(v,-1,(void**)Qk::Target[0]);

	GelTarget* Target;
	sq_getinstanceup(v,-1,(void**)&Target,0);

//	placement_Sub_GelTarget( Target, w, h );
	placement_Sub_GelTarget( Target, Parent, x,y, w,h );
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkTarget_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_target_constructor,3,NULL),
	_DECL_FUNC(qk_target_get,2,NULL),
	_DECL_FUNC(qk_target_set,3,NULL),
	_DECL_FUNC(qk_target_typeof,0,NULL),
	_DECL_FUNC(qk_target_tostring,1,NULL),
//	_DECL_FUNC(qk_target_cloned,2,NULL),

	_DECL_FUNC(qk_target_GetAspectRatio,1,NULL),
	_DECL_FUNC(qk_target_Bind,-1,NULL),
	_DECL_FUNC(qk_target_BindAsTexture,-1,NULL),

	_DECL_FUNC(qk_target_GetRegion,5,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkTarget(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkTarget_funcs;
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
		_ADD_CLASS_START(GelTarget,"QkTarget",QK_TAG_TARGET);
		_CLASS_ADDFUNC(qk_target_constructor,constructor);
		_CLASS_ADDFUNC(qk_target_get,_get);
		_CLASS_ADDFUNC(qk_target_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_target_typeof,_typeof);
		_CLASS_ADDFUNC(qk_target_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_target_cloned,_cloned);
		_CLASS_ADDFUNC(qk_target_GetAspectRatio,GetAspectRatio);
		_CLASS_ADDFUNC(qk_target_Bind,Bind);
		_CLASS_ADDFUNC(qk_target_BindAsTexture,BindAsTexture);
		_CLASS_ADDFUNC(qk_target_GetRegion,GetRegion);
		_ADD_CLASS_END(GelTarget);
	}

	{
		_ADD_PTRCLASS_START(GelTarget,"QkTargetPtr",QK_TAG_TARGET);
		_CLASS_ADDFUNC(qk_target_constructor,constructor);
		_CLASS_ADDFUNC(qk_target_get,_get);
		_CLASS_ADDFUNC(qk_target_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_target_typeof,_typeof);
		_CLASS_ADDFUNC(qk_target_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_target_cloned,_cloned);
		_CLASS_ADDFUNC(qk_target_GetAspectRatio,GetAspectRatio);
		_CLASS_ADDFUNC(qk_target_Bind,Bind);
		_CLASS_ADDFUNC(qk_target_BindAsTexture,BindAsTexture);
		_CLASS_ADDFUNC(qk_target_GetRegion,GetRegion);
		_ADD_CLASS_END(GelTarget);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
