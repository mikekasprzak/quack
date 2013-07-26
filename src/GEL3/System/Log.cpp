// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_LOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Log_FLog.h"
#include "Log_MLog.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(DEFAULT_LOG_LEVEL)
	int LogLevel = DEFAULT_LOG_LEVEL;
#elif defined(LOG_LEVEL)
	int LogLevel = LOG_LEVEL;
#else // LOG_LEVEL //
	int LogLevel = 1; // Default level is 1, primary logging only, but all levels are recorded //
#endif // LOG_LEVEL //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Assert code has an optional _Assert method, and a following AssertFlush, for chaining asserts //
// - ------------------------------------------------------------------------------------------ - //
extern bool _AssertFlush;
bool _AssertFlush = false;
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void LogColor( const int Color ) {
	FLogColor( Color );
	MLogColor( Color );
}
// - ------------------------------------------------------------------------------------------ - //
void LogAlways( const char* s, ... ) {
	// These had to be seperate (no sharing vargs) because of Linux 64 //
	{
		va_list vargs;
		va_start( vargs, s );
		FLogAlways( s, vargs );
		va_end( vargs );
	}
	// These had to be seperate (no sharing vargs) because of Linux 64 //
	{
		va_list vargs;
		va_start( vargs, s );
		MLogAlways( s, vargs );
		va_end( vargs );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void _LogAlways( const char* s, ... ) {
	// These had to be seperate (no sharing vargs) because of Linux 64 //
	{
		va_list vargs;
		va_start( vargs, s );
		_FLogAlways( s, vargs );
		va_end( vargs );
	}
	// These had to be seperate (no sharing vargs) because of Linux 64 //
	{
		va_list vargs;
		va_start( vargs, s );
		_MLogAlways( s, vargs );
		va_end( vargs );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// NOTE: vprintf style, so these can be nested inside new printf style functions //
// - ------------------------------------------------------------------------------------------ - //
void vLogAlways( const char* s, va_list vargs ) {
	FLogAlways( s, vargs );
	MLogAlways( s, vargs );
}
// - ------------------------------------------------------------------------------------------ - //
void _vLogAlways( const char* s, va_list vargs ) {
	_FLogAlways( s, vargs );
	_MLogAlways( s, vargs );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void LogFlush() {
	FLogFlush();
	MLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void LogExit() {
	// Flush //
	LogFlush();
	
	// Exit //
	FLogExit();
	MLogExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef __unix
#include <unistd.h>		// getpid()

int GetPID() {
	return (int)getpid();
}
#endif // __unix //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int GetPID() {
	return GetCurrentProcessId();
}
#endif // _WIN32 //
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_3DS) || defined(USES_WIIU) || defined(USES_PSP)
int GetPID() {
	// STUB //
	return 1;
}
#endif // defined(USES_3DS) || defined(USES_WIIU) || defined(USES_PSP) //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Main/Main_HgVersion.h>
#include <Main/Main_Product.h>
// - ------------------------------------------------------------------------------------------ - //
#include <time.h>
// - ------------------------------------------------------------------------------------------ - //
void LogInit( const char* TargetFile ) {
	FLogInit( TargetFile );
	MLogInit();

	atexit(LogExit);

	// Embedded LogLevel Test (since Log isn't available... yet) //
	if ( LogLevel >= 1 ) {
		time_t rawtime;
		struct tm* timeinfo;
		
		time( &rawtime );
		timeinfo = localtime( &rawtime );
		
//		__BASE_FILE__ is a lot like __FILE__
//		__TIMESTAMP__ -- Source File Time Stamp
		
		// asctime adds a "\n" //
		_LogAlways( "-=- Logging Started -- PID: %i -- %s", GetPID(), asctime(timeinfo) );
	}

	LogAlways( "-=======- GEL3 Application Started -- %s Branch -- SKU: %s -=======-", PRODUCT_BRANCH_NAME, PRODUCT_SKU );
	LogAlways( "GEL (C) Copyright 2008-2014 Mike Kasprzak and Sykhronics Entertainment" );
	LogAlways( "" );
	LogAlways( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	LogAlways( "Hg Revision: %i [%s]", HG_VERSION, HG_HASH );
	LogAlways( "Compiled on: %s %s", __DATE__, __TIME__ );
	LogAlways( "" );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // NO_LOGGING //
// - ------------------------------------------------------------------------------------------ - //
