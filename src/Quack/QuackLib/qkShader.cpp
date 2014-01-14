// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a ".Draw" function.
// TODO: Add a ".tostring" function. Returns "[QkShader:content/Cube.pod]"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Shader/Shader.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Constructor argument (bool) that enables/disables Smoothing. //
_FUNC_POOL_CONSTRUCTOR(GelShaderPool,qk_shader_constructor,ShaderPool);
_FUNC_LOAD_POOL(qkShaderLoad,"QkShader",8,"qk_shader_constructor");

_FUNC_TYPEOF(GelShaderPool::UID,qk_shader_typeof,"QkShader",8);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkShader_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qk_shader_constructor,-1,NULL),
	_DECL_FUNC(qk_shader_typeof,1,NULL),

	_DECL_FUNC(qkShaderLoad,-1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkShader(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkShader_funcs;
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
		_ADD_CLASS_START(GelShaderPool::UID,"QkShader",QK_TAG_SHADER);
		_CLASS_ADDFUNC(qk_shader_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_shader_typeof,_typeof);
//		_CLASS_ADDFUNC(qk_shader_tostring,_tostring);
//		_CLASS_ADDFUNC(qk_shader_cloned,_cloned);
		_ADD_CLASS_END(GelShaderPool::UID);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
