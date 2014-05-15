// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ATLAS_GELATLASPOOL_H__
#define __GEL_ATLAS_GELATLASPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelAtlas.h"
// - ------------------------------------------------------------------------------------------ - //
class GelAtlasPool: public GelPool<GelAtlas> {
public:
	_GELPOOL_LOAD_FUNC()
	_GELPOOL_LOAD_BODY("Atlas",GelAtlas)

	inline UID LoadAndIndex( const char* _FileName, int* ArtIndex = 0 ) {
		std::string AtlasName = _FileName;
		std::string AssetName;
		
		st StrPos = AtlasName.find(":");
		if ( StrPos != std::string::npos ) {
			AssetName = AtlasName.substr(StrPos+1);
			AtlasName = AtlasName.substr(0,StrPos);
		}
		
		UID Ret = Load( AtlasName.c_str() );
		if ( AssetName.size() ) {
			if ( ArtIndex ) {
				GelAtlas& Atlas = operator[](Ret);
				*ArtIndex = Atlas.Find( AssetName.c_str() );
			}
		}
		else {			
			*ArtIndex = 0;
		}
		
		return Ret;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ATLAS_GELATLASPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
