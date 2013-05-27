// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include "Render_Core.h"
#include "Shader.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	atexit( Exit );
	
	InitShader();
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	ExitShader();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
