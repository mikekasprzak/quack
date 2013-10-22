// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include "Render_Core.h"
#include "Shader.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
void InitRender() {
	atexit( ExitRender );
	
	InitShader();
}
// - ------------------------------------------------------------------------------------------ - //
void ExitRender() {
	ExitShader();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //