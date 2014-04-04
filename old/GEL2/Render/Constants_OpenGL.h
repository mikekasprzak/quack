// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_RENDER_CONSTANTS_OPENGL_H__
#define __GEL2_RENDER_CONSTANTS_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGLES2)
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL2.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Stencil Test and Depth Test Function Modes //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_NEVER								GL_NEVER
#define GEL_LESS								GL_LESS
#define GEL_LESSEQUAL							GL_LEQUAL
#define GEL_GREATER								GL_GREATER
#define GEL_GREATEREQUAL						GL_GEQUAL
#define GEL_EQUAL								GL_EQUAL
#define GEL_NOTEQUAL							GL_NOTEQUAL
#define GEL_ALWAYS								GL_ALWAYS
// - ------------------------------------------------------------------------------------------ - //
// Stencil Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_KEEP								GL_KEEP
#define GEL_ZERO								GL_ZERO
#define GEL_REPLACE								GL_REPLACE
#define GEL_INVERT								GL_INVERT
#define GEL_INCR								GL_INCR				// Saturate //
#define GEL_DECR								GL_DECR				// Saturate //
#define GEL_INCRWRAP							GL_INCR_WRAP		// GL 1.4+, ES 2.0 and D3D //
#define GEL_DECRWRAP							GL_DECR_WRAP		// GL 1.4+, ES 2.0 and D3D //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Render Operations //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_POINTS								GL_POINTS
#define GEL_LINES								GL_LINES
#define GEL_LINE_STRIP							GL_LINE_STRIP
#define GEL_TRIANGLES							GL_TRIANGLES
#define GEL_TRIANGLE_STRIP						GL_TRIANGLE_STRIP

#define GEL_LINE_LOOP							GL_LINE_LOOP		// GL Only //
#define GEL_TRIANGLE_FAN						GL_TRIANGLE_FAN		// GL Only //

#define GEL_LINES_ADJ							GL_LINES			// D3D Only (Stub) //
#define GEL_LINE_STRIP_ADJ						GL_LINE_STRIP		// D3D Only (Stub) //
#define GEL_TRIANGLES_ADJ						GL_TRIANGLES		// D3D Only (Stub) //
#define GEL_TRIANGLE_STRIP_ADJ					GL_TRIANGLE_STRIP	// D3D Only (Stub) //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// DrawMode States //
// - ------------------------------------------------------------------------------------------ - //
#define GEL_DRAWMODE_NULL						-1
#define GEL_DRAWMODE_FLAT						0
#define GEL_DRAWMODE_COLORS						1
#define GEL_DRAWMODE_TEXTURED					2
#define GEL_DRAWMODE_TEXTURED_COLORS			3
#define GEL_DRAWMODE_SHADER						16
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGLES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_RENDER_CONSTANTS_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
