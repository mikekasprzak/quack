// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_INPUT_INPUT_DEVICE_CONTROLLER_STEAMCONTROLLER_H__
#define __GEL_INPUT_INPUT_DEVICE_CONTROLLER_STEAMCONTROLLER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Math.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
namespace Input {
// - ------------------------------------------------------------------------------------------ - //
namespace Steam {
// - ------------------------------------------------------------------------------------------ - //
// This exists so all the internal SteamController stuff can be completely hidden away //
struct GelSteamPad {
	st32 Button;
	Vector2D LStick;
	Vector2D RStick;
//	Real LTrigger;
//	Real RTrigger;
//	Vector2D DPad;
};
// - ------------------------------------------------------------------------------------------ - //
extern GelSteamPad SteamPad[16];
// - ------------------------------------------------------------------------------------------ - //
void Init();
void InitEvent( void* = 0 );
void Poll();
void PollEvent( void* = 0 );
void Exit();
void ExitEvent( void* = 0 );

//void LoseFocusEvent( void* = 0 );
//void GainFocusEvent( void* = 0 );

size_t Size();

size_t DevicesConnected();

bool IsConnected( const int Index );
bool IsConnected();

bool HasConnectionChanged( const int Index );
bool HasConnectionChanged();
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Steam //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_INPUT_INPUT_DEVICE_CONTROLLER_STEAMCONTROLLER_H__ //
// - ------------------------------------------------------------------------------------------ - //
