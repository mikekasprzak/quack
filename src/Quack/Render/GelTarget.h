// - ------------------------------------------------------------------------------------------ - //
// GelTarget wraps screens and render targets, for a single targettable entity. //
// GelSubTarget 
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELTARGET_H__
#define __GEL_RENDER_GELTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
//#include <Math/Math.h>
//#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
enum {
	GEL_GT_NATIVE = 1,
	GEL_GT_FBO
};
// - ------------------------------------------------------------------------------------------ - //
class GelTarget {
	int x,y,w,h;

	int		Flags;
	void*	Data;
public:
	inline int GetX() const {
		return x;
	}
	inline int GetY() const {
		return y;
	}
	inline int GetWidth() const {
		return w;
	}
	inline int GetHeight() const {
		return h;
	}
	
public:
	inline void Bind() {
		// Bind RT (FBO), or screen //
	}
};
// - ------------------------------------------------------------------------------------------ - //
class GelSubTarget {
	int x,y,w,h;

	GelTarget* Parent;	
public:
	inline int GetX() const {
		return x;
	}
	inline int GetY() const {
		return y;
	}
	inline int GetWidth() const {
		return w;
	}
	inline int GetHeight() const {
		return h;
	}

public:
	inline void Bind() {
		// Sets Viewport //
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
