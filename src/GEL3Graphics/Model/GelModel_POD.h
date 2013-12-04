// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_MODEL_GELMODEL_POD_H__
#define __GEL_MODEL_GELMODEL_POD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //
#include <PVRTModelPOD.h>
// - ------------------------------------------------------------------------------------------ - //
class GelModel {
protected:
	CPVRTModelPOD* Model;
	std::vector< GelTexturePool::UID > TexturePage;
	
public:
	inline GelModel() :
		Model( 0 )
	{	
	}
	
public:
	inline void Load( const char* InFile ) {
		const char* File = Gel::Search( InFile );
		_Load( File );
	}

	inline void _Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		Unload();

		GelAssetPool::UID AssetUID = Gel::AssetPool.Load( InFile );		

		if ( AssetUID ) {
			GelAsset& Asset = Gel::AssetPool[AssetUID];
			
			Model = new CPVRTModelPOD();
			EPVRTError Error = Model->ReadFromMemory( Asset.Get(), Asset.GetSize() );
		
			if ( Error == PVR_SUCCESS ) {
				Log("Success!");
				
				Log("Nodes: %i  MeshNodes: %i  Meshes: %i  AnimationFrames: %i (Lights: %i  Cameras: %i  Materials: %i  Textures: %i)", 
					Model->nNumNode, Model->nNumMeshNode, Model->nNumMesh, Model->nNumFrame,
					Model->nNumLight, Model->nNumCamera, Model->nNumMaterial, Model->nNumTexture );
					
				Log("Verts: %i  Faces: %i  UVW: %i",
					Model->pMesh[0].nNumVertex, Model->pMesh[0].nNumFaces, Model->pMesh[0].nNumUVW );
					
				for ( st32 idx = 0; idx < Model->nNumTexture; idx++ ) {
					Log("%i T: %s", idx, Model->pTexture[idx].pszName );
				}
				
//		for ( size_t idx = 0; idx < Font->PageName->Size; idx++ ) {
//			const char* TextureFile = Gel::Search( Font->PageName->Data[idx] );
//
//			if ( TextureFile ) {
//				// HACK: Don't Flip. Need to sort out the flip order in my brain //
//				TexturePage.push_back( Gel::TexturePool.Load( TextureFile, Smooth, false, PreMultiplyAlpha ) );
//			}
//		}
			}
		}
	}
	
	inline void Unload() {
		TexturePage.clear();		
				
		if ( Model ) {
			delete Model;
			Model = 0;
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_MODEL_GELMODEL_POD_H__ //
// - ------------------------------------------------------------------------------------------ - //
