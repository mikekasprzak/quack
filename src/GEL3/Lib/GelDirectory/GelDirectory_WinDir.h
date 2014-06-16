// - ------------------------------------------------------------------------------------------ - //
// GelDirectory WinDir - Windows Style implementation of polling a directory tree //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDirectory_WinDir_H__
#define __Library_Data_GelDirectory_WinDir_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS_DIR
// - ------------------------------------------------------------------------------------------ - //
#ifdef WINCE
#include <WinCE/io.h>
#else // WINCE //
#include <io.h>
#endif // WINCE //

#include <string>
#include <Lib/StdString/StdString.h>

#include "GelDirectory_Core.h"
#include <Lib/GelFileInfo/GelFileInfo.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Init and Exit code, called once in case a platform needs to properly init directory support //
// - ------------------------------------------------------------------------------------------ - //
inline void init_GelDirectory() {
	Log("* USES_WINDOWS_DIR");
}
// - ------------------------------------------------------------------------------------------ - //
inline void exit_GelDirectory() {
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// This is called recursively. //
inline void populate_GelDirectory( GelDirectory* p, const char* SearchDirectory, const char* Prefix ) {
	_finddata_t Data;
	std::string SearchPath(SearchDirectory);
	SearchPath += "\\*.*";

	VVLog( "+ %s: %s [%s -- %s]", __func__, SearchDirectory, Prefix, SearchPath.c_str() );
	
	// Extract the directory part, and open the directory //
	// Read the first entry in the directory //
	intptr_t ThisDir = _findfirst( SearchPath.c_str(), &Data);
	int HasFiles = (int)ThisDir;
	
	// While we still have entries left in this directory //
	{	
		while ( HasFiles != -1 ) {
			// Build the full path name of the file //
			char* CurrentFile = new char[ length_String(SearchDirectory) + 1 + length_String(Data.name) + 1 ];
			copy_String( SearchDirectory, CurrentFile );
			cat_String( "\\", CurrentFile );
			cat_String( Data.name, CurrentFile );

			VVLog("* %s (%i) (%i) ", CurrentFile, Data.attrib, Data.size );
			
			// If it's a directory //
			if ( Data.attrib & _A_SUBDIR ) {
				VVVLog("*");
				// Recursively do this again, if not a dot file or folder //
				if( Data.name[0] != '.' ) {
					VVVLog("*");
					if( Data.name[0] != '_' ) {
						VVVLog("* DIRECTORY ADDED");
						// Build our prefix string //
						char* PrefixString = new char[ length_String(Prefix) + length_String(Data.name) + 2 ];
						copy_String( Prefix, PrefixString );
						cat_String( Data.name, PrefixString );
						cat_String( "\\", PrefixString );
						
						// Recursive call //
						populate_GelDirectory( p, CurrentFile, PrefixString );
							
						// Delete our prefix string //
						delete_String( PrefixString );
					}
				}
			}
			// If it's a regular file //
			else
			{
				VVVLog("#");
				if( Data.name[0] != '.' ) {
					VVVLog("#");
					if( Data.name[0] != '_' ) {
						VVVLog("# FILE ADDED");
						// Build our filename string //
						char* NewFile = new char[ length_String(Prefix) + length_String(Data.name) + 1 ];
						copy_String( Prefix, NewFile );
						cat_String( Data.name, NewFile );
						
						// Change Slash //
						{
							int Len = length_String(NewFile);
							for ( int idx = 0; idx < Len; idx++ ) {
								if ( NewFile[idx] == '\\' ) {
									NewFile[idx] = '/';
								}
							}
						}
			
						// Add the file //
						add_GelDirectory( p, NewFile );
						
						// Delet our filename string //
						delete_String( NewFile );
					}
				}
			}
			
			// Remove our string //
			delete_String( CurrentFile );
		
			// Read the next entry //
			HasFiles = _findnext(ThisDir, &Data);
		};
	
		// Close the directory //
		_findclose( ThisDir );
	}
	VVLog( "- %s: %s", __func__, SearchDirectory );
}
// - ------------------------------------------------------------------------------------------ - //
inline void populate_GelDirectory( GelDirectory* p ) {
	populate_GelDirectory( p, p->BaseName, "" );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline GelDirectory* new_GelDirectory( const char* _BaseName ) {
	GelDirectory* NewDir = new GelDirectory();

	NewDir->BaseName = new_String( _BaseName );
	NewDir->FileName = new_GelHeap();
	NewDir->FileInfo = new_GelDataArray<GelFileInfo>( 0 );
	
	// Work //
	populate_GelDirectory( NewDir );
	
	return NewDir;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline bool is_Directory( const char* _Name ) {
/*
	struct stat Status;
	stat( _Name, &Status );
	
	// If it's a directory //
	return S_ISDIR( Status.st_mode );
*/
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
inline bool is_File( const char* _Name ) {
/*
	struct stat Status;
	stat( _Name, &Status );
	
	// If it's a directory //
	return S_ISREG( Status.st_mode );
*/
	return false;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS_DIR //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDirectory_WinDir_H__ //
// - ------------------------------------------------------------------------------------------ - //
