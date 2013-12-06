// - ------------------------------------------------------------------------------------------ - //
#include "Texture.h"
// - ------------------------------------------------------------------------------------------ - //
void GelTexturePool_Subscriber( const st UserData ) {
	GelTexture& MyTexture = Gel::TexturePool[UserData];
	
	GelAsset& MyAsset = Gel::AssetPool[MyTexture.AssetID];
	const char* FileName = MyAsset.GetFileName();

	VLog( "+ Reloading Texture File (%s) [%i:%i]...", FileName, MyTexture.AssetID, UserData );

	if ( !MyAsset.IsBad() ) {
		MyTexture.Unload();
		if ( GelTexture::LoadBody( MyTexture, MyAsset ) ) {
			// It worked... Do something... Maybe //
		}
		else {
			Log( "! Unsupported Texture! %s", FileName );
			VLog( "- Unable to reload Texture File (%s).", FileName );
		}				
	}

	VLog( "- Unable to reload Texture File (%s).", FileName );
}
// - ------------------------------------------------------------------------------------------ - //
