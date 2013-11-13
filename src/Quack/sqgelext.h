// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_SQGELEXT_H__
#define __GEL_WTF_SQGELEXT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Asset/Asset.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
// The function we use to subscribe to AssetPool changes //
void sqext_reload_subscriber( const st UserData );
// - ------------------------------------------------------------------------------------------ - //
inline SQBool sqext_compile_nut( HSQUIRRELVM v, const char* Text, const st TextSize, const char* Name = "?" ) {
	VVLog( "+ Compiling Script File (%s)...", Name );

	// Compile and push a closure on to the stack //
	if ( SQ_SUCCEEDED( sq_compilebuffer(v, Text, TextSize, Name, true) ) ) {
		VVVLog( "* Executing Script File (%s)...", Name );
		sq_pushroottable(v);	// Push the root table (first argument) //
		if ( SQ_SUCCEEDED( sq_call(v,1,false,SQTrue) ) ) {
			sq_remove(v,-1); 	// Remove the closure
			VVLog( "- Script File Compiled and Executed successfully (%s).", Name );
			return SQTrue;
		}
		sq_pop(v,1);			// Pop the root table //
	}
	
	VVLog( "- Error using Script File (%s).", Name );
	
	return SQFalse;
}
// - ------------------------------------------------------------------------------------------ - //
inline SQBool sqext_load_nut( HSQUIRRELVM v, const char* NutFile ) {
	VLog( "+ Loading Script File (%s)...", NutFile );

	const char* NutFileResult = Gel::Search(NutFile);
	VVVLog( "* Full Name: %s", NutFileResult );
	GelAssetPool::UID Nut = Gel::AssetPool.Load(NutFileResult);
		
	GelAsset& MyAsset = Gel::AssetPool[Nut];
	VVVLog( "* NUT: %i", Nut );

	if ( !MyAsset.IsBad() ) {
		MyAsset.SubscribeToChanges( sqext_reload_subscriber, Nut );
		
		return_if_VLog( 
			sqext_compile_nut( v, MyAsset.Get(), MyAsset.GetSize(), NutFileResult ), 
			"- Script File Loaded Successfully (%s).", NutFile 
		);
	}
	
	VLog( "- Unable to load Script File (%s).", NutFile );
	
	return SQFalse;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_SQGELEXT_H__ //
// - ------------------------------------------------------------------------------------------ - //
