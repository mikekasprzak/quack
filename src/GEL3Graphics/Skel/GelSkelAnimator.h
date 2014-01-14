// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SKEL_GELSKELANIMATOR_H__
#define __GEL_SKEL_GELSKELANIMATOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSkel.h"
#include "GelSkelPool.h"

#include <Render/Render.h>
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //
class GelSkelAnimator {
protected:
	GelSkelPool::UID		AssetUID;
	spSkeleton*				Skeleton;
	spAnimationState*		AnimState;
public:
	inline GelSkelAnimator() :
		AssetUID( 0 ),
		Skeleton( 0 ),
		AnimState( 0 )
	{
	}
	
	inline GelSkelAnimator( const GelSkelPool::UID _Asset ) :
		AssetUID( _Asset ),
		Skeleton( spSkeleton_create( Gel::SkelPool[AssetUID].GetSkeletonData() ) ),
		AnimState( spAnimationState_create(0) ) // stateData //
	{
	}
	
	inline void _Constructor() {
		AssetUID = 0;
		Skeleton = 0;
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

		if ( Skeleton ) {
			spSkeleton_dispose( Skeleton );
			Skeleton = 0;
		}
	}
		
	inline void Load( const GelSkelPool::UID _Asset ) {
		Unload();
		
		AssetUID = _Asset,
		Skeleton = spSkeleton_create( Gel::SkelPool[AssetUID].GetSkeletonData() );
		AnimState = spAnimationState_create(0); // To do animation mixing, apparently you pass an AnimationStateData here //
	}

public:
	// What Animation to set, by name //
	inline void Set( const char* Name ) {
		spSkeleton_setToSetupPose( Skeleton );
		const bool Loop = true;
		spAnimationState_setAnimation( AnimState, 0, spSkeletonData_findAnimation( Skeleton->data, Name), Loop );
	}
	
	inline void SetFlips( const bool _x = false, const bool _y = false ) {
		Skeleton->flipX = _x;
		Skeleton->flipY = _y;		
	}
	
	inline void Step() {
		float deltaTime = 1000.0f/60.0f;
		float timeScale = 0.001f;
		
		spSkeleton_update( Skeleton, deltaTime ); // Add deltaTime //
		spAnimationState_update( AnimState, deltaTime * timeScale ); // Step all active animations //
		spAnimationState_apply( AnimState, Skeleton ); // Apply and Mix Animations, trigger event callbacks //
		spSkeleton_updateWorldTransform( Skeleton ); // Build Matrix //
	}
	
	inline void Draw( const Matrix4x4& Matrix ) {
		spSkeleton* skeleton = Skeleton;
		
		float worldVertices[8];
		for (int i = 0; i < skeleton->slotCount; ++i) {
			spSlot* slot = skeleton->drawOrder[i];
			spAttachment* attachment = slot->attachment;
			if (!attachment || attachment->type != ATTACHMENT_REGION) 
				continue;
			spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;
	
			if ( slot->data->additiveBlending ) {
				gelBlendingEnableAddative();
			}
			else {
				gelBlendingEnable();
			}
	
			spRegionAttachment_computeWorldVertices(regionAttachment, slot->skeleton->x, slot->skeleton->y, slot->bone, worldVertices);
	
			Uint8 r = skeleton->r * slot->r * 255;
			Uint8 g = skeleton->g * slot->g * 255;
			Uint8 b = skeleton->b * slot->b * 255;
			Uint8 a = skeleton->a * slot->a * 255;
			GelColor Color = GEL_RGBA(r,g,b,a);
			
			// TODO: Use general vertex type (pos,uv,color), and write color to the vertices. //
	
	//		sf::Vertex vertices[4];
	//		vertices[0].color.r = r;
	//		vertices[0].color.g = g;
	//		vertices[0].color.b = b;
	//		vertices[0].color.a = a;
	//		vertices[1].color.r = r;
	//		vertices[1].color.g = g;
	//		vertices[1].color.b = b;
	//		vertices[1].color.a = a;
	//		vertices[2].color.r = r;
	//		vertices[2].color.g = g;
	//		vertices[2].color.b = b;
	//		vertices[2].color.a = a;
	//		vertices[3].color.r = r;
	//		vertices[3].color.g = g;
	//		vertices[3].color.b = b;
	//		vertices[3].color.a = a;
	
	
			const st32 VertCount = 6;
			Vector3D Verts[ VertCount ];
			Verts[0] = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
			Verts[1] = Vector3D(worldVertices[VERTEX_X2],worldVertices[VERTEX_Y2],0);
			Verts[2] = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
			
			Verts[3] = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
			Verts[4] = Vector3D(worldVertices[VERTEX_X4],worldVertices[VERTEX_Y4],0);
			Verts[5] = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
			
			// DO THIS WITH MATRIX //
//			for ( st32 idx = 0; idx < VertCount; idx++ ) {
//				Verts[idx] += Pos;
//			}
	
			GelTexture& Tex = Gel::TexturePool[(st)((spAtlasRegion*)regionAttachment->rendererObject)->page->rendererObject];
	
			UVSet<Gel::UVType> UVs[ VertCount ];
			UVs[0] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X1],regionAttachment->uvs[VERTEX_Y1]);
			UVs[1] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X2],regionAttachment->uvs[VERTEX_Y2]);
			UVs[2] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X3],regionAttachment->uvs[VERTEX_Y3]);
	
			UVs[3] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X3],regionAttachment->uvs[VERTEX_Y3]);
			UVs[4] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X4],regionAttachment->uvs[VERTEX_Y4]);
			UVs[5] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X1],regionAttachment->uvs[VERTEX_Y1]);
	
	//		vertexArray->append(vertices[0]);
	//		vertexArray->append(vertices[1]);
	//		vertexArray->append(vertices[2]);
	//		vertexArray->append(vertices[3]);
	
			// TODO: Do batching cleverness here. If same texture, continue batching. If different, render the current batch.
			//       Advance poniter, so further render ops don't re-draw prior data.
			Tex.Bind();
			Gel::RenderTexture( GEL_TRIANGLES, Matrix, Color, Verts, UVs, VertCount );
	//		Gel::RenderFlat( GEL_TRIANGLES, Matrix, Color, Verts, VertCount );
	
		}
		// Render everything in the final batch //
	
	//	target.draw(*vertexArray, states);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SKEL_GELSKELANIMATOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
