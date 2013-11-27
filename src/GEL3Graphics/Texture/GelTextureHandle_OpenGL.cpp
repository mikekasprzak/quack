// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL_2_FAMILY)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelTextureHandle_OpenGL.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
	enum {
		GEL_MAX_TEXTURE_UNITS = 32
	};
	
	// OpenGL Specific, for eliminating redundant calls //
	st32 ActiveTextureUnit = 0;
	GelTextureHandle ActiveTexture[GEL_MAX_TEXTURE_UNITS];
};
// - ------------------------------------------------------------------------------------------ - //
void init_GelTextureHandle() {
	Gel::ActiveTextureUnit = 0;
	glActiveTexture( GL_TEXTURE0 + Gel::ActiveTextureUnit );
		
	for ( int idx = 0; idx < Gel::GEL_MAX_TEXTURE_UNITS; idx++ ) { 	
		Gel::ActiveTexture[idx] = 0;
	}
	// TODO: Actually check how many TU's there are, and call this. //
	glBindTexture( GL_TEXTURE_2D, Gel::ActiveTexture[0] );
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
	if ( Handle != Gel::ActiveTexture[Gel::ActiveTextureUnit] ) {
		glBindTexture( GL_TEXTURE_2D, Handle );
		Gel::ActiveTexture[Gel::ActiveTextureUnit] = Handle;
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
	if ( Gel::ActiveTexture[Gel::ActiveTextureUnit] != 0 ) {
		glBindTexture( GL_TEXTURE_2D, 0 );
		Gel::ActiveTexture[Gel::ActiveTextureUnit] = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL_2_FAMILY) //
// - ------------------------------------------------------------------------------------------ - //
