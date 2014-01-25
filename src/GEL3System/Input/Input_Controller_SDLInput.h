// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_INPUT_INPUT_CONTROLLER_SDLINPUT_H__
#define __GEL_INPUT_INPUT_CONTROLLER_SDLINPUT_H__
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
extern st32 IndexBase;
extern st32 ProxyIndexBase;
extern SDLGamePad Pad[];
// - ------------------------------------------------------------------------------------------ - //
void Exit();
void ExitEvent( void* = 0 );

void Init();
void InitEvent( void* = 0 );

void Poll();
void PollEvent( void* = 0 );

void Pulse( const int Index, const int Motor, const int Amount );
void Vibrate( const int Index, const int Motor, const int Amount );

st32 Size();
st32 DevicesConnected();

bool Is360( int Index );
bool IsPS4( int Index );
// - ------------------------------------------------------------------------------------------ - //
}; // namespace SDLInput //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //	
extern bool KeyESC;
extern bool KeyRefresh;

extern int KeyFakeLStick;
extern int KeyFakeRStick;
extern int KeyFakeButtons;

enum {
	KEY_UP = 	0x1,
	KEY_DOWN = 	0x2,
	KEY_LEFT = 	0x4,
	KEY_RIGHT =	0x8,
	
	KEY_L =		0x10,
	KEY_R =		0x20,
	KEY_MENU = 	0x40,
	KEY_EXTRA = 0x80,
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_INPUT_INPUT_CONTROLLER_SDLINPUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
