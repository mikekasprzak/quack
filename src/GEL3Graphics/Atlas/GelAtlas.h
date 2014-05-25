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

#include <Graphics/GelUV.h>
// - ------------------------------------------------------------------------------------------ - //
#include <spine/spine.h>
// - ------------------------------------------------------------------------------------------ - //
class GelAtlas {
	friend class GelSkel;
protected:
	st32 MyID;	// My ID (an Internal Copy) //

	GelAssetPool::UID AssetUID;	

	spAtlas* Atlas;
	
	// Regions Array //
	st32 RegionCount;
	spAtlasRegion** Region;
	
public:
	inline GelAtlas( const st32 _MyID ) :
		MyID( _MyID ),
		AssetUID( 0 ),
		Atlas( 0 ),
		RegionCount( 0 ),
		Region( 0 )
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
			
			
			if ( Atlas == 0 ) {
				Log( "!!! ERROR! ATLAS \"%s\" NOT LOADED! (Bad File?)",  Gel::String::GetDirectorySlash(InFile).c_str() );
				return;
			}
			
			//spAtlasRegion* MyRegion = spAtlas_findRegion(Atlas,"regionName");
			// spAtlas contains linked lists. A list of Pages, and a list of Regions //
			
			// I've stored the Texture UID in MyRegion->page->rendererObject

			// It may be reasonable to always search for a region initially.
			// Need a way of getting a Region Handle. GelAtlasRegion ?
			
			// If an Atlas changes, any pointers (spAtlasRegion's) break. 
			
			// *** //
			
			// Iterate over all regions, to count them //
			RegionCount = 0;
			spAtlasRegion* CurrentRegion = Atlas->regions;
			while (CurrentRegion) {
				RegionCount++;
				CurrentRegion = CurrentRegion->next;
			};
			
			// Create an array of Regions //
			Region = new spAtlasRegion*[RegionCount];
			
			// Iterate over all regions, to copy pointers to them //
			CurrentRegion = Atlas->regions;
			for ( st idx = 0; CurrentRegion; idx++ ) {
				Region[idx] = CurrentRegion;
				CurrentRegion = CurrentRegion->next;
			};
		}
	}
	
	inline void Unload() {
		if ( Region ) {
			delete [] Region;
			Region = 0;
			RegionCount = 0;
		}
		
		// NOTE: Disposal is currently broken (Dec 20th) //
//		if ( Atlas ) {
//			spAtlas_dispose(Atlas);
//			Atlas = 0;
//		}
	}
	
	inline void Draw( const Matrix4x4& Matrix, const int Index, GelColor Color = GEL_RGB_DEFAULT, int ClipX = 0, int ClipY = 0, int ClipW = 0, int ClipH = 0 ) {		
		spAtlasRegion* Reg = Region[Index];//Atlas->regions->next; // ...

		const st32 VertCount = 6;
		Vector3D Verts[ VertCount ];
		Verts[0] = Vector3D(0+ClipX, Reg->height-ClipH, 0);
		Verts[1] = Vector3D(Reg->width-ClipW, Reg->height-ClipH, 0);
		Verts[2] = Vector3D(Reg->width-ClipW, 0+ClipY, 0);

		Verts[3] = Vector3D(Reg->width-ClipW, 0+ClipY, 0);
		Verts[4] = Vector3D(0+ClipX, 0+ClipY, 0);
		Verts[5] = Vector3D(0+ClipX, Reg->height-ClipH, 0);
				
		for ( st32 idx = 0; idx < VertCount; idx++ ) {
			// Add Offsets and subtract half the original width (i.e. center) //
			Verts[idx] += Vector3D(Reg->offsetX-((Reg->originalWidth-ClipW+ClipX)>>1),Reg->offsetY-((Reg->originalHeight-ClipH+ClipY)>>1));
//			Verts[idx] += Vector3D(Reg->offsetX,Reg->offsetY);
		}

		GelTexture& Tex = Gel::TexturePool[(st)Reg->page->rendererObject];
			
		float CX = ClipX / (float)Reg->page->width;
		float CY = ClipY / (float)Reg->page->height;
		float CW = ClipW / (float)Reg->page->width;
		float CH = ClipH / (float)Reg->page->height;

		UVSet<Gel::UVType> UVs[ VertCount ];
		UVs[0] = UVSet<Gel::UVType>(Reg->u+CX,Reg->v+CY);
		UVs[1] = UVSet<Gel::UVType>(Reg->u2-CW,Reg->v+CY);
		UVs[2] = UVSet<Gel::UVType>(Reg->u2-CW,Reg->v2-CH);

		UVs[3] = UVSet<Gel::UVType>(Reg->u2-CW,Reg->v2-CH);
		UVs[4] = UVSet<Gel::UVType>(Reg->u+CX,Reg->v2-CH);
		UVs[5] = UVSet<Gel::UVType>(Reg->u+CX,Reg->v+CY);

//		vertexArray->append(vertices[0]);
//		vertexArray->append(vertices[1]);
//		vertexArray->append(vertices[2]);
//		vertexArray->append(vertices[3]);

		// TODO: Do batching cleverness here. If same texture, continue batching. If different, render the current batch.
		//       Advance poniter, so further render ops don't re-draw prior data.
		Tex.Bind();
		Gel::RenderTexture( GEL_TRIANGLES, Matrix, Color, Verts, UVs, VertCount );
	}

	inline void FakeDraw( Vector2D* Verts, GelUV* UVs, const int Index ) {
		spAtlasRegion* Reg = Region[Index];//Atlas->regions->next; // ...

		const st32 VertCount = 4;
		//Vector2D Verts[ VertCount ];
		Verts[0] = Vector2D(0,Reg->height);
		Verts[1] = Vector2D(Reg->width,Reg->height);
		Verts[2] = Vector2D(Reg->width,0);
		Verts[3] = Vector2D(0,0);
		
		for ( st32 idx = 0; idx < VertCount; idx++ ) {
			// Add Offsets and subtract half the original width (i.e. center) //
			Verts[idx] += Vector2D(Reg->offsetX-(Reg->originalWidth>>1),Reg->offsetY-(Reg->originalHeight>>1));
		}

//		GelTexture& Tex = Gel::TexturePool[(st)Reg->page->rendererObject];

//		GelUV UVs[ VertCount ];
		UVs[0] = GelUV(Reg->u,Reg->v);
		UVs[1] = GelUV(Reg->u2,Reg->v);
		UVs[2] = GelUV(Reg->u2,Reg->v2);
		UVs[3] = GelUV(Reg->u,Reg->v2);

//		vertexArray->append(vertices[0]);
//		vertexArray->append(vertices[1]);
//		vertexArray->append(vertices[2]);
//		vertexArray->append(vertices[3]);

		// TODO: Do batching cleverness here. If same texture, continue batching. If different, render the current batch.
		//       Advance poniter, so further render ops don't re-draw prior data.
//		Tex.Bind();
//		Gel::RenderTexture( GEL_TRIANGLES, Matrix, Color, Verts, UVs, VertCount );
	}
		
	inline GelTexture& GetTex() {
		spAtlasRegion* Reg = Region[0];
		return Gel::TexturePool[(st)Reg->page->rendererObject];
	}
	
	inline st32 Size() const {
		return RegionCount;
	}
	
	inline int Find( const char* Name ) const {
		for ( st idx = 0; idx < Size(); idx++ ) {
			if ( strcmp(Name,Region[idx]->name) == 0 ) {
				//Log( "%s", Region[idx]->name );
				return idx;
			}
		}
		return -1;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ATLAS_GELATLAS_H__ //
// - ------------------------------------------------------------------------------------------ - //
