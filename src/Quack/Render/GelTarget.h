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
class GelTarget;
class GelSubTarget;
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	GT_NULL = 0,
	
	GT_NATIVE = 		0x1,	// Native Screens/Windows
	GT_RENDERTARGET =	0x2,	// FBO (FrameBuffer Object)
	
	GT_TARGET = 		0x1000,
	GT_SUBTARGET =		0x2000,
};
// - ------------------------------------------------------------------------------------------ - //
extern class GelTarget* LastBoundTarget;		// a GelTarget or a GelSubTarget //
extern int				LastBoundLayer;			// The last bound layer of a RenderTarget //
extern class GelTarget* CurrentTarget;			// GelTarget Only. Native or RenderTarget. //
extern class GelTarget* CurrentNativeTarget;	// GelTarget Only. Native Only (Screen). //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GelTarget {
public:
	int 	x,y;
	int 	Width,Height;
protected:
	int		Flags;
	void*	Data;
	
	friend class GelSubTarget;
public:
	
public:
	inline bool _Bind( const int Layer = 0 ) {
		bool Change = false;
		
		if ( IsNativeTarget() ) {
			// If now binding a Native, and was a RenderTarget, I must UnBind //
			if ( Gel::LastBoundTarget ) {
				if ( Gel::LastBoundTarget->IsRenderTarget() ) {
					if ( Gel::LastBoundTarget->IsSubTarget() )
						Gel::LastBoundTarget->UnBindSubTarget();
					else
						Gel::LastBoundTarget->UnBind();
					Change = true;
				}
			}
			
			// Check if the same Native (not necessarily the same as last bound) //
			if ( Gel::CurrentNativeTarget != this ) { // Zero case okay //
				((GelNativeTarget*)Data)->Bind();
				//((GelNativeTarget*)Data)->Viewport();
				
				Gel::CurrentNativeTarget = this;
				Change = true;
			}
		}
		else if ( IsRenderTarget() ) {
			// No need to UnBind if prior state was a Native or RT! //
			
			// Check if the Last Bound and this Target are different //
			if ( (Gel::LastBoundTarget != this) || (Gel::LastBoundLayer != Layer) ) {	// Zero case okay //
				((GelRenderTarget*)Data)->Bind( Layer );
				//((GelRenderTarget*)Data)->Viewport();
				
				Gel::LastBoundLayer = Layer;
				Change = true;
			}
		}
		else {
			Log("! Bad GelTarget!!!");
		}
		
		Gel::LastBoundTarget = this;
		Gel::CurrentTarget = this;
		
		return Change;
	}

	inline void Viewport() {
		if ( IsNativeTarget() ) {
			((GelNativeTarget*)Data)->Viewport();
		}
		else if ( IsRenderTarget() ) {
			((GelRenderTarget*)Data)->Viewport();
		}
		else {
			Log("! Bad GelTarget!!!");
		}
	}
	
	
	inline bool Bind( const int Layer = 0 ) {
		bool Change = _Bind( Layer );
		if ( Change )
			Viewport();

		return Change;
	}
	
	inline void UnBind() {
		if ( IsRenderTarget() ) {
			((GelRenderTarget*)Data)->UnBind();
		}		
	}
	
public:
	// Helper Functions //
	inline bool IsTarget() const {
		return Flags & Gel::GT_TARGET;
	}
	inline bool IsSubTarget() const {
		return Flags & Gel::GT_SUBTARGET;
	}
	inline bool IsNativeTarget() const {
		return Flags & Gel::GT_NATIVE;
	}
	inline bool IsRenderTarget() const {
		return Flags & Gel::GT_RENDERTARGET;
	}
	
	inline class GelSubTarget* ToSubTarget() {
		return (GelSubTarget*)this;
	}
	inline void UnBindSubTarget();
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GelSubTarget {
public:
	int 		x,y;
	int 		Width,Height;
protected:
	int			Flags;
	GelTarget*	Parent;	
	
	friend GelTarget;
public:
	inline GelSubTarget( GelTarget* _Parent, const int _x, const int _y, const int _w, const int _h ) :
		x(_x),
		y(_y),
		Width(_w),
		Height(_h),
		Flags(_Parent->Flags),
		Parent(_Parent)
	{
	}
public:
	inline bool Bind( const int Layer = 0 ) {
		bool Change = false;
		
		// If Parent is not bound, Bind the parent first! //
		if ( Gel::CurrentTarget ) {
			if ( Gel::CurrentTarget != Parent ) {
				Change = Parent->_Bind( Layer );
			}
		}
		
		void* Data = Parent->Data;
		
		if ( IsNativeTarget() ) {
			//((GelNativeTarget*)Data)->Bind();
			((GelNativeTarget*)Data)->Viewport( x,y, Width,Height );
			Change = true;
		}
		else if ( IsRenderTarget() ) {
			//((GelRenderTarget*)Data)->Bind( Layer );
			((GelRenderTarget*)Data)->Viewport( x,y, Width,Height );
			Change = true;
		}

		Gel::LastBoundTarget = (GelTarget*)this;
			
		return Change;
	}

public:
	// Helper Functions //
	inline bool IsTarget() const {
		return Flags & Gel::GT_TARGET;
	}
	inline bool IsSubTarget() const {
		return Flags & Gel::GT_SUBTARGET;
	}
	inline bool IsNativeTarget() const {
		return Flags & Gel::GT_NATIVE;
	}
	inline bool IsRenderTarget() const {
		return Flags & Gel::GT_RENDERTARGET;
	}
};
// - ------------------------------------------------------------------------------------------ - //
void GelTarget::UnBindSubTarget() {
	ToSubTarget()->Parent->UnBind();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
