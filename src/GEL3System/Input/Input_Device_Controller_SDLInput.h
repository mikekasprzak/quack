// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_INPUT_INPUT_DEVICE_CONTROLLER_SDLINPUT_H__
#define __GEL_INPUT_INPUT_DEVICE_CONTROLLER_SDLINPUT_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
namespace SDLInput {
// - ------------------------------------------------------------------------------------------ - //
struct SDLGamePad {
	Real Axis[8];	// 2 Axis Per Analog Stick, 1 per Analog Trigger //
	st32 Button;
	st32 Hat;		// DPad //
	//Vector2D Ball;
	
	Vector2D DPad;	// Hat in a more usable form //
	
	st32 NumAxis;	// An Axis Count //
};
// - ------------------------------------------------------------------------------------------ - //
enum { 
	MAX_GAMEPADS = 32
};
// - ------------------------------------------------------------------------------------------ - //
extern SDLGamePad GamePad[MAX_GAMEPADS];
// - ------------------------------------------------------------------------------------------ - //
void Exit();
void ExitEvent( void* = 0 );

void Init();
void InitEvent( void* = 0 );

void Poll();
void PollEvent( void* = 0 );

size_t Size();
size_t DevicesConnected();

bool Is360( int Index );
bool IsPS4( int Index );
// - ------------------------------------------------------------------------------------------ - //
}; // namespace SDLInput //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_INPUT_INPUT_DEVICE_CONTROLLER_SDLINPUT_H__ //
// - ------------------------------------------------------------------------------------------ - //