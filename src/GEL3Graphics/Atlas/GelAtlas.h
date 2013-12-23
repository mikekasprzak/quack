// - ------------------------------------------------------------------------------------------ - //
// GelAtlas is based on Spine's Texture Atlases (libGDX) //
//
// https://github.com/libgdx/libgdx/wiki/Texture-packer
// http://code.google.com/p/libgdx-texturepacker-gui/
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ATLAS_GELATLAS_H__
#define __GEL_ATLAS_GELATLAS_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //
#include <spine/spine.h>
// - ------------------------------------------------------------------------------------------ - //
class GelAtlas {
	friend class GelSkelMesh;
protected:
	st32 MyID;	// My TextureID (an Internal Copy) //

	GelAssetPool::UID AssetUID;	

	spAtlas* Atlas;	
	std::vector< GelTexturePool::UID > TexturePage;
	
public:
	inline GelAtlas( const st32 _MyID ) :
		MyID( _MyID ),
		AssetUID( 0 ),
		Atlas( 0 )
	{	
	}
	
public:
	inline void Load( const char* InFile ) {
		const char* File = Gel::Search( InFile );
		_Load( File );
	}

	inline void _Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		Unload();
		
		AssetUID = Gel::AssetPool.Load( InFile );

		if ( AssetUID ) {
			GelAsset& Asset = Gel::AssetPool[AssetUID];

			Log("+ spAtlas_readAtlas");
			Atlas = spAtlas_readAtlas( Asset.Get(), Asset.GetSize(), Gel::String::GetDirectorySlash(InFile).c_str() );
			//Atlas = spAtlas_readAtlasFile("spineboy.atlas");
			Log("- spAtlas_readAtlas (%x)",Atlas);

//			if ( Error == PVR_SUCCESS ) {
//				Log("Nodes: %i  MeshNodes: %i  Meshes: %i  AnimationFrames: %i (Lights: %i  Cameras: %i  Materials: %i  Textures: %i)", 
//					Model->nNumNode, Model->nNumMeshNode, Model->nNumMesh, Model->nNumFrame,
//					Model->nNumLight, Model->nNumCamera, Model->nNumMaterial, Model->nNumTexture );
//					
//				Log("Verts: %i  Faces: %i  UVW: %i",
//					Model->pMesh[0].nNumVertex, Model->pMesh[0].nNumFaces, Model->pMesh[0].nNumUVW );
//					
//				for ( st32 idx = 0; idx < Model->nNumTexture; idx++ ) {
//					Log("%i T: %s", idx, Model->pTexture[idx].pszName );
//					const char* TextureFile = Gel::Search( Model->pTexture[idx].pszName );
//		
//					if ( TextureFile ) {
//						TexturePage.push_back( Gel::TexturePool.Load( TextureFile ) );
//					}
//				}
//			}
		}
	}
	
	inline void Unload() {
		TexturePage.clear();

		// NOTE: Disposal is currently broken (Dec 20th) //
//		if ( Atlas ) {
//			spAtlas_dispose(Atlas);
//			Atlas = 0;
//		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ATLAS_GELATLAS_H__ //
// - ------------------------------------------------------------------------------------------ - //
