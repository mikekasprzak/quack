// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_RENDER_RENDERTARGET_OPENGL_FBO_H__
#define __GEL2_RENDER_RENDERTARGET_OPENGL_FBO_H__
// - ------------------------------------------------------------------------------------------ - //
// Usage:
//   Number of Textures determines how many FBOs are created. If Multiple Render Targets (MRT) is
//   available and enabled in the constructor, then only a single FBO will be allocated, and the
//   additional textures will be bound to the respected COLOR_ATTACHMENT pages (0, 1, etc).
//   Depth and Stencil are optional (0). If you use 1 of either, then they will be bound to all
//   FBOs. Otherwise, it's expected that you will create an equal number of Depth and Stencil
//   buffers as the number of textures. If using MRTs, you should use no more than 1 of each.
// - ------------------------------------------------------------------------------------------ - //
// Shader Usage:
//   Typically gl_FragColor is the data you write, but when using MRTs you use gl_FragData[i],
//   where "i" is the index in GL_COLOR_ATTACHMENTi (i.e. 0, 1, 2). gl_FragData[0] is a synonym
//   for GL_COLOR_ATTACHMENT0.
// - ------------------------------------------------------------------------------------------ - //
// TIP: I may want to use a non Renderbuffer for Depth (i.e. a texture). //
//	If I do, it means I could use samplers in the shader for reading the data. //
// - ------------------------------------------------------------------------------------------ - //
// TODO: Allow choice of Depth and Stencil modes. Maybe even Texture mode (RGBA4444?) //
//	GL_RGBA4	(ES2 Spec)
//	GL_RGB565	(ES2 Spec)
//	GL_RGB5_A1	(ES2 Spec)
//	GL_DEPTH_COMPONENT16
//	GL_DEPTH_COMPONENT24 (with extension)
//	GL_STENCIL_INDEX8
//	GL_DEPTH24_STENCIL8_EXT (with extension)
//	GL_DEPTH24_STENCIL8_OES (with extension)
// - ------------------------------------------------------------------------------------------ - //
// TODO: Consider manipulating the input arguments based on UseMRT. If Depth/Stencil >1, then
//   assume an equal number of Depth and Stencil buffers to the number of textures. This may
//   not actually be a good idea. At the very least, some Asserts could be added to detect this.
// - ------------------------------------------------------------------------------------------ - //
// FYI: According to Songho, it's actually faster to switch the texture pages of an FBO than it is
//   to actually outright change FBOs. I'm actually kinda bothered by this. If this is true, then
//   then that means it's actually faster to allocate a single FBO object (like how MRT's are
//   implemented here) and then swap out the pages. I will have to do some benchmarking before I'm
//   satisfied with this. I will have to test this across multiple GPUs. I imagine some will do
//   this about equal speed as an FBO change, but if there are any GPUs that lag because of the
//   switching, then it's worth following Songho's advice. It just means the bind function
//   becomes far more detailed (practically moving the entire constructor body in to the binder).
//
//   Songho's tutorial can be found in the [Docs] folder, or at his website:
//   http://www.songho.ca/opengl/gl_fbo.html
// - ------------------------------------------------------------------------------------------ - //
// FYI: The gl_FragColor name can be changed in the shader when using GLSL 1.5+. *shrug* Who cares?
//		http://en.wikipedia.org/wiki/GLSL#A_sample_trivial_GLSL_fragment_shader
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_FBO) || defined(USES_FBO_EXT) || defined(USES_FBO_OES)
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <Style/Style.h>
#include <Screen/Screen.h>
//#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
#include "RenderTarget_OpenGL_FBO_GLDefines.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Render {
// - ------------------------------------------------------------------------------------------ - //
class cRenderTarget {
public:
	size_t Width;
	size_t Height;

private:	
	std::vector< GLuint > FBO;				// If an MRT, then there will be only 1 FBO //
	std::vector< GLuint > Texture;
	std::vector< GLuint > DepthBuffer;
	std::vector< GLuint > StencilBuffer;		
		
public:
	inline cRenderTarget( const size_t _w, const size_t _h, const size_t _Textures, const size_t _DepthBuffers = 1, const size_t _StencilBuffers = 0, const bool UseMRT = true ) :
		Width( _w ),
		Height( _h )
	{
		// Number of FBOs //
#ifdef USES_MRT
		if ( UseMRT )
			FBO.resize( 1 );
		else
#endif // USES_MRT //
		FBO.resize( _Textures );

		// Generate FBO IDs //
		gels_GenFramebuffers( FBO.size(), &FBO[0] );
		
		
		// Depth Buffers //
		if ( _DepthBuffers > 0 ) {
			// Number of DepthBuffers //
			DepthBuffer.resize( _DepthBuffers );
			// Generate DepthBuffers IDs //
			gels_GenRenderBuffers( DepthBuffer.size(), &DepthBuffer[0] );
			
			// For all Depth Buffers //
			for ( size_t idx = 0; idx < _DepthBuffers; idx++ ) {
				gels_BindRenderbuffer( GELS_RENDERBUFFER, DepthBuffer[idx] );
				gels_RenderbufferStorage( GELS_RENDERBUFFER, GL_DEPTH_COMPONENT16, Width, Height );
			}
			gels_BindRenderbuffer( GELS_RENDERBUFFER, 0 ); // Unbind //
		}		


		// Stencil Buffers //
		if ( _StencilBuffers > 0 ) {
			// Number of StencilBuffers //
			StencilBuffer.resize( _StencilBuffers );
			// Generate StencilBuffer IDs //
			gels_GenRenderBuffers( StencilBuffer.size(), &StencilBuffer[0] );
			
			// For all Stencil Buffers //
			for ( size_t idx = 0; idx < _StencilBuffers; idx++ ) {
				gels_BindRenderbuffer( GELS_RENDERBUFFER, StencilBuffer[idx] );
				gels_RenderbufferStorage( GELS_RENDERBUFFER, GL_STENCIL_INDEX8, Width, Height );
			}
			gels_BindRenderbuffer( GELS_RENDERBUFFER, 0 ); // Unbind //			
		}

		// Number of Textures //
		Texture.resize( _Textures );
		// Set the first Texture Unit //
		glActiveTexture( GL_TEXTURE0 );
		// Generate Texture IDs //
		glGenTextures( Texture.size(), &Texture[0] );

		// For all Textures //
		for ( size_t idx = 0; idx < _Textures; idx++ ) {
#ifdef USES_MRT
			if ( UseMRT )
				gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[0] );
			else
#endif // USES_MRT //
			gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[idx] );
			
