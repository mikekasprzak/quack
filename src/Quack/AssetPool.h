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
	std::string FileName;
	
	enum /* AssetFlags */ {
		AF_NULL				= 0,
		AF_LOADED			= 0x1,
	};
	
	int Flags;
public:
	inline cAsset() :
		Data( 0 ),
		Flags( AF_NULL )
	{
	}
	
	inline cAsset( const char* _FileName ) :
		Data( 0 ),
		Flags( AF_NULL )
	{
		Load( _FileName );		
	}
	
	inline ~cAsset() {
		UnLoad();
	}
	
	inline void Load( const char* _FileName ) {
		UnLoad();
		FileName = _FileName;
		// Using the Null Terminator version of new_read, so the loaded data can //
		// safely be used as strings. //
		Data = new_read_nullterminate_DataBlock( _FileName );
		Flags |= AF_LOADED;
	}
	
	inline void UnLoad() {
		if ( Data ) {
			delete_DataBlock( Data );
		}		
	}
	
	inline bool IsLoaded() {
		return (bool)(Flags & AF_LOADED);
	}
	
	inline char* Get() {
		if ( IsLoaded() ) {
			return Data->Data;
		}
		else {
			return 0;
		}
	}
	// Variation of Get. Returns an empty string upon fail (instead of 0) //
	inline char* GetStr() {
		if ( IsLoaded() ) {
			return Data->Data;
		}
		else {
			return "";
		}
	}

	inline st32 GetSize() {
		if ( IsLoaded() ) {
			return Data->Size;
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
