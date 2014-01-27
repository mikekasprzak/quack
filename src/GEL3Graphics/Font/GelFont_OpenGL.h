// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELFONT_OPENGL_H__
#define __GEL_RENDER_GELFONT_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL_2_FAMILY
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelFont_BMFont.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/Asset.h>
#include <Texture/Texture.h>
#include <Render/Render.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Vert/Vert.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <stdio.h>
#include <stdarg.h>

#include <Lib/StdString/StdString.h>
// - ------------------------------------------------------------------------------------------ - //
extern void GelFontPool_Subscriber( const st UserData );
// - ------------------------------------------------------------------------------------------ - //
class GelFont {
	friend void GelFontPool_Subscriber( const st UserData );
public:
	st32 MyID;	// My FontID (an Internal Copy) //
	GelAssetPool::UID AssetID;
	BMFont* Font;
	std::vector< GelTexturePool::UID > TexturePage;

	enum {
		GF_SMOOTH = 			0x100,
		GF_FLIP = 				0x200,
		GF_PREMULTIPLYALPHA = 	0x400,
	};
	
	int Flags;
	
public:
	inline GelFont( const st32 _MyID ) :
		MyID( _MyID ),
		AssetID( 0 ),
		Font( 0 ),
		Flags( 0 )
	{	
	}


public:
	inline void Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		const char* File = Gel::Search( InFile );
		_Load( File, Smooth, PreMultiplyAlpha );
	}
	
	inline void _Load( const char* InFile, const bool Smooth = true, const bool PreMultiplyAlpha = true ) {
		AssetID = Gel::AssetPool.Load( InFile );
		
		if ( AssetID ) {
			Flags = Smooth ? GF_SMOOTH : 0;
			// HACK: Don't Flip. Need to sort out the flip order in my brain //
			Flags |= 0; //Flip ? GY_FLIP : 0;
			Flags |= PreMultiplyAlpha ? GF_PREMULTIPLYALPHA : 0;

			GelAsset& MyAsset = Gel::AssetPool[AssetID];
			MyAsset.SubscribeToChanges( GelFontPool_Subscriber, MyID );
			
			if ( LoadBody( *this, MyAsset ) ) {
				// It worked... Do something... Maybe //
			}
		}
	}

	inline void Unload() {
		// TODO: Delete Textures ?
//		for ( size_t idx = 0; idx < Font->PageName->Size; idx++ ) {
//			delete_GelTextureHandle( TexturePage[idx] );
//		}
		TexturePage.clear();		
				
		if ( Font ) {
			delete_BMFont( Font );
			Font = 0;
		}
	}
	
	static bool LoadBody( GelFont& MyFont, GelAsset& MyAsset ) {
		MyFont.Font = new_read_BMFont( MyAsset.GetDataBlock() );
		if ( MyFont.Font ) {	
			for ( size_t idx = 0; idx < MyFont.Font->PageName->Size; idx++ ) {
				const char* TextureFile = Gel::Search( MyFont.Font->PageName->Data[idx] );
	
				if ( TextureFile ) {
					MyFont.TexturePage.push_back( Gel::TexturePool.Load( 
						TextureFile, 
						MyFont.Flags & GF_SMOOTH, 
						MyFont.Flags & GF_FLIP, 
						MyFont.Flags & GF_PREMULTIPLYALPHA
						));
				}
			}
		
			return true;
		}
		
		return false;		
	}
	
