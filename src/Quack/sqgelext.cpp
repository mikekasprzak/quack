// - ------------------------------------------------------------------------------------------ - //
#include "sqgelext.h"
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
void sqext_reload_subscriber( const st UserData ) {
	GelAsset& MyAsset = Gel::AssetPool[UserData];
	const char* NutFile = MyAsset.GetFileName();

	VLog( "+ Reloading Script File (%s) [%i]...", NutFile, UserData );

	if ( !MyAsset.IsBad() ) {
		return_if_void_Log( 
			sqext_compile_nut( vm, MyAsset.Get(), MyAsset.GetSize(), NutFile ), 
			"- Script File Reloaded Successfully (%s).", NutFile 
		);
	}
	
	VLog( "- Unable to reload Script File (%s).", NutFile );
}
// - ------------------------------------------------------------------------------------------ - //
