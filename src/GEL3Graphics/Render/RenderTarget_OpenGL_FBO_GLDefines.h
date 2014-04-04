// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_RENDERTARGET_OPENGL_FBO_GLDEFINES_H__
#define __GEL_RENDER_RENDERTARGET_OPENGL_FBO_GLDEFINES_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL_2_FAMILY
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_FBO
// - ------------------------------------------------------------------------------------------ - //
#define _glGenFramebuffers				glGenFramebuffers
#define _glDeleteFramebuffers			glDeleteFramebuffers
#define _glBindFramebuffer				glBindFramebuffer
#define _glGenRenderBuffers				glGenRenderbuffers
#define _glDeleteRenderbuffers			glDeleteRenderbuffers
#define _glBindRenderbuffer				glBindRenderbuffer
#define _glRenderbufferStorage 			glRenderbufferStorage
#define _glFramebufferTexture2D			glFramebufferTexture2D
#define _glFramebufferRenderbuffer		glFramebufferRenderbuffer
#define _glCheckFramebufferStatus		glCheckFramebufferStatus

#define _GL_FRAMEBUFFER					GL_FRAMEBUFFER
#define _GL_RENDERBUFFER				GL_RENDERBUFFER
#define _GL_FRAMEBUFFER_COMPLETE		GL_FRAMEBUFFER_COMPLETE
#define _GL_MAX_COLOR_ATTACHMENTS		GL_MAX_COLOR_ATTACHMENTS
#define _GL_COLOR_ATTACHMENT0			GL_COLOR_ATTACHMENT0
#define _GL_COLOR_ATTACHMENT1			GL_COLOR_ATTACHMENT1
#define _GL_COLOR_ATTACHMENT2			GL_COLOR_ATTACHMENT2
#define _GL_COLOR_ATTACHMENT3			GL_COLOR_ATTACHMENT3
#define _GL_COLOR_ATTACHMENT4			GL_COLOR_ATTACHMENT4
#define _GL_COLOR_ATTACHMENT5			GL_COLOR_ATTACHMENT5
#define _GL_COLOR_ATTACHMENT6			GL_COLOR_ATTACHMENT6
#define _GL_COLOR_ATTACHMENT7			GL_COLOR_ATTACHMENT7
#define _GL_COLOR_ATTACHMENT8			GL_COLOR_ATTACHMENT8
#define _GL_COLOR_ATTACHMENT9			GL_COLOR_ATTACHMENT9
#define _GL_COLOR_ATTACHMENT10			GL_COLOR_ATTACHMENT10
#define _GL_COLOR_ATTACHMENT11			GL_COLOR_ATTACHMENT11
#define _GL_COLOR_ATTACHMENT12			GL_COLOR_ATTACHMENT12
#define _GL_COLOR_ATTACHMENT13			GL_COLOR_ATTACHMENT13
#define _GL_COLOR_ATTACHMENT14			GL_COLOR_ATTACHMENT14
#define _GL_COLOR_ATTACHMENT15			GL_COLOR_ATTACHMENT15
#define _GL_DEPTH_ATTACHMENT			GL_DEPTH_ATTACHMENT
#define _GL_STENCIL_ATTACHMENT			GL_STENCIL_ATTACHMENT
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_FBO_EXT)
// - ------------------------------------------------------------------------------------------ - //
#define _glGenFramebuffers				glGenFramebuffersEXT
#define _glDeleteFramebuffers			glDeleteFramebuffersEXT
#define _glBindFramebuffer				glBindFramebufferEXT
#define _glGenRenderBuffers				glGenRenderbuffersEXT
#define _glDeleteRenderbuffers			glDeleteRenderbuffersEXT
#define _glBindRenderbuffer				glBindRenderbufferEXT
#define _glRenderbufferStorage 			glRenderbufferStorageEXT
#define _glFramebufferTexture2D			glFramebufferTexture2DEXT
#define _glFramebufferRenderbuffer		glFramebufferRenderbufferEXT
#define _glCheckFramebufferStatus		glCheckFramebufferStatusEXT

