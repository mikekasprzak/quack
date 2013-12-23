// - ------------------------------------------------------------------------------------------ - //
// Skeleton JSONs can be optionally created with an Attachment Loader. I'm not actually sure what
//   the other "attachment" options are, but the only option in Spine is an atlas.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKELMESH_GELSKELMESH_H__
#define __GEL_SKELMESH_GELSKELMESH_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
#include <Atlas/Atlas.h>
// - ------------------------------------------------------------------------------------------ - //
#include <spine/spine.h>
// - ------------------------------------------------------------------------------------------ - //
class GelSkelMesh {
protected:
	st32 MyID;	// My TextureID (an Internal Copy) //

	GelAtlasPool::UID AtlasUID;
	GelAssetPool::UID AssetUID;
	
	spSkeletonJson* SkeletonJson;
	spSkeletonData* SkeletonData;
	
	spSkeleton* Skeleton;

	std::vector< spAnimation* > Animation;
//	spAnimation* Animation;	// NOTE: Need one per animation stored in the Spine file //
	
public:
	inline GelSkelMesh( const st32 _MyID ) :
		MyID( _MyID ),
		AtlasUID( 0 ),
		AssetUID( 0 ),
		SkeletonJson( 0 ),
		SkeletonData( 0 ),
		Skeleton( 0 )
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
			std::string BaseFileName = Gel::String::GetBaseDirectory(InFile);	
			AtlasUID = Gel::AtlasPool.Load( (BaseFileName + ".atlas").c_str() );

			GelAtlas& Atlas = Gel::AtlasPool[AtlasUID];
			GelAsset& Asset = Gel::AssetPool[AssetUID];

			Log("+ Skeleton");
			SkeletonJson = spSkeletonJson_create(Atlas.Atlas);
			SkeletonData = spSkeletonJson_readSkeletonData( SkeletonJson, Asset.GetStr() ); // The raw JSON data as a c string
			Skeleton = spSkeleton_create(SkeletonData);
			
			//Animation = spSkeletonData_findAnimation(SkeletonData, "walk");
			for ( st32 idx = 0; idx < ) {
				SkeletonData->animations
			}
				
			
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

			Log("- Skeleton (%x,%x,%x)",SkeletonJson,SkeletonData,Skeleton);
		}
	}
	
	inline void Unload() {
		// TODO: For all aimations //
//		if ( Animation )
//			spAnimation_dispose(Animation);
		Animation.clear();		

		if ( Skeleton ) {
			spSkeleton_dispose(Skeleton);
			Skeleton = 0;
		}
		if ( SkeletonData ) {
			spSkeletonData_dispose(SkeletonData);
			SkeletonData = 0;
		}
		if ( SkeletonJson ) {
			spSkeletonJson_dispose(SkeletonJson);
			SkeletonJson = 0;
		}
		
		// TODO: Free Atlas and AssetUID's ? //
		// or at the very least, say "I'm done with them" //
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKELMESH_GELSKELMESH_H__ //
// - ------------------------------------------------------------------------------------------ - //
