// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_CURSES
// - ------------------------------------------------------------------------------------------ - //
// Curses FLog Implimentation //
// - ------------------------------------------------------------------------------------------ - //
#ifdef _WIN32
	#undef MOUSE_MOVED
	#include <curses.h>
#else // Linux //
	#include <ncurses.h>
#endif // _WIN32
// - ------------------------------------------------------------------------------------------ - //
WINDOW* FLOG_TARGET = 			0; // stdscr not initialized until init //
#define FLOG_FUNCV( ... )		vwprintw( FLOG_TARGET, __VA_ARGS__ )
#define FLOG_FUNC( ... )		wprintw( FLOG_TARGET, __VA_ARGS__ )
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogFlush() {
	refresh();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_FLOG_COLORS
// - ------------------------------------------------------------------------------------------ - //
inline void _FLogColor( const int InColor ) {
	if ( InColor < 0 ) {
		standend();
	}
	else {
		int Color = InColor & 7;
		if ( Color == 0 )
			Color = 8;
	
		attrset( 
			COLOR_PAIR(Color) | 
			(((InColor & 15) > 7) ? A_BOLD : A_NORMAL) |
			((InColor > 15) ? A_REVERSE : A_NORMAL)
			);
	}
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //
#define _FLogColor( ... ) ;
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_FLOG_COLORS //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void FLogInit( const char* ) {
	CurrentFLogIndentation = 0;

	FLOG_TARGET = initscr();	// Default Init //

//	//raw();					// CTRL-Z and CTRL-C *DON'T* trigger signals //
//	cbreak();					// CTRL-Z and CTRL-C trigger signals //
//	//halfdelay(1);				// Calls to getch() return 'ERR' if no key pressed. Time in 10ths //
//	nodelay( stdscr, TRUE );	// Non-Blocking getch(). Returns 'ERR' if no key pressed //
//	keypad( stdscr, TRUE ); 	// Enable Arrow Keys, Function Keys, etc //
//	noecho();					// User input not displayed. "echo()" to display //

	start_color();				// Enable Color //

	init_pair( 1, COLOR_RED, 		COLOR_BLACK );
	init_pair( 2, COLOR_GREEN,		COLOR_BLACK );
	init_pair( 3, COLOR_YELLOW,		COLOR_BLACK );
	init_pair( 4, COLOR_BLUE,		COLOR_BLACK );
	init_pair( 5, COLOR_MAGENTA,	COLOR_BLACK );
	init_pair( 6, COLOR_CYAN,		COLOR_BLACK );
	init_pair( 7, COLOR_WHITE,		COLOR_BLACK );
	init_pair( 8, COLOR_BLACK, 		COLOR_BLACK );
}
// - ------------------------------------------------------------------------------------------ - //
void FLogExit() {	
	endwin();	// Shutdown Curses //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_CURSES //
// - ------------------------------------------------------------------------------------------ - //
