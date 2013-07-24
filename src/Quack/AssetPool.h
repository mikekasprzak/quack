// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_ASSETPOOL_H__
#define __GEL_WTF_ASSETPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/DataBlock/DataBlock.h>
#include <Lib/GelArray/GelArray_Core.h>

#include <map>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
// IMPORTANT NOTE: cAsset DOES NOT clean up after itself. Managed by cAssetPool. //
class cAsset {
	friend class cAssetPool;
protected:
	DataBlock* Data;
	std::string FileName;
	// TODO: FileInfo //
	// TODO: TimeStamp //
	
	enum /* AssetFlags */ {
		AF_NULL				= 0,
		
		AF_LOADED			= 0x1,	// Asset is Loaded //
		AF_RELEASED			= 0x2,	// Asset was Unloaded due to the autorelease mechanism (NOT IMPLEMENTED) // 
		
		AF_DONT_LOAD		= 0x4,	// Never load the asset (Index Zero) //
		AF_UNLOADED			= 0x8,	// Asset was explicitly Unloaded //
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
		// NOTE: Disabled cleanup. cAssetPool is going to clean-up for us. //	
		//Unload();
	}

public:	
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
			Flags = AF_UNLOADED;
		}		
	}

public:
	// Flag and State Checking Functions //	
	inline bool IsLoaded() const {
		return (bool)(Flags & AF_LOADED);
	}
	inline bool IsUnloaded() const {
		return (bool)(Flags & AF_UNLOADED);
	}
	inline bool IsReleased() const {
		return (bool)(Flags & AF_RELEASED);
	}
	inline bool IsDontLoad() const {
		return (bool)(Flags & AF_DONT_LOAD);
	}

public:
	inline char* Get() {
		// TODO: Write a timestamp every time this is accessed //
		if ( IsLoaded() ) {
			return Data->Data;
		}
		else {
			return 0;
		}
	}
	// Variation of Get. Returns an empty string upon fail (instead of 0) //
	inline const char* GetStr() {
		// TODO: Write a timestamp every time this is accessed //
		if ( IsLoaded() ) {
			return Data->Data;
		}
		else {
			return "";
		}
	}

	inline st32 GetSize() const {
		if ( IsLoaded() ) {
			return Data->Size;
		}
		else {
			return 0;
		}
	}
	
	inline const char* GetFileName() const {
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
	
	std::map<std::string,UID> NameTable;
public:
	inline cAssetPool() :
		Assets( 0 )
	{
		// Add 1 element to the Assets array: A dummy placeholder for Id 0. //
		pushback_GelArray( &Assets );
		back_GelArray( Assets )->Flags |= cAsset::AF_DONT_LOAD;
	}
	
	inline ~cAssetPool() {
		if ( Assets ) {
			for ( st idx = 0; idx < Assets->Size; idx++ ) {
				Assets->Data[idx].Unload();
			}
		}
	}
	
public:
	// Lookup an asset via the UID //
	inline cAsset& operator[] ( const UID Id ) {
		return Assets->Data[ Id ];
	}
	
	// Get a UID for an Asset //
	inline UID Load( const char* _FileName ) {
		// Step 1: Check Hash Table for a match //
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName);
		if ( Itr != NameTable.end() ) {
			Log( "Asset \"%s\" found in Pool: %i", _FileName, Itr->second );
			// Found a UID match, so we're done //
			return Itr->second;
		}
		// Step 2: If no match, then do a load //
		else {
			Log( "Asset \"%s\" not in Pool. Loading...", _FileName );
			// TOOD: Check if file exists (where applicible). Return 0 on fail. //
			// UNTODO: No don't. Instead return a legal UID, but it will fail the load. //
			// Remember: Eventually the Load will become an Async operation. //
			
			// TODO: Scan for a UID's in the 'available' table before deciding to use the back //
			if ( false ) {
				// Bleh //
			}
			else {
				// Use the Back, as there are no UID's in the 'available' table //
				UID Id = Assets->Size;
				NameTable[_FileName] = Id;
				pushback_GelArray( &Assets );
				// TODO: Add this to the Job Queue //
				back_GelArray( Assets )->Load( _FileName );
				return Id;
			}
		}
	}

	// Remove an Asset via original FileName //	
	inline void Unload( const char* _FileName ) {
		std::map<std::string,UID>::iterator Itr = NameTable.find(_FileName);
		if ( Itr != NameTable.end() ) {
			// Only Unload if it wasn't previously Unloaded //
			if ( !operator[]( Itr->second ).IsUnloaded() ) {
				operator[]( Itr->second ).Unload();
				NameTable.erase( Itr );
				// TODO: Store this UID in the 'available' table //
			}
		}
	}
	// Remove an Asset via the UID //
	inline void Unload( const UID Id ) {
		// Only Unload if it wasn't previously Unloaded //
		if ( !operator[](Id).IsUnloaded() ) {
			NameTable.erase( NameTable.find( operator[](Id).GetFileName() ) );
			operator[](Id).Unload();
			// TODO: Store this UID in the 'available' table //
		}
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_ASSETPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