#define _GL_FRAMEBUFFER					GL_FRAMEBUFFER_EXT
#define _GL_RENDERBUFFER				GL_RENDERBUFFER_EXT
#define _GL_FRAMEBUFFER_COMPLETE		GL_FRAMEBUFFER_COMPLETE_EXT
#define _GL_MAX_COLOR_ATTACHMENTS		GL_MAX_COLOR_ATTACHMENTS_EXT
#define _GL_COLOR_ATTACHMENT0			GL_COLOR_ATTACHMENT0_EXT
#define _GL_COLOR_ATTACHMENT1			GL_COLOR_ATTACHMENT1_EXT
#define _GL_COLOR_ATTACHMENT2			GL_COLOR_ATTACHMENT2_EXT
#define _GL_COLOR_ATTACHMENT3			GL_COLOR_ATTACHMENT3_EXT
#define _GL_COLOR_ATTACHMENT4			GL_COLOR_ATTACHMENT4_EXT
#define _GL_COLOR_ATTACHMENT5			GL_COLOR_ATTACHMENT5_EXT
#define _GL_COLOR_ATTACHMENT6			GL_COLOR_ATTACHMENT6_EXT
#define _GL_COLOR_ATTACHMENT7			GL_COLOR_ATTACHMENT7_EXT
#define _GL_COLOR_ATTACHMENT8			GL_COLOR_ATTACHMENT8_EXT
#define _GL_COLOR_ATTACHMENT9			GL_COLOR_ATTACHMENT9_EXT
#define _GL_COLOR_ATTACHMENT10			GL_COLOR_ATTACHMENT10_EXT
#define _GL_COLOR_ATTACHMENT11			GL_COLOR_ATTACHMENT11_EXT
#define _GL_COLOR_ATTACHMENT12			GL_COLOR_ATTACHMENT12_EXT
#define _GL_COLOR_ATTACHMENT13			GL_COLOR_ATTACHMENT13_EXT
#define _GL_COLOR_ATTACHMENT14			GL_COLOR_ATTACHMENT14_EXT
#define _GL_COLOR_ATTACHMENT15			GL_COLOR_ATTACHMENT15_EXT
#define _GL_DEPTH_ATTACHMENT			GL_DEPTH_ATTACHMENT_EXT
#define _GL_STENCIL_ATTACHMENT			GL_STENCIL_ATTACHMENT_EXT
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_FBO_OES)
// - ------------------------------------------------------------------------------------------ - //
#define _glGenFramebuffers				glGenFramebuffersOES
#define _glDeleteFramebuffers			glDeleteFramebuffersOES
#define _glBindFramebuffer				glBindFramebufferOES
#define _glGenRenderBuffers				glGenRenderbuffersOES
#define _glDeleteRenderbuffers			glDeleteRenderbuffersOES
#define _glBindRenderbuffer				glBindRenderbufferOES
#define _glRenderbufferStorage 			glRenderbufferStorageOES
#define _glFramebufferTexture2D			glFramebufferTexture2DOES
#define _glFramebufferRenderbuffer		glFramebufferRenderbufferOES
#define _glCheckFramebufferStatus		glCheckFramebufferStatusOES

#define _GL_FRAMEBUFFER					GL_FRAMEBUFFER_OES
#define _GL_RENDERBUFFER				GL_RENDERBUFFER_OES
#define _GL_FRAMEBUFFER_COMPLETE		GL_FRAMEBUFFER_COMPLETE_OES
#define _GL_MAX_COLOR_ATTACHMENTS		GL_MAX_COLOR_ATTACHMENTS_OES
#define _GL_COLOR_ATTACHMENT0			GL_COLOR_ATTACHMENT0_OES
#define _GL_COLOR_ATTACHMENT1			GL_COLOR_ATTACHMENT1_OES
#define _GL_COLOR_ATTACHMENT2			GL_COLOR_ATTACHMENT2_OES
#define _GL_COLOR_ATTACHMENT3			GL_COLOR_ATTACHMENT3_OES
#define _GL_COLOR_ATTACHMENT4			GL_COLOR_ATTACHMENT4_OES
#define _GL_COLOR_ATTACHMENT5			GL_COLOR_ATTACHMENT5_OES
#define _GL_COLOR_ATTACHMENT6			GL_COLOR_ATTACHMENT6_OES
#define _GL_COLOR_ATTACHMENT7			GL_COLOR_ATTACHMENT7_OES
#define _GL_COLOR_ATTACHMENT8			GL_COLOR_ATTACHMENT8_OES
#define _GL_COLOR_ATTACHMENT9			GL_COLOR_ATTACHMENT9_OES
#define _GL_COLOR_ATTACHMENT10			GL_COLOR_ATTACHMENT10_OES
#define _GL_COLOR_ATTACHMENT11			GL_COLOR_ATTACHMENT11_OES
#define _GL_COLOR_ATTACHMENT12			GL_COLOR_ATTACHMENT12_OES
#define _GL_COLOR_ATTACHMENT13			GL_COLOR_ATTACHMENT13_OES
#define _GL_COLOR_ATTACHMENT14			GL_COLOR_ATTACHMENT14_OES
#define _GL_COLOR_ATTACHMENT15			GL_COLOR_ATTACHMENT15_OES
#define _GL_DEPTH_ATTACHMENT			GL_DEPTH_ATTACHMENT_OES
#define _GL_STENCIL_ATTACHMENT			GL_STENCIL_ATTACHMENT_OES
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FBO //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_2_FAMILY //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_RENDERTARGET_OPENGL_FBO_GLDEFINES_H__ //
// - ------------------------------------------------------------------------------------------ - //