public:
		
	void DrawText( const Matrix4x4& Mat, const char* Text, const size_t Length, Vector3D Pos, Real Scalar = Real::One, const GelColor Color = GEL_RGB_WHITE, const GelAlign Align = GEL_ALIGN_DEFAULT ) {
		size_t CharsDrawn = 0;
		
		int ScaleW = common_BMFont( Font )->ScaleW;
		int ScaleH = common_BMFont( Font )->ScaleH;
		// Reciprocals //
		float ScaleW_R_F = 1.0f / (float)ScaleW; 
		float ScaleH_R_F = 1.0f / (float)ScaleH;

		Scalar *= (float)size_BMFont( Font );

		int Width = width_BMFont( Font, Text, Length );
		int Height = height_BMFont( Font, Text, Length );
		int BaseLine = baseline_BMFont( Font );
		BMFont_Chars** Glyph = glyph_BMFont( Font );
				
		// Alignment //
		if ( (Align & GEL_ALIGN_FONT_HBITS) == GEL_ALIGN_CENTER ) {
			Pos.x -= Real((Width>>1) * Scalar.ToFloat() * ScaleW_R_F);
		}
		else if ( (Align & GEL_ALIGN_FONT_HBITS) == GEL_ALIGN_RIGHT ) {
			Pos.x -= Real(Width * Scalar.ToFloat() * ScaleW_R_F);
		}
		
		if ( (Align & GEL_ALIGN_FONT_VBITS) == GEL_ALIGN_MIDDLE ) {
			Pos.y -= Real((Height>>1) * Scalar.ToFloat() * ScaleH_R_F);
		}
		else if ( (Align & GEL_ALIGN_FONT_VBITS) == GEL_ALIGN_TOP ) {
			Pos.y -= Real(Height * Scalar.ToFloat() * ScaleH_R_F);
		}
		else if ( (Align & GEL_ALIGN_FONT_VBITS) == GEL_ALIGN_BASELINE ) {
			Pos.y -= Real(BaseLine * Scalar.ToFloat() * ScaleH_R_F);
		}
		
		GelAlloc3U Vert( Length*6 );

		// Assume Matrix and texture mode are set correctly outside this function //
		for ( size_t Tex = 0; Tex < TexturePage.size(); Tex++ ) {
			Vert.Clear();
			
			Vector3D CurPos = Pos;
			
			// Draw Text //
			for ( size_t idx = 0; idx < Length; idx++ ) {
				// NOTE: ASCII+EXT ONLY //
				int Ch = Text[idx] & 0xff;
				
				// If I'm on the correct texture page, draw the glyph //
				if ( (unsigned)Glyph[Ch]->Page == Tex ) {
					// NOTE: I now subtract the positions from the height, since we are creating coords that start from bottom left //
					Vector2D V1( Glyph[Ch]->OffsetX * ScaleW_R_F, (Height - Glyph[Ch]->OffsetY) * ScaleH_R_F );
					Vector2D V2( (Glyph[Ch]->OffsetX + Glyph[Ch]->Width) * ScaleW_R_F, (Height - (Glyph[Ch]->OffsetY + Glyph[Ch]->Height)) * ScaleH_R_F );
					V1 *= Scalar;
					V2 *= Scalar;

					// NOTE: FORMER HACK: I (used to) CHANGED THE Y's AROUND! I DUNNO WHY THEY WERE UPSIDE DOWN! //
					// NOTE: Also, these used to be "int"s, back when UVType was a short. 
					float UV1_x = Glyph[Ch]->x * UV_ONE / ScaleW;
					float UV1_y = Glyph[Ch]->y * UV_ONE / ScaleH;
					float UV2_x = (Glyph[Ch]->x + Glyph[Ch]->Width) * UV_ONE / ScaleW;
					float UV2_y = (Glyph[Ch]->y + Glyph[Ch]->Height) * UV_ONE / ScaleH;
					
					Vert.Next()->Pos = Vector3D( V1.x, V1.y, 0) + CurPos;
					Vert->UV = GelUV( UV1_x, UV1_y );
					Vert.Next()->Pos = Vector3D( V2.x, V1.y, 0) + CurPos;
					Vert->UV = GelUV( UV2_x, UV1_y );
					Vert.Next()->Pos = Vector3D( V2.x, V2.y, 0) + CurPos;
					Vert->UV = GelUV( UV2_x, UV2_y );
					Vert.Next()->Pos = Vector3D( V2.x, V2.y, 0) + CurPos;
					Vert->UV = GelUV( UV2_x, UV2_y );
					Vert.Next()->Pos = Vector3D( V1.x, V2.y, 0) + CurPos;
					Vert->UV = GelUV( UV1_x, UV2_y );
					Vert.Next()->Pos = Vector3D( V1.x, V1.y, 0) + CurPos;
					Vert->UV = GelUV( UV1_x, UV1_y );

					CharsDrawn++;
				}
				
				CurPos.x += Glyph[Ch]->AdvanceX * Scalar.ToFloat() * ScaleW_R_F;
			}
			
			Gel::Default->Bind( Gel::TextureAlphaShader_Packed );
			Gel::Default->UniformMatrix4x4( 0, Mat );
			Gel::Default->UniformColor( 1, Color );
			Gel::Default->Uniform1i( 2, 0 ); // "TexImage0" //
			Gel::Default->BindUniforms();
			//Bind( TexturePage[Tex], 0 );
			Gel::TexturePool[TexturePage[Tex]].Bind( 0 );
			Gel::Default->Attrib( 0, &(Vert.Get()->Pos) );
			Gel::Default->Attrib( 1, &(Vert.Get()->UV) );
			Gel::Default->DrawArrays( GL_TRIANGLES, Vert.Size() );
			
			if ( Length == CharsDrawn )
				break;
		}
	}
	
	inline void DrawText( const Matrix4x4& Mat, const char* Text, const Vector3D& Pos, const Real Scalar = Real::One, const GelColor Color = GEL_RGB_WHITE, const GelAlign Align = GEL_ALIGN_DEFAULT ) {
		DrawText( Mat, Text, length_String( Text ), Pos, Scalar, Color, Align );
	}
	inline void DrawText( const Matrix4x4& Mat, const char* Text, const Vector2D& Pos, const Real Scalar = Real::One, const GelColor Color = GEL_RGB_WHITE, const GelAlign Align = GEL_ALIGN_DEFAULT ) {
		DrawText( Mat, Text, Pos.ToVector3D(), Scalar, Color, Align );
	}
	
	// NOTE: Not recommended due to weird syntax.
	inline void printf( const Matrix4x4& Mat, const Vector3D& Pos, const Real Scalar, const GelColor Color, const GelAlign Align, const char* Text, ... ) {
		char StrBuff[4096];
		
		{
			va_list vl;
			va_start( vl, Text );
	
			safe_vsprintf( StrBuff, sizeof(StrBuff), Text, vl );
	
			va_end( vl );
		}

		DrawText( Mat, StrBuff, Pos, Scalar, Color, Align );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_2_FAMILY //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELFONT_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