			glBindTexture( GL_TEXTURE_2D, Texture[idx] );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
			glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glBindTexture( GL_TEXTURE_2D, 0 );	// Unbind //

			// NOTE: There may be a bug here when using non MRT's (i.e. COLOR_ATTATCHMENT should always be 0) //
			// NOTE: Fix added. Will require testing. If wrong, the attachment+idx will have to become main one. //
			
			// Bind texture to current FBO //
#ifdef USES_MRT
			if ( UseMRT )
				gels_FramebufferTexture2D( GELS_FRAMEBUFFER, GELS_COLOR_ATTACHMENT0+idx, GL_TEXTURE_2D, Texture[idx], 0 );
			else
#endif // USES_MRT //
			gels_FramebufferTexture2D( GELS_FRAMEBUFFER, GELS_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture[idx], 0 );

#ifdef USES_MRT
			if ( (UseMRT && (idx == 0)) || (!UseMRT) ) {
#endif // USES_MRT //
				// Bind the Depth Buffer //
				if ( _DepthBuffers > 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_DEPTH_ATTACHMENT, GELS_RENDERBUFFER, DepthBuffer[idx] );
				}
				else if ( _DepthBuffers == 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_DEPTH_ATTACHMENT, GELS_RENDERBUFFER, DepthBuffer[0] );
				}
#ifdef USES_MRT
			}
#endif // USES_MRT //

#ifdef USES_MRT
			if ( (UseMRT && (idx == 0)) || (!UseMRT) ) {
#endif // USES_MRT //
				// Bind the Stencil Buffer //
				if ( _StencilBuffers > 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_STENCIL_ATTACHMENT, GELS_RENDERBUFFER, StencilBuffer[idx] );
				}
				else if ( _StencilBuffers == 1 ) {
					gels_FramebufferRenderbuffer( GELS_FRAMEBUFFER, GELS_STENCIL_ATTACHMENT, GELS_RENDERBUFFER, StencilBuffer[0] );
				}
#ifdef USES_MRT
			}
#endif // USES_MRT //
		}
		
		// Validate FBOs //
		for ( size_t idx = 0; idx < FBO.size(); idx++ ) {
			gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[idx] );
			
			if ( gels_CheckFramebufferStatus( GELS_FRAMEBUFFER ) != GELS_FRAMEBUFFER_COMPLETE ) {
				Log( "* ERROR: FBO %i Unavailable! (%i)", idx, FBO[idx] );
			}
			else {
				Log( "* FBO %i OK. (GL_ID: %i)", idx, FBO[idx] );
			}
		}
		
		gels_BindFramebuffer( GELS_FRAMEBUFFER, 0 ); // Unbind //
	}
	
	inline ~cRenderTarget() {
		if ( FBO.size() > 0 )
			gels_DeleteFramebuffers( FBO.size(), &FBO[0] );

		if ( Texture.size() > 0 )
			glDeleteTextures( Texture.size(), &Texture[0] );

		if ( DepthBuffer.size() > 0 )
			gels_DeleteRenderbuffers( DepthBuffer.size(), &DepthBuffer[0] );

		if ( StencilBuffer.size() > 0 )
			gels_DeleteRenderbuffers( StencilBuffer.size(), &StencilBuffer[0] );
	}
	
	inline void Bind( const size_t Index = 0 ) const {
		gels_BindFramebuffer( GELS_FRAMEBUFFER, FBO[Index] );
		
		glViewport( 
			0,
			0,
			Width, 
			Height
			);	
	}
		
	inline static void _UnBind( ) {
		gels_BindFramebuffer( GELS_FRAMEBUFFER, 0 );
	}
		
	inline static void UnBind( ) {
		_UnBind();
		Screen::Native[0].UpdateViewport();		// Reset glViewport to the whole Native Screen //
	}
	
	inline void BindAsTexture( const st32 Index = 0, const st32 TextureUnit = 0 ) const {
		glActiveTexture( GL_TEXTURE0 + TextureUnit );
		glBindTexture( GL_TEXTURE_2D, Texture[Index] );
	}
};

//#ifdef USES_MRT
//			if ( FBO.size() == 1 )

//#ifdef USES_MRT // Multiple Render Targets //
// - ------------------------------------------------------------------------------------------ - //
// Synonym for the static UnBind member of RenderTarget //
inline void _UnBind() {
	cRenderTarget::_UnBind();
}
inline void UnBind() {
	cRenderTarget::UnBind();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Render //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_FBO) || defined(USES_FBO_EXT) || defined(USES_FBO_OES) //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_RENDER_RENDERTARGET_OPENGL_FBO_H__ //
// - ------------------------------------------------------------------------------------------ - //
