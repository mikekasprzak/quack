// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL_2_FAMILY)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelTextureHandle_OpenGL.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
	// OpenGL Specific, for eliminating redundant calls //
	st32 ActiveTextureUnit = 0;
	GelTextureHandle ActiveTexture = 0;
};
// - ------------------------------------------------------------------------------------------ - //
void init_GelTextureHandle() {
	Gel::ActiveTextureUnit = 0;
	glActiveTexture( GL_TEXTURE0 + Gel::ActiveTextureUnit );
	Gel::ActiveTexture = 0;
	glBindTexture( GL_TEXTURE_2D, Gel::ActiveTexture );
}
// - ------------------------------------------------------------------------------------------ - //
void exit_GelTextureHandle() {
}
// - ------------------------------------------------------------------------------------------ - //

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
	// Checks, to avoid redundant gl calls //
	if ( TextureUnit != Gel::ActiveTextureUnit ) {
		glActiveTexture( GL_TEXTURE0 + TextureUnit );
		Gel::ActiveTextureUnit = TextureUnit;
	}
	if ( Handle != Gel::ActiveTexture ) {
		glBindTexture( GL_TEXTURE_2D, Handle );
		Gel::ActiveTexture = Handle;
	}
}
// - ------------------------------------------------------------------------------------------ - //
// Rarely Used. Alternatively, just bund another texture //
void unbind_GelTextureHandle( GelTextureHandle, const st32 TextureUnit ) {
	// Checks, to avoid redundant gl calls //
	if ( TextureUnit != Gel::ActiveTextureUnit ) {
		glActiveTexture( GL_TEXTURE0 + TextureUnit );
		Gel::ActiveTextureUnit = TextureUnit;
	}
	if ( Gel::ActiveTexture != 0 ) {
		glBindTexture( GL_TEXTURE_2D, 0 );
		Gel::ActiveTexture = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL_2_FAMILY) //
// - ------------------------------------------------------------------------------------------ - //
