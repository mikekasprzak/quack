// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_THREADLOCAL_H__
#define __GEL_LIB_THREADLOCAL_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Handle exotic platforms
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_THREAD_LOCAL
	#define threadlocal __thread
#else // NO_THREAD_LOCAL //
	#define threadlocal
	#warning NO_THREAD_LOCAL used. Variables of 'threadlocal' type may be compromised.
#endif // NO_THREAD_LOCAL //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_THREADLOCAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
