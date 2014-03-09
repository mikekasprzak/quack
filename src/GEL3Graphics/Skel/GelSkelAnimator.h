// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKEL_GELSKELANIMATOR_H__
#define __GEL_SKEL_GELSKELANIMATOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSkel.h"
#include "GelSkelPool.h"

#include <Render/Render.h>
#include <Texture/Texture.h>
#include <Array/Array.h>
// - ------------------------------------------------------------------------------------------ - //
class GelSkelAnimator {
protected:
	GelSkelPool::UID		AssetUID;
	spSkeleton*				Skeleton;
	spAnimationStateData*	AnimStateData;
	spAnimationState*		AnimState;
public:
	inline GelSkelAnimator() :
		AssetUID( 0 ),
		Skeleton( 0 ),
		AnimStateData( 0 ),
		AnimState( 0 )
	{
	}
	
	inline GelSkelAnimator( const GelSkelPool::UID _Asset ) :
		AssetUID( _Asset ),
		Skeleton( spSkeleton_create( Gel::SkelPool[AssetUID].GetSkeletonData() ) ),
		AnimStateData( spAnimationStateData_create( Skeleton->data ) ),
		AnimState( spAnimationState_create( AnimStateData ) )
	{
	}
	
	inline void _Constructor() {
		AssetUID = 0;
		Skeleton = 0;
		AnimStateData = 0;
		AnimState = 0;
	}
	
	inline ~GelSkelAnimator() {
		Unload();
	}

	inline void Unload() {
		// TODO: Done with asset? //
		AssetUID = 0;

		if ( AnimState ) {
			spAnimationState_dispose( AnimState );
			AnimState = 0;
		}

		if ( AnimStateData ) {
			spAnimationStateData_dispose( AnimStateData );
			AnimStateData = 0;
		}

		if ( Skeleton ) {
			spSkeleton_dispose( Skeleton );
			Skeleton = 0;
		}
	}
		
	inline void Load( const GelSkelPool::UID _Asset ) {
		Unload();
		
		AssetUID = _Asset,
		Skeleton = spSkeleton_create( Gel::SkelPool[AssetUID].GetSkeletonData() );
		AnimStateData = spAnimationStateData_create( Skeleton->data );
		AnimState = spAnimationState_create( AnimStateData );
	}

public:
	// Set an animation (Clear, Add Track), but only if it's not the current animation //
	inline void Set( const int TrackIndex, const char* Name, const bool Loop = true ) {
		Set( TrackIndex, spSkeletonData_findAnimation( Skeleton->data, Name ), Loop );
	}
	inline void Set( const int TrackIndex, spAnimation* Anim, const bool Loop = true ) {
		if ( GetAnim(TrackIndex) != Anim ) {
			Force( TrackIndex, Anim, Loop );
		}
	}
	// Always set an animation (Clear, Add Track) //
	inline void Force( const int TrackIndex, const char* Name, const bool Loop = true ) {
		Force( TrackIndex, spSkeletonData_findAnimation( Skeleton->data, Name ), Loop );
	}
	inline void Force( const int TrackIndex, spAnimation* Anim, const bool Loop = true ) {
		spSkeleton_setToSetupPose( Skeleton );
		spAnimationState_setAnimation( AnimState, TrackIndex, Anim, Loop );
	}
	
	// Clear the Animation Tracklist //
	inline void Clear() {
		spAnimationState_clearTracks( AnimState );
	}
	inline void Clear( const int TrackIndex ) {
		spAnimationState_clearTrack( AnimState, TrackIndex );
	}
	
	// Add a new Animation Track //
	inline void Add( const int TrackIndex, const char* Name, const bool Loop = true, const int Delay = 0 ) {
		Add( TrackIndex, spSkeletonData_findAnimation( Skeleton->data, Name ), Loop, Delay );
	}
	inline void Add( const int TrackIndex, spAnimation* Anim, const bool Loop = true, const int Delay = 0 ) {
		spAnimationState_addAnimation( AnimState, TrackIndex, Anim, Loop, Delay );
	}
	
	
	inline void SetFlips( const bool _x = false, const bool _y = false ) {
		Skeleton->flipX = _x;
		Skeleton->flipY = _y;		
	}

public:
	inline spAnimation* GetAnim( const int TrackIndex ) {
		spTrackEntry* Track = GetTrack(TrackIndex);
		if ( Track ) {
			return Track->animation;
		}
		return 0;
	}
	inline spTrackEntry* GetTrack( const int TrackIndex ) {
		return spAnimationState_getCurrent( AnimState, TrackIndex );
	}

public:	
	inline void Step() {
		float deltaTime = 1000.0f/60.0f;
		float timeScale = 1.0f/1000.0f;
		
		spSkeleton_update( Skeleton, deltaTime ); 		// Add deltaTime //
		spAnimationState_update( AnimState, deltaTime * timeScale ); // Step all active animations //
		spAnimationState_apply( AnimState, Skeleton );	// Apply and Mix Animations, trigger event callbacks //
		spSkeleton_updateWorldTransform( Skeleton ); 	// Build Matrix //
	}
	
