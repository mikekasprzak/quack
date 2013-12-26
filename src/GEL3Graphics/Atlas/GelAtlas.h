// - ------------------------------------------------------------------------------------------ - //
// GelAtlas is based on Spine's Texture Atlases (libGDX) //
//
// https://github.com/libgdx/libgdx/wiki/Texture-packer (requires a Java program, bleh)
// http://code.google.com/p/libgdx-texturepacker-gui/ (pretty lousy)
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
	friend class GelSkel;
protected:
	st32 MyID;	// My ID (an Internal Copy) //

	GelAssetPool::UID AssetUID;	

	spAtlas* Atlas;	
	
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
			Log("- spAtlas_readAtlas (%x)",Atlas);
			
			//spAtlasRegion* MyRegion = spAtlas_findRegion(Atlas,"regionName");
			// spAtlas contains linked lists. A list of Pages, and a list of Regions //
			
			// I've stored the Texture UID in MyRegion->page->rendererObject

			// It may be reasonable to always search for a region initially.
			// Need a way of getting a Region Handle. GelAtlasRegion ?
			
			// If an Atlas changes, any pointers (spAtlasRegion's) break. 
		}
	}
	
	inline void Unload() {
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
