// - ------------------------------------------------------------------------------------------ - //
// Directory - File Name tree cataloging library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelDirectory_File_H__
#define __Library_GELCore_GelDirectory_File_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelFile.h"
#include "GelVFile.h"
#include "GelContentHandle.h"
#include "GelStorageHandle.h"

#include "GelDirectory_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Directories are lists of file names.  They can be populated manually, or be polled from disk
//   and other sources.  The next step up from a Directory is an Archive, which contains data too.
//
// TODO: When indexing a string, consider attaching the name (BaseName/) to the front.
// TODO: Searching for a file (given a pattern to match)
// TODO: Saving and loading Directories to and from disk/streams. (Need FILE* library)
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you don't know how big a file is //
// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* new_GelDirectory( GelFile* fp ) {
	GelDirectory* p = new GelDirectory;
	
	p->BaseName = new_String( fp );
	p->FileName = new_GelHeap( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* new_GelDirectory( GelVFile* fp ) {
	GelDirectory* p = new GelDirectory;
	
	p->BaseName = new_String( fp );
	p->FileName = new_GelHeap( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* read_GelDirectory( GelFile* fp ) {
	return new_GelDirectory( fp );
}
// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* read_GelDirectory( GelVFile* fp ) {
	return new_GelDirectory( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This is our "new_GelDirectory" that takes a file.  We can't use new, because it's taken up by //
//   UnixDir's "new_GelDirectory" call.  It takes a string and poll's that from disk. //
// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* read_GelDirectory( const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	// GelDirectory is too complicated a type to rely on the file size alone, so we need to read //
	//   and write a stored GelHeap in much the same way as we would to a FILE*. //
	GelDirectory* p = new GelDirectory;
	
	p->BaseName = new_String( fp );
	p->FileName = new_GelHeap( fp );

	
	// Close file //
	close_GelFile( fp );
	
	// Return data //
	return p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it relys on the arrays being correctly allocated //
inline const size_t read_GelDirectory( GelDirectory* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_readonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}
	
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_GelHeap( p->FileName, fp ); 

	// Close file //
	close_GelFile( fp );
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelDirectory( const GelDirectory* p, const char* _FileName ) {
	// Open File //
	GelFile* fp = open_writeonly_GelFile( _FileName );
	if ( fp == 0 ) {
		return 0;
	}

	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_GelHeap( p->FileName, fp ); 

	// TODO: Assert on fire write error //
	
	// Close file //
	close_GelFile( fp );
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //
// For syntactical compatability, read_GelHeap which functions the same as new_GelHeap. //
// Note: This is bad, as it's unclear allocation is done.  new_GelHeap() is preferred. //
// - ------------------------------------------------------------------------------------------ - //
//inline GelHeap* read_GelHeap( const char* _FileName ) {
//	return new_GelHeap( _FileName );
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
inline const size_t read_GelDirectory( GelDirectory* p, GelFile* fp ) {
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_GelHeap( p->FileName, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelDirectory( const GelDirectory* p, GelFile* fp ) {
	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_GelHeap( p->FileName, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// This function is only so useful, as it rely's on the arrays being correctly allocated //
inline const size_t read_GelDirectory( GelDirectory* p, GelVFile* fp ) {
	size_t BytesRead = read_String( p->BaseName, fp );
	BytesRead += read_GelHeap( p->FileName, fp ); 
		
	// TODO: If I happen to only read some of the file, less than Size, that would be bad. //
	
	// Return the number of bytes read //
	return BytesRead;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelDirectory( const GelDirectory* p, GelVFile* fp ) {
	size_t BytesWritten = write_String( p->BaseName, fp );
	BytesWritten += write_GelHeap( p->FileName, fp ); 
	
	// TODO: Assert on fire write error //
		
	// Return the number of bytes read //
	return BytesWritten;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDirectory_File_H__ //
// - ------------------------------------------------------------------------------------------ - //
