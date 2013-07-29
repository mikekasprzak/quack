// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/AssetPool.h>
#include <Asset/Search.h>
// - ------------------------------------------------------------------------------------------ - //
void AppInit() {
	gelSystemInit();
	Log( "" );
	
	QuackVMInit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int AppMain() {
	Log( "-=- AppMain -=-" );
	Log( "Screens: %i", (int)Gel::Screen.Count() );
		
	{
		Log( "" );
		Log( "** GelFileInfo Test: " );
		
		GelFileInfo Info( "project/main.nut" );
		
		if( Info.Exists() ) {
			Log( "Size: %i   Type: %s (%x)   Time: %i", Info.Size, Info.IsDir() ? "Directory" : "File", Info.Flags, (int)Info.Time );
		}
		else {
			Log( "Doesn't Exist" );
		}

		Info.Load( "project" );
		
		if( Info.Exists() ) {
			Log( "Size: %i   Type: %s (%x)   Time: %i", Info.Size, Info.IsDir() ? "Directory" : "File", Info.Flags, (int)Info.Time );
		}
		else {
			Log( "Doesn't Exist" );
		}
		
		Info.Load( "project/main.nut.copy" );
		
		if( Info.Exists() ) {
			Log( "Size: %i   Type: %s (%x)   Time: %i", Info.Size, Info.IsDir() ? "Directory" : "File", Info.Flags, (int)Info.Time );
		}
		else {
			Log( "Doesn't Exist" );
		}

	}
	
	{
		Log( "" );
		Log( "** AssetPool Test:" );

		// AssetPool Test //
		cAssetPool AssetPool;
		
		cAssetPool::UID MyId = AssetPool.Load( "project/main.nut" );
		cAssetPool::UID MyOtherId = AssetPool.Load( "project/main.nut" );
			
		if ( AssetPool[MyId].IsLoaded() ) {
			Log( "Yep!" );
			//Log( AssetPool[MyId].GetStr() );
		}
		else {
			Log( "Nope!" );
		}
		
		AssetPool.Unload( MyOtherId );

		if ( AssetPool[MyId].IsLoaded() ) {
			Log( "Yep!" );
		}
		else {
			Log( "Nope!" );
		}
		
		cAssetPool::UID YouId = AssetPool.Load( "project/content/C64Pro.fnt" );
			
		if ( AssetPool[YouId].IsLoaded() ) {
			Log( "Yep2!" );
		}
		else {
			Log( "Nope2!" );
		}
		
		AssetPool[YouId].Release();
		if ( !AssetPool[YouId].IsLoaded() ) {
			Log( "Aww2!" );
		}
		AssetPool[YouId].RequestReload();
		if ( AssetPool[YouId].IsLoaded() ) {
			Log( "Yep2!" );
		}
		
		// Automatic Cleanup //
	}

	{
		Log( "" );
		Log( "** GelTime Test:" );
		
		gelTimeInit();
		
		// PRi64 is "printf integer 64" //
		#ifdef USES_WINDOWS
			#define PRi64 "%I64i"
		#else  // USES_UNIX //
			#define PRi64 "%lli"
		#endif // USES_WINDOWS //

		//Log( "stime: "PRi64, stime_GelTime() );

		// GelTime Test //	
		GelTime Start = get_time_GelTime();
		GelTime StartMs = get_ms_GelTime();
		
		int Barf = 0;
		for ( int idx = 0; idx < 1000000000; idx++ ) {
			Barf++;
		}
			
		GelTime EndMs = get_ms_GelTime();
		GelTime End = get_time_GelTime();
		
		GelTime Diff = End-Start;
		GelTime DiffMs = EndMs-StartMs;
		
		Log( "Time: "PRi64" ("PRi64" -> "PRi64") :: TimeMs: "PRi64" ("PRi64" -> "PRi64")", 
			Diff, Start, End, 
			DiffMs, StartMs, EndMs 
		);
		
		Log( "s_to_time: "PRi64" ("PRi64")", ms_to_time_GelTime( EndMs ), stime_GelTime() );
	}
	
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