	inline void FlushDraw( const Matrix4x4& Matrix, const GelTexturePool::UID& TexIndex, GelAlloc3UC& Vert ) const {
		if ( Vert.Size() ) {
			Gel::TexturePool[TexIndex].Bind();
			Gel::RenderTextureColorPacked( GEL_TRIANGLES, Matrix, GEL_RGB_WHITE, &(Vert.Get()->Pos), &(Vert.Get()->UV), &(Vert.Get()->Color), Vert.Size() );

			Vert.Clear();
		}
	}
	
	inline void Draw( const Matrix4x4& Matrix ) {
		spSkeleton* skeleton = Skeleton;
		
		GelAlloc3UC Vert( skeleton->slotCount * 6 );
		GelTexturePool::UID TexIndex = 0;
		int BlendState = 0;
		gelBlendingEnable();
		
		float worldVertices[8];
		for (int i = 0; i < skeleton->slotCount; ++i) {
			spSlot* slot = skeleton->drawOrder[i];
			spAttachment* attachment = slot->attachment;
			if (!attachment || attachment->type != ATTACHMENT_REGION) 
				continue;
			spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;
	
			if ( slot->data->additiveBlending ) {
				if ( BlendState != 1 )
					FlushDraw( Matrix, TexIndex, Vert );
				BlendState = 1;
				gelBlendingEnableAddative();
			}
			else {
				if ( BlendState != 0 )
					FlushDraw( Matrix, TexIndex, Vert );
				BlendState = 0;
				gelBlendingEnable();
			}
	
			spRegionAttachment_computeWorldVertices(regionAttachment, slot->skeleton->x, slot->skeleton->y, slot->bone, worldVertices);
	
			Uint8 r = skeleton->r * slot->r * 255;
			Uint8 g = skeleton->g * slot->g * 255;
			Uint8 b = skeleton->b * slot->b * 255;
			Uint8 a = skeleton->a * slot->a * 255;
			GelColor Color = GEL_RGBA(r,g,b,a);
			
			// TODO: Use general vertex type (pos,uv,color), and write color to the vertices. //
			GelTexturePool::UID OldTexIndex = TexIndex;
			TexIndex = (st)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;
			if ( TexIndex != OldTexIndex ) {
				FlushDraw( Matrix, OldTexIndex, Vert );
			}

			Vert.Next()->Pos = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
			Vert->UV = GelUV(regionAttachment->uvs[VERTEX_X1],regionAttachment->uvs[VERTEX_Y1]);
			Vert->Color = Color;
			Vert.Next()->Pos = Vector3D(worldVertices[VERTEX_X2],worldVertices[VERTEX_Y2],0);
			Vert->UV = GelUV(regionAttachment->uvs[VERTEX_X2],regionAttachment->uvs[VERTEX_Y2]);
			Vert->Color = Color;
			Vert.Next()->Pos = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
			Vert->UV = GelUV(regionAttachment->uvs[VERTEX_X3],regionAttachment->uvs[VERTEX_Y3]);
			Vert->Color = Color;
			
			Vert.Next()->Pos = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
			Vert->UV = GelUV(regionAttachment->uvs[VERTEX_X3],regionAttachment->uvs[VERTEX_Y3]);
			Vert->Color = Color;
			Vert.Next()->Pos = Vector3D(worldVertices[VERTEX_X4],worldVertices[VERTEX_Y4],0);
			Vert->UV = GelUV(regionAttachment->uvs[VERTEX_X4],regionAttachment->uvs[VERTEX_Y4]);
			Vert->Color = Color;
			Vert.Next()->Pos = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
			Vert->UV = GelUV(regionAttachment->uvs[VERTEX_X1],regionAttachment->uvs[VERTEX_Y1]);
			Vert->Color = Color;
		}
		
		// Render everything in the final batch //
		FlushDraw( Matrix, TexIndex, Vert );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKEL_GELSKELANIMATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
