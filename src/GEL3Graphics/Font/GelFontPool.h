// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_FONT_GELFONTPOOL_H__
#define __GEL_FONT_GELFONTPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Lib/GelPool/GelPool.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Render/Render.h>
#include "GelFont.h"
// - ------------------------------------------------------------------------------------------ - //
class GelFontPool: public GelPool<GelFont> {
public:
	
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
			Log( "* Font \"%s\" found in Pool: %i", _FileName, Itr->second );
			// Found a UID match, so we're done //
			return Itr->second;
		}
		// Step 2: If no match, then do a load //
		else {
			Log( "* Font \"%s\" not in Pool. Loading...", _FileName );
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
				UID Id = Items.size();
				NameTable[_FileName] = Id;
				Items.push_back( GelFont() );							// *CHANGE* //
				
				// TODO: Add this to the Job Queue //
				Items.back().Load( _FileName );							// *CHANGE* //
				Log( "* Font \"%s\" loaded as: %i", _FileName, Id );	
				return Id;
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_FONT_GELFONTPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
