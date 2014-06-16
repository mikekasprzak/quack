// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
#include "Log_FLog.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_FLOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int CurrentFLogIndentation = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Include the FLog targets //
// - ------------------------------------------------------------------------------------------ - //
#include "Log_FLog_Curses.cpp.h"
#include "Log_FLog_MSVC_Debugger.cpp.h"
#include "Log_FLog_STDOut.cpp.h"
#include "Log_FLog_SDLLog.cpp.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void FLogIndentation( int Count, const char Val = ' ' ) {
	// NOTE: We now have a limited number of Indentation Level... because it made MSVC simpler. //
	enum {
		INDENTATION_MAX = 128
	};
	
	if ( Count > 0 ) {
		char s[INDENTATION_MAX+1];

		if ( Count > INDENTATION_MAX )
			Count = INDENTATION_MAX;

		for ( int idx = 0; idx < Count; idx++ ) {
			s[idx] = Val;
		}
		s[Count] = 0;

#ifdef USES_CLANG
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"
#endif // USES_CLANG //

#ifdef USES_GCC
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-security"
#endif // USES_GCC //

		FLOG_FUNC( s );

#ifdef USES_GCC
#pragma GCC diagnostic pop
#endif // USES_GCC //

#ifdef USES_CLANG
#pragma clang diagnostic pop
#endif // USES_CLANG //
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void FPreLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		_FLogColor( LOG_INV_RED );
		FLogIndentation( CurrentFLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			_FLogColor( LOG_GREEN );
			FLogIndentation( CurrentFLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			_FLogColor( LOG_WHITE );
			FLogIndentation( CurrentFLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_FLogColor( LOG_MAGENTA );
			FLogIndentation( CurrentFLogIndentation, '>' );
		}
		else if ( s[0] == '+' ) {
			_FLogColor( LOG_YELLOW );
			FLogIndentation( CurrentFLogIndentation );

			CurrentFLogIndentation += 2;
		}
		else if ( s[0] == '-' ) {
			CurrentFLogIndentation -= 2;

			_FLogColor( LOG_YELLOW );
			FLogIndentation( CurrentFLogIndentation );
		}
	}
	else if ( s[1] == 0 ) {
		return;
	}
	else if ( s[2] == 0 ) {
		return;
	}
	else if ( s[0] == '-' ) {
		if ( s[1] == '=' ) {
			// Headline //
			_FLogColor( LOG_CYAN );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void FPostLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		_FLogColor( LOG_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			_FLogColor( LOG_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			_FLogColor( LOG_NORMAL );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_FLogColor( LOG_NORMAL );
		}
		else if ( s[0] == '+' ) {
			_FLogColor( LOG_NORMAL );
		}
		else if ( s[0] == '-' ) {
			_FLogColor( LOG_NORMAL );
		}
	}
	else if ( s[1] == 0 ) {
		return;
	}
	else if ( s[2] == 0 ) {
		return;
	}
	else if ( s[0] == '-' ) {
		if ( s[1] == '=' ) {
			// Headline //
			_FLogColor( LOG_NORMAL );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifndef USES_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
void FLogColor( const int InColor ) {
	_FLogColor( InColor );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogFlush() {
	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void FLogAlways( const char* s, va_list vargs ) {
	FPreLog( s );
	FLOG_FUNCV( s, vargs );
	FPostLog( s );

#ifndef USES_NO_NEWLINES
#ifndef USES_LESS_NEWLINES
	FLOG_FUNC( (char*)"\n" );
#else // USES_LESS_NEWLINES // 
	// Only print newlines on empty strings //
	if ( strlen(s) == 0 ) {
		FLOG_FUNC( (char*)"\n" );
	}		
#endif // USES_LESS_NEWLINES //
#endif // USES_NO_NEWLINES //

	_FLogFlush();
}
// - ------------------------------------------------------------------------------------------ - //
void _FLogAlways( const char* s, va_list vargs ) {
	FPreLog( s );
	FLOG_FUNCV( s, vargs );
	FPostLog( s );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // NO_FLOGGING //
// - ------------------------------------------------------------------------------------------ - //
