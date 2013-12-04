// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_MODEL_GELMODEL_POD_H__
#define __GEL_MODEL_GELMODEL_POD_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
// - ------------------------------------------------------------------------------------------ - //
class GelModel {
public:
	inline void Load( const char* InFile ) {
		const char* File = Gel::Search( InFile );
		_Load( File );
	}

	inline void _Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		GelAssetPool::UID AssetUID = Gel::AssetPool.Load( InFile );
		
		// POD Code goes here //
//		POD = new_read_BMFont( Gel::AssetPool[FontUID].GetDataBlock() );
//		
//		for ( size_t idx = 0; idx < Font->PageName->Size; idx++ ) {
//			const char* TextureFile = Gel::Search( Font->PageName->Data[idx] );
//
//			if ( TextureFile ) {
//				// HACK: Don't Flip. Need to sort out the flip order in my brain //
//				TexturePage.push_back( Gel::TexturePool.Load( TextureFile, Smooth, false, PreMultiplyAlpha ) );
//			}
//		}
	}
	
	inline void Unload() {
//		TexturePage.clear();		
//				
//		if ( POD ) {
//			delete_BMFont( Font );
//			POD = 0;
//		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_MODEL_GELMODEL_POD_H__ //
// - ------------------------------------------------------------------------------------------ - //
