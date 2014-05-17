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
	
	if ( MemberName[1] == 0 ) {
		// Return different data depending on requested member //
		if ( MemberName[0] == 'x' ) {
			sq_pushfloat(v, LayoutNode->BaseRegion.Pos.x);		// +1 //
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'y' ) {
			sq_pushfloat(v, LayoutNode->BaseRegion.Pos.y);		// +1 //
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'w' ) {
			sq_pushfloat(v, LayoutNode->BaseRegion.Shape.x);	// +1 //
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'h' ) {
			sq_pushfloat(v, LayoutNode->BaseRegion.Shape.y);	// +1 //
			return SQ_RETURN;
		}
	}

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

	if ( MemberName[1] == 0 ) {
		// Get the value //
		SQFloat Value;
		sq_getfloat(v,3,&Value);
		
		// Return different data depending on requested member //
		if ( MemberName[0] == 'x' ) {
			LayoutNode->BaseRegion.Pos.x = Value;
			LayoutNode->CopyBases();
			LayoutNode->Update();
			sq_pushinteger( v, Value );
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'y' ) {
			LayoutNode->BaseRegion.Pos.y = Value;
			LayoutNode->CopyBases();
			LayoutNode->Update();
			sq_pushinteger( v, Value );
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'w' ) {
			LayoutNode->BaseRegion.Shape.x = Value;
			LayoutNode->CopyBases();
			LayoutNode->Update();
			sq_pushinteger( v, Value );
			return SQ_RETURN;
		}
		else if ( MemberName[0] == 'h' ) {
			LayoutNode->BaseRegion.Shape.y = Value;
			LayoutNode->CopyBases();
			LayoutNode->Update();
			sq_pushinteger( v, Value );
			return SQ_RETURN;
		}
	}

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
#define __FUNC_START_SETTEXT( _FUNCNAME_ ) \
SQInteger _FUNCNAME_(HSQUIRRELVM v) { \
	GelLayoutNode* Node; \
	sq_getinstanceup(v,1,(void**)&Node,0); \
	\
	const SQChar* Value; \
	sq_getstring(v,2,&Value);
// - ------------------------------------------------------------------------------------------ - //
#define __FUNC_END_SET() \
	return SQ_VOID; \
}
// - ------------------------------------------------------------------------------------------ - //
#define __FUNC_START_SETINTEGER( _FUNCNAME_ ) \
SQInteger _FUNCNAME_(HSQUIRRELVM v) { \
	GelLayoutNode* Node; \
	sq_getinstanceup(v,1,(void**)&Node,0); \
	\
	SQInteger Value; \
	sq_getinteger(v,2,&Value);
// - ------------------------------------------------------------------------------------------ - //
#define __FUNC_START_SETFLOAT( _FUNCNAME_ ) \
SQInteger _FUNCNAME_(HSQUIRRELVM v) { \
	GelLayoutNode* Node; \
	sq_getinstanceup(v,1,(void**)&Node,0); \
	\
	SQFloat Value; \
	sq_getfloat(v,2,&Value);
// - ------------------------------------------------------------------------------------------ - //
#define __FUNC_START_SETINSTANCE( _FUNCNAME_, _CLASSNAME_ ) \
SQInteger _FUNCNAME_(HSQUIRRELVM v) { \
	GelLayoutNode* Node; \
	sq_getinstanceup(v,1,(void**)&Node,0); \
	\
	_CLASSNAME_* Value; \
	sq_getinstanceup(v,2,(void**)&Value,0);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETTEXT( qk_layoutnode_SetName )
	Node->SetName( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETTEXT( qk_layoutnode_SetText )
	Node->Data.SetText( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETTEXT( qk_layoutnode_SetArt )
	Node->Data.SetArt( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETTEXT( qk_layoutnode_SetFont )
	Node->Data.SetFont( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETINTEGER( qk_layoutnode_SetFlags )
	Node->SetFlags( Value );
	Node->Update();
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETINTEGER( qk_layoutnode_SetType )
	Node->Data.SetType( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETINTEGER( qk_layoutnode_SetFontAlign )
	Node->Data.SetFontAlign( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETFLOAT( qk_layoutnode_SetFontSize )
	Node->Data.SetFontSize( Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETFLOAT( qk_layoutnode_SetScale )
	SQFloat Value2; \
	sq_getfloat(v,3,&Value2);

	Node->Data.SetScale( Value, Value2 );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
__FUNC_START_SETINSTANCE( qk_layoutnode_SetColor, GelColor )
	Node->Data.SetColor( *Value );
__FUNC_END_SET()
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#undef __FUNC_START_SETTEXT
#undef __FUNC_END_SET
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

	_DECL_FUNC(qk_layoutnode_SetName,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetText,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetArt,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetFont,2,NULL),

	_DECL_FUNC(qk_layoutnode_SetFlags,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetType,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetFontAlign,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetFontSize,2,NULL),
	
	_DECL_FUNC(qk_layoutnode_SetColor,2,NULL),
	_DECL_FUNC(qk_layoutnode_SetScale,3,NULL),

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

		_CLASS_ADDFUNC(qk_layoutnode_SetName,SetName);
		_CLASS_ADDFUNC(qk_layoutnode_SetText,SetText);
		_CLASS_ADDFUNC(qk_layoutnode_SetArt,SetArt);
		_CLASS_ADDFUNC(qk_layoutnode_SetFont,SetFont);

		_CLASS_ADDFUNC(qk_layoutnode_SetFlags,SetFlags);
		_CLASS_ADDFUNC(qk_layoutnode_SetType,SetType);
		_CLASS_ADDFUNC(qk_layoutnode_SetFontAlign,SetFontAlign);
		_CLASS_ADDFUNC(qk_layoutnode_SetFontSize,SetFontSize);

		_CLASS_ADDFUNC(qk_layoutnode_SetColor,SetColor);
		_CLASS_ADDFUNC(qk_layoutnode_SetScale,SetScale);

		_ADD_CLASS_END(GelLayoutNode);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
