// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "GelNativeTarget.h"
#include <System/GelScreen/GelScreens.h>
#include <System/GelScreen/GelScreens_Internal_SDL.h>
// - ------------------------------------------------------------------------------------------ - //
typedef GelNativeScreen NSType;
// - ------------------------------------------------------------------------------------------ - //
GelNativeTarget::GelNativeTarget( const int /*_w*/, const int /*_h*/, const int Index ) {
	// HACK! Ignore Dimensions, and use existing Native Indexes //
	Data = &Gel::Native[Index];
}
// - ------------------------------------------------------------------------------------------ - //
GelNativeTarget::~GelNativeTarget() {
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int GelNativeTarget::GetWidth() const {
	return ((NSType*)Data)->GetWidth();
}
// - ------------------------------------------------------------------------------------------ - //
int GelNativeTarget::GetHeight() const {
	return ((NSType*)Data)->GetHeight();
}
// - ------------------------------------------------------------------------------------------ - //
void GelNativeTarget::Bind() const {
	((NSType*)Data)->MakeCurrent();
}
// - ------------------------------------------------------------------------------------------ - //
void GelNativeTarget::Viewport( const int x, const int y, const int w, const int h ) const {
	((NSType*)Data)->UpdateViewport( x,y, w,h );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //