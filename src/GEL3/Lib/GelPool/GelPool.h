// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GELPOOL_H__
#define __GEL_LIB_GELPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
template< class T >
class GelPool {
public:
	typedef int UID;
protected:
	std::vector<T> Items;	
	std::map<std::string,UID> NameTable;
public:
	inline GelPool() {
		// Add 1 element to the Items array: A dummy placeholder for Id 0. //
		Items.push_back( T( 0 ) );
//		Items.back().SetFlag( GelAsset::AF_DONT_LOAD | GelAsset::AF_BAD );
	}
	inline ~GelPool() {
		for ( st idx = 0; idx < Items.size(); idx++ ) {
			Items[idx].Unload();
		}
	}

public:
	// Lookup an asset via the UID //
	inline T& operator[] ( const UID Id ) {
		return Items[Id];
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get a UID for an Asset //
// - ------------------------------------------------------------------------------------------ - //
#define _GELPOOL_LOAD_FUNC( ... ) \
	inline UID Load( const char* _FileName, ## __VA_ARGS__ ) {
// - ------------------------------------------------------------------------------------------ - //
#define _GELPOOL_LOAD_BODY( _Name, _Type, ... ) \
		/* NOTE: This should always return a legal UID */ \
		\
		/* If we got a zero (Search Failure) then return the dummy UID */ \
		if ( _FileName == 0 ) { \
			return 0; \
		} \
		\
		/* Step 1: Check Hash Table for a match */ \
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName); \
		if ( Itr != NameTable.end() ) { \
			Log( "* " _Name " \"%s\" found in Pool: %i", _FileName, Itr->second ); \
			/* Found a UID match, so we're done */ \
			return Itr->second; \
		} \
		/* Step 2: If no match, then do a load */ \
		else { \
			Log( "* " _Name " \"%s\" not in Pool. Loading...", _FileName ); \
			/* TOOD: Check if file exists (where applicible). Return 0 on fail. */ \
			/* UNTODO: No don't. Instead return a legal UID, but it will fail the load. */ \
			/* Remember: Eventually the Load will become an Async operation. */ \
			\
			/* TODO: Scan for a UID's in the 'available' table before deciding to use the back */ \
			if ( false ) { \
				/* Bleh */ \
				return 0; \
			} \
			else { \
				/* Use the Back, as there are no UID's in the 'available' table */ \
				UID Id = Items.size(); \
				NameTable[_FileName] = Id; \
				Items.push_back( _Type( Items.size() ) ); \
				\
				/* TODO: Add this to the Job Queue */ \
				Items.back().Load( _FileName, ## __VA_ARGS__ ); \
				Log( "* " _Name " \"%s\" loaded as: %i", _FileName, Id ); \
				return Id; \
			} \
		} \
	}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GELPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
