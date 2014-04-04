// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELRENDERTARGET_H__
#define __GEL_RENDER_GELRENDERTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
class GelRenderTarget {
	typedef GelRenderTarget thistype;

	void* Data;
public:
	GelRenderTarget( 
		const int _w, const int _h, 
		const int Textures = 1, const int DepthBuffers = 1, const int StencilBuffers = 0,
		const bool UseMRT = false 
	);
	~GelRenderTarget();
	
	int GetWidth() const;
	int GetHeight() const;

	inline void Bind( const int Layer = 0 ) const {
		_Bind(Layer);
		Viewport();
	}
		
	void _Bind( const int Layer = 0 ) const;
	void Viewport( const int x = 0, const int y = 0, int w = -1, int h = -1 ) const;
	void BindAsTexture( const int Layer = 0, const int TextureUnit = 0 ) const;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELRENDERTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
