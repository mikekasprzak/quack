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
		Unload();
	}
	
	inline void Load( const char* _FileName ) {
		Unload();
		FileName = _FileName;
		// Using the Null Terminator version of new_read, so the loaded data can //
		// safely be used as strings. //
		Data = new_read_nullterminate_DataBlock( _FileName );
		Flags |= AF_LOADED;
	}
	
	inline void Unload() {
		if ( Data ) {
			delete_DataBlock( Data );
			Data = 0;
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
	inline const char* GetStr() {
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
	
	inline const char* GetFileName() {
		return FileName.c_str();
	}
};
// - ------------------------------------------------------------------------------------------ - //
class cAssetPool {
public:
	typedef int UID;
protected:
	// TODO: This should use the doubler allocator, as assets are a-plenty //
	GelArray<cAsset>* Assets;
	
	std::map<std::string,UID> HashTable;
public:
	inline cAssetPool() :
		Assets( 0 )
	{
		// Add 1 element to the Assets array: A dummy placeholder for Id 0. //
		pushback_GelArray( &Assets );
	}
	
	inline ~cAssetPool() {
		if ( Assets ) {
			for ( st idx = 0; idx < Assets->Size; idx++ ) {
				Assets->Data[idx].Unload();
			}
		}
	}
	
public:
	inline cAsset& operator[] ( const UID Id ) {
		return Assets->Data[ Id ];
	}
	
	inline UID Load( const char* _FileName ) {
		// Step 1: Check Hash Table for a match //
		std::map<std::string,UID>::iterator Itr = HashTable.find(_FileName);
		if ( Itr != HashTable.end() ) {
			VVLog( "Asset \"%s\" found in Pool: %i", _FileName, Itr->second );
			return Itr->second;
		}
		// Step 2: If no match, then do a load //
		else {
			// TOOD: Check if file exists (where applicible). Return 0 on fail. //
			
			// TODO: Scan a released UID's list before deciding to use the back //
			UID Id = Assets->Size;
			pushback_GelArray( &Assets );
			back_GelArray( Assets )->Load( _FileName );
			HashTable[_FileName] = Id;
			return Id;
		}
	}
	
	inline void Unload( const char* _FileName ) {
		std::map<std::string,UID>::iterator Itr = HashTable.find(_FileName);
		if ( Itr != HashTable.end() ) {
			operator[]( Itr->second ).Unload();
			HashTable.erase( Itr );
			// Store this UID in the 'available' table //
		}
	}
	
	inline void Unload( const UID Id ) {
		// TODO: Check if unloaded //
		
		HashTable.erase( HashTable.find( operator[](Id).GetFileName() ) );
		operator[](Id).Unload();
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_ASSETPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
