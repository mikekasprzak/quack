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
	
	enum {
		GT_1BPP =				1,
		GT_2BPP =				2,
		GT_3BPP =				3,
		GT_4BPP =				4,
		GT_BYTESPERPIXEL = 		0xF,
		
		GT_SMOOTH = 			0x100,
		GT_FLIP = 				0x200,
		GT_PREMULTIPLYALPHA = 	0x400,
	};
	
	int Flags;

public:
	inline GelTexture( const st32 _MyID ) :
		MyID( _MyID ),
		AssetID( 0 ),
		Handle( 0 ),
		_Width( 0 ), _Height( 0 ),
		Flags( 0 )
	{
	}
	
public:
	inline void Load( const char* _FileName, const bool Smooth = true, const bool Flip = true, const bool PreMultiplyAlpha = true ) {
		AssetID = Gel::AssetPool.Load( _FileName );
			
		// TODO: Add the following to an OnLoaded listener.
		
		if ( AssetID ) {
			Flags = Smooth ? GT_SMOOTH : 0;
			Flags |= Flip ? GT_FLIP : 0;
			Flags |= PreMultiplyAlpha ? GT_PREMULTIPLYALPHA : 0;
			
			GelAsset& MyAsset = Gel::AssetPool[AssetID];
			MyAsset.SubscribeToChanges( GelTexturePool_Subscriber, MyID );

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
			MyTexture.Handle = Gel::upload_STBTexture( 
				Tex, 
				MyTexture.Flags & GT_SMOOTH, 
				MyTexture.Flags & GT_FLIP, 
				MyTexture.Flags & GT_PREMULTIPLYALPHA
				);
				
			// TODO: Correct these numbers in the case of MaxTextureSize being larger.
			MyTexture._Width = Tex.Width;
			MyTexture._Height = Tex.Height;
			MyTexture.Flags = Tex.Info | (MyTexture.Flags & ~GT_BYTESPERPIXEL);
			
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
