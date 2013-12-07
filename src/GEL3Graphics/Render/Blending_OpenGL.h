// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_BLENDING_OPENGL_H__
#define __GEL_RENDER_BLENDING_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnablePremultipliedAlphaBlending() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableAddativeBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelEnableModulationBlending() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_DST_COLOR, GL_ZERO );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelDisableBlending() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_BLENDING_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
