// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SHADER_GELSHADER_H__
#define __GEL_SHADER_GELSHADER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Render/UberShader.h>
// - ------------------------------------------------------------------------------------------ - //
class GelShader {
protected:
	st32 MyID;	// My ID (an Internal Copy) //

	GelAssetPool::UID AssetUID;	

	GelUberShader* Shader;
	
public:
	inline GelShader( const st32 _MyID ) :
		MyID( _MyID ),
		AssetUID( 0 )
//		Atlas( 0 ),
	{	
	}
	
public:
	inline void Load( const char* InFile ) {
		const char* File = Gel::Search( InFile );
		_Load( File );
	}

	inline void _Load( const char* InFile ) {
		Unload();
		
		AssetUID = Gel::AssetPool.Load( InFile );

		if ( AssetUID ) {
			GelAsset& Asset = Gel::AssetPool[AssetUID];

//			Log("+ spShader_readShader");
//			Atlas = spAtlas_readAtlas( Asset.Get(), Asset.GetSize(), Gel::String::GetDirectorySlash(InFile).c_str() );
//			Log("- spAtlas_readAtlas (%x)",Atlas);
		}
	}
	
	inline void Unload() {		
//		if ( Shader ) {
//			spAtlas_dispose(Atlas);
//			Atlas = 0;
//		}
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SHADER_GELSHADER_H__ //
// - ------------------------------------------------------------------------------------------ - //
