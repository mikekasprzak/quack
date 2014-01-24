// - ------------------------------------------------------------------------------------------ - //
#include "Input.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
GelSignal Poll; // Was void Poll() {} //
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	#ifdef USES_XINPUT
	XInput::InitEvent();
	#endif // USES_XINPUT //

	#ifdef USES_STEAM
	Steam::InitEvent();
	#endif // USES_STEAM //
	
	#ifdef USES_SDL2
	SDLInput::InitEvent();
	#endif // USES_SDL2 //
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	#ifdef USES_XINPUT
//	XInput::ExitEvent();
	#endif // USES_XINPUT //

	#ifdef USES_STEAM
	Steam::ExitEvent();
	#endif // USES_STEAM //
	
	#ifdef USES_SDL2
	SDLInput::ExitEvent();
	#endif // USES_SDL2 //
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
