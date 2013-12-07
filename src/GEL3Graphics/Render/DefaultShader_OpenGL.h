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
extern cUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
extern ShaderHandle FlatShader;
extern ShaderHandle FlatShader2D;
extern ShaderHandle FlatShader_Packed;
extern ShaderHandle FlatShader2D_Packed;
extern ShaderHandle ColorShader;
extern ShaderHandle ColorShader2D;
extern ShaderHandle TextureShader;
extern ShaderHandle TextureShader2D;
extern ShaderHandle TextureShader_Packed;
extern ShaderHandle TextureShader2D_Packed;
extern ShaderHandle ColorTextureShader;
extern ShaderHandle ColorTextureShader2D;
extern ShaderHandle ColorTextureShader_Packed;
extern ShaderHandle ColorTextureShader2D_Packed;
extern ShaderHandle TextureAlphaShader;
extern ShaderHandle TextureAlphaShader2D;
extern ShaderHandle TextureAlphaShader_Packed;
extern ShaderHandle TextureAlphaShader2D_Packed;
extern ShaderHandle ColorTextureAlphaShader;
extern ShaderHandle ColorTextureAlphaShader2D;
extern ShaderHandle ColorTextureAlphaShader_Packed;
extern ShaderHandle ColorTextureAlphaShader2D_Packed;
extern ShaderHandle NoiseShader;
extern ShaderHandle ColorNoiseShader;
extern ShaderHandle Noise1BitShader;
extern ShaderHandle ColorNoise1BitShader;
extern ShaderHandle NoiseShader_Packed;
extern ShaderHandle ColorNoiseShader_Packed;
extern ShaderHandle Noise1BitShader_Packed;
extern ShaderHandle ColorNoise1BitShader_Packed;
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
inline void RenderFlatIndexed( const int Mode, const Matrix4x4& Matrix, const GelColor Color, const void* Verts, const st32 VertCount, const void* Indexes, const st32 IndexCount ) {
	Default->Bind( FlatShader );
	Default->UniformMatrix4x4( 0, Matrix );
	Default->UniformColor( 1, Color ); // GlobalColor //
	Default->BindUniforms();
	Default->Attrib( 0, Verts );
	Default->DrawElements( Mode, VertCount, Indexes, IndexCount );
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
