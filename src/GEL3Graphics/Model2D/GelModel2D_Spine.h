// - ------------------------------------------------------------------------------------------ - //
// NOTE: Getting this working is going to require some slight rearchitecting.
//
// Spine exports are ambiguous. "n" atlas files, and a single json skeleton file. But 
//   before we can load a skeleton file, we need at least 1 atlas loaded. Thing is, the
//   spine json file makes no mention at all of the atlas file. So, a spine export by
//   itself is actually worthless. A list of all atlases, plus the spine file associated
//   with it is required.
//
// Skeleton JSONs can be optionally created with an Attachment Loader. I'm not actually sure what
//   the other "attachment" options are, but the only option in Spine is an atlas.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_MODEL2D_GELMODEL2D_SPINE_H__
#define __GEL_MODEL2D_GELMODEL2D_SPINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //
#include <spine/spine.h>
// - ------------------------------------------------------------------------------------------ - //
class GelModel2D {
protected:
	// NOTE: This is bad! Spine requires a source atlas or a "Attachment Loader" to read a skeleton file.
	spAtlas* Atlas;
	spSkeletonJson* SkeletonJson;
	spSkeletonData* SkeletonData;
	
	spSkeleton* Skeleton;
	spAnimation* Animation;	// NOTE: Need one per animation stored in the Spine file //
	
	std::vector< GelTexturePool::UID > TexturePage;
	
public:
	inline GelModel2D() :
		Atlas( 0 ),
		SkeletonJson( 0 ),
		SkeletonData( 0 ),
		Skeleton( 0 ),
		Animation( 0 )
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

			Log("+ spAtlas_readAtlas");
			// TODO: Replace the last part with the "DirOnly" part of the loaded Asset File. //
			// NOTE: Asset is the JSON file, not the Atlas!!!!!
			Atlas = spAtlas_readAtlas( Asset.Get(), Asset.GetSize(), "/dir/goes/here/");
			//Atlas = spAtlas_readAtlasFile("spineboy.atlas");
			Log("- spAtlas_readAtlas (%x)",Atlas);

			Log("+ Skeleton");
			SkeletonJson = spSkeletonJson_create(Atlas);
			Log("* Tween (%x)",SkeletonJson);
			SkeletonData = spSkeletonJson_readSkeletonData( SkeletonJson, Asset.GetStr() ); // The raw JSON data as a c string
			//SkeletonData = spSkeletonJson_readSkeletonDataFile(SkeletonJson, "spineboy.json");
			Log("* Tween (%x)",SkeletonData);
			Skeleton = spSkeleton_create(SkeletonData);		
			Log("* Tween (%x)",Skeleton);
			Animation = spSkeletonData_findAnimation(SkeletonData, "walk");
					
			Log("- Skeleton (%x,%x,%x,%x)",SkeletonJson,SkeletonData,Skeleton,Animation);
			
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
				
//		if ( Model ) {
//			delete Model;
//			Model = 0;
//		}

		if ( Skeleton )
			spSkeleton_dispose(Skeleton);
		if ( SkeletonData )
			spSkeletonData_dispose(SkeletonData);
		if ( SkeletonJson )
			spSkeletonJson_dispose(SkeletonJson);
		if ( Atlas )
			spAtlas_dispose(Atlas);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_MODEL2D_GELMODEL2D_SPINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
