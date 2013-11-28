// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_texture_constructor( HSQUIRRELVM v ) {
	GelTexturePool::UID* Data;
	sq_getinstanceup(v,1,(void**)&Data,0);

	if ( sq_gettop(v) > 1 ) {
		// Do a load //
		const char* FileName;
		sq_getstring(v,2,&FileName);
		
		Log("In: %s", FileName );
		
		if ( FileName ) {
			const char* SearchResult = Gel::Search( FileName );
			*Data = Gel::TexturePool.Load( SearchResult );
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
_FUNC_TYPEOF(GelTexturePool::UID,qk_texture_typeof,"QkTexture",9);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_texture_bind( HSQUIRRELVM v ) {
	GelTexturePool::UID* Data;
	sq_getinstanceup(v,1,(void**)&Data,0);

	if ( Data ) {
		int TextureUnit = 0;
		if ( sq_gettop(v) > 1 ) {
			sq_getinteger(v,2,&TextureUnit);
		}
		
		Gel::TexturePool[*Data].Bind( TextureUnit );
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
SQInteger qkTextureLoad( HSQUIRRELVM v ) {
	int ArgCount = sq_gettop(v);

	sq_pushroottable(v);

	int Root = sq_gettop(v);
	
	sq_pushstring(v,"QkTexture",9);					// +1 //
	sq_get(v,Root);									// =0 //
	sq_createinstance(v,-1);						// +1 //

	sq_pushstring(v,"qk_texture_constructor",-1);	// +1 //
	sq_get(v,Root);									// =0 //

	sq_push(v,-2); // Instance //					// +1 //
	
	// Arguments 2+ //
	for ( int idx = 2; idx <= ArgCount; idx++ ) {
		sq_push(v,idx);  // Arg //					// +1 //
	}
	sq_call(v,ArgCount,false,true);					// -ArgCount //
	
	sq_push(v,-2); // Instance //					// +1 //
	
	// returns a QkTexture
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkTextureBind( HSQUIRRELVM v ) {
/*	// Synonym for MyQkTexture.Bind();
	int ArgCount = sq_gettop(v);

	sq_pushroottable(v);

	int Root = sq_gettop(v);

	sq_pushstring(v,"qk_texture_bind",-1);			// +1 //
	sq_get(v,Root);									// =0 //
	
	// Arguments 2+ //
	for ( int idx = 2; idx <= ArgCount; idx++ ) {
		sq_push(v,idx);  // Arg //					// +1 //
	}
	sq_call(v,ArgCount-1,false,true);				// -ArgCount //

	return SQ_VOID;	
*/

	// Simpler version. Remove redundant stack item, and call directly. //
	sq_remove(v,1);
	return qk_texture_bind(v);
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkTexture_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_texture_constructor,-1,NULL),
	_DECL_FUNC(qk_texture_typeof,1,NULL),
	_DECL_FUNC(qk_texture_bind,-1,NULL),

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
	
	int Root = sq_gettop(v); // root table pos //
	{
		_ADD_CLASS_START(GelTexturePool::UID,"QkTexture",QK_TAG_TEXTURE);
		_CLASS_ADDFUNC(qk_texture_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_texture_typeof,_typeof);
//		_CLASS_ADDFUNC(qk_texture_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_texture_cloned,_cloned);
		_CLASS_ADDFUNC(qk_texture_bind,Bind);
		_ADD_CLASS_END(GelTexturePool::UID);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
