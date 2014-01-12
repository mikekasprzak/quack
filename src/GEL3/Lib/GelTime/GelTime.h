// - ------------------------------------------------------------------------------------------ - //
// GelTime is a general time representing type.
//
// You can use GelTime for any timing operations you like, but of course if you compare them
//   you must make sure that the times are in the same timing units first.
//
// Time Units:
// - Current Time -- The current time of day.
// - Start Time -- The time since the application started.
// - Frame Time -- The number of frames that have passed while the app was active.
//
// Thoughts:
//   Frame Time (ft) should be the 
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add SDL Timer, and add a Stub Timer
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GELTIME_H__
#define __GEL_LIB_GELTIME_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelTypes.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// The Type //
// - ------------------------------------------------------------------------------------------ - //
typedef u64 GelTime;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Time Getting Functions //
// - ------------------------------------------------------------------------------------------ - //
// Start Time Functions -- The time since the application was started //
GelTime get_s_GelTime();			// Get the start time in seconds.
GelTime get_ms_GelTime();			// Get the start time in milliseconds (1000 per second).
GelTime get_us_GelTime();			// Get the start time in microseconds (1,000,000 per second).
// TIP: the 'u' in 'us' means Micro (µ) //
// - ------------------------------------------------------------------------------------------ - //
GelTime get_time_GelTime();			// Get the current time in seconds relative the epoc.
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// The Start Time //
inline GelTime stime_GelTime() {
	static GelTime StartTime = get_time_GelTime();
	return StartTime;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Init //
// - ------------------------------------------------------------------------------------------ - //
void gelsTimeInit();
// - ------------------------------------------------------------------------------------------ - //
//namespace Gel {
//	extern GelTime StartTime;
//}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
inline void gelTimeInit() {
	gelsTimeInit();	// Call the System Specific (gels) Time Init //
	
	// Store a copy of the original time when the app started. We can use this to convert //
	//   any Start Time to Current Time. Just add StartTime to any Start Time (in seconds). //
	stime_GelTime();
//	Gel::StartTime = get_time_GelTime();
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Conversion Functions //
// - ------------------------------------------------------------------------------------------ - //
inline GelTime us_to_s_GelTime( const GelTime Original ) {
	return Original / 1000000ull;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime ms_to_s_GelTime( const GelTime Original ) {
	return Original / 1000ull;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime us_to_ms_GelTime( const GelTime Original ) {
	return Original / 1000ull;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime s_to_us_GelTime( const GelTime Original ) {
	return Original * 1000000ull;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime s_to_ms_GelTime( const GelTime Original ) {
	return Original * 1000ull;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime ms_to_us_GelTime( const GelTime Original ) {
	return Original * 1000ull;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// NOTE: Will be somewhat inaccurate, since sub-seconds are gone in both //
// - ------------------------------------------------------------------------------------------ - //
inline GelTime s_to_time_GelTime( const GelTime Original ) {
	return stime_GelTime() + Original;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime ms_to_time_GelTime( const GelTime Original ) {
	return stime_GelTime() + ms_to_s_GelTime(Original);
}
// - ------------------------------------------------------------------------------------------ - //
inline GelTime us_to_time_GelTime( const GelTime Original ) {
	return stime_GelTime() + us_to_s_GelTime(Original);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GELTIME_H__ //
// - ------------------------------------------------------------------------------------------ - //
