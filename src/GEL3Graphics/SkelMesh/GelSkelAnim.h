// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKELMESH_GELSKELANIM_H__
#define __GEL_SKELMESH_GELSKELANIM_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSkelMesh.h"
// - ------------------------------------------------------------------------------------------ - //
class GelSkelAnim {
protected:
	GelSkelMeshPool::UID	AssetUID;
	spSkeleton*				Skeleton;
	spAnimationState*		AnimState;
public:
	inline GelSkelAnim() {
//		AssetUID = Gel::SkelMeshPool.Load( "SpineTest/spineboy.json" );
//		Skeleton = spSkeleton_create( Gel::SkelMeshPool[AssetUID].GetSkeletonData() );
//		AnimState = spAnimationState_create(0);//stateData);
	}
		
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKELMESH_GELSKELANIM_H__ //
// - ------------------------------------------------------------------------------------------ - //
