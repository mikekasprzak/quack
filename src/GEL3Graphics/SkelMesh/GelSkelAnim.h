// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKELMESH_GELSKELANIMATOR_H__
#define __GEL_SKELMESH_GELSKELANIMATOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSkelMesh.h"
// - ------------------------------------------------------------------------------------------ - //
class GelSkelAnimator {
protected:
	GelSkelMeshPool::UID	AssetUID;
	spSkeleton*				Skeleton;
	spAnimationState*		AnimState;
public:
	inline GelSkelAnimator() {
//		AssetUID = Gel::SkelMeshPool.Load( "SpineTest/spineboy.json" );
//		Skeleton = spSkeleton_create( Gel::SkelMeshPool[AssetUID].GetSkeletonData() );
//		AnimState = spAnimationState_create(0);//stateData);
	}
		
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKELMESH_GELSKELANIMATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
