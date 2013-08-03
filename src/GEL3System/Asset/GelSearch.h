// - ------------------------------------------------------------------------------------------ - //
// TODO: Prioritize certain file extensions
// TODO: Add prefix ("project" is being lost)
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
// GelSearchFile's are the entries found and stored in the Search system //
class GelSearchFile {
public:
	std::string Name;
//	GelFileInfo Info;
};
// - ------------------------------------------------------------------------------------------ - //
class GelSearch {
	std::vector<GelSearchFile> File;
//	GelDirectory* Dir;

public:	
	inline GelSearch() {	
	}
	
	inline ~GelSearch() {
//		if ( Dir ) {
//			delete_GelDirectory( Dir );
//		}
	}
	
//	inline void Init( const char* DirName ) {
//		Dir = new_GelDirectory( DirName );
//	}

public:	
	inline void Add( const char* DirName ) {
		Log( "Adding \"%s\" to Search...", DirName );
		
		// Create a GelDirectory, and populate it //
		GelDirectory* Dir = new_GelDirectory();
		// TODO: SetBasedir 
		populate_GelDirectory( Dir, DirName, "" );

		// Copy all files found to my vector of Files //
		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
			const char* Name = index_GelDirectory( Dir, idx );
			
			File.push_back( GelSearchFile() );
			File.back().Name = std::string(DirName) + "/" + std::string(Name);
		}
		
		// We're finished and made our own copy, so throw away the GelDirectory //
		delete_GelDirectory( Dir );		
	}
	
	inline const char* operator()( const char* Pattern ) {
		VLog( "* Searching for %s...", Pattern );
		
		// TODO: Build a search hash table. //
		//   BaseName, ParentDir/BaseName, Parent/Parent/BaseName, //
		//   BaseName.FirstExt, etc //
		
		// NOTE: The other Search uses GelDirectory as only a temporary. This is a good idea //
		//   because Windows uses a different system slash. A workaround would be to change //
		//   the slashes inside the Windows code. However, this means File Ops will need to //
		//   convert back to System slashes before attempting to read the file. //

		// Linear Search (i.e. slow) //
		for( size_t idx = 0; idx < File.size(); idx++ ) {
			if ( File[idx].Name.find( Pattern ) != std::string::npos ) {
				const char* Name = File[idx].Name.c_str();
				VLog( "* Found %s!", Name );
				return Name;
			}
		}

//		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
//			const char* Name = index_GelDirectory( Dir, idx );
//			if ( find_String( Pattern, Name ) ) {
//				VLog( "* Found %s!", Name );
//				return Name;
//			}
//		}

		Log( "* %s NOT FOUND!!", Pattern );
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;		
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSEARCH_H__ //
// - ------------------------------------------------------------------------------------------ - //
