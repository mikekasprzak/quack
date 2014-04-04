// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_DEBUG_Depricated_H__
#define __GEL_DEBUG_Depricated_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef __GNUC__
// - ------------------------------------------------------------------------------------------ - //
#define DEPRECATED(func) func __attribute__ ((deprecated))
// - ------------------------------------------------------------------------------------------ - //
#elif defined(_MSC_VER)
// - ------------------------------------------------------------------------------------------ - //
#define DEPRECATED(func) __declspec(deprecated) func
// - ------------------------------------------------------------------------------------------ - //
#else // Unknown Compiler //
// - ------------------------------------------------------------------------------------------ - //
#pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#define DEPRECATED(func) func
// - ------------------------------------------------------------------------------------------ - //
#endif // Compiler //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_DEBUG_Depricated_H__ //
// - ------------------------------------------------------------------------------------------ - //