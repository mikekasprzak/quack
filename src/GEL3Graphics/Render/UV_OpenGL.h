// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_UV_OPENGL_H__
#define __GEL_RENDER_UV_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
// Our UV's are Signed Short's. The numeric range allows for +/- 32 repeats (beyond 0-1) //
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
typedef short				UVType;
#define GL_UVType 			GL_SHORT
// - ------------------------------------------------------------------------------------------ - //
#define UV_SHIFT			10
#define UV_ONE				1024
#define UV_ZERO				0
// - ------------------------------------------------------------------------------------------ - //
#define UV_ONE_F			1024.0f
#define UV_ZERO_F			0.0f
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_UV_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //