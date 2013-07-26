// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //
#include "AssetPool.h"
// - ------------------------------------------------------------------------------------------ - //

void MyFunc() {
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
int AppMain() {
	{
		Log( "" );
		Log( "-=- Signal Test:" );
		
		// Signal Testing Code //
		Signal MySignal;
		MySignal.Connect( MyFunc );
		MySignal.Connect( MyFunc2, 200 );
		MySignal.Connect( MyFunc3, 1 );
		MySignal.Connect( MyFunc3, 2 );
		MySignal.Connect( MyFunc3, 3 );
		st Ret = (st)MySignal( 25 );
		Log( "Final Ret is: %i", (int)Ret );
	}
	
	{
		Log( "" );
		Log( "-=- Deferred Test:" );
		
		// Deferred Testing Code //
		Deferred MyDef;
		MyDef.Then( MyFunc );
		MyDef.OnError( MyFunc2 );
		//MyDef.Always( MyFunc2, 64 );
		
		MyDef.Callback( 13 );
//		MyDef.Errback( 10 );

		Log( "Adding a late action. These will automatically trigger Callback or Errback." );
		
		MyDef.Then( MyFunc2 );
		MyDef.OnError( MyFunc );
	}
	
	{
//		Log( "" );
//		Log( "-=- Asset Test:" );
//
//		// Asset Test //
//		cAsset MyAsset;
//		
//		MyAsset.Load( "project/main.nut" );
//		if ( MyAsset.IsLoaded() ) {
//			Log( MyAsset.GetStr() );
//		}
//		else {
//			Log( "Nope!" );
//		}
//		
//		MyAsset.Unload();
	}
	
	{
		Log( "" );
		Log( "-=- AssetPool Test:" );

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
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
