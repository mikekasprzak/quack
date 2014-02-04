// - ------------------------------------------------------------------------------------------ - //
#include "GelTiledMap.h"
#include <cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
void GelTiledMap::Load( const char* const InFile ) {
	// Use Asset Pool //
	GelAssetPool::UID Id = Gel::AssetPool.Load( Gel::Search( InFile ) );
	
	// Load JSON //
	cJSON* Root = cJSON_Parse( Gel::AssetPool[Id].GetStr() );
	
	
	// Process JSON Data //
//	cJSON* format = cJSON_GetObjectItem(root,"format");
//	int framerate = cJSON_GetObjectItem(format,"frame rate")->valueint;
	
	if ( Root ) {
		Log("I'm a wirrnerr");	
	}
	
	// Cleanup //
	cJSON_Delete(Root);
}
// - ------------------------------------------------------------------------------------------ - //
