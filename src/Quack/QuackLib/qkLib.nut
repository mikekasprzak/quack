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
	local recursive = function( files ) {
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
			else if ( typeof(val) == "array" ) {
				print_table( val, level+1, idx + " " );
			}
			else {
				print( Prefix + Indent + "* " + idx + " [" + typeof(val) + "]: " + val );
			}
		}
		print( Prefix + "- " + name + "[" + typeof(table) + "]" );
	}
	else if ( typeof(table) == "array" ) {
		print( Prefix + "+ " + name + "[" + typeof(table) + "]: " + table.len() + " elements" );
		for ( local idx = 0; idx < table.len(); idx++ ) {
			if ( typeof(table[idx]) == "table" ) {
				print_table( table[idx], level+1, idx + " " );
			}
			else if ( typeof(table[idx]) == "array" ) {
				print_table( table[idx], level+1, idx + " " );
			}
			else {
				print( Prefix + Indent + "* " + idx + " [" + typeof table[idx] + "]: " + table[idx] );
			}
		}
		print( Prefix + "- " + name + "[" + typeof(table) + "]" );
	}
	else {
		print( Prefix + "* [" + typeof(table) + "]: " + table );
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// Returns the highest bit. Like a "floor" op that rounds to the nearest bit. i.e. 255 -> 128, 0 -> 0 //
function floorbit( n ) {
    n = n | (n >> 1);
    n = n | (n >> 2);
    n = n | (n >> 4);
    n = n | (n >> 8);
    n = n | (n >> 16);
    return n - (n >> 1);
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Returns the next highest bit. Like a "ceil" op that rounds to the nearest bit. i.e. 255 -> 256, 0 -> 0 //
function ceilbit( n ) {
	n = n - 1;
    n = n | (n >> 1);
    n = n | (n >> 2);
    n = n | (n >> 4);
    n = n | (n >> 8);
    n = n | (n >> 16);
    return n + 1;
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Convert a power of two (bit) back in to a number. i.e. Undo 1<<bit. //
function bitlog2( n ) {
	local ret = (n & 0xAAAAAAAA) != 0;
	ret = ret | ((n & 0xFFFF0000) != 0) << 4;
	ret = ret | ((n & 0xFF00FF00) != 0) << 3;
	ret = ret | ((n & 0xF0F0F0F0) != 0) << 2;
	ret = ret | ((n & 0xCCCCCCCC) != 0) << 1;
	ret = ret | ((n & 0xAAAAAAAA) != 0) << 0;
	return ret;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function _DefaultSetup() {
	Log("# Setup (_DefaultSetup)");

	if ( qkIsDevMode() ) {
		Log("# Dev Mode Detected.");
		qkScreensSetScalar( 0.8 );
	}
	qkScreensInit();	
}
// - -------------------------------------------------------------------------------------------------------------- - //
