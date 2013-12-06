// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_GELTEXTURE_H__
#define __GEL_TEXTURE_GELTEXTURE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/Asset.h>
#include "GelTextureHandle.h"

#include "Texture_STB.h"
#include "Texture_PVR3.h"
// - ------------------------------------------------------------------------------------------ - //
extern void GelTexturePool_Subscriber( const st UserData );
// - ------------------------------------------------------------------------------------------ - //
class GelTexture {
	friend class GelTexturePool;
	friend void GelTexturePool_Subscriber( const st UserData );
protected:
	st32 MyID;	// My TextureID (an Internal Copy) //
	GelAssetPool::UID AssetID;
	GelTextureHandle Handle;
	
	int _Width, _Height;

public:
	inline GelTexture( const st32 _MyID ) :
		MyID( _MyID ),
		AssetID( 0 ),
		Handle( 0 ),
		_Width( 0 ), _Height( 0 )
	{
	}
	
public:
	inline void Load( const char* _FileName, const bool Smooth = true, const bool Flip = true, const bool PreMultiplyAlpha = true ) {
		AssetID = Gel::AssetPool.Load( _FileName );
			
		// TODO: Add the following to an OnLoaded listener.
		
		if ( AssetID ) {
			GelAsset& MyAsset = Gel::AssetPool[AssetID];
			Log("MyID: %i", MyID);
			MyAsset.SubscribeToChanges( GelTexturePool_Subscriber, MyID );
			
//			if ( Gel::is_STBTexture(MyAsset.Get(),MyAsset.GetSize()) ) {
//				Gel::STBTexture Tex = Gel::new_STBTexture( MyAsset.Get(), MyAsset.GetSize() );
//
//				Handle = Gel::upload_STBTexture( Tex, Smooth, Flip, PreMultiplyAlpha );
//					
//				// TODO: Correct these numbers in the case of MaxTextureSize being larger.
//				_Width = Tex.Width;
//				_Height = Tex.Height;
//				//SizeInBytes = Tex.Info;
//				
//				Gel::delete_STBTexture( Tex );
//			}
			if ( LoadBody( *this, MyAsset ) ) {
				// It worked... Do something... Maybe //
			}
			else {
				Log( "! Unsupported Texture! %s", _FileName );
			}
		}
	}
	
	inline void Unload() {
		if ( Handle ) {
			delete_GelTextureHandle( Handle );
			//Gel::AssetPool[AssetID].Unload(); // Done automatically by AssetPool //
			Handle = 0;
		}
	}
	
	static bool LoadBody( GelTexture& MyTexture, GelAsset& MyAsset ) {
		if ( Gel::is_STBTexture(MyAsset.Get(),MyAsset.GetSize()) ) {
			Gel::STBTexture Tex = Gel::new_STBTexture( MyAsset.Get(), MyAsset.GetSize() );

			// NOTE: Cannot handle these extra args. //
			MyTexture.Handle = Gel::upload_STBTexture( Tex );//, Smooth, Flip, PreMultiplyAlpha );
				
			// TODO: Correct these numbers in the case of MaxTextureSize being larger.
			MyTexture._Width = Tex.Width;
			MyTexture._Height = Tex.Height;
			//SizeInBytes = Tex.Info;
			
			Gel::delete_STBTexture( Tex );
			
			return true;
		}
		// TODO: PVR //
		
		return false;
	}
	
public:
	inline void Bind( const st32 TextureUnit = 0 ) {
		bind_GelTextureHandle( Handle, TextureUnit );
	}
	
	inline const GelAssetPool::UID GetAssetId() const {
		return AssetID;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_TEXTUREPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
