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
	
	if ( sq_gettop(v) > 1 ) {
		extern SQInteger qk_layout_populate( HSQUIRRELVM v );
		qk_layout_populate( v );
	}

//	Layout->Root.SetPos(-64,-64);
//	Layout->Root.SetShape(128,128);

//	Layout->Root.AddChild( GLAY_BOTTOM | GLAY_CENTER );
//	Layout->Root.Child.back().SetShape(32,32);
//	Layout->Root.Child.back().AddChild( GLAY_DEFAULT, GelLayoutNodeData( Gel::GLO_IMAGE, "ItemIcons.atlas:IconFish" ) );
//	Layout->Root.Child.back().Child.back().SetShape(2,2);

	// Minimum Spacing: 1.25 to avoid overlap //
	//
	
//	Layout->Root.AddChild( GLAY_MIDDLE | GLAY_CENTER, GelLayoutNodeData( Gel::GLO_BOX ) );
//	Layout->Root.Child.back().SetShape(256+128,64+0);//+16);
//	Layout->Root.Child.back().Data.SetColor( GEL_RGBA(32,32,32,128) );
//
//	Layout->Root.AddChild( GLAY_MIDDLE | GLAY_CENTER, GelLayoutNodeData( Gel::GLO_BOX ) );
//	Layout->Root.Child.back().SetShape(256+128,64+16);//+16);
//	Layout->Root.Child.back().Data.SetColor( GEL_RGBA(32,32,32,128) );
//
//	Layout->Root.AddChild( GLAY_MIDDLE | GLAY_CENTER, GelLayoutNodeData( Gel::GLO_BOX ) );
//	Layout->Root.Child.back().SetShape(256+128,64+32);//+16);
//	Layout->Root.Child.back().Data.SetColor( GEL_RGBA(32,32,32,128) );
//
//	Layout->Root.Child.back().AddChild( GLAY_DEFAULT, GelLayoutNodeData( Gel::GLO_TEXT, "\xD5y Eat This!" ) );
//	Layout->Root.Child.back().Child.back().Data.SetFont( "DeliusSwash.fnt" );
//	Layout->Root.Child.back().Child.back().Data.SetFontSize( 64 );
//	//Layout->Root.Child.back().Child.back().Data.SetFontAlign( GEL_ALIGN_BASELINE | GEL_ALIGN_RIGHT );
//	
//	
//	Layout->Update();

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
//	sq_getfloat(v,3,&Value);
	
