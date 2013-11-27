// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Math.h>
#include <Graphics/Graphics.h>
#include <Render/Render.h>
#include <Generate/Generate.h>
#include <Asset/Asset.h>
// - ------------------------------------------------------------------------------------------ - //

// TODO: Texture Class Funcs //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkTextureLoad(HSQUIRRELVM vm ) {
	// returns a QkTexture
	// Wraps a search+load.
	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkTextureBind(HSQUIRRELVM vm ) {
	// Synonym for MyQkTexture.Bind();
	// Arg1 is the TU //
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkTexture_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qkTextureLoad,-1,NULL),
	_DECL_FUNC(qkTextureBind,-1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkTexture(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkTexture_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	// TODO: Class
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
