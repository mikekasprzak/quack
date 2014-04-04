// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELNATIVETARGET_H__
#define __GEL_RENDER_GELNATIVETARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
class GelNativeTarget {
	typedef GelNativeTarget thistype;

	void* Data;
public:
	GelNativeTarget( const int _w, const int _h, const int ScreenIndex = 0 );
	~GelNativeTarget();

	int GetWidth() const;
	int GetHeight() const;
	
	void Bind() const;
	void Viewport( const int x = 0, const int y = 0, int w = -1, int h = -1 ) const;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELNATIVETARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
