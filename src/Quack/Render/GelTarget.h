// - ------------------------------------------------------------------------------------------ - //
// GelTarget wraps screens and render targets, for a single targettable entity. //
// GelSubTarget's are sub-sections of GelTargets, such as split screen regions. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELTARGET_H__
#define __GEL_RENDER_GELTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include "GelTarget/GelNativeTarget.h"
#include "GelTarget/GelRenderTarget.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	GT_NULL = 0,
	
	GT_NATIVE,			// Native Screens/Windows //
	GT_RENDERTARGET,	// FBO (FrameBuffer Object) //
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
class GelTarget {
public:
	int x,y;
	int Width,Height;
protected:
	int		Flags;
	void*	Data;
public:
	
public:
	inline void Bind( const int Layer = 0 ) {
		if ( Flags == Gel::GT_NATIVE )
			((GelNativeTarget*)Data)->Bind( Layer );
		else if ( Flags == Gel::GT_RENDERTARGET )
			((GelRenderTarget*)Data)->Bind( Layer );
	}
};
// - ------------------------------------------------------------------------------------------ - //
class GelSubTarget {
public:
	int x,y;
	int Width,Height;
protected:
	GelTarget* Parent;	
public:

public:
	inline void Bind() {
		// Sets Viewport //
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
