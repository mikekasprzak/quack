// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a ".Draw" function.
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Font/Font.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_font_constructor( HSQUIRRELVM v ) {
	GelFontPool::UID* Data;
	sq_getinstanceup(v,1,(void**)&Data,0);

	if ( sq_gettop(v) > 1 ) {
		// Do a load //
		const char* FileName;
		sq_getstring(v,2,&FileName);
		
		Log("In: %s", FileName );
		
		if ( FileName ) {
			const char* SearchResult = Gel::Search( FileName );
			*Data = Gel::FontPool.Load( SearchResult );
		}
		else {
			*Data = 0;
		}
	}
	else {
		*Data = 0;	// Dummy UID //
	}

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
_FUNC_TYPEOF(GelFontPool::UID,qk_font_typeof,"QkFont",9);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
SQInteger qkFontLoad( HSQUIRRELVM v ) {
	int ArgCount = sq_gettop(v);

	sq_pushroottable(v);

	int Root = sq_gettop(v);
	
	sq_pushstring(v,"QkFont",6);					// +1 //
	sq_get(v,Root);									// =0 //
	sq_createinstance(v,-1);						// +1 //

	sq_pushstring(v,"qk_font_constructor",-1);		// +1 //
	sq_get(v,Root);									// =0 //

	sq_push(v,-2); // Instance //					// +1 //
	
	// Arguments 2+ //
	for ( int idx = 2; idx <= ArgCount; idx++ ) {
		sq_push(v,idx);  // Arg //					// +1 //
	}
	sq_call(v,ArgCount,false,true);					// -ArgCount //
	
	sq_push(v,-2); // Instance //					// +1 //
	
	// returns a QkFont
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkFont_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_font_constructor,-1,NULL),
	_DECL_FUNC(qk_font_typeof,1,NULL),

	_DECL_FUNC(qkFontLoad,-1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkFont(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkFont_funcs;
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
		_ADD_CLASS_START(GelFontPool::UID,"QkFont",QK_TAG_FONT);
		_CLASS_ADDFUNC(qk_font_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_font_typeof,_typeof);
//		_CLASS_ADDFUNC(qk_font_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_font_cloned,_cloned);
		_ADD_CLASS_END(GelFontPool::UID);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
