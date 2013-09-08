// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include "TextureHandle_OpenGL.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
TextureHandle new_TextureHandle() {
	TextureHandle Handle;
	glGenTextures( 1, &Handle );
	return Handle;
}
// - ------------------------------------------------------------------------------------------ - //
void delete_TextureHandle( TextureHandle Handle ) {
	glDeleteTextures( 1, (const GLuint*)&Handle );
}
// - ------------------------------------------------------------------------------------------ - //
void bind_TextureHandle( TextureHandle Handle, const st32 TextureUnit ) {
	glActiveTexture( GL_TEXTURE0 + TextureUnit );
	glBindTexture( GL_TEXTURE_2D, Handle );
}
// - ------------------------------------------------------------------------------------------ - //
// Rarely Used. Alternatively, just bund another texture //
void unbind_TextureHandle( TextureHandle, const st32 TextureUnit ) {
	glActiveTexture( GL_TEXTURE0 + TextureUnit );
	glBindTexture( GL_TEXTURE_2D, 0 );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
