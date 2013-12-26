// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKEL_GELSKELANIMATOR_H__
#define __GEL_SKEL_GELSKELANIMATOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSkel.h"
// - ------------------------------------------------------------------------------------------ - //
class GelSkelAnimator {
protected:
	GelSkelPool::UID		AssetUID;
	spSkeleton*				Skeleton;
	spAnimationState*		AnimState;
public:
	inline GelSkelAnimator() {
//		AssetUID = Gel::SkelPool.Load( "SpineTest/spineboy.json" );
//		Skeleton = spSkeleton_create( Gel::SkelMeshPool[AssetUID].GetSkeletonData() );
//		AnimState = spAnimationState_create(0);//stateData);
	}
		
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKEL_GELSKELANIMATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
