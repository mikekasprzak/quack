// - ------------------------------------------------------------------------------------------ - //
// GelTarget wraps screens and render targets, for a single targettable entity. //
// GelSubTarget's are sub-sections of GelTargets, such as split screen regions. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELTARGET_H__
#define __GEL_RENDER_GELTARGET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include "GelTarget/GelScreenTarget.h"
#include "GelTarget/GelRenderTarget.h"
// - ------------------------------------------------------------------------------------------ - //
class GelTarget;
class GelSubTarget;
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	GT_NULL = 0,
	
	GT_SCREENTARGET =	0x1,	// Screens and Windows (formerly NativeTarget)
	GT_RENDERTARGET =	0x2,	// FBO (FrameBuffer Object)
	
	GT_TYPEMASK = 		0xFF,
	
	GT_TARGET = 		0x1000,
	GT_SUBTARGET =		0x2000,
};
// - ------------------------------------------------------------------------------------------ - //
extern class GelTarget* LastBoundTarget;		// a GelTarget or a GelSubTarget //
extern int				LastBoundLayer;			// The last bound layer of a RenderTarget //
extern class GelTarget* CurrentTarget;			// GelTarget Only. ScreenTarget or RenderTarget. //
extern class GelTarget* CurrentScreenTarget;	// GelTarget Only. ScreenTarget Only (Screen). //
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
	inline GelTarget( const int _Flags, void* _Data ) :
		x(0),
		y(0),
		Flags( _Flags | Gel::GT_TARGET ),
		Data( _Data ) 
	{
		if ( IsScreenTarget() ) {
			Width = ((GelScreenTarget*)Data)->GetWidth();
			Height = ((GelScreenTarget*)Data)->GetHeight();
		}
		else if ( IsRenderTarget() ) {
			Width = ((GelRenderTarget*)Data)->GetWidth();
			Height = ((GelRenderTarget*)Data)->GetHeight();
		}
		else {
			Log("! Bad GelTarget!!!");
		}
	}
	
	inline ~GelTarget()	{
		if ( Data ) {
			if ( IsScreenTarget() ) {
				delete ((GelScreenTarget*)Data);
			}
			else if ( IsRenderTarget() ) {
				delete ((GelRenderTarget*)Data);
			}
		}			
	}
	
public:
	inline bool _Bind( const int Layer = 0 ) {
		bool Change = false;
		
		if ( IsScreenTarget() ) {
			// If now binding a ScreenTarget, and was a RenderTarget, I must UnBind //
			if ( Gel::LastBoundTarget ) {
				if ( Gel::LastBoundTarget->IsRenderTarget() ) {
					if ( Gel::LastBoundTarget->IsSubTarget() )
						Gel::LastBoundTarget->UnBindSubTarget();
					else
						Gel::LastBoundTarget->UnBind();
					Change = true;
				}
			}
			
			// Check if it is the same ScreenTarget (not necessarily the same as last bound) //
			if ( Gel::CurrentScreenTarget != this ) { // Zero case okay //
				((GelScreenTarget*)Data)->Bind();
				//((GelScreenTarget*)Data)->Viewport();
				
				Gel::CurrentScreenTarget = this;
				Change = true;
			}
		}
		else if ( IsRenderTarget() ) {
			// No need to UnBind if prior state was a Screen or RT! //
			
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
		if ( IsScreenTarget() ) {
			((GelScreenTarget*)Data)->Viewport();
		}
		else if ( IsRenderTarget() ) {
			((GelRenderTarget*)Data)->Viewport();
		}
		else {
			Log("! Bad GelTarget!!!");
		}
	}
	
	
	inline bool Bind( const int Layer = 0 ) {
		bool Change = false;
		
		if ( IsTarget() ) {
			Change = _Bind( Layer );
			if ( Change )
				Viewport();
		}
		else if ( IsSubTarget() ) {
			Change = BindSubTarget( Layer );
		}

		return Change;
	}
	// Automatically called //
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
	inline bool IsScreenTarget() const {
		return Flags & Gel::GT_SCREENTARGET;
	}
	inline bool IsRenderTarget() const {
		return Flags & Gel::GT_RENDERTARGET;
	}
	
	inline class GelSubTarget* ToSubTarget() {
		return (GelSubTarget*)this;
	}

	inline bool BindSubTarget( const int Layer = 0 );
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
		Flags( (_Parent->Flags & Gel::GT_TYPEMASK) | Gel::GT_SUBTARGET ),
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
		
		if ( IsScreenTarget() ) {
			//((GelScreenTarget*)Data)->Bind();
			((GelScreenTarget*)Data)->Viewport( x,y, Width,Height );
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
	inline bool IsScreenTarget() const {
		return Flags & Gel::GT_SCREENTARGET;
	}
	inline bool IsRenderTarget() const {
		return Flags & Gel::GT_RENDERTARGET;
	}
};
// - ------------------------------------------------------------------------------------------ - //
bool GelTarget::BindSubTarget( const int Layer ) {
	return ToSubTarget()->Bind( Layer );
}
// - ------------------------------------------------------------------------------------------ - //
void GelTarget::UnBindSubTarget() {
	ToSubTarget()->Parent->UnBind();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void placement_Screen_GelTarget( GelTarget* Out, const int _w = 0, const int _h = 0, const int ScreenIndex = 0 ) {
	GelScreenTarget* NT = new GelScreenTarget(_w,_h,ScreenIndex);

	new(Out) GelTarget(Gel::GT_SCREENTARGET,NT);
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTarget* new_Screen_GelTarget( const int _w = 0, const int _h = 0, const int ScreenIndex = 0 ) {
	GelScreenTarget* NT = new GelScreenTarget(_w,_h,ScreenIndex);

	return new GelTarget(Gel::GT_SCREENTARGET,NT);
}
// - ------------------------------------------------------------------------------------------ - //
inline void placement_Render_GelTarget( GelTarget* Out, const int _w, const int _h, const int Textures = 1, const int DepthBuffers = 1, const int StencilBuffers = 0, const bool UseMRT = false ) {
	GelRenderTarget* RT = new GelRenderTarget(_w,_h,Textures,DepthBuffers,StencilBuffers,UseMRT);

	new(Out) GelTarget(Gel::GT_RENDERTARGET,RT);
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTarget* new_Render_GelTarget(  const int _w, const int _h, const int Textures = 1, const int DepthBuffers = 1, const int StencilBuffers = 0, const bool UseMRT = false ) {
	GelRenderTarget* RT = new GelRenderTarget(_w,_h,Textures,DepthBuffers,StencilBuffers,UseMRT);

	return new GelTarget(Gel::GT_RENDERTARGET,RT);
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_GelTarget( GelTarget* In ) {
	delete In;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELTARGET_H__ //
// - ------------------------------------------------------------------------------------------ - //
