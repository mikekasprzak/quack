// - ------------------------------------------------------------------------------------------ - //
#include "System.h"
// - ------------------------------------------------------------------------------------------ - //
namespace System {
// - ------------------------------------------------------------------------------------------ - //
Signal GainFocus;
Signal LoseFocus;

char BaseDir[4096] = "";
char SaveDir[4096] = "";

eGPU GPUVendor = GPU_NONE;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef ndebug
void DummyGain(void*) {
	Log( "** Focus Gained" );
}
void DummyLose(void*) {
	Log( "** Focus Lost" );
}
#endif // ndebug //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void Init() {
	atexit( Exit ) ;
	
#ifndef ndebug
	// Debug Builds Only, an extra signal function call that logs focus gained and lost //
	GainFocus.Connect( DummyGain );
	LoseFocus.Connect( DummyLose );
#endif // ndebug //

	TimeInit();
	GraphicsInit();
}
// - ------------------------------------------------------------------------------------------ - //
void Exit() {
	GraphicsExit();
	TimeExit();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace System //
// - ------------------------------------------------------------------------------------------ - //