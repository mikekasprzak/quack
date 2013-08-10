// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_SYSSLEEP_H__
#define __GEL_SYSTEM_SYSSLEEP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelTime/GelTime.h>
// - ------------------------------------------------------------------------------------------ - //
void gelSysSleep( const GelTime _Seconds );			// Whole Seconds //
void gelSysMSleep( const GelTime _Milliseconds );	// Milliseconds (1000 per Second) //
void gelSysUSleep( const GelTime _Microseconds );	// Microseconds (1000000 per Second) //
void gelSysYield();									// Yeild to the CPU (sometimes "sleep(0);") //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_SYSSLEEP_H__ //
// - ------------------------------------------------------------------------------------------ - //
