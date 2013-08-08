// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_UNIX_TIME
// - ------------------------------------------------------------------------------------------ - //
#include "SysSleep.h"
#include <unistd.h>
#include <time.h>
// - ------------------------------------------------------------------------------------------ - //
// If Priority Scheduling is available (defined in unistd), include sched.h //
#ifdef _POSIX_PRIORITY_SCHEDULING
#include <sched.h>
#endif // _POSIX_PRIORITY_SCHEDULING //
// - ------------------------------------------------------------------------------------------ - //
void gelSysSleep( const GelTime _Seconds ) {
	gelSysUSleep( _Seconds * 1000000000ll );
//	usleep( _Seconds * 1000 );
}
// - ------------------------------------------------------------------------------------------ - //
void gelSysMSleep( const GelTime _Milliseconds ) {
	gelSysUSleep( _Milliseconds * 1000000ll );
//	usleep( _Milliseconds );
}
// - ------------------------------------------------------------------------------------------ - //
void gelSysUSleep( const GelTime _Microseconds ) {
	timespec SleepTime;
	SleepTime.tv_sec = _Microseconds / 1000000000ll;
	SleepTime.tv_nsec = _Microseconds % 1000000000ll;
	nanosleep( &SleepTime, 0 );	// Arg #2 is the remainder (unslept time), if I wanted to do something with that //
//	usleep( _Microseconds / 1000 );
}
// - ------------------------------------------------------------------------------------------ - //
void gelSysYield() {
#ifdef _POSIX_PRIORITY_SCHEDULING
	sched_yield();
#else // !_POSIX_PRIORITY_SCHEDULING //
	gelSysUSleep( 1 );
#endif // _POSIX_PRIORITY_SCHEDULING //
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_UNIX_TIME //
// - ------------------------------------------------------------------------------------------ - //
