// - ------------------------------------------------------------------------------------------ - //
#include "Input.h"
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
GelSignal Poll; // Was void Poll() {} //
// - ------------------------------------------------------------------------------------------ - //
void Init() {
	st IndexBase = 0;
	#ifdef USES_STEAM
	Steam::InitEvent( (void*)IndexBase );
	IndexBase += Steam::Size();
	#endif // USES_STEAM //

	#ifdef USES_XINPUT
	XInput::InitEvent( (void*)IndexBase );
	IndexBase += XInput::Size();
	#endif // USES_XINPUT //
	
	#ifdef USES_SDL2
	SDLInput::InitEvent( (void*)IndexBase );
	IndexBase += SDLInput::Size();
	#endif // USES_SDL2 //
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	#ifdef USES_SDL2
	SDLInput::ExitEvent();
	#endif // USES_SDL2 //

	#ifdef USES_XINPUT
//	XInput::ExitEvent();
	#endif // USES_XINPUT //

	#ifdef USES_STEAM
	Steam::ExitEvent();
	#endif // USES_STEAM //
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
