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
		Items.push_back( T() );
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
#endif // __GEL_LIB_GELPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
