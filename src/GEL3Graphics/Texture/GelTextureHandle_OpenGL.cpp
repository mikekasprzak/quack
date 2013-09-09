// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelTextureHandle_OpenGL.h"
// - ------------------------------------------------------------------------------------------ - //
GelTextureHandle new_GelTextureHandle() {
	GelTextureHandle Handle;
	glGenTextures( 1, &Handle );
	return Handle;
}
// - ------------------------------------------------------------------------------------------ - //
void delete_GelTextureHandle( GelTextureHandle Handle ) {
	glDeleteTextures( 1, (const GLuint*)&Handle );
}
// - ------------------------------------------------------------------------------------------ - //
void bind_GelTextureHandle( GelTextureHandle Handle, const st32 TextureUnit ) {
	glActiveTexture( GL_TEXTURE0 + TextureUnit );
	glBindTexture( GL_TEXTURE_2D, Handle );
}
// - ------------------------------------------------------------------------------------------ - //
// Rarely Used. Alternatively, just bund another texture //
void unbind_GelTextureHandle( GelTextureHandle, const st32 TextureUnit ) {
	glActiveTexture( GL_TEXTURE0 + TextureUnit );
	glBindTexture( GL_TEXTURE_2D, 0 );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
