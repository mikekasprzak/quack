// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_RENDER_BLENDING_OPENGL_H__
#define __GEL2_RENDER_BLENDING_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL2.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
inline void EnableAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
inline void EnablePremultipliedAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
inline void EnableAddativeBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
inline void EnableModulationBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_DST_COLOR, GL_ZERO );
}
// - ------------------------------------------------------------------------------------------ - //
inline void DisableBlending() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_RENDER_BLENDING_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
