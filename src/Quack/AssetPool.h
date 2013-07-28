// - ------------------------------------------------------------------------------------------ - //
// Assets are loaded files //
//
// Once an Asset is loaded, details about it will be remembered.
// An asset can be released, which means details are still tracked, but the data is gone.
// The next time an asset is asked for, a released asset will trigger a reload, and eventually
//   the data will work. 
// A released asset is still a usable asset.
//
// NOTE: VRAM should auto-release the Data after upload, as the 2nd copy isn't necessary. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_ASSETPOOL_H__
#define __GEL_WTF_ASSETPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/DataBlock/DataBlock.h>
#include <Lib/GelArray/GelArray_Core.h>

#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
// IMPORTANT NOTE: cAsset DOES NOT clean up after itself! Managed by cAssetPool. //
class cAsset {
	friend class cAssetPool;
protected:
	DataBlock* Data;
	std::string FileName;
	// TODO: FileInfo //
	// TODO: TimeStamp (May be part of FileInfo) //
	// TODO: Signal (onchange, who to notify) //
	int Flags;
	
	enum /* AssetFlags */ {
		AF_NULL				= 0,
		
		// States //
		AF_LOADED			= 0x1,		// Asset is Loaded //
		AF_RELEASED			= 0x2,		// Asset was Unloaded due to the autorelease mechanism //
		AF_UNLOADED			= 0x4,		// Asset was explicitly Unloaded //
		
		// Bad States //
		AF_FILE_NOT_FOUND	= 0x10,		// Failed to load file: Was not found :( //
		AF_TIMED_OUT		= 0x20,		// Failed to load file: It took too long. //
		
		AF_BAD				= 0xFFF0,	// The state is bad (Not found, timed out, etc) //
		AF_STATE_MASK		= 0xFFFF,
		
		// Additional Flags (Not States) //
		AF_DONT_LOAD		= 0x10000,	// Never load the asset (i.e. Index Zero) //
		AF_DECOMPRESSED		= 0x20000,	// The data was decompressed //
	};
public:
	inline cAsset() :
		Data( 0 ),
		Flags( AF_NULL )
	{
	}
	
//	inline cAsset& operator = ( const cAsset& _Vs ) {
//		Data = _Vs.Data;
//		FileName = _Vs.FileName;
//		Flags = _Vs.Flags;
//		
//		return *this;
//	}
	
	// Disabled Constructor and Destructor. Loading/Unloading is now explicit. //
//	inline cAsset( const char* _FileName ) :
//		Data( 0 ),
//		Flags( AF_NULL )
//	{
//		Load( _FileName );		
//	}
//	
//	inline ~cAsset() {
//		// NOTE: Disabled cleanup. cAssetPool is going to clean-up for us. //	
//		//Unload();
//	}

protected:	
	inline void Load( const char* _FileName ) {
		Unload();
		FileName = _FileName;
		DoLoad();
	}
	
	inline void Unload() {
		if ( Data ) {
			delete_DataBlock( Data );
			Data = 0;
			SetState( AF_UNLOADED );
			FileName = "";	// Clear the FileName too. No reminants! //
		}
	}
	
	// Like Load, but used on Released data (i.e. I still have the filename) //
	inline void DoLoad() {
		// TODO: Detect (.lzma, .gz, etc) and Uncompress the data // 
		
		// Using the Null Terminator version of new_read, so the loaded data can //
		// safely be used as strings. //
		Data = new_read_nullterminate_DataBlock( FileName.c_str() );
		if ( Data )
			SetState( AF_LOADED );
		else
			SetState( AF_FILE_NOT_FOUND );		
	}

public:
	// Releasing is a special kind of Unload. Should only be used by memory managers. //
	inline void Release() {
		if ( Data ) {
			delete_DataBlock( Data );
			Data = 0;
			SetState( AF_RELEASED );
		}		
	}

	inline void RequestReload() {
		// TODO: Make this queue a reload //
		// NOTE: A reload is a call to DoLoad() //
		DoLoad();
	}

public:
	// Flag and State Checking Functions //
	inline bool IsLoaded() {
		bool Loaded = _IsLoaded();
		if ( !Loaded ) {
			// If we ever did a IsLoaded check on something that was released, then we should reload it //
			if ( _IsReleased() ) {
				RequestReload();
			}
		}
		return Loaded;
	}
	inline bool IsReleased() const {
		return _IsReleased();
	}
	inline bool IsUnloaded() const {
		return _IsUnloaded();
	}
	inline bool IsDontLoad() const {
		return _IsDontLoad();
	}
	inline bool IsFileNotFound() const {
		return _IsFileNotFound();
	}
	inline bool IsTimedOut() const {
		return _IsTimedOut();
	}
	inline bool IsBad() const {
		return _IsBad();
	}
	inline bool IsDecompressed() const {
		return _IsDecompressed();
	}
	
