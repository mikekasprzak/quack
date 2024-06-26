// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS_TIME
// - ------------------------------------------------------------------------------------------ - //
#include "SysSleep.h"
#include <windows.h>
// - ------------------------------------------------------------------------------------------ - //
void gelSysSleep( const GelTime _Seconds ) {
	Sleep( _Seconds * 1000 );
}
// - ------------------------------------------------------------------------------------------ - //
void gelSysMSleep( const GelTime _Milliseconds ) {
	Sleep( _Milliseconds );
}
// - ------------------------------------------------------------------------------------------ - //
void gelSysUSleep( const GelTime _Microseconds ) {
	Sleep( _Microseconds / 1000 );
}
// - ------------------------------------------------------------------------------------------ - //
void gelSysYield() {
	Sleep( 0 );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS_TIME //
// - ------------------------------------------------------------------------------------------ - //
