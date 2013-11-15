// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_API_OPENGL2_H__
#define __GEL_API_OPENGL2_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL
// - ------------------------------------------------------------------------------------------ - //
// TODO: Upgrade me to GLEW //
#ifdef USES_GLEE
	#include <GLee.h>
	
	#ifdef _WIN32
		// Hide some Warnings on Windows //
		#undef GL_LINES_ADJACENCY_EXT
		#undef GL_LINE_STRIP_ADJACENCY_EXT
		#undef GL_TRIANGLES_ADJACENCY_EXT
		#undef GL_TRIANGLE_STRIP_ADJACENCY_EXT
	#endif // _WIN32
#endif // USES_GLEE //

#include <GL/gl.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <GLES2/gl2platform.h>
#ifndef USES_NO_EGL
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <EGL/eglplatform.h>
#endif // NO_EGL //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_ES2 //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_API_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
