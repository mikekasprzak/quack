// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a ".Draw" function.
// TODO: Add a ".tostring" function. Returns "[QkFont:content/Fonts/Arial.fnt]"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Font/Font.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Constructor argument (bool) that enables/disables Smoothing. //
_FUNC_POOL_CONSTRUCTOR(GelFontPool,qk_font_constructor,FontPool);
_FUNC_LOAD_POOL(qkFontLoad,"QkFont",6,"qk_font_constructor");

_FUNC_TYPEOF(GelFontPool::UID,qk_font_typeof,"QkFont",6);
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
