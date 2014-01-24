// - ------------------------------------------------------------------------------------------ - //
// AssetPools maintain a list of Assets.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ASSET_GELASSETPOOL_H__
#define __GEL_ASSET_GELASSETPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "GelAsset.h"
// - ------------------------------------------------------------------------------------------ - //
class GelAssetPool {
public:
	typedef int UID;
protected:
	std::vector<GelAsset> Assets;	
	std::map<std::string,UID> NameTable;
public:
	inline GelAssetPool() {
		// Add 1 element to the Assets array: A dummy placeholder for Id 0. //
		Assets.push_back( GelAsset() );
		Assets.back().SetFlag( GelAsset::AF_DONT_LOAD | GelAsset::AF_BAD );
	}
	inline ~GelAssetPool() {
		for ( st idx = 0; idx < Assets.size(); idx++ ) {
			Assets[idx].Unload();
		}
	}
	
public:
	// Lookup an asset via the UID //
	inline GelAsset& operator[] ( const UID Id ) {
		return Assets[Id];
	}
	
	// Get a UID for an Asset //
	inline UID Load( const char* _FileName ) {
		// NOTE: This should always return a legal UID //
		
		// If we got a zero (Search Failure) then return the dummy UID //
		if ( _FileName == 0 ) {
			return 0;
		}
		
		// Step 1: Check Hash Table for a match //
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName);
		if ( Itr != NameTable.end() ) {
			Log( "* Asset \"%s\" found in Pool: %i", _FileName, Itr->second );
			// Found a UID match, so we're done //
			return Itr->second;
		}
		// Step 2: If no match, then do a load //
		else {
			Log( "* Asset \"%s\" not in Pool. Loading...", _FileName );
			// TOOD: Check if file exists (where applicible). Return 0 on fail. //
			// UNTODO: No don't. Instead return a legal UID, but it will fail the load. //
			// Remember: Eventually the Load will become an Async operation. //
			
			// TODO: Scan for a UID's in the 'available' table before deciding to use the back //
			if ( false ) {
				// Bleh //
				return 0;
			}
			else {
				// Use the Back, as there are no UID's in the 'available' table //
				UID Id = Assets.size();//Assets->Size;
				NameTable[_FileName] = Id;
				Assets.push_back( GelAsset() );
				
				std::string FullFileName;
				FullFileName += Gel::BaseDir;
#ifdef USES_ANDROID
				FullFileName += "/mnt/sdcard/work/";
#endif // USES_ANDROID //
				FullFileName += _FileName;
				
				// TODO: Add this to the Job Queue //
				Assets.back().Load( FullFileName.c_str() );//_FileName );
				Log( "* Asset \"%s\" loaded as: %i", _FileName, Id );
				return Id;
			}
		}
	}
	
	// Find a UID for an Asset //
	inline UID Find( const char* _FileName ) {
		// NOTE: This should always return a legal UID //
		
		// If we got a zero (Search Failure) then return the dummy UID //
		if ( _FileName == 0 ) {
			return 0;
		}
		
		// Check Hash Table for a match //
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName);
		if ( Itr != NameTable.end() ) {
			Log( "* Asset \"%s\" found in Pool: %i", _FileName, Itr->second );
			// Found a UID match, so we're done //
			return Itr->second;
		}
		
		// Otherwise there's no such thing //
		return 0;
	}
	
	inline bool ScanForChanges() {
		Log( "+ Scanning for Asset Changes..." );
		bool Changes = false;
		// Assets.size() may change during this loop //
		for ( st idx = 1; idx < Assets.size(); idx++ ) {
			if ( Assets[idx].IsActive() ) {
				if ( Assets[idx].HasChanged() ) {
					Assets[idx].Reload();
					Changes = true;
				}
			}
		}
		Log( "- Scan complete. %s", Changes ? "Changes found." : "No changes." );
		return Changes;
	}

	// Remove an Asset via original FileName //	
	inline void Unload( const char* _FileName ) {
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName);
		if ( Itr != NameTable.end() ) {
			// Only Unload if it wasn't previously Unloaded //
			if ( !operator[]( Itr->second )._IsUnloaded() ) {
				operator[]( Itr->second ).Unload();
				NameTable.erase( Itr );
				// TODO: Store this UID in the 'available' table //
			}
		}
	}
	// Remove an Asset via the UID //
	inline void Unload( const UID Id ) {
		// Only Unload if it wasn't previously Unloaded //
		if ( !operator[](Id)._IsUnloaded() ) {
			NameTable.erase( NameTable.find( operator[](Id).GetFileName() ) );
			operator[](Id).Unload();
			// TODO: Store this UID in the 'available' table //
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ASSET_GELASSETPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
