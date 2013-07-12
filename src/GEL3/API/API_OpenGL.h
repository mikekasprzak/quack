// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_API_OPENGL2_H__
#define __GEL_API_OPENGL2_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL1) || defined(USES_OPENGL2) || defined(USES_OPENGL3) || defined(USES_OPENGL4)
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
#endif // USES_OPENGL1 USES_OPENGL2 USES_OPENGL3 USES_OPENGL4 //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_ES2 //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_API_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //