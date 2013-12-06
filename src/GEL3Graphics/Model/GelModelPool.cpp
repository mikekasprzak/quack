// - ------------------------------------------------------------------------------------------ - //
#include "Model.h"
// - ------------------------------------------------------------------------------------------ - //
void GelModelPool_Subscriber( const st UserData ) {
	GelModel& MyPoolAsset = Gel::ModelPool[UserData];
	
	GelAsset& MyAsset = Gel::AssetPool[MyPoolAsset.AssetID];
	const char* FileName = MyAsset.GetFileName();

	VLog( "+ Reloading Model File (%s) [%i:%i]...", FileName, MyPoolAsset.AssetID, UserData );

	if ( !MyAsset.IsBad() ) {
		MyPoolAsset.Unload();
		if ( GelModel::LoadBody( MyPoolAsset, MyAsset ) ) {
			// It worked... Do something... Maybe //
		}
		else {
			VLog( "- Unable to reload Model File (%s).", FileName );
		}				
	}

	VLog( "- Unable to reload Model File (%s).", FileName );
}
// - ------------------------------------------------------------------------------------------ - //
