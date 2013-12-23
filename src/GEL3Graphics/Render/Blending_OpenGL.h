// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_BLENDING_OPENGL_H__
#define __GEL_RENDER_BLENDING_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	BLEND_SRC_ALPHA = 0x1,
	BLEND_PREMULTIPLIED_ALPHA = 0x2,
	BLEND_ADDATIVE = 0x4,
	BLEND_MODULATION = 0x8,
	
	BLEND_MODES	= 0xFFFF,
	
	BLEND_ENABLE = 0x10000
};

extern int BlendState;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
inline void _gelBlendingEnable() {
	if ( !(Gel::BlendState & Gel::BLEND_ENABLE) )
		glEnable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //
inline void _gelBlendingDisable() {
	if ( (Gel::BlendState & Gel::BLEND_ENABLE) )
		glDisable( GL_BLEND );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnableSourceAlpha() {
	_gelBlendingEnable();
	if ( (Gel::BlendState & Gel::BLEND_MODES) != Gel::BLEND_SRC_ALPHA )
		glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	
	Gel::BlendState = Gel::BLEND_SRC_ALPHA | Gel::BLEND_ENABLE;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnablePremultipliedAlpha() {
	_gelBlendingEnable();
	if ( (Gel::BlendState & Gel::BLEND_MODES) != Gel::BLEND_PREMULTIPLIED_ALPHA )
		glBlendFunc( GL_ONE, GL_ONE_MINUS_SRC_ALPHA );

	Gel::BlendState = Gel::BLEND_PREMULTIPLIED_ALPHA | Gel::BLEND_ENABLE;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnableAddative() {
	_gelBlendingEnable();
	if ( (Gel::BlendState & Gel::BLEND_MODES) != Gel::BLEND_ADDATIVE )
		glBlendFunc( GL_SRC_ALPHA, GL_ONE );

	Gel::BlendState = Gel::BLEND_ADDATIVE | Gel::BLEND_ENABLE;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnableModulation() {
	_gelBlendingEnable();
	if ( (Gel::BlendState & Gel::BLEND_MODES) != Gel::BLEND_MODULATION )
		glBlendFunc( GL_DST_COLOR, GL_ZERO );

	Gel::BlendState = Gel::BLEND_MODULATION | Gel::BLEND_ENABLE;
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingEnable() {
	gelBlendingEnablePremultipliedAlpha();
}
// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingDisable() {
	_gelBlendingDisable();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelBlendingInit() {
	Gel::BlendState = 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_BLENDING_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
