// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <GelLayout/GelLayout.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// the constructor //
SQInteger qk_layoutnode_constructor( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayoutNode* LayoutNode;
	sq_getinstanceup(v,1,(void**)&LayoutNode,0);
	
	Log("! THIS SHOULD NEVER BE CONSTRUCTED: QkLayoutNode");
	
	// Write Data //
//	new(Layout) GelLayout();

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// _get metamethod //
SQInteger qk_layoutnode_get( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayoutNode* LayoutNode;
	sq_getinstanceup(v,1,(void**)&LayoutNode,0);
	
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
SQInteger qk_layoutnode_set( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayoutNode* LayoutNode;
	sq_getinstanceup(v,1,(void**)&LayoutNode,0);
	
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
SQInteger qk_layoutnode_tostring( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayoutNode* LayoutNode;
	sq_getinstanceup(v,1,(void**)&LayoutNode,0);
	
	char Text[128];
	sprintf(Text,"[QkLayoutNode:0x%x,?,?]", (int)(st)LayoutNode );
	
	sq_pushstring(v,Text,-1);
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned metamethod //
//SQInteger qk_layoutnode_cloned( HSQUIRRELVM v ) {
//	// Retrieve Data (Pointer) //
//	GelLayoutNode* LayoutNode;
//	sq_getinstanceup(v,1,(void**)&LayoutNode,0);
//
//	// Retrieve Other Data (Pointer) //
//	GelLayoutNode* OtherLayoutNode;
//	sq_getinstanceup(v,2,(void**)&OtherLayoutNode,0);
//	
//	*LayoutNode = *OtherLayoutNode;
//
//	return SQ_VOID;
//}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(GelLayoutNode,qk_layoutnode_typeof,"QkLayoutNode",12);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_layoutnode_SetText(HSQUIRRELVM v) {
	// Retrieve Data (Pointer) //
	GelLayoutNode* Node;
	sq_getinstanceup(v,1,(void**)&Node,0);

	const SQChar* Value;
	sq_getstring(v,2,&Value);

	Node->Data.SetText( Value );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
#define _DECL_FUNC_ALT(sqname,name,nparams,pmask) {_SC(sqname),name,nparams,pmask}
SQRegFunction qkLayoutNode_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	
	_DECL_FUNC(qk_layoutnode_constructor,-1,NULL),
	_DECL_FUNC(qk_layoutnode_get,2,NULL),
	_DECL_FUNC(qk_layoutnode_set,3,NULL),
	_DECL_FUNC(qk_layoutnode_typeof,0,NULL),
	_DECL_FUNC(qk_layoutnode_tostring,1,NULL),
//	_DECL_FUNC(qk_layoutnode_cloned,2,NULL),	

	_DECL_FUNC(qk_layoutnode_SetText,2,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkLayoutNode(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkLayoutNode_funcs;
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
		_ADD_PTRCLASS_START(GelLayoutNode,"QkLayoutNode",QK_TAG_LAYOUTNODE);
		_CLASS_ADDFUNC(qk_layoutnode_constructor,constructor);
		_CLASS_ADDFUNC(qk_layoutnode_get,_get);
		_CLASS_ADDFUNC(qk_layoutnode_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_layoutnode_typeof,_typeof);
		_CLASS_ADDFUNC(qk_layoutnode_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_layoutnode_cloned,_cloned);

		_CLASS_ADDFUNC(qk_layoutnode_SetText,SetText);

		_ADD_CLASS_END(GelLayoutNode);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
