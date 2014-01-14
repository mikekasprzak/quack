// - ------------------------------------------------------------------------------------------ - //
// GelAtlas is based on Spine's Texture Atlases (libGDX) //
//
// https://github.com/libgdx/libgdx/wiki/Texture-packer (requires a Java program, bleh)
// http://code.google.com/p/libgdx-texturepacker-gui/ (pretty lousy)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ATLAS_GELATLAS_H__
#define __GEL_ATLAS_GELATLAS_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
#include <spine/spine.h>
// - ------------------------------------------------------------------------------------------ - //
class GelAtlas {
	friend class GelSkel;
protected:
	st32 MyID;	// My ID (an Internal Copy) //

	GelAssetPool::UID AssetUID;	

	spAtlas* Atlas;	
	
public:
	inline GelAtlas( const st32 _MyID ) :
		MyID( _MyID ),
		AssetUID( 0 ),
		Atlas( 0 )
	{	
	}
	
public:
	inline void Load( const char* InFile ) {
		const char* File = Gel::Search( InFile );
		_Load( File );
	}

	inline void _Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		Unload();
		
		AssetUID = Gel::AssetPool.Load( InFile );

		if ( AssetUID ) {
			GelAsset& Asset = Gel::AssetPool[AssetUID];

			Log("+ spAtlas_readAtlas");
			Atlas = spAtlas_readAtlas( Asset.Get(), Asset.GetSize(), Gel::String::GetDirectorySlash(InFile).c_str() );
			Log("- spAtlas_readAtlas (%x)",Atlas);
			
			//spAtlasRegion* MyRegion = spAtlas_findRegion(Atlas,"regionName");
			// spAtlas contains linked lists. A list of Pages, and a list of Regions //
			
			// I've stored the Texture UID in MyRegion->page->rendererObject

			// It may be reasonable to always search for a region initially.
			// Need a way of getting a Region Handle. GelAtlasRegion ?
			
			// If an Atlas changes, any pointers (spAtlasRegion's) break. 
		}
	}
	
	inline void Unload() {
		// NOTE: Disposal is currently broken (Dec 20th) //
//		if ( Atlas ) {
//			spAtlas_dispose(Atlas);
//			Atlas = 0;
//		}
	}
	
	inline void Draw( const Matrix4x4& Matrix, int Index ) {
		GelColor Color = GEL_RGB(255,255,255);
		
		// TODO: Find region //
		spAtlasRegion* Region = Atlas->regions;

		const st32 VertCount = 6;
		Vector3D Verts[ VertCount ];
		Verts[0] = Vector3D(-32,+32,0);
		Verts[1] = Vector3D(+32,+32,0);
		Verts[2] = Vector3D(+32,-32,0);

		Verts[3] = Vector3D(+32,-32,0);
		Verts[4] = Vector3D(-32,-32,0);
		Verts[5] = Vector3D(-32,+32,0);
//		Verts[0] = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
//		Verts[1] = Vector3D(worldVertices[VERTEX_X2],worldVertices[VERTEX_Y2],0);
//		Verts[2] = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
//		
//		Verts[3] = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
//		Verts[4] = Vector3D(worldVertices[VERTEX_X4],worldVertices[VERTEX_Y4],0);
//		Verts[5] = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);

		GelTexture& Tex = Gel::TexturePool[(st)Region->page->rendererObject];

		UVSet<Gel::UVType> UVs[ VertCount ];
		UVs[0] = UVSet<Gel::UVType>(0,0);
		UVs[1] = UVSet<Gel::UVType>(1,0);
		UVs[2] = UVSet<Gel::UVType>(1,1);

		UVs[3] = UVSet<Gel::UVType>(1,1);
		UVs[4] = UVSet<Gel::UVType>(0,1);
		UVs[5] = UVSet<Gel::UVType>(0,0);
//		UVs[0] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X1],regionAttachment->uvs[VERTEX_Y1]);
//		UVs[1] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X2],regionAttachment->uvs[VERTEX_Y2]);
//		UVs[2] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X3],regionAttachment->uvs[VERTEX_Y3]);
//
//		UVs[3] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X3],regionAttachment->uvs[VERTEX_Y3]);
//		UVs[4] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X4],regionAttachment->uvs[VERTEX_Y4]);
//		UVs[5] = UVSet<Gel::UVType>(regionAttachment->uvs[VERTEX_X1],regionAttachment->uvs[VERTEX_Y1]);

//		vertexArray->append(vertices[0]);
//		vertexArray->append(vertices[1]);
//		vertexArray->append(vertices[2]);
//		vertexArray->append(vertices[3]);

		// TODO: Do batching cleverness here. If same texture, continue batching. If different, render the current batch.
		//       Advance poniter, so further render ops don't re-draw prior data.
		Tex.Bind();
		Gel::RenderTexture( GEL_TRIANGLES, Matrix, Color, Verts, UVs, VertCount );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ATLAS_GELATLAS_H__ //
// - ------------------------------------------------------------------------------------------ - //
