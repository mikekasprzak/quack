// - ------------------------------------------------------------------------------------------ - //
#include "Font.h"
// - ------------------------------------------------------------------------------------------ - //
void GelFontPool_Subscriber( const st UserData ) {
	GelFont& MyPoolAsset = Gel::FontPool[UserData];
	
	GelAsset& MyAsset = Gel::AssetPool[MyPoolAsset.AssetID];
	const char* FileName = MyAsset.GetFileName();

	VLog( "+ Reloading Font File (%s) [%i:%i]...", FileName, MyPoolAsset.AssetID, UserData );

	if ( !MyAsset.IsBad() ) {
		MyPoolAsset.Unload();
		if ( GelFont::LoadBody( MyPoolAsset, MyAsset ) ) {
			// It worked... Do something... Maybe //
		}
		else {
			VLog( "- Unable to reload Font File (%s).", FileName );
		}				
	}

	VLog( "- Unable to reload Font File (%s).", FileName );
}
// - ------------------------------------------------------------------------------------------ - //
