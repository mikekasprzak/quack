// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_API_OPENGL2_H__
#define __GEL_API_OPENGL2_H__
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
#endif // __GEL_API_OPENGL2_H__ //
// - ------------------------------------------------------------------------------------------ - //
