// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_APP_H__
#define __QUACK_APP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include "GelProfiler.h"
// - ------------------------------------------------------------------------------------------ - //
namespace App {
// - ------------------------------------------------------------------------------------------ - //
enum /* eAppMode */ {
	AM_NULL			= 0,		// Mode NULL (i.e. Error) //
	AM_ERROR		= AM_NULL,	// Mode ERROR (same as Null ) //
	AM_MAIN			= 1,		// Standard Main Function //
	AM_GAMELOOP		= 2,		// Game Loop Mode (Step Draw) //
	AM_ENGINE		= 3,		// Engine Mode (Objects) //
};
// - ------------------------------------------------------------------------------------------ - //
extern int Mode;
void SetMode( const int _Mode );
const char* GetModeName();
const char* GetModeName( const int _Mode );
// - ------------------------------------------------------------------------------------------ - //
extern bool Exit;				// Do we Exit? //
extern GelTime FrameTime;		// Current Frame Executed (according to GameLoop Step) //
// - ------------------------------------------------------------------------------------------ - //
// For recording profiling information about the two functions //
extern GelProfiler StepProfiler;
extern GelProfiler DrawProfiler;
// - ------------------------------------------------------------------------------------------ - //
// Signals for triggering things on focus gain and lose //
extern GelSignal GainFocus;
extern GelSignal LoseFocus;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace App //
// - ------------------------------------------------------------------------------------------ - //
void AppInit();
void AppExit();

void AppStep();
void AppDraw();

void AppGainFocus();
void AppLoseFocus();
void AppRequestExit();
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_APP_H__ //
// - ------------------------------------------------------------------------------------------ - //
