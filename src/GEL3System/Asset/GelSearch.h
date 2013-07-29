// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_GELSEARCH_H__
#define __GEL_SYSTEM_GELSEARCH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Lib/GelDirectory/GelDirectory.h>
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class GelSearch {
	GelDirectory* Dir;

public:	
	inline GelSearch() :
		Dir( new_GelDirectory() )
	{	
	}
	
	inline ~GelSearch() {
		if ( Dir ) {
			delete_GelDirectory( Dir );
		}
	}
	
//	inline void Init( const char* DirName ) {
//		Dir = new_GelDirectory( DirName );
//	}

public:	
	inline void Add( const char* DirName ) {
		Log( "Adding \"%s\" to Search...", DirName );
		populate_GelDirectory( Dir, DirName, "" );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSEARCH_H__ //
// - ------------------------------------------------------------------------------------------ - //
