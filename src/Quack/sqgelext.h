// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_SQGELEXT_H__
#define __GEL_WTF_SQGELEXT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Asset/Asset.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
inline void sqext_log( HSQUIRRELVM v ) {
	Log( "! STACK: %i", sq_gettop(v) );	
}
// - ------------------------------------------------------------------------------------------ - //
inline SQBool sqext_compile_nut( HSQUIRRELVM v, const char* Text, const st TextSize, const char* Name = "?" ) {
	VLog( "+ Compiling Script File (%s)...", Name );

	// Compile and push a closure on to the stack //
	if ( SQ_SUCCEEDED( sq_compilebuffer(v, Text, TextSize, Name, true) ) ) {
		VLog( "* Executing Script File (%s)...", Name );
		sq_pushroottable(v);	// Push the root table (first argument) //
		if ( SQ_SUCCEEDED( sq_call(v,1,false,SQTrue) ) ) {
			sq_remove(v,-1); 	// Remove the closure
			VLog( "- Script File Compiled and Executed successfully (%s).", Name );
			return SQTrue;
		}
		sq_pop(v,1);			// Pop the root table //
	}
	
	VLog( "- Error using Script File (%s).", Name );
	
	return SQFalse;
}
// - ------------------------------------------------------------------------------------------ - //
inline SQBool sqext_load_nut( HSQUIRRELVM v, const char* NutFile ) {
	Log( "+ Loading Script File (%s)...", NutFile );

	const char* NutFileResult = Gel::Search(NutFile);
	GelAssetPool::UID Nut = Gel::AssetPool.Load(NutFileResult);
		
	GelAsset& MyAsset = Gel::AssetPool[Nut];

	if ( !MyAsset.IsBad() ) {
		return_if_Log( sqext_compile_nut( v, MyAsset.Get(), MyAsset.GetSize(), NutFileResult ), "- Script File Loaded Successfully (%s).", NutFile );
//		// Compile and push a closure on to the stack //
//		if ( SQ_SUCCEEDED( sq_compilebuffer(v, MyAsset.Get(), MyAsset.GetSize(), NutFileResult, true) ) ) {
//			//sq_push(v,-2); // Grab the root table (because it's typically already pushed) //
//			sq_pushroottable(v);	// Push the root table (first argument) //
//			if ( SQ_SUCCEEDED( sq_call(v,1,false,SQTrue) ) ) {
//				sq_remove(v,-1); 	// Remove the closure
//				Log( "- Script File loaded (%s)", NutFile );
//				return SQTrue;
//			}
//			sq_pop(v,1);			// Pop the root table //
//		}
	}
	
	Log( "- Unable to load Script File (%s).", NutFile );
	
	return SQFalse;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_SQGELEXT_H__ //
// - ------------------------------------------------------------------------------------------ - //
