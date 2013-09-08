// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_TEXTUREHANDLE_OPENGL_H__
#define __GEL_TEXTURE_TEXTUREHANDLE_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int		TextureHandle;
// - ------------------------------------------------------------------------------------------ - //
TextureHandle new_TextureHandle();
void delete_TextureHandle( TextureHandle Handle );

void bind_TextureHandle( TextureHandle Handle, const st32 TextureUnit = 0 );
void unbind_TextureHandle( TextureHandle = 0, const st32 TextureUnit = 0 );
// - ------------------------------------------------------------------------------------------ - //
inline void Bind( TextureHandle Handle, const st32 TextureUnit = 0 ) {
	bind_TextureHandle( Handle, TextureUnit );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_TEXTUREHANDLE_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
