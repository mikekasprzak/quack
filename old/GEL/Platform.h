// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_PLATFORM_H__
#define __GEL_PLATFORM_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(EMSCRIPTEN) || defined(USES_UNIX) || defined(USES_IOS) || defined(USES_WEBOS) || defined(USES_BLACKBERRY)
// - ------------------------------------------------------------------------------------------ - //

#define USES_C_FILEHANDLER
#define USES_UNIX_TIMER
#define USES_UNIX_DIR

// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WINDOWS)
// - ------------------------------------------------------------------------------------------ - //

#define USES_C_FILEHANDLER
#define USES_WINDOWS_TIMER

// Only use Windows-Style directories with MSVC //
#ifdef _MSC_VER
#define USES_WINDOWS_DIR
#else
#define USES_UNIX_DIR
#endif // _MSC_VER //

// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_ANDROID)
// - ------------------------------------------------------------------------------------------ - //

#define USES_C_FILEHANDLER
#define USES_UNIX_TIMER
#define USES_STUB_DIR

// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_MARMALADE)
// - ------------------------------------------------------------------------------------------ - //

#define USES_C_FILEHANDLER
#define USES_UNIX_TIMER
#define USES_UNIX_DIR

//#define USES_STUB_DIR
//#define USES_FAKE_DIR

// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PS3)
// - ------------------------------------------------------------------------------------------ - //

#define USES_C_FILEHANDLER

// - ------------------------------------------------------------------------------------------ - //
#else // USES //
// - ------------------------------------------------------------------------------------------ - //
#error "UNKNOWN PLATFORM"
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_PLATFORM_H__ //
// - ------------------------------------------------------------------------------------------ - //