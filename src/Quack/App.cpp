// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
#include "AssetPool.h"
#include "Search.h"
// - ------------------------------------------------------------------------------------------ - //
void AppInit() {
	QuackVMInit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int AppMain() {
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
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
