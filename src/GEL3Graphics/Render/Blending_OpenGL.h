// - ------------------------------------------------------------------------------------------ - //
// TODO: Cache GL_BLEND state and Function //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_BLENDING_OPENGL_H__
#define __GEL_RENDER_BLENDING_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnableSourceAlpha() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnablePremultipliedAlpha() {
	glEnable( GL_BLEND );
	glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnableAddative() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnableModulation() {
	glEnable( GL_BLEND );
    glBlendFunc( GL_DST_COLOR, GL_ZERO );
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnable() {
	gelBlendingEnablePremultipliedAlpha();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingDisable() {
	glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_BLENDING_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
