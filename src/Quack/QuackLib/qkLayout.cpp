// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <GelLayout/GelLayout.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_layout_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);
	
	// Write Data //
	new(Layout) GelLayout();

	Layout->Root.SetPos(-64,-64);
	Layout->Root.SetShape(128,128);

//	Layout->Root.AddChild( GLAY_BOTTOM | GLAY_CENTER );
//	Layout->Root.Child.back().SetShape(32,32);

//	Layout->Root.Child.back().AddChild( GLAY_DEFAULT, GelLayoutNode( Gel::GLO_IMAGE, "ItemIcons.atlas:IconFish" ) );
//	Layout->Root.Child.back().Child.back().SetShape(2,2);

	Layout->Root.AddChild( GLAY_TOP | GLAY_CENTER, GelLayoutNode( Gel::GLO_BOX ) );
	Layout->Root.Child.back().SetShape(256+128,64+16);
	Layout->Root.Child.back().Data.SetColor( GEL_RGBA(32,32,32,128) );

	Layout->Root.Child.back().AddChild( GLAY_DEFAULT, GelLayoutNode( Gel::GLO_TEXT, "ÔQ Eat This!" ) );
	Layout->Root.Child.back().Child.back().Data.SetFont( "Delius.fnt" );
	Layout->Root.Child.back().Child.back().Data.SetFontSize( 64 );
	//Layout->Root.Child.back().Child.back().Data.SetFontAlign( GEL_ALIGN_BASELINE | GEL_ALIGN_RIGHT );
	
	
	Layout->Update();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_layout_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);
	
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
SQInteger qk_layout_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);
	
	// Get the requested member //
	const char* MemberName;
	sq_getstring(v,2,&MemberName);

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

	// Throw null on member not found //
	sq_pushnull(v);				// +1 //
	return sq_throwobject(v);	// -1 //
}
// - ------------------------------------------------------------------------------------------ - //
// _tostring metamethod //
SQInteger qk_layout_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);
	
	char Text[128];
	sprintf(Text,"[QkLayout:0x%x,?,?]", (int)(st)Layout );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_layout_cloned( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelLayout* Layout;
//	sq_getinstanceup(v,1,(void**)&Layout,0);
//
//	// Retrieve Other Data (Pointer) //
//	GelLayout* OtherLayout;
//	sq_getinstanceup(v,2,(void**)&OtherLayout,0);
//	
//	*Layout = *OtherLayout;
//
//	return SQ_VOID;
//}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(GelLayout,qk_layout_typeof,"QkLayout",8);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//SQInteger qk_layout_step( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	QK::GelLayout* Layout;
//	sq_getinstanceup(v,1,(void**)&Layout,0);
//
//	// Do Step //	
//	Layout->Step();	
//	
//	// Finished //
//	return SQ_VOID;
//}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_layout_draw( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);
	
	// Need a View and a Matrix //
	Rect2D* View;
	sq_getinstanceup(v,2,(void**)&View,NULL);
	
	Matrix4x4* Mat;
	sq_getinstanceup(v,3,(void**)&Mat,NULL);

	// Do Draw //	
	Layout->Draw(/* *View,*/ *Mat);	
		
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkLayout_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_layout_constructor,-1,NULL),
	_DECL_FUNC(qk_layout_get,2,NULL),
	_DECL_FUNC(qk_layout_set,3,NULL),
	_DECL_FUNC(qk_layout_typeof,0,NULL),
	_DECL_FUNC(qk_layout_tostring,1,NULL),
//	_DECL_FUNC(qk_layout_cloned,2,NULL),	

//	_DECL_FUNC(qk_layout_step,1,NULL),
	_DECL_FUNC(qk_layout_draw,3,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkLayout(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkLayout_funcs;
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
		_ADD_CLASS_START(GelLayout,"QkLayout",QK_TAG_LAYOUT);
		_CLASS_ADDFUNC(qk_layout_constructor,constructor);
		_CLASS_ADDFUNC(qk_layout_get,_get);
		_CLASS_ADDFUNC(qk_layout_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_layout_typeof,_typeof);
		_CLASS_ADDFUNC(qk_layout_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_layout_cloned,_cloned);

//		_CLASS_ADDFUNC(qk_layout_step,Step);
		_CLASS_ADDFUNC(qk_layout_draw,Draw);

		_ADD_CLASS_END(GelLayout);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
