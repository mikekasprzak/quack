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
// 
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
function print_table( table, level = 0 ) {
	local Prefix = gen_string("  ",level);
	print( Prefix + "+ " + typeof(table) + ": " + table.len() + " elements." );
	foreach ( idx, val in table ) {
		if ( typeof(val) == "table" ) {
			print_table( val, level+1 );
		}
		else {
			print( Prefix + "  * " + idx + " [" + typeof(val) + "]: " + val );
		}
	}
	print( Prefix + "- " + typeof(table) + " ends." );
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