//	// Return different data depending on requested member //
//	if ( MemberName[0] == 'x' ) {
//		*Color = GEL_SET_R( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'y' ) {
//		*Color = GEL_SET_G( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'w' ) {
//		*Color = GEL_SET_B( *Color, GEL_CLAMP_COLOR_COMPONENT(Value) );
//		sq_pushinteger( v, Value );
//		return SQ_RETURN;
//	}
//	else if ( MemberName[0] == 'h' ) {
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
SQInteger qk_layout_populate_body( HSQUIRRELVM v, GelLayoutNode* Node ) {
	const int Value = -1;
	const int Key = -2;

	// Table is already on the Stack, so push a 'null iterator' //
	sq_pushnull(v);
			
	while( SQ_SUCCEEDED( sq_next(v,-2) ) ) {
		const SQChar* KeyStr;
		sq_getstring(v,Key,&KeyStr);
		
		// Base-Node Data //
		if ( strcmp( KeyStr, "Width") == 0 ) {
			sq_getfloat(v,Value,&Node->BaseRegion.Shape.x);
		}
		else if ( strcmp( KeyStr, "Height") == 0 ) {
			sq_getfloat(v,Value,&Node->BaseRegion.Shape.y);
		}
		else if ( strcmp( KeyStr, "x") == 0 ) {
			sq_getfloat(v,Value,&Node->BaseRegion.Pos.x);
		}
		else if ( strcmp( KeyStr, "y") == 0 ) {
			sq_getfloat(v,Value,&Node->BaseRegion.Pos.y);
		}
		else if ( strcmp( KeyStr, "Align") == 0 ) {
			// Wrap in function ? //
			sq_getinteger(v,Value,(SQInteger*)&Node->Align);
		}
		else if ( strcmp( KeyStr, "Visible") == 0 ) {
			SQBool Visible;
			sq_getbool(v,Value,(SQBool*)&Visible);

			Node->Data.SetVisible( Visible );
		}
		else if ( strcmp( KeyStr, "Name") == 0 ) {
			const SQChar* ValueStr;
			sq_getstring(v,Value,&ValueStr);
			
			Node->SetName( ValueStr );
		}

		else if ( strcmp( KeyStr, "ClipX") == 0 ) {
			SQInteger RetValue;
			sq_getinteger(v,Value,(SQInteger*)&RetValue);
			Node->Data.ClipX = RetValue;
		}
		else if ( strcmp( KeyStr, "ClipY") == 0 ) {
			SQInteger RetValue;
			sq_getinteger(v,Value,(SQInteger*)&RetValue);
			Node->Data.ClipY = RetValue;
		}
		else if ( strcmp( KeyStr, "ClipW") == 0 ) {
			SQInteger RetValue;
			sq_getinteger(v,Value,(SQInteger*)&RetValue);
			Node->Data.ClipW = RetValue;
		}
		else if ( strcmp( KeyStr, "ClipH") == 0 ) {
			SQInteger RetValue;
			sq_getinteger(v,Value,(SQInteger*)&RetValue);
			Node->Data.ClipH = RetValue;
		}
		
		// Data //
		else if ( strcmp( KeyStr, "Type") == 0 ) {
			// Wrap in function ? //
			sq_getinteger(v,Value,(SQInteger*)&Node->Data.Type);
		}		
		else if ( strcmp( KeyStr, "Text") == 0 ) {
			const SQChar* ValueStr;
			sq_getstring(v,Value,&ValueStr);
			
			Node->Data.SetText( ValueStr );
		}
		else if ( strcmp( KeyStr, "Art") == 0 ) {
			const SQChar* ValueStr;
			sq_getstring(v,Value,&ValueStr);
			
			Node->Data.SetArt( ValueStr );
		}
		else if ( strcmp( KeyStr, "Font") == 0 ) {
			const SQChar* ValueStr;
			sq_getstring(v,Value,&ValueStr);
			
			Node->Data.SetFont( ValueStr );
		}
		else if ( strcmp( KeyStr, "FontSize") == 0 ) {
			// Wrap in function ? //
			sq_getfloat(v,Value,&Node->Data.FontSize);
		}
		else if ( strcmp( KeyStr, "FontAlign") == 0 ) {
			// Wrap in function ? //
			sq_getinteger(v,Value,(SQInteger*)&Node->Data.FontAlign);
		}
		else if ( strcmp( KeyStr, "Color") == 0 ) {
			GelColor* Color;
			sq_getinstanceup(v,Value,(void**)&Color,0);
			
			Node->Data.SetColor( *Color );
		}
	
		// Children //
		else if ( strcmp( KeyStr, "Child") == 0 ) {
			int Type = sq_gettype(v,Value);
			if ( Type == OT_ARRAY ) {
				// The top of the stack (Value) holds the array //
				
				sq_pushnull(v); // Push our Null Iterator on to the stack, so we can loop
				
				while( SQ_SUCCEEDED( sq_next(v,-2) ) ) {
					SQInteger KeyInt;
					sq_getinteger(v,Key,&KeyInt);
					
					qk_layout_populate_body( v, &Node->AddChild() );
					
					sq_pop(v,2); // Pop old key and value before the next iteration
				}

				sq_pop(v,1); // Pops the Null Iterator
			}
			else {
				Log("! Child is not an array !");
			}	
		}
		
		sq_pop(v,2); // Pop old key and value before the next iteration
	}

	sq_pop(v,1); // Pops the null iterator
	
	// Finished, so load what we need to load //
	Node->Data.PostLoad();
}
// - ------------------------------------------------------------------------------------------ - //
// This Function will never be called alone. It will be called by other methods. //
SQInteger qk_layout_populate( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);
	
	const int Root = 2;

	const int Value = -1;
	const int Key = -2;

	int Type = sq_gettype(v,Root);
	if ( Type == OT_TABLE ) {
		GelLayoutNode* Node = &Layout->Root;
		
		qk_layout_populate_body( v, Node );
	
		Layout->Update();
	}
	else {
		Log("! Invalid Table for Layout Import !");
	}

	// Finished //
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_layout_find(HSQUIRRELVM v) {
	// Retrieve Data (Pointer) //
	GelLayout* Layout;
	sq_getinstanceup(v,1,(void**)&Layout,0);

	const SQChar* Name;
	sq_getstring(v,2,&Name);

	GelLayoutNode* Ret = Layout->Find( Name );

	if ( Ret ) {
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"QkLayoutNode",-1);	// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_createinstance(v,-1);			// +1 //
	
		sq_setinstanceup(v,-1,(void**)Ret);
	}
	else {
		sq_pushnull(v);
	}

	return SQ_RETURN;
}
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

	_DECL_FUNC(qk_layout_find,2,NULL),

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

		_CLASS_ADDFUNC(qk_layout_find,Find);

//		_CLASS_ADDFUNC(qk_layout_step,Step);
		_CLASS_ADDFUNC(qk_layout_draw,Draw);

		_ADD_CLASS_END(GelLayout);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
