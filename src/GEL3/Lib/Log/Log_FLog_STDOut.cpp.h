// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_STDOUT) || defined(USES_LOGCAT)
// - ------------------------------------------------------------------------------------------ - //
// Standard Output FLog Implementation //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_STDOUT
// - ------------------------------------------------------------------------------------------ - //
FILE* FLOG_TARGET = 			stdout;
#define FLOG_FUNCV( ... )		vfprintf( FLOG_TARGET, __VA_ARGS__ )
#define FLOG_FUNC( ... )		fprintf( FLOG_TARGET, __VA_ARGS__ )
#define FLOG_PFUNC( arg )		fputs( arg, FLOG_TARGET )

inline void _FLogFlush() {
	fflush( FLOG_TARGET );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STDOUT //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Android LogCat (adb logcat) Implementation //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_LOGCAT
// - ------------------------------------------------------------------------------------------ - //
#include <android/log.h>
#include <Main/Main_Product.h>

inline void __fixed_log_vprint( const char* Format, va_list Args ) {
	char Text[(1024-128)*8];
	vsprintf( Text, Format, Args );
	
	int Offset = 0;
	int Len = strlen(Text);
	char Text2[1024-128+1];
	Text2[1024-128] = 0;
	while ( Len > (1024-128) ) {
		memcpy(Text2,&Text[Offset],1024-128);
		const char* Out = Text2;
		__android_log_print( ANDROID_LOG_DEBUG, ProductName, "%s", Out );
		Offset += 1024-128;
		Len -= 1024-128;
	};

	const char* Out = &Text[Offset];
	__android_log_print( ANDROID_LOG_DEBUG, ProductName, "%s", Out );
}


inline void __fixed_log_print( const char* Format, ... ) {
	va_list Args;
	va_start( Args, Format );
	__fixed_log_vprint( Format, Args );
	va_end( Args );
}

FILE* FLOG_TARGET = 			stdout;
#define FLOG_FUNCV( ... )		__fixed_log_vprint( __VA_ARGS__ )
#define FLOG_FUNC( ... )		__fixed_log_print( __VA_ARGS__ )

// These can print a max of 1024 characters total //
//#define FLOG_FUNCV( ... )		__android_log_vprint( ANDROID_LOG_DEBUG, ProductName, __VA_ARGS__ )
//#define FLOG_FUNC( ... )		__android_log_print( ANDROID_LOG_DEBUG, ProductName, __VA_ARGS__ )

inline void _FLogFlush() {
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_LOGCAT //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
#define ANSI_HEADER					"\033["

#define ANSI_NORMAL					"\033[0m"
#define ANSI_RESET					ANSI_NORMAL
#define ANSI_NEGATIVE				"\033[7m"

#define ANSI_BLACK					"\033[0;30m"
#define ANSI_RED					"\033[0;31m"
#define ANSI_GREEN					"\033[0;32m"
#define ANSI_BROWN					"\033[0;33m"
#define ANSI_BLUE					"\033[0;34m"
#define ANSI_MAGENTA				"\033[0;35m"
#define ANSI_CYAN					"\033[0;36m"
#define ANSI_LIGHT_GRAY				"\033[0;37m"
#define ANSI_DARK_GRAY				"\033[1;30m"
#define ANSI_LIGHT_RED				"\033[1;31m"
#define ANSI_LIGHT_GREEN			"\033[1;32m"
#define ANSI_YELLOW					"\033[1;33m"
#define ANSI_LIGHT_BLUE				"\033[1;34m"
#define ANSI_LIGHT_MAGENTA			"\033[1;35m"
#define ANSI_LIGHT_CYAN				"\033[1;36m"
#define ANSI_WHITE					"\033[1;37m"

#define ANSI_INV_BLACK				"\033[0;40m"
#define ANSI_INV_RED				"\033[0;41m"
#define ANSI_INV_GREEN				"\033[0;42m"
#define ANSI_INV_BROWN				"\033[0;43m"
#define ANSI_INV_BLUE				"\033[0;44m"
#define ANSI_INV_MAGENTA			"\033[0;45m"
#define ANSI_INV_CYAN				"\033[0;46m"
#define ANSI_INV_LIGHT_GRAY			"\033[0;47m"
#define ANSI_INV_DARK_GRAY			"\033[1;40m"
#define ANSI_INV_LIGHT_RED			"\033[1;41m"
#define ANSI_INV_LIGHT_GREEN		"\033[1;42m"
#define ANSI_INV_YELLOW				"\033[1;43m"
#define ANSI_INV_LIGHT_BLUE			"\033[1;44m"
#define ANSI_INV_LIGHT_MAGENTA		"\033[1;45m"
#define ANSI_INV_LIGHT_CYAN			"\033[1;46m"
#define ANSI_INV_WHITE				"\033[1;47m"
// - ------------------------------------------------------------------------------------------ - //
const char* const ANSIColorTable[] = {
	ANSI_BLACK,
	ANSI_RED,
	ANSI_GREEN,
	ANSI_BROWN,
	ANSI_BLUE,
	ANSI_MAGENTA,
	ANSI_CYAN,
	ANSI_LIGHT_GRAY,
	ANSI_DARK_GRAY,
	ANSI_LIGHT_RED,
	ANSI_LIGHT_GREEN,
	ANSI_YELLOW,
	ANSI_LIGHT_BLUE,
	ANSI_LIGHT_MAGENTA,
	ANSI_LIGHT_CYAN,
	ANSI_WHITE,
	
	ANSI_INV_BLACK,
	ANSI_INV_RED,
	ANSI_INV_GREEN,
	ANSI_INV_BROWN,
	ANSI_INV_BLUE,
	ANSI_INV_MAGENTA,
	ANSI_INV_CYAN,
	ANSI_INV_LIGHT_GRAY,
	ANSI_INV_DARK_GRAY,
	ANSI_INV_LIGHT_RED,
	ANSI_INV_LIGHT_GREEN,
	ANSI_INV_YELLOW,
	ANSI_INV_LIGHT_BLUE,
	ANSI_INV_LIGHT_MAGENTA,
	ANSI_INV_LIGHT_CYAN,
	ANSI_INV_WHITE
};
// - ------------------------------------------------------------------------------------------ - //
inline void __FLogColor( const char* ColorString ) {
	// Only output color codes when the target is stdout (no color codes in text files) //
	if ( FLOG_TARGET == stdout )
		FLOG_PFUNC( ColorString );
//		FLOG_FUNC( ColorString );
}
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogColor( const int Color ) {
	if ( Color >= 0 )
		__FLogColor( ANSIColorTable[ Color ] );
	else
		__FLogColor( ANSI_NORMAL );
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define _FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogInit( const char* TargetFile ) {
	CurrentFLogIndentation = 0;

	if ( TargetFile ) {
		FLOG_TARGET = fopen( TargetFile, "wb" );
	}
}
// - ------------------------------------------------------------------------------------------ - //
void FLogExit() {
	if ( FLOG_TARGET != stdout ) {
		fclose( FLOG_TARGET );
		FLOG_TARGET = stdout;
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STDOUT //
// - ------------------------------------------------------------------------------------------ - //
