// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_INPUT_INPUT_CONTROLLER_XINPUT_H__
#define __GEL_INPUT_INPUT_CONTROLLER_XINPUT_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_XINPUT
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
namespace XInput {
// - ------------------------------------------------------------------------------------------ - //
// This exists so all the internal XInput stuff can be completely hidden away //
struct XGamePad {
	st32 Button;
	Vector2D LStick;
	Vector2D RStick;
	Real LTrigger;
	Real RTrigger;
	Vector2D DPad;
};
// - ------------------------------------------------------------------------------------------ - //
extern XGamePad GamePad[4];
// - ------------------------------------------------------------------------------------------ - //
void Init();
void InitEvent( void* = 0 );

void Poll();
void PollEvent( void* = 0 );

void LoseFocusEvent( void* = 0 );
void GainFocusEvent( void* = 0 );

void Pulse( const int Index, const int Motor, const int Amount );
void Vibrate( const int Index, const int Motor, const int Amount );

size_t Size();

size_t DevicesConnected();

bool IsConnected( const int Index );
bool IsConnected();

bool HasConnectionChanged( const int Index );
bool HasConnectionChanged();
// - ------------------------------------------------------------------------------------------ - //
}; // namespace XInput //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_XINPUT //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_INPUT_INPUT_CONTROLLER_XINPUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
