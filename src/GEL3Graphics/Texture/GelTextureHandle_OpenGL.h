// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_GELTEXTUREHANDLE_OPENGL_H__
#define __GEL_TEXTURE_GELTEXTUREHANDLE_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int		GelTextureHandle;
// - ------------------------------------------------------------------------------------------ - //
GelTextureHandle new_GelTextureHandle();
void delete_GelTextureHandle( GelTextureHandle Handle );

void bind_GelTextureHandle( GelTextureHandle Handle, const st32 TextureUnit = 0 );
void unbind_GelTextureHandle( GelTextureHandle = 0, const st32 TextureUnit = 0 );
// - ------------------------------------------------------------------------------------------ - //
inline void Bind( GelTextureHandle Handle, const st32 TextureUnit = 0 ) {
	bind_GelTextureHandle( Handle, TextureUnit );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_GELTEXTUREHANDLE_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
