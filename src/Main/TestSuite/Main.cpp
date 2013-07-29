// - ------------------------------------------------------------------------------------------ - //
// A special version of main to be run on new platforms BEFORE graphics work, to confirm that //
// logging and low level library features are all working. //
//
// Move all test code written when building new libraries here. //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_TESTSUITE
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
//#include <App.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// The Signal Test Suite //
void MyFunc( int* ) {
	Log("Triggered");
}
void MyFunc2( st User, st Arg ) {
	Log("Triggered Also. %i %i", (int)User, (int)Arg );
}
st MyFunc3( st User, st Arg, st Ret ) {
	Log("Targ: %i %i %i", (int)User, (int)Arg, (int)Ret );
	return Ret+1;
}
// - ------------------------------------------------------------------------------------------ - //
void SignalTest() {
	Log( "" );
	Log( "** Signal Test:" );

	// Signal Testing Code //
	GelSignal MySignal;
	MySignal.Connect( MyFunc );
	MySignal.Connect( MyFunc2, 200 );
	MySignal.Connect( MyFunc3, 1 );
	MySignal.Connect( MyFunc3, 2 );
	MySignal.Connect( MyFunc3, 3 );
	st Ret = (st)MySignal( 25 );
	Log( "Final Ret is: %i", (int)Ret );
}
// - ------------------------------------------------------------------------------------------ - //
void DeferredTest() {
	Log( "" );
	Log( "** Deferred Test:" );
	
	// Deferred Testing Code //
	Deferred MyDef;
	MyDef.Then( MyFunc );
	MyDef.OnError( MyFunc2 );
	//MyDef.Always( MyFunc2, 64 );
	
	MyDef.Callback( 13 );
//	MyDef.Errback( 10 );

	Log( "Adding a late action. These will automatically trigger Callback or Errback." );
	
	MyDef.Then( MyFunc2 );
	MyDef.OnError( MyFunc );
}
// - ------------------------------------------------------------------------------------------ - //
void TimeTest() {
	Log( "" );
	Log( "** GelTime Test:" );
	
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
// - ------------------------------------------------------------------------------------------ - //
void FileInfoTest() {
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
// - ------------------------------------------------------------------------------------------ - //
void AssetPoolTest() {
	Log( "" );
	Log( "** GelAssetPool Test:" );
	
	GelAsset::SetTimeStamp( 1 );

	// AssetPool Test //
	GelAssetPool AssetPool;
	
	GelAssetPool::UID MyId = AssetPool.Load( "project/main.nut" );
	GelAssetPool::UID MyOtherId = AssetPool.Load( "project/main.nut" );
		
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
	
	GelAssetPool::UID YouId = AssetPool.Load( "project/content/C64Pro.fnt" );
		
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
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();
	
	gelLogCompilerDetails();
	gelLogSystemAPIDetails();
	gelLogGraphicsAPIDetails();

	// *** //

	SignalTest();
	DeferredTest();
	TimeTest();
	FileInfoTest();
	AssetPoolTest();

	// *** //
	
//	return AppMain();
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_TESTSUITE //
// - ------------------------------------------------------------------------------------------ - //
