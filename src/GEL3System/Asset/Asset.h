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
#ifndef __GEL_ASSET_ASSET_H__
#define __GEL_ASSET_ASSET_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Lib/DataBlock/DataBlock.h>
#include <Lib/DataBlock/DataBlock_LZMA.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
// IMPORTANT NOTE: cAsset DOES NOT clean up after itself! Managed by cAssetPool. //
class cAsset {
	friend class cAssetPool;
protected:
	DataBlock* 	Data;				// The Data //
	std::string FileName;			// Name of the File //
	GelFileInfo FileInfo;			// Information about the file //
	GelTime 	TimeStamp;			// When the data was last accessed using .Get() //
	GelSignal 	ChangeCallbacks; 	// Notifications to make upon file change //
	int Flags;
	
	enum /* AssetFlags */ {
		AF_NULL				= 0,
		
		// States //
		AF_LOADED			= 0x1,		// Asset is Loaded //
		AF_RELEASED			= 0x2,		// Asset was Unloaded due to the autorelease mechanism //
		AF_UNLOADED			= 0x4,		// Asset was explicitly Unloaded //
		
		AF_ACTIVE			= AF_LOADED | AF_RELEASED, // An active state is one of the good states //
		
		// Bad States //
		AF_FILE_NOT_FOUND	= 0x10,		// Failed to load file: Was not found :( //
		AF_TIMED_OUT		= 0x20,		// Failed to load file: It took too long. //
		
		AF_BAD				= 0xFFF0,	// The state is bad (Not found, timed out, etc) //
		AF_STATE_MASK		= 0xFFFF,	// If it's a state //
		
		// Additional Flags (Not States) //
		AF_DONT_LOAD		= 0x10000,	// Never load the asset (i.e. Index Zero) //
		AF_DECOMPRESSED		= 0x20000,	// The data was decompressed //
	};
public:
	inline cAsset() :
		Data( 0 ),
		TimeStamp( 0ull ),
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
			ChangeCallbacks.Clear();	// Clear the list of callbacks to call upon change //
			FileName = "";				// Clear the FileName too. No reminants! //
			TimeStamp = 0ull;			// Clear the TimeStamp //
			SetState( AF_UNLOADED );
		}
	}
	
	// Like Load, but used on Released data (i.e. I still have the filename) //
	inline void DoLoad() {
		FileInfo.Load( FileName.c_str() );	// Get Information about the File //
		
		if ( FileInfo.Exists() ) {
			// Using the Null Terminator version of new_read, so the loaded data can //
			// safely be used as strings. //
			Data = new_read_nullterminate_DataBlock( FileName.c_str() );
			if ( Data ) {
				// TODO: Detect (.lzma, .gz, etc) //
				if ( false ) {
					// Uncompress the data //
					DataBlock* Uncompressed = new_unpack_LZMA_DataBlock( Data );
					
					// Throw away original //
					delete_DataBlock( Data );
					Data = Uncompressed;
					
					// NOTE: SetFlags not SetState, because state only affects the lower part //
					SetFlags( AF_LOADED | AF_DECOMPRESSED );
				}
				else {
					SetState( AF_LOADED );
				}			
			}
			else {
				SetState( AF_FILE_NOT_FOUND );	// NOTE: Now a different failure case actually //
			}
		}
		else {
			SetState( AF_FILE_NOT_FOUND );
		}
	}

public:
	// Releasing is a special kind of Unload. Only removes the data, but keeps the rest of the //
	// information around needed to reload the data. Used to both refresh data and to free memory //
	// that would otherwise be wasted. //
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
		if ( _IsReleased() ) {
			DoLoad();
		}
	}


	// Check if the file has since changed //
	inline bool HasChanged() {
		GelFileInfo NewFileInfo( FileName.c_str() );
		return FileInfo != NewFileInfo;
	}
	// When a file has changed, this is how we reload. //
	inline void Reload() {
		Release();				// Release instead of Unload, as we want to keep the File Name //
		DoLoad();				// Explicitly reload //
		ChangeCallbacks();		// Notify the subscribers that this file was changed //
	}
	
	// Attach a function that is notified whenever an asset is reloaded //
	template< class T >
	inline void SubscribeToChanges( T Callback ) {
		ChangeCallbacks.Connect( Callback );
	}
	// Remove a function that was added to monitor for changes //
	template< class T >
	inline void UnsubscribeFromChanges( T Callback ) {
		ChangeCallbacks.Disconnect( Callback );
	}
	
	// Set the Time Stamp to the current time //
	inline void DoTimeStamp() {
		// TODO: Use FrameTime //
		TimeStamp = get_s_GelTime();
	}

public:
	// An active Asset is one that is either Loaded or Released (freed because data not needed) //
	inline bool IsActive() {
		return ( IsLoaded() || IsReleased() );
	}
	
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
	inline bool _IsActive() {
		return (bool)(Flags & AF_ACTIVE);
	}
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
	// Set Flag //
	inline void SetFlag( const int _Flags ) {
		Flags |= _Flags;
	}
	// Set Flags (i.e. All) //
	inline void SetFlags( const int _Flags ) {
		Flags = _Flags;
	}

public:
	// Get the Data (as a char*) //
	inline char* Get() {
		DoTimeStamp(); // Write a timestamp every time this is accessed //
		
		if ( _IsLoaded() )
			return Data->Data;
		else if ( _IsReleased() )
			RequestReload();
		return 0;
	}
	// Variation of Get. Returns an empty string upon fail (instead of 0) //
	inline const char* GetStr() {
		DoTimeStamp(); // Write a timestamp every time this is accessed //
		
		if ( _IsLoaded() )
			return Data->Data;
		else if ( _IsReleased() )
			RequestReload();
		return "";
	}

	// Variation that does not request Reload //
	inline char* _Get() {
		DoTimeStamp(); // Write a timestamp every time this is accessed //
		
		if ( _IsLoaded() )
			return Data->Data;
		else
			return 0;
	}
	inline const char* _GetStr() {
		DoTimeStamp(); // Write a timestamp every time this is accessed //
		
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
#endif // __GEL_ASSET_ASSET_H__ //
// - ------------------------------------------------------------------------------------------ - //
