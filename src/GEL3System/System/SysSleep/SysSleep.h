// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_SYSSLEEP_H__
#define __GEL_SYSTEM_SYSSLEEP_H__
// - ------------------------------------------------------------------------------------------ - //
void gelSysSleep( const int _Seconds );			// Whole Seconds //
void gelSysMSleep( const int _Milliseconds );	// Milliseconds (1000 per Second) //
void gelSysUSleep( const int _Microseconds );	// Microseconds (1000000 per Second) //
void gelSysYield();								// Yeild to the CPU (sometimes "sleep(0);") //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_SYSSLEEP_H__ //
// - ------------------------------------------------------------------------------------------ - //
