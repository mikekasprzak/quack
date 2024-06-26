// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SHADER_GELSHADERPOOL_H__
#define __GEL_SHADER_GELSHADERPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelShader.h"
// - ------------------------------------------------------------------------------------------ - //
class GelShaderPool: public GelPool<GelShader> {
public:
	_GELPOOL_LOAD_FUNC()
	_GELPOOL_LOAD_BODY("Shader",GelShader)
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SHADER_GELSHADERPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
