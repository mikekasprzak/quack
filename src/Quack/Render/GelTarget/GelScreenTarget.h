// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELSCREENTARGET_H__
#define __GEL_RENDER_GELSCREENTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
class GelScreenTarget {
	typedef GelScreenTarget thistype;

	void* Data;
public:
	GelScreenTarget( const int _w, const int _h, const int ScreenIndex = 0 );
	~GelScreenTarget();

	int GetWidth() const;
	int GetHeight() const;
	
	void Bind() const;
	void Viewport( const int x = 0, const int y = 0, int w = -1, int h = -1 ) const;
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELSCREENTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
