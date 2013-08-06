// - -------------------------------------------------------------------------------------------------------------- - //
function Log(...) {
	//print( format(str,vargv) );		// This does not work //
	for ( local idx = 0; idx < vargv.len(); idx++ ) {
		print(vargv[idx]);
	}
}
// - -------------------------------------------------------------------------------------------------------------- - //
//function gen_string( char, count ) {
//	local Ret = ""
//	for ( local idx = 0; idx < count; idx++ ) {
//		Ret += char;
//	}
//	return Ret;
//}
// - -------------------------------------------------------------------------------------------------------------- - //
//function print_table( table, level = 0 ) {
//	local Prefix = gen_string("  ",level);
//	print( Prefix + "+ " + typeof(table) + ": " + table.len() + " elements." );
//	foreach ( idx, val in table ) {
//		if ( typeof(val) == "table" ) {
//			print_table( val, level+1 );
//		}
//		else {
//			print( Prefix + "  * " + idx + " [" + typeof(val) + "]: " + val );
//		}
//	}
//	print( Prefix + "- " + typeof(table) + " ends." );
//}
// - -------------------------------------------------------------------------------------------------------------- - //


// In documentation, talk about "Reload Scope", which is anything defined globally. //
//   Creating class instances for a game should be in the Init function. //
//   If they are ever defined in the global (Reload) scope, then they will be trashed on file change. //

function require( files ) {
	// TODO: Support wildcards (*.nut) (**.nut for all recursively) //
	// TODO: Track dependencies (which files requested a file, which files a file requseted).
	//       Note in the logs if a refcount ever becomes zero. //
	if ( typeof files == "array" ) {
		for ( local idx = 0; idx < files.len(); idx++ ) {
			print( "> require: " + files[idx] );
		}
	}
	else if ( typeof files == "string" ) {
		print( "> require: " + files );
	}
}

function RGBA( r, g, b, a ) {
	return ((r<<0) & 0xff) | ((g<<8) & 0xff00) | ((b<<16) & 0xff0000) | ((a<<24) & 0xff000000);
}
function RGB( r, g, b ) {
	return ((r<<0) & 0xff) | ((g<<8) & 0xff00) | ((b<<16) & 0xff0000) | (0xff000000);
}
