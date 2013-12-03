// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_GELTEXTUREPOOL_H__
#define __GEL_TEXTURE_GELTEXTUREPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
// A Smart System built on top of Texture that is indiffent of texture format, and caches the
//   data so multiple requests for the same data do not waste VRAM.

// TODO: Make it so the new TexturePool can actually be instanced. Smaller pools of textures. //
// MAYBE: No top level Texture Pool. Part of Texture instead.
// NOPE: GelTextureHandle's rely on an internal active Texture Unit and Handle. Not really viable.
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a listener for OnReload.
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "GelTexture.h"
// - ------------------------------------------------------------------------------------------ - //
class GelTexturePool: public GelPool<GelTexture> {
public:
	_GELPOOL_LOAD_FUNC( const bool Smooth = true, const bool Flip = true, const bool PreMultiplyAlpha = true )
	_GELPOOL_LOAD_BODY( "Texture",GelTexture, Smooth, Flip, PreMultiplyAlpha )
};
/*
class GelTexturePool {
public:
	typedef int UID;
protected:
	std::vector<GelTexture> Textures;	
	std::map<std::string,UID> NameTable;
public:
	inline GelTexturePool() {
		// Add 1 element to the Textures array: A dummy placeholder for Id 0. //
		Textures.push_back( GelTexture() );
	}
	inline ~GelTexturePool() {
		for ( st idx = 0; idx < Textures.size(); idx++ ) {
			Textures[idx].Unload();
		}
	}

public:
	// Lookup an asset via the UID //
	inline GelTexture& operator[] ( const UID Id ) {
		return Textures[Id];
	}

	// Get a UID for an Asset //
	inline UID Load( const char* _FileName, const bool Smooth = true, const bool Flip = true, const bool PreMultiplyAlpha = true ) {
		// NOTE: This should always return a legal UID //
		
		// If we got a zero (Search Failure) then return the dummy UID //
		if ( _FileName == 0 ) {
			return 0;
		}
		
		// Step 1: Check Hash Table for a match //
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName);
		if ( Itr != NameTable.end() ) {
			Log( "* Texture \"%s\" found in Pool: %i", _FileName, Itr->second );
			// Found a UID match, so we're done //
			return Itr->second;
		}
		// Step 2: If no match, then do a load //
		else {
			Log( "* Texture \"%s\" not in Pool. Loading...", _FileName );
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
				UID Id = Textures.size();
				NameTable[_FileName] = Id;
				Textures.push_back( GelTexture() );
				
				// TODO: Add this to the Job Queue //
				Textures.back().Load( _FileName, Smooth, Flip, PreMultiplyAlpha );
				Log( "* Texture \"%s\" loaded as: %i", _FileName, Id );
				return Id;
			}
		}
	}

};*/
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_GELTEXTUREPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
