// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_MSVC_DEBUGGER
// - ------------------------------------------------------------------------------------------ - //
// Use MSVC Debugger Logging //
// - ------------------------------------------------------------------------------------------ - //
#define FLOG_FUNCV( ... )		vODSAprintf( __VA_ARGS__ )
#define FLOG_FUNC( ... )		ODSAprintf( __VA_ARGS__ )
// - ------------------------------------------------------------------------------------------ - //
#define _FLogFlush() ;
#define _FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
void FLogInit( const char* ) {
	CurrentFLogIndentation = 0;
}
// - ------------------------------------------------------------------------------------------ - //
void FLogExit() {	
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int vODSAprintf( const char* Format, va_list VArgs ) {
	int Size = 4*1024;
	char* Data = new char[Size];
	
	while( true ) {
		int Count = safe_vsprintf( Data, Size, Format, VArgs );

		// Borrowed from MLog, the resizer. Will Loop until the whole string is written. //
		if ( (Count < 0) || (Count >= Size) ) { // Not enough room (both versions) //
			Size += 4*1024;
			delete [] Data;
			Data = new char[Size];
		}
		else {
			// NOTE: Why this is slow: http://unixwiz.net/techtips/outputdebugstring.html
			OutputDebugStringA( Data );
			return Count;
		}
	};
}
// - ------------------------------------------------------------------------------------------ - //
int ODSAprintf( const char* Format, ... ) {
	va_list VArgs;
	va_start( VArgs, s );
	vODSAprintf( s, VArgs );
	va_end( VArgs );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_MSVC_DEBUGGER //
// - ------------------------------------------------------------------------------------------ - //
