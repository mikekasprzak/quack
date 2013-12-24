// - ------------------------------------------------------------------------------------------ - //
// Skeleton JSONs can be optionally created with an Attachment Loader. I'm not actually sure what
//   the other "attachment" options are, but the only option in Spine is an atlas.
//
// TODO: Since Skeletons rely on Atlas' and internally use pointers, the SkelMesh should
//       subscribe to changes made to the Atlas, and reload self.
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
	friend class GelSkelAnim;
protected:
	st32 MyID;	// My TextureID (an Internal Copy) //

	GelAtlasPool::UID AtlasUID;
	GelAssetPool::UID AssetUID;
	
	spSkeletonJson* SkeletonJson;
	spSkeletonData* SkeletonData;
	
public:
	inline GelSkelMesh( const st32 _MyID ) :
		MyID( _MyID ),
		AtlasUID( 0 ),
		AssetUID( 0 ),
		SkeletonJson( 0 ),
		SkeletonData( 0 )
	{	
	}
	
public:
	inline void Load( const char* InFile ) {
		const char* File = Gel::Search( InFile );
		_Load( File );
	}

	inline void _Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		Unload();
		
		// Load the Asset First //
		AssetUID = Gel::AssetPool.Load( InFile );

		if ( AssetUID ) {
			// Load the Atlas 2nd, so the files are correctly prioritized //
			std::string BaseFileName = Gel::String::GetBaseDirectory(InFile);	
			AtlasUID = Gel::AtlasPool.Load( (BaseFileName + ".atlas").c_str() );

			GelAtlas& Atlas = Gel::AtlasPool[AtlasUID];
			GelAsset& Asset = Gel::AssetPool[AssetUID];

			Log("+ SkelMesh");
			SkeletonJson = spSkeletonJson_create(Atlas.Atlas);
			SkeletonData = spSkeletonJson_readSkeletonData( SkeletonJson, Asset.GetStr() ); // The raw JSON data as a c string
			//Skeleton = spSkeleton_create(SkeletonData);
			
			//Animation = spSkeletonData_findAnimation(SkeletonData, "walk"); // Linear Search //
			//SkeletonData->animations[Index]; // An array of SkeletonData->animationCount elements //
			
			Log("- SkelMesh (%x,%x)",SkeletonJson,SkeletonData);
		}
	}
	
	inline void Unload() {
//		if ( Skeleton ) {
//			spSkeleton_dispose(Skeleton);
//			Skeleton = 0;
//		}
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

public:
	inline spSkeletonData* GetSkeletonData() const {
		return SkeletonData;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKELMESH_GELSKELMESH_H__ //
// - ------------------------------------------------------------------------------------------ - //
