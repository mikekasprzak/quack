// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_ASSETPOOL_H__
#define __GEL_WTF_ASSETPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/DataBlock/DataBlock.h>
#include <Lib/GelArray/GelArray_Core.h>

#include <map>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class cAsset {
public:
	typedef unsigned int UID;
protected:
	DataBlock* Data;
	
	enum /* AssetFlags */ {
		AF_NULL				= 0,
		
		AF_LOADED			= 0x1,
	};
	
	int Flags;
public:
	inline cAsset() :
		Flags( AF_NULL )
	{
	}
	
	inline DataBlock* Get() {
		if ( Flags & AF_LOADED ) {
			return Data;
		}
		else {
			return 0;
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //
class cAssetPool {
protected:
	// TODO: This should use the doubler allocator, as assets are a-plenty //
	GelArray<cAsset>* Assets;
	
	std::map<std::string,cAsset::UID> HashTable;
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_ASSETPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
