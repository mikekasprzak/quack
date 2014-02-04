// - ------------------------------------------------------------------------------------------ - //
// GelDirectory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDirectory_Core_H__
#define __Library_Data_GelDirectory_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelString/GelString_Core.h>
#include <Lib/GelString/GelString_File.h>
#include <Lib/GelHeap/GelHeap_Core.h>
#include <Lib/GelHeap/GelHeap_File.h>

#include <Lib/GelFileInfo/GelFileInfo.h>
// - ------------------------------------------------------------------------------------------ - //
// Directories are lists of file names.  They can be populated manually, or be polled from disk
//   and other sources.  The next step up from a Directory is an Archive, which contains data too.
//
// TODO: When indexing a string, consider attaching the name (BaseName/) to the front.
// TODO: Searching for a file (given a pattern to match)
// TODO: Saving and loading Directories to and from disk/streams. (Need FILE* library)
// - ------------------------------------------------------------------------------------------ - //
struct GelDirectory {
	// The given Base GelDirectory name (include the trailing backslash .. ?) //
	char* BaseName;
	
	GelHeap* FileName;					// A GelHeap of filenames //
	
	GelDataArray<GelFileInfo>* FileInfo;
	
	GelDirectory() :
		BaseName( 0 ),
		FileName( 0 ),
		FileInfo( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t add_GelDirectory( GelDirectory* p, const char* _String, const GelFileInfo& _FileInfo ) {
	size_t StringLength = length_String( _String ) + 1;
	
	pushback_GelDataArray<GelFileInfo>( &p->FileInfo, _FileInfo );
	
	return allocate_GelHeap( p->FileName, _String, StringLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t add_GelDirectory( GelDirectory* p, const char* _String ) {
	size_t StringLength = length_String( _String ) + 1;
		
	return allocate_GelHeap( p->FileName, _String, StringLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_GelDirectory( const GelDirectory* p ) {
	return size_GelHeap( p->FileName );
}
// - ------------------------------------------------------------------------------------------ - //
inline const char* index_GelDirectory( const GelDirectory* p, const size_t Index ) { 
	return index_GelHeap( p->FileName, Index );
}
// - ------------------------------------------------------------------------------------------ - //
inline const GelFileInfo& info_GelDirectory( const GelDirectory* p, const size_t Index ) { 
	return *index_GelDataArray<GelFileInfo>( p->FileInfo, Index );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Create a dummy empty File Name list //
inline GelDirectory* new_GelDirectory() {
	GelDirectory* NewDir = new GelDirectory();
	
	// Create and initalize an empty name string //
	NewDir->BaseName = new_String("");
	NewDir->FileName = new_GelHeap();
	NewDir->FileInfo = new_GelDataArray<GelFileInfo>( 0 );

	VVLog("* NEWDIR: \"%s\"  0x%x  0x%x\n", NewDir->BaseName, NewDir->FileName, NewDir->FileInfo );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_GelDirectory( GelDirectory* p ) {
	if ( p->BaseName )
		delete [] p->BaseName;
		
	if ( p->FileName )
		delete_GelHeap( p->FileName );
	
	if ( p->FileInfo )
		delete_GelDataArray( p->FileInfo );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Create a GelDirectory from an existing GelDirectory, by pattern matching //
inline GelDirectory* new_GelDirectory( GelDirectory* p, const char* Pattern ) {
	GelDirectory* NewDir = new_GelDirectory();
	delete_String( NewDir->BaseName );
	NewDir->BaseName = new_String( p->BaseName );
	
	for (size_t idx = 0; idx < size_GelDirectory( p ); idx++ ) {
		if ( find_String( Pattern, index_GelDirectory( p, idx ) ) )
			add_GelDirectory( NewDir, index_GelDirectory( p, idx ), info_GelDirectory( p, idx ) );
	}
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDirectory_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
