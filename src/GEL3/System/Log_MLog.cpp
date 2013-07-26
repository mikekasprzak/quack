// - ------------------------------------------------------------------------------------------ - //
#include "Log.h"
#include "Log_MLog.h"
// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_MLOGGING
// - ------------------------------------------------------------------------------------------ - //
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int CurrentMLogIndentation = 0;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Memory Log Implimentation //
// - ------------------------------------------------------------------------------------------ - //
struct MLogType {
	int Size;		// How Large the Data is //
	int Used;		// How much space is Used //
	char* Data;		// The Data //

	MLogType() {
		Size = 32*1024;						// Start with a 32k buffer //
		Data = new char[Size];				// Allocate Memory //
		Used = 0;							// No space used yet //

		Data[Used] = 0;						// Null Terminate (Alloc ensures there will be room) //		
	}
	
	~MLogType() {
		if ( Data ) {
			delete [] Data;
		}
	}
	
	void Grow() {
		char* OldData = Data;				// Store Old Pointer //
		
		Size += 32*1024;					// Add 32k more buffer size //
		Data = new char[Size];				// Alloc new Memory //
		
		memcpy( Data, OldData, Used );		// Copy the good part over //
		
		Data[Used] = 0;						// Null Terminate (Alloc ensures there will be room) //
		
		delete [] OldData;					// Delete the Old Data now that we're done with it //
	}
};
// - ------------------------------------------------------------------------------------------ - //
MLogType* MLOG_TARGET = 0;

#define MLOG_FUNCV( ... )		vMEMprintf( MLOG_TARGET, __VA_ARGS__ )
#define MLOG_FUNC( ... )		MEMprintf( MLOG_TARGET, __VA_ARGS__ )
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void MLogInit() {
	CurrentMLogIndentation = 0;
	MLOG_TARGET = new MLogType;
}
// - ------------------------------------------------------------------------------------------ - //
void MLogExit() {
	delete MLOG_TARGET;
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetMLogData() {
	return MLOG_TARGET->Data;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int vMEMprintf( MLogType* Dest, const char* Format, va_list VArgs ) {	
#ifdef _MSC_VER
	while( true ) {
		int Diff = Dest->Size - Dest->Used;
		int Count = vsprintf_s( 
			&(Dest->Data[ Dest->Used ]),
			Diff,
			Format, 
			VArgs 
			);

		if ( Count < 0 ) { // Less than Zero (vsprintf_s) not enough room //
			Dest->Grow();
		}
		else {
			Dest->Used += Count;
			return Count;
		}
	};
#else // GCC or CLANG //
	while( true ) {
		int Diff = Dest->Size - Dest->Used;
		int Count = vsnprintf( 
			&(Dest->Data[ Dest->Used ]),
			Diff,
			Format,
			VArgs 
			);
		
		if ( Count >= Diff ) { // Greater & Equal (vsnprintf) not enough room
			Dest->Grow();
		}
		else if ( Count < 0 ) {
			// Less than zero, meaning there was an error building the string //
			return 0;//Count;
		}
		else {
			Dest->Used += Count;
			return Count;
		}
	};
#endif // _MSC_VER //
}
// - ------------------------------------------------------------------------------------------ - //
int MEMprintf( MLogType* Dest, const char* Format, ... ) {
	va_list VArgs;
	va_start( VArgs, Format );
	int Count = vMEMprintf( Dest, Format, VArgs );
	va_end( VArgs );
	
	return Count;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#ifndef NO_MLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void _MLogColor( const int Color ) {
	// TODO: Interpret Color as some sort of color code //
}
// - ------------------------------------------------------------------------------------------ - //
#else // NO_MLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define _MLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_MLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void MLogIndentation( int Count, const char Val = ' ' ) {
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

		MLOG_FUNC( s );
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void MPreLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		_MLogColor( LOG_INV_RED );
		MLogIndentation( CurrentMLogIndentation, '!' );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star+ //
			_MLogColor( LOG_GREEN );
			MLogIndentation( CurrentMLogIndentation, '*' );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
			MLogIndentation( CurrentMLogIndentation );
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_MLogColor( LOG_MAGENTA );
			MLogIndentation( CurrentMLogIndentation, '>' );
		}
		else if ( s[0] == '+' ) {
			_MLogColor( LOG_YELLOW );
			MLogIndentation( CurrentMLogIndentation );

			CurrentMLogIndentation += 2;
		}
		else if ( s[0] == '-' ) {
			CurrentMLogIndentation -= 2;

			_MLogColor( LOG_YELLOW );
			MLogIndentation( CurrentMLogIndentation );
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
			_MLogColor( LOG_CYAN );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
// String only, so we can take action //
inline void MPostLog( const char* s ) {
	if ( s[0] == 0 ) {
		return;
	}
	else if ( s[0] == '!' ) {
		_MLogColor( LOG_NORMAL );
	}
	else if ( s[0] == '*' ) {
		if ( s[1] == '*' ) {
			// Double Star //
			_MLogColor( LOG_NORMAL );
		}
		else if ( s[1] == ' ' ) {
			// Single Star //
		}
	}
	else if ( s[1] == ' ' ) {
		if ( s[0] == '>' ) {
			_MLogColor( LOG_NORMAL );
		}
		else if ( s[0] == '+' ) {
			_MLogColor( LOG_NORMAL );
		}
		else if ( s[0] == '-' ) {
			_MLogColor( LOG_NORMAL );
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
			_MLogColor( LOG_NORMAL );
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef NO_MLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
void MLogColor( const int InColor ) {
	_MLogColor( InColor );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // NO_MLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void MLogFlush() {
}
// - ------------------------------------------------------------------------------------------ - //
void MLogAlways( const char* s, va_list vargs ) {
	MPreLog( s );
	MLOG_FUNCV( s, vargs );
	MPostLog( s );

	MLOG_FUNC( (char*)"\n" );
}
// - ------------------------------------------------------------------------------------------ - //
void _MLogAlways( const char* s, va_list vargs ) {
	MPreLog( s );
	MLOG_FUNCV( s, vargs );
	MPostLog( s );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // NO_MLOGGING //
// - ------------------------------------------------------------------------------------------ - //
