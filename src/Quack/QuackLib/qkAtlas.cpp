// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a ".Draw" function.
// TODO: Add a ".tostring" function. Returns "[QkAtlas:content/Cube.pod]"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Atlas/Atlas.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Constructor argument (bool) that enables/disables Smoothing. //
_FUNC_POOL_CONSTRUCTOR(GelAtlasPool,qk_atlas_constructor,AtlasPool);
_FUNC_LOAD_POOL(qkAtlasLoad,"QkAtlas",7,"qk_atlas_constructor");

_FUNC_TYPEOF(GelAtlasPool::UID,qk_atlas_typeof,"QkAtlas",7);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_atlas_Draw( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelAtlasPool::UID* AtlasID;
	sq_getinstanceup(v,1,(void**)&AtlasID,0);

	// Check the number of arguments //
	int Top = sq_gettop(v);

	Matrix4x4* Matrix;
	sq_getinstanceup(v,2,(void**)&Matrix,0);
	
	SQInteger Index = 0;
	
	if ( Top >= 3 ) {
		sq_getinteger(v,3,&Index);
	}
	
	Gel::AtlasPool[*AtlasID].Draw( *Matrix, Index );

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_atlas_len( HSQUIRRELVM v ) {
	// Retrieve Data (Pointer) //
	GelAtlasPool::UID* AtlasID;
	sq_getinstanceup(v,1,(void**)&AtlasID,0);

	sq_pushinteger(v,Gel::AtlasPool[*AtlasID].Size());

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkAtlas_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_atlas_constructor,-1,NULL),
	_DECL_FUNC(qk_atlas_typeof,1,NULL),

	_DECL_FUNC(qk_atlas_Draw,-2,NULL),
	_DECL_FUNC(qk_atlas_len,1,NULL),

	_DECL_FUNC(qkAtlasLoad,-1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkAtlas(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkAtlas_funcs;
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
		_ADD_CLASS_START(GelAtlasPool::UID,"QkAtlas",QK_TAG_ATLAS);
		_CLASS_ADDFUNC(qk_atlas_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_atlas_typeof,_typeof);
//		_CLASS_ADDFUNC(qk_atlas_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_atlas_cloned,_cloned);
		_CLASS_ADDFUNC(qk_atlas_Draw,Draw);
		_CLASS_ADDFUNC(qk_atlas_len,len);
		_ADD_CLASS_END(GelAtlasPool::UID);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
