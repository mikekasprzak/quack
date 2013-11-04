// - -------------------------------------------------------------------------------------------------------------- - //
// Create Qk namespace (for global Quack variable) //
Qk <- {};
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// Logs to the console (can also use print, but this is more Gel consistent) //
function Log(...) {
	//print( format(str,vargv) );		// This does not work //
	for ( local idx = 0; idx < vargv.len(); idx++ ) {
		print(vargv[idx]);
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Recursively request all files passed to this //
function require( ... ) {
	// CLEVER: Will recursively iterate through all arrays deep in arguments to find files to require. //
	function recursive( files ) {
		for ( local idx = 0; idx < files.len(); idx++ ) {
			if ( typeof files[idx] == "array" ) {
				recursive( files[idx] );
			}
			else if ( typeof files[idx] == "string" ) {
				qkRequireFile( files[idx] );
			}
		}
	};

	recursive( vargv );
}
// - -------------------------------------------------------------------------------------------------------------- - //
function gen_string( char, count ) {
	local Ret = ""
	for ( local idx = 0; idx < count; idx++ ) {
		Ret += char;
	}
	return Ret;
}
// - -------------------------------------------------------------------------------------------------------------- - //
function print_table( table, level = 0, name = "" ) {
	const Indent = "  ";
	local Prefix = gen_string(Indent,level);
	if ( typeof(table) == "table" ) {
		print( Prefix + "+ " + name + "[" + typeof(table) + "]: " + table.len() + " elements" );
		foreach ( idx, val in table ) {
			if ( typeof(val) == "table" ) {
				print_table( val, level+1, idx + " " );
			}
			else {
				print( Prefix + Indent + "* " + idx + " [" + typeof(val) + "]: " + val );
			}
		}
		print( Prefix + "- " + name + "[" + typeof(table) + "] ends." );
	}
	else {
		print( Prefix + "* [" + typeof(table) + "]: " + table );
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //
function RGBA( r, g, b, a ) {
	return ((r<<0) & 0xff) | ((g<<8) & 0xff00) | ((b<<16) & 0xff0000) | ((a<<24) & 0xff000000);
}
// - -------------------------------------------------------------------------------------------------------------- - //
function RGB( r, g, b ) {
	return ((r<<0) & 0xff) | ((g<<8) & 0xff00) | ((b<<16) & 0xff0000) | (0xff000000);
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _DefaultSetup() {
	Log("# Setup (_DefaultSetup)");

	if ( qkIsDevMode() ) {
		Log("# Dev Mode Detected.");
		qkSetScreenScalar( 0.8 );
	}
	qkInitScreens();	
}
// - -------------------------------------------------------------------------------------------------------------- - //
