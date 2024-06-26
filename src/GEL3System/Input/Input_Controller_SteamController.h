// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_INPUT_INPUT_CONTROLLER_STEAMCONTROLLER_H__
#define __GEL_INPUT_INPUT_CONTROLLER_STEAMCONTROLLER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Math.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
	extern bool IsSteamRunning;
// - ------------------------------------------------------------------------------------------ - //
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
extern st32 IndexBase;
extern GelSteamPad Pad[];
// - ------------------------------------------------------------------------------------------ - //
void Init();
void InitEvent( void* = 0 );
void Poll();
void PollEvent( void* = 0 );
void Exit();
void ExitEvent( void* = 0 );

//void LoseFocusEvent( void* = 0 );
//void GainFocusEvent( void* = 0 );

void Pulse( const int Index, const int Motor, const int Amount );
void Vibrate( const int Index, const int Motor, const int Amount );

st32 Size();
st32 DevicesConnected();

bool IsConnected( const int Index );
bool IsConnected();

bool HasConnectionChanged( const int Index );
bool HasConnectionChanged();
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Steam //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Input //
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_INPUT_INPUT_CONTROLLER_STEAMCONTROLLER_H__ //
// - ------------------------------------------------------------------------------------------ - //
