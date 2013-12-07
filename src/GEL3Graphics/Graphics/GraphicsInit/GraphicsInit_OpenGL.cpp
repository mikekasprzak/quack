// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL_LIB
// - ------------------------------------------------------------------------------------------ - //
#include "GraphicsInit.h"
#include <API/API_OpenGL.h>
#include <Lib/Lib.h>

#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
	int DepthBits;
	int StencilBits;
	int MaxRenderBufferSize;
	int MaxTextureSize;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelGraphicsInit() {
	Log( "* OpenGL Gel3Graphics Init()..." );

	// GL Environment Settings //
	glGetIntegerv( GL_DEPTH_BITS, (GLint*)&Gel::DepthBits );
	Log( "GL_DEPTH_BITS: %i", Gel::DepthBits );

	glGetIntegerv( GL_STENCIL_BITS, (GLint*)&Gel::StencilBits );
	Log( "GL_STENCIL_BITS: %i", Gel::StencilBits );
	
	glGetIntegerv( GL_MAX_RENDERBUFFER_SIZE, (GLint*)&Gel::MaxRenderBufferSize );
	Log( "GL_MAX_RENDERBUFFER_SIZE: %i", Gel::MaxRenderBufferSize );
	
	glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&Gel::MaxTextureSize );
	Log( "GL_MAX_TEXTURE_SIZE: %i", Gel::MaxTextureSize );
		
	gelShaderInit();
	atexit( gelGraphicsExit );
}
// - ------------------------------------------------------------------------------------------ - //
void gelGraphicsExit() {
	gelShaderExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_LIB //
// - ------------------------------------------------------------------------------------------ - //
