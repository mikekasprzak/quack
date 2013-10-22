// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_INDEXHANDLE_OPENGL_H__
#define __GEL_RENDER_INDEXHANDLE_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL2) || defined(USES_OPENGL_ES2)
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int		IndexHandle;
// - ------------------------------------------------------------------------------------------ - //
IndexHandle new_IndexHandle();
void delete_IndexHandle( IndexHandle Handle );

void bind_IndexHandle( IndexHandle Handle );
void unbind_IndexHandle( IndexHandle = 0 );	// TODO: Remove this argument, once unbind confirmed
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL2) || defined(USES_OPENGL_ES2) //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_INDEXHANDLE_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //