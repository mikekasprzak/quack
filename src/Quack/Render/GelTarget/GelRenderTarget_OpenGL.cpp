// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL_2_FAMILY
// - ------------------------------------------------------------------------------------------ - //
// NOTE: This uses the old Gel RenderTarget code. That should should be merged/moved here, some day.
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "GelRenderTarget.h"
#include <Render/RenderTarget_OpenGL_FBO.h>
// - ------------------------------------------------------------------------------------------ - //
typedef Gel::cRenderTarget RTType;
// - ------------------------------------------------------------------------------------------ - //
GelRenderTarget::GelRenderTarget( const int _w, const int _h, const int Textures, const int DepthBuffers, const int StencilBuffers, const bool UseMRT ) {
	Data = new RTType(_w,_h,Textures,DepthBuffers,StencilBuffers,UseMRT);
}
// - ------------------------------------------------------------------------------------------ - //
GelRenderTarget::~GelRenderTarget() {
	if ( Data )
		delete ((RTType*)Data);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int GelRenderTarget::GetWidth() const {
	return ((RTType*)Data)->Width;
}
// - ------------------------------------------------------------------------------------------ - //
int GelRenderTarget::GetHeight() const {
	return ((RTType*)Data)->Height;
}
// - ------------------------------------------------------------------------------------------ - //
void GelRenderTarget::Bind( const int Layer ) const {
	((RTType*)Data)->_Bind( Layer );
}
// - ------------------------------------------------------------------------------------------ - //
void GelRenderTarget::Viewport( const int x, const int y, const int w, const int h ) const {
	((RTType*)Data)->Viewport( x,y, w,h );
}
// - ------------------------------------------------------------------------------------------ - //
void GelRenderTarget::UnBind() const {
	((RTType*)Data)->_UnBind();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void GelRenderTarget::BindAsTexture( const int Layer, const int TextureUnit ) const {
	((RTType*)Data)->BindAsTexture( Layer, TextureUnit );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_2_FAMILY //
// - ------------------------------------------------------------------------------------------ - //
