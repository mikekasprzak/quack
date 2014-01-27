// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_DEFAULTSHADER_OPENGL_H__
#define __GEL_RENDER_DEFAULTSHADER_OPENGL_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL_2_FAMILY
// - ------------------------------------------------------------------------------------------ - //
#include "UberShader.h"
// - ------------------------------------------------------------------------------------------ - //
void gelShaderInit();
void gelShaderExit();
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
extern GelUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
extern GelShaderHandle FlatShader;
extern GelShaderHandle FlatShader2D;
extern GelShaderHandle FlatShader_Packed;
extern GelShaderHandle FlatShader2D_Packed;
extern GelShaderHandle ColorShader;
extern GelShaderHandle ColorShader2D;
extern GelShaderHandle ColorShader_Packed;
extern GelShaderHandle ColorShader2D_Packed;
extern GelShaderHandle TextureShader;
extern GelShaderHandle TextureShader2D;
extern GelShaderHandle TextureShader_Packed;
extern GelShaderHandle TextureShader2D_Packed;
extern GelShaderHandle ColorTextureShader;
extern GelShaderHandle ColorTextureShader2D;
extern GelShaderHandle ColorTextureShader_Packed;
extern GelShaderHandle ColorTextureShader2D_Packed;
extern GelShaderHandle TextureAlphaShader;
extern GelShaderHandle TextureAlphaShader2D;
extern GelShaderHandle TextureAlphaShader_Packed;
extern GelShaderHandle TextureAlphaShader2D_Packed;
extern GelShaderHandle ColorTextureAlphaShader;
extern GelShaderHandle ColorTextureAlphaShader2D;
extern GelShaderHandle ColorTextureAlphaShader_Packed;
extern GelShaderHandle ColorTextureAlphaShader2D_Packed;
extern GelShaderHandle NoiseShader;
extern GelShaderHandle ColorNoiseShader;
extern GelShaderHandle Noise1BitShader;
extern GelShaderHandle ColorNoise1BitShader;
extern GelShaderHandle NoiseShader_Packed;
extern GelShaderHandle ColorNoiseShader_Packed;
extern GelShaderHandle Noise1BitShader_Packed;
extern GelShaderHandle ColorNoise1BitShader_Packed;
// - ------------------------------------------------------------------------------------------ - //
inline void RenderFlat( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const st32 VertCount ) {
	Default->Bind( FlatShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderFlat2D( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const st32 VertCount ) {
	Default->Bind( FlatShader2D );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderFlatIndexed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const st32 VertCount, const void* Indexes, const st32 IndexCount ) {
	Default->Bind( FlatShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->DrawElements( Mode, VertCount, Indexes, IndexCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderColor2D_Packed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* Colors, const st32 VertCount ) {
	Default->Bind( ColorShader2D_Packed );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 2, Colors );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderTexture( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount ) {
	Default->Bind( TextureShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->Uniform1i( 2, 0 ); // "TexImage0" //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderTextureIndexed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount, const void* Indexes, const st32 IndexCount ) {
	Default->Bind( TextureShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->Uniform1i( 2, 0 ); // "TexImage0" //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawElements( Mode, VertCount, Indexes, IndexCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderTexturePacked( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount ) {
	Default->Bind( TextureShader_Packed );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->Uniform1i( 2, 0 ); // "TexImage0" //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderTexturePackedIndexed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount, const void* Indexes, const st32 IndexCount ) {
	Default->Bind( TextureShader_Packed );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->Uniform1i( 2, 0 ); // "TexImage0" //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawElements( Mode, VertCount, Indexes, IndexCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderTextureColorPacked( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const void* Colors, const st32 VertCount ) {
	Default->Bind( ColorTextureShader_Packed );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->Uniform1i( 2, 0 ); // "TexImage0" //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->Attrib( 2, Colors );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderNoise( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount ) {
	Default->Bind( NoiseShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderNoiseIndexed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount, const void* Indexes, const st32 IndexCount ) {
	Default->Bind( NoiseShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawElements( Mode, VertCount, Indexes, IndexCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderNoisePacked( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount ) {
	Default->Bind( NoiseShader_Packed );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawArrays( Mode, VertCount );
}
// - ------------------------------------------------------------------------------------------ - //
inline void RenderNoisePackedIndexed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const void* UVs, const st32 VertCount, const void* Indexes, const st32 IndexCount ) {
	Default->Bind( NoiseShader_Packed );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->Attrib( 1, UVs );
	Default->DrawElements( Mode, VertCount, Indexes, IndexCount );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_2_FAMILY //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_DEFAULTSHADER_OPENGL_H__ //
// - ------------------------------------------------------------------------------------------ - //
