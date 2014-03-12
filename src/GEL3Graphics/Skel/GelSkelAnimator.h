// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKEL_GELSKELANIMATOR_H__
#define __GEL_SKEL_GELSKELANIMATOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSkel.h"
#include "GelSkelPool.h"

#include "ConvexVsConvex.h"

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
	inline void Set( const int TrackIndex, const char* Name, const bool Loop = true, const float MixLength = 0.0f ) {
		Set( TrackIndex, spSkeletonData_findAnimation( Skeleton->data, Name ), Loop, MixLength );
	}
	inline void Set( const int TrackIndex, spAnimation* Anim, const bool Loop = true, const float MixLength = 0.0f ) {
		if ( GetAnim(TrackIndex) != Anim ) {
			Force( TrackIndex, Anim, Loop, MixLength );
		}
	}
	// Always set an animation (Clear, Add Track) //
	inline void Force( const int TrackIndex, const char* Name, const bool Loop = true, const float MixLength = 0.0f ) {
		Force( TrackIndex, spSkeletonData_findAnimation( Skeleton->data, Name ), Loop, MixLength );
	}
	inline void Force( const int TrackIndex, spAnimation* Anim, const bool Loop = true, const float MixLength = 0.0f ) {
		if ( MixLength > 0.0f ) {
			spAnimation* Old = GetAnim(TrackIndex);
			spAnimationState_setAnimation( AnimState, TrackIndex, Anim, Loop );
			spAnimationStateData_setMix( AnimState->data, Old, Anim, MixLength );
		}
		else {
			spSkeleton_setToSetupPose( Skeleton );
			spAnimationState_setAnimation( AnimState, TrackIndex, Anim, Loop );
		}
	}
	
	// Clear the Animation Tracklist //
	inline void Clear() {
		spAnimationState_clearTracks( AnimState );
	}
	inline void Clear( const int TrackIndex ) {
		spAnimationState_clearTrack( AnimState, TrackIndex );
	}
	
	// Add a new Animation Track //
	inline void Add( const int TrackIndex, const char* Name, const bool Loop = true, const float Delay = 0.0f ) {
		Add( TrackIndex, spSkeletonData_findAnimation( Skeleton->data, Name ), Loop, Delay );
	}
	inline void Add( const int TrackIndex, spAnimation* Anim, const bool Loop = true, const float Delay = 0.0f ) {
		spAnimationState_addAnimation( AnimState, TrackIndex, Anim, Loop, Delay );
	}
	
	
	inline void SetFlips( const bool _x = false, const bool _y = false ) {
		Skeleton->flipX = _x;
		Skeleton->flipY = _y;
	}

	inline void SetColor( const GelColor Color ) {
		float ColorMax = 1.0f / 255.0f;
		Skeleton->r = GEL_GET_R(Color) * ColorMax;
		Skeleton->g = GEL_GET_G(Color) * ColorMax;
		Skeleton->b = GEL_GET_B(Color) * ColorMax;
		Skeleton->a = GEL_GET_A(Color) * ColorMax;
	}
	
	inline void SetTrackMix( const int TrackIndex, const float Value = 1.0f ) {
		GetTrack(TrackIndex)->mix = Value;
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

	// Iterating Bonunding Boxes requires iterating over slots //
	inline int GetSlotCount() const {
		return Skeleton->slotCount;
	}
	// Retrieve Slot //
	inline spSlot* GetSlot( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetSlot(Index);
	}
	inline spSlot* _GetSlot( const st Index ) const {
		return Skeleton->drawOrder[Index];
	}
	// Slots contain attachments //
	inline spAttachment* GetAttachment( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetAttachment(Index);
	}
	inline spAttachment* _GetAttachment( const st Index ) const {
		return Skeleton->drawOrder[Index]->attachment;
	}
	// An attachment can be a region (art box) //
	inline spRegionAttachment* GetRegion( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetRegion(Index);
	}
	inline spRegionAttachment* _GetRegion( const st Index ) const {
		spAttachment* Attachment = _GetAttachment(Index);
		return GetRegion(Attachment);
	}
	inline spRegionAttachment* GetRegion( spAttachment* Attachment ) const {
		if ( !Attachment ) return 0;
		return _GetRegion(Attachment);
	}
	inline spRegionAttachment* _GetRegion( spAttachment* Attachment ) const {
		if ( Attachment->type != ATTACHMENT_REGION ) return 0;
		return (spRegionAttachment*)Attachment;
	}
	// Or an attachment can be a BoundingBox //
	inline spBoundingBoxAttachment* GetBB( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetBB(Index);
	}
	inline spBoundingBoxAttachment* _GetBB( const st Index ) const {
		spAttachment* Attachment = _GetAttachment(Index);
		return GetBB(Attachment);
	}
	inline spBoundingBoxAttachment* GetBB( spAttachment* Attachment ) const {
		if ( !Attachment ) return 0;
		return _GetBB(Attachment);
	}
	inline spBoundingBoxAttachment* _GetBB( spAttachment* Attachment ) const {
		if ( Attachment->type != ATTACHMENT_BOUNDING_BOX ) return 0;
		return (spBoundingBoxAttachment*)Attachment;
	}
	// Or go right to the name //
	inline const char* GetName( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetName(Index);
	}
	inline const char* _GetName( const st Index ) const {
		spAttachment* Attachment = _GetAttachment(Index);
		return GetName(Attachment);
	}
	inline const char* GetName( spAttachment* Attachment ) const {
		if ( !Attachment ) return 0;
		return _GetName(Attachment);
	}
	inline const char* _GetName( spAttachment* Attachment ) const {
		return Attachment->name;
	}
	// Or right to the Polygon data (UNTRANSFORMED) //
	inline float* GetBBVertices( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetBBVertices(Index);
	}
	inline float* _GetBBVertices( const st Index ) const {
		spBoundingBoxAttachment* Attachment = _GetBB(Index);
		return GetBBVertices(Attachment);
	}
	inline float* GetBBVertices( spBoundingBoxAttachment* Attachment ) const {
		if ( !Attachment ) return 0;
		return _GetBBVertices(Attachment);
	}
	inline float* _GetBBVertices( spBoundingBoxAttachment* Attachment ) const {
		return Attachment->vertices;
	}
	// Or Vertex Count //
	inline int GetBBVertexCount( const st Index ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _GetBBVertexCount(Index);
	}
	inline int _GetBBVertexCount( const st Index ) const {
		spBoundingBoxAttachment* Attachment = _GetBB(Index);
		return GetBBVertexCount(Attachment);
	}
	inline int GetBBVertexCount( spBoundingBoxAttachment* Attachment ) const {
		if ( !Attachment ) return 0;
		return _GetBBVertexCount(Attachment);
	}
	inline int _GetBBVertexCount( spBoundingBoxAttachment* Attachment ) const {
		return Attachment->verticesCount;
	}
	// Transform Polygon Data //
	inline float* TransformBBVertices( const st Index, float* Out ) const {
		if ( Index >= GetSlotCount() ) return 0;
		return _TransformBBVertices(Index, Out);
	}
	inline float* _TransformBBVertices( const st Index, float* Out ) const {
		spSlot* Slot = _GetSlot(Index);
		spAttachment* Attachment = Slot->attachment;
		if ( !Attachment ) return 0;
		spBoundingBoxAttachment* BBAttachment = _GetBB(Attachment);
		if ( !BBAttachment ) return 0;
		return _TransformBBVertices(Slot,BBAttachment,Out);
	}
	inline float* _TransformBBVertices( spSlot* Slot, spBoundingBoxAttachment* BBAttachment, float* Out ) const {
		spBoundingBoxAttachment_computeWorldVertices(BBAttachment, Slot->skeleton->x, Slot->skeleton->y, Slot->bone, Out);
		return Out;
	}
		
public:	
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
inline void Sense_GelSkelAnimator( const Vector2D& PosA, const GelSkelAnimator& SkelA, const Vector2D& PosB, const GelSkelAnimator& SkelB ) {
	for ( int IndexA = 0; IndexA < SkelA.GetSlotCount(); IndexA++ ) {
		spSlot* SlotA = SkelA._GetSlot(IndexA);
		//if ( !SlotA ) continue;
		spBoundingBoxAttachment* BBA = SkelA._GetBB(IndexA);
		if ( !BBA ) continue;
		for ( int IndexB = 0; IndexB < SkelB.GetSlotCount(); IndexB++ ) {
			spSlot* SlotB = SkelB._GetSlot(IndexB);
			//if ( !SlotB ) continue;
			spBoundingBoxAttachment* BBB = SkelB._GetBB(IndexB);
			if ( !BBB ) continue;

			// NOTE: Max Verts 8! //
			float bbVertA[16*2];
			float bbVertB[16*2];
			
			int bbVertASize = BBA->verticesCount;
			int bbVertBSize = BBB->verticesCount;
			
			for ( int idx = 0; idx < bbVertASize>>1; idx++ ) {
				bbVertA[(idx<<1)+0] += PosA.x.ToFloat();
				bbVertA[(idx<<1)+1] += PosA.y.ToFloat();
			}

			for ( int idx = 0; idx < bbVertBSize>>1; idx++ ) {
				bbVertB[(idx<<1)+0] += PosB.x.ToFloat();
				bbVertB[(idx<<1)+1] += PosB.y.ToFloat();
			}

			SkelA._TransformBBVertices(SlotA,BBA,bbVertA);
			SkelB._TransformBBVertices(SlotB,BBB,bbVertB);
			
			if ( ConvexVsConvex(bbVertA,bbVertASize, bbVertB,bbVertBSize ) ) {
				Log("FUCK");
			}
		}
	}

	// How we retieve Bounding Boxes //
	/*
	{
		float bbVertices[16*2];
		for (int i = 0; i < Skeleton->slotCount; ++i) {
			spSlot* slot = Skeleton->drawOrder[i];
			spAttachment* attachment = slot->attachment;
			if (!attachment || attachment->type != ATTACHMENT_BOUNDING_BOX) 
				continue;
			spBoundingBoxAttachment* bbAttachment = (spBoundingBoxAttachment*)attachment;
			
			spBoundingBoxAttachment_computeWorldVertices(bbAttachment, slot->skeleton->x, slot->skeleton->y, slot->bone, bbVertices);
			int Count = bbAttachment->verticesCount;
			
			_Log("%s: ",bbAttachment->super.name);
			for ( int idx = 0; idx < Count; idx++ ) {
				_Log("%f, ", bbVertices[idx]);
			}
			Log("");
		}
	}
	*/
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKEL_GELSKELANIMATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
