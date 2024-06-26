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
#include <Lib/StdString/StdString.h>
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
#include <algorithm>
// - ------------------------------------------------------------------------------------------ - //
class GelSearch {
public:
	typedef u32 GelSearchUID;
protected:
	typedef std::map<std::string,GelSearchUID> HashType;

	// Directiores to Search for Assets //
	std::vector<std::string> SearchDir;
	
	// The File List //
	std::vector<std::string> File;
	HashType Hash;					// TODO: Use a hash_map or unordered_map (C++11) //
public:	
	inline GelSearch() {	
	}
	
	inline ~GelSearch() {
	}

public:	
	inline void Add( const char* DirName ) {
		Log( "Adding \"%s\" to Search...", DirName );

		SearchDir.push_back( DirName );
		BuildFileList();
	}

	inline void BuildFileList() {
		Log( "+ Rebuilding File List..." );
		
		File.clear();
		Hash.clear();
		
		for ( st SearchIndex = 0; SearchIndex < SearchDir.size(); SearchIndex++ ) {
			const char* DirName = SearchDir[SearchIndex].c_str();
					
			// Store a copy of the original size //
			st OriginalSize = File.size();
			
			{
				std::string TheDir;
				TheDir += Gel::BaseDir;
				TheDir += DirName;
				// Create a GelDirectory, and populate it //
				GelDirectory* Dir = new_GelDirectory( TheDir.c_str() );//DirName );
		
				// Copy all file names found, adding them to results and hash tables //
				for( st idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
					// Since File is a vector (array), the current size will correctly be //
					// the index of the next element. Therefor, store a copy as a UID. //
					//GelSearchUID ThisUID = File.size();
					
					std::string FullName = std::string(DirName) + "/" + index_GelDirectory( Dir, idx );;
					
					// Add this file to the File list //
					File.push_back( FullName );
				}	
		
				// We're finished and made our own copy, so throw away the GelDirectory //
				delete_GelDirectory( Dir );		
			}
			
			// Sort the recently added Files //
			std::sort( File.begin() + OriginalSize, File.end() );
				
			st32 DirNameLength = strlen( DirName );
	
			// Add the recently added files to the Hash table //
			for( st idx = 0; idx < File.size(); idx++ ) {
				//std::string Name = File[idx]; 							// Includes DirName //
				std::string Name = File[idx].substr( DirNameLength + 1 );	// Ignores DirName //
				
				// Since a linear search of the entire File list will find the first instance //
				// of a file, then the hash tables should follow a similar behavior. //
				
				st32 DirCount = Gel::String::GetSubDirectoryCount( Name );
				st32 ExtCount = Gel::String::GetExtensionCount( Name );
				
				for ( st Dirs = 0; Dirs < DirCount + 1; Dirs++ ) {
					for ( st Exts = 0; Exts < ExtCount + 1; Exts++ ) {
						std::string Pattern = Gel::String::GetSubDirectories( Name, Dirs );
						if ( Pattern.size() > 0 )
							Pattern += "/";
						Pattern += Gel::String::GetBaseName( Name ) + Gel::String::GetExtensions( Name, Exts );
	
						// Make sure it doesn't exist first //
						if ( Hash.find( Pattern ) == Hash.end() ) {
							VVVLog( "> %s", Pattern.c_str() );
							Hash[ Pattern ] = idx;//ThisUID;
						}
						else {
							VVVLog( "** %s exists. Ignoring...", Pattern.c_str() );
						}
					}
				}
			}
		}
		Log("- Finished Rebuilding File List: %i (%i)", File.size(), Hash.size() );
	}
	
	// Search for a Pattern //
	inline const char* operator()( const char* Pattern, const int RecursiveDepth = 0 ) {
		VLog( "* Searching for %s...", Pattern );

		// Hash Search (i.e. fast) //
		HashType::iterator SearchIterator = Hash.find( Pattern );
		if ( SearchIterator != Hash.end() ) {
			VLog( "* %s found in lookup cache! (%s)", File[SearchIterator->second].c_str(), SearchIterator->first.c_str() );
			return File[SearchIterator->second].c_str();
		}
		
		// Linear Search (i.e. slow) //
		for( st idx = 0; idx < File.size(); idx++ ) {
			if ( File[idx].find( Pattern ) != std::string::npos ) {
				const char* Name = File[idx].c_str();
				VLog( "* Found %s! (WARNING: Found via Linear Search)", Name );
				return Name;
			}
		}
		
		if ( RecursiveDepth == 0 ) {
			BuildFileList();
			return operator()( Pattern, RecursiveDepth+1 );
		}

		Log( "! %s NOT FOUND!!", Pattern );
		
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
