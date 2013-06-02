// -------------------------------------------------------------------------- //
#include "Timer.h"
// -------------------------------------------------------------------------- //
#ifdef USES_BADA_TIMER
// -------------------------------------------------------------------------- //
#include <FSystem.h>
// -------------------------------------------------------------------------- //
using namespace Osp::System;
// -------------------------------------------------------------------------- //
int FrameRateConstant;
TIMEVALUE OneFrameConstant;
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
TIMEVALUE GetTimeNow() {
	TIMEVALUE Value;
	SystemTime::GetTicks( Value );
	return Value;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
TIMEVALUE AddTime( TIMEVALUE a, TIMEVALUE b ) {
	return a + b;
}
// -------------------------------------------------------------------------- //
TIMEVALUE SubtractTime( TIMEVALUE a, TIMEVALUE b ) {
	return a - b;
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
int GetFrames( TIMEVALUE* tv ) {
	return *tv / OneFrameConstant;
}
// -------------------------------------------------------------------------- //
void AddFrame( TIMEVALUE* tv ) {
	*tv = AddTime( *tv, OneFrameConstant );
}
// -------------------------------------------------------------------------- //
void AddFrames( TIMEVALUE* tv, const int Count ) {
	*tv = AddTime( *tv, OneFrameConstant * Count );
}
// -------------------------------------------------------------------------- //
void SetFramesPerSecond( const int Ticks ) {
	FrameRateConstant = Ticks;
	OneFrameConstant = (1000 / Ticks);
}
// -------------------------------------------------------------------------- //
void Wait( const int Ticks ) {
	// TODO: How do I sleep ? //
}
// -------------------------------------------------------------------------- //
#endif // USES_BADA_TIMER //
// -------------------------------------------------------------------------- //
