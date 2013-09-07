// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_VERTEXHANDLE_OPENGL_H__
#define __GEL_RENDER_VERTEXHANDLE_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int		VertexHandle;
// - ------------------------------------------------------------------------------------------ - //
VertexHandle new_VertexHandle();
void delete_VertexHandle( VertexHandle Handle );

void bind_VertexHandle( VertexHandle Handle );
void unbind_VertexHandle( VertexHandle = 0 );	// TODO: Remove this argument, once unbind confirmed
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_VERTEXHANDLE_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