	// Safe Versions that only check flags //
	inline bool _IsLoaded() const {
		return (bool)(Flags & AF_LOADED);
	}
	inline bool _IsReleased() const {
		return (bool)(Flags & AF_RELEASED);
	}
	inline bool _IsUnloaded() const {
		return (bool)(Flags & AF_UNLOADED);
	}
	inline bool _IsDontLoad() const {
		return (bool)(Flags & AF_DONT_LOAD);
	}
	inline bool _IsFileNotFound() const {
		return (bool)(Flags & AF_FILE_NOT_FOUND);
	}
	inline bool _IsTimedOut() const {
		return (bool)(Flags & AF_TIMED_OUT);
	}
	inline bool _IsBad() const {
		return (bool)(Flags & AF_BAD);
	}
	inline bool _IsDecompressed() const {
		return (bool)(Flags & AF_DECOMPRESSED);
	}

protected:	
	// Set States //
	inline void SetState( const int _Flags ) {
		Flags = (Flags & ~AF_STATE_MASK) | _Flags;
	}
	// Set Flags //
	inline void SetFlag( const int _Flags ) {
		Flags |= _Flags;
	}

public:
	// Get the Data (as a char*) //
	inline char* Get() {
		// TODO: Write a timestamp every time this is accessed //
		if ( _IsLoaded() )
			return Data->Data;
		else if ( _IsReleased() )
			RequestReload();
		return 0;
	}
	// Variation of Get. Returns an empty string upon fail (instead of 0) //
	inline const char* GetStr() {
		// TODO: Write a timestamp every time this is accessed //
		if ( _IsLoaded() )
			return Data->Data;
		else if ( _IsReleased() )
			RequestReload();
		return "";
	}

	// Variation that does not request Reload //
	inline char* _Get() {
		// TODO: Write a timestamp every time this is accessed //
		if ( _IsLoaded() )
			return Data->Data;
		else
			return 0;
	}
	inline const char* _GetStr() {
		// TODO: Write a timestamp every time this is accessed //
		if ( _IsLoaded() )
			return Data->Data;
		else
			return "";
	}

	// Weak version that does not set timestamp or request reload //
	inline char* __Get() {
		if ( _IsLoaded() )
			return Data->Data;
		else
			return 0;
	}
	inline const char* __GetStr() const {
		if ( _IsLoaded() )
			return Data->Data;
		else
			return "";
	}

	// Gets the size, and also requests a reload if the data was released //
	inline st32 GetSize() {
		if ( _IsLoaded() )
			return Data->Size;
		else if ( _IsReleased() )
			RequestReload();
		return 0;
	}
	// Does not request a reload //
	inline st32 _GetSize() const {
		if ( _IsLoaded() )
			return Data->Size;
		else
			return 0;
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
	std::vector<cAsset> Assets;	
	std::map<std::string,UID> NameTable;
public:
	inline cAssetPool() {
		// Add 1 element to the Assets array: A dummy placeholder for Id 0. //
		Assets.push_back( cAsset() );
		Assets.back().SetFlag( cAsset::AF_DONT_LOAD );
	}
	inline ~cAssetPool() {
		for ( st idx = 0; idx < Assets.size(); idx++ ) {
			Assets[idx].Unload();
		}
	}
	
public:
	// Lookup an asset via the UID //
	inline cAsset& operator[] ( const UID Id ) {
		return Assets[Id];
	}
	
	// Get a UID for an Asset //
	inline UID Load( const char* _FileName ) {
		// NOTE: This should always return a legal UID //
		
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
				UID Id = Assets.size();//Assets->Size;
				NameTable[_FileName] = Id;
				Assets.push_back( cAsset() );
				// TODO: Add this to the Job Queue //
				Assets.back().Load( _FileName );
				Log( "Asset \"%s\" loaded as: %i", _FileName, Id );
				return Id;
			}
		}
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
#endif // __GEL_WTF_ASSETPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
