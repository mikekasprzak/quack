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
extern void GelModelPool_Subscriber( const st UserData );
// - ------------------------------------------------------------------------------------------ - //
class GelModel {
public:
	st32 MyID;	// My TextureID (an Internal Copy) //
	GelAssetPool::UID AssetID;
	CPVRTModelPOD* Model;
	std::vector< GelTexturePool::UID > TexturePage;
	
public:
	inline GelModel( const st32 _MyID ) :
		MyID( _MyID ),
		AssetID( 0 ),
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

		AssetID = Gel::AssetPool.Load( InFile );

		if ( AssetID ) {
			GelAsset& MyAsset = Gel::AssetPool[AssetID];
			MyAsset.SubscribeToChanges( GelModelPool_Subscriber, MyID );
			
			if ( LoadBody( *this, MyAsset ) ) {
				// It worked... Do something... Maybe //
			}
		
//			Model = new CPVRTModelPOD();
//			EPVRTError Error = Model->ReadFromMemory( Asset.Get(), Asset.GetSize() );
//		
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
				
		if ( Model ) {
			delete Model;
			Model = 0;
		}
	}
	
	static bool LoadBody( GelModel& MyModel, GelAsset& MyAsset ) {
		MyModel.Model = new CPVRTModelPOD();
		EPVRTError Error = MyModel.Model->ReadFromMemory( MyAsset.Get(), MyAsset.GetSize() );
	
		if ( Error == PVR_SUCCESS ) {
			CPVRTModelPOD* Model = MyModel.Model;
			
			Log("Nodes: %i  MeshNodes: %i  Meshes: %i  AnimationFrames: %i (Lights: %i  Cameras: %i  Materials: %i  Textures: %i)", 
				Model->nNumNode, Model->nNumMeshNode, Model->nNumMesh, Model->nNumFrame,
				Model->nNumLight, Model->nNumCamera, Model->nNumMaterial, Model->nNumTexture );
				
			Log("Verts: %i  Faces: %i  UVW: %i",
				Model->pMesh[0].nNumVertex, Model->pMesh[0].nNumFaces, Model->pMesh[0].nNumUVW );
				
			for ( st32 idx = 0; idx < Model->nNumTexture; idx++ ) {
				Log("%i T: %s", idx, Model->pTexture[idx].pszName );
				const char* TextureFile = Gel::Search( Model->pTexture[idx].pszName );
	
				if ( TextureFile ) {
					MyModel.TexturePage.push_back( Gel::TexturePool.Load( TextureFile ) );
				}
			}
			
			return true;
		}
		
		return false;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_MODEL_GELMODEL_POD_H__ //
// - ------------------------------------------------------------------------------------------ - //
