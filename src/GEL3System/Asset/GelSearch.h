// - ------------------------------------------------------------------------------------------ - //
// NOTE: Search is only File Names. If you want file information, you should use your search
//   results on GelFileInfo.
// - ------------------------------------------------------------------------------------------ - //
// TODO: Prioritize certain file extensions
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_GELSEARCH_H__
#define __GEL_SYSTEM_GELSEARCH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Lib/GelDirectory/GelDirectory.h>
#include <Lib/String/String.h>
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class GelSearch {
public:
	typedef u32 GelSearchUID;
protected:
	std::vector<std::string> File;
	std::map<std::string,GelSearchUID> Hash;		// TODO: Use a hash_map or unordered_map (C++11) //
public:	
	inline GelSearch() {	
	}
	
	inline ~GelSearch() {
	}

public:	
	inline void Add( const char* DirName ) {
		Log( "Adding \"%s\" to Search...", DirName );
		
		// Create a GelDirectory, and populate it //
		GelDirectory* Dir = new_GelDirectory( DirName );

		// Copy all file names found, adding them to results and hash tables //
		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
			const char* Name = index_GelDirectory( Dir, idx );
			
			// Since File is a vector (array), the current size will correctly be //
			// the index of the next element. Therefor, store a copy as a UID. //
			GelSearchUID ThisUID = File.size();
			
			std::string FileName = std::string(DirName) + "/" + std::string(Name);
			
			// Add this file to the File list //
			File.push_back( FileName );
			
//			Log( "TEST: %i %s (%s)", Gel::String::GetExtensionCount( FileName ), Gel::String::GetLastExtensions( FileName, 2 ).c_str(), FileName.c_str() );
//			Log( "TEST: %i %s (%s)", Gel::String::GetSubDirectoryCount( FileName ), Gel::String::GetLastSubDirectories( FileName, 1 ).c_str(), FileName.c_str() );
				
			// Since a linear search of the entire File list will find the first instance //
			// of a file, then the hash tables should follow a similar behavior. //
			
			// BaseName //
			{
				std::string Pattern = Gel::String::GetBaseName( FileName );
				// Make sure it doesn't exist first //
				if ( Hash.find( Pattern ) != Hash.end() ) {
					Hash[ Pattern ] = ThisUID;
				}
			}
			
		}
		
		// We're finished and made our own copy, so throw away the GelDirectory //
		delete_GelDirectory( Dir );		
	}
	
	// Search for a Pattern //
	inline const char* operator()( const char* Pattern ) {
		VLog( "* Searching for %s...", Pattern );
		
		// TODO: Build a search hash table. //
		//   BaseName, ParentDir/BaseName, Parent/Parent/BaseName, //
		//   BaseName.FirstExt, etc //
		
		// Linear Search (i.e. slow) //
		for( size_t idx = 0; idx < File.size(); idx++ ) {
			if ( File[idx].find( Pattern ) != std::string::npos ) {
				const char* Name = File[idx].c_str();
				VLog( "* Found %s! (WARNING: Found via Linear Search)", Name );
				return Name;
			}
		}

		Log( "* %s NOT FOUND!!", Pattern );
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;		
	}
	inline const char* operator()( const std::string& Pattern ) {
		return operator()( Pattern.c_str() );
	}
	
	// TODO:
	//inline GelSearchUID GetUID( const char* Pattern ) {
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSEARCH_H__ //
// - ------------------------------------------------------------------------------------------ - //
