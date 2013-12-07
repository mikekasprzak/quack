// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL_2_FAMILY)
// - ------------------------------------------------------------------------------------------ - //
#include "DefaultShader.h"
#include "Embedded/GLSL/EmbeddedShaders.h"	// DefaultShader_json, etc //
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
cUberShader* Default;
// - ------------------------------------------------------------------------------------------ - //
ShaderHandle FlatShader;
ShaderHandle FlatShader2D;
ShaderHandle FlatShader_Packed;
ShaderHandle FlatShader2D_Packed;
ShaderHandle ColorShader;
ShaderHandle ColorShader2D;
ShaderHandle TextureShader;
ShaderHandle TextureShader2D;
ShaderHandle TextureShader_Packed;
ShaderHandle TextureShader2D_Packed;
ShaderHandle ColorTextureShader;
ShaderHandle ColorTextureShader2D;
ShaderHandle ColorTextureShader_Packed;
ShaderHandle ColorTextureShader2D_Packed;
ShaderHandle TextureAlphaShader;
ShaderHandle TextureAlphaShader2D;
ShaderHandle TextureAlphaShader_Packed;
ShaderHandle TextureAlphaShader2D_Packed;
ShaderHandle ColorTextureAlphaShader;
ShaderHandle ColorTextureAlphaShader2D;
ShaderHandle ColorTextureAlphaShader_Packed;
ShaderHandle ColorTextureAlphaShader2D_Packed;
ShaderHandle NoiseShader;
ShaderHandle ColorNoiseShader;
ShaderHandle Noise1BitShader;
ShaderHandle ColorNoise1BitShader;
ShaderHandle NoiseShader_Packed;
ShaderHandle ColorNoiseShader_Packed;
ShaderHandle Noise1BitShader_Packed;
ShaderHandle ColorNoise1BitShader_Packed;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
void gelShaderInit() {
#ifdef USES_DESKTOP
	// Use Files //	
	Gel::Default = new Gel::cUberShader( "src/GEL3Graphics/Render/Embedded/GLSL/DefaultShader.json" );
#endif // USES DESKTOP //

#ifdef USES_MOBILE
	// Use Embedded //
	Gel::Default = new Gel::cUberShader( DefaultShader_json, DefaultShader_json_Size, DefaultShader_glsl, DefaultShader_glsl_Size );
#endif // USES_MOBILE //

	// Find all the shaders //
	Gel::FlatShader = Gel::Default->Find( "Flat" );
	Gel::FlatShader2D = Gel::Default->Find( "Flat2D" );
	Gel::FlatShader_Packed = Gel::Default->Find( "Flat_Packed" );
	Gel::FlatShader2D_Packed = Gel::Default->Find( "Flat2D_Packed" );
	Gel::ColorShader = Gel::Default->Find( "Color" );
	Gel::ColorShader2D = Gel::Default->Find( "Color2D" );
	Gel::TextureShader = Gel::Default->Find( "Texture" );
	Gel::TextureShader2D = Gel::Default->Find( "Texture2D" );
	Gel::TextureShader_Packed = Gel::Default->Find( "Texture_Packed" );
	Gel::TextureShader2D_Packed = Gel::Default->Find( "Texture2D_Packed" );
	Gel::ColorTextureShader = Gel::Default->Find( "ColorTexture" );
	Gel::ColorTextureShader2D = Gel::Default->Find( "ColorTexture2D" );
	Gel::ColorTextureShader_Packed = Gel::Default->Find( "ColorTexture_Packed" );
	Gel::ColorTextureShader2D_Packed = Gel::Default->Find( "ColorTexture2D_Packed" );
	Gel::TextureAlphaShader = Gel::Default->Find( "TextureAlpha" );
	Gel::TextureAlphaShader2D = Gel::Default->Find( "TextureAlpha2D" );
	Gel::TextureAlphaShader_Packed = Gel::Default->Find( "TextureAlpha_Packed" );
	Gel::TextureAlphaShader2D_Packed = Gel::Default->Find( "TextureAlpha2D_Packed" );
	Gel::ColorTextureAlphaShader = Gel::Default->Find( "ColorTextureAlpha" );
	Gel::ColorTextureAlphaShader2D = Gel::Default->Find( "ColorTextureAlpha2D" );
	Gel::ColorTextureAlphaShader_Packed = Gel::Default->Find( "ColorTextureAlpha_Packed" );
	Gel::ColorTextureAlphaShader2D_Packed = Gel::Default->Find( "ColorTextureAlpha2D_Packed" );
	Gel::NoiseShader = Gel::Default->Find( "Noise" );
	Gel::ColorNoiseShader = Gel::Default->Find( "ColorNoise" );
	Gel::Noise1BitShader = Gel::Default->Find( "Noise1Bit" );
	Gel::ColorNoise1BitShader = Gel::Default->Find( "ColorNoise1Bit" );
	Gel::NoiseShader_Packed = Gel::Default->Find( "Noise_Packed" );
	Gel::ColorNoiseShader_Packed = Gel::Default->Find( "ColorNoise_Packed" );
	Gel::Noise1BitShader_Packed = Gel::Default->Find( "Noise1Bit_Packed" );
	Gel::ColorNoise1BitShader_Packed = Gel::Default->Find( "ColorNoise1Bit_Packed" );
	
	// Enable this here, since all shaders will always require Attrib 0 to be enabled //
	//glEnableVertexAttribArray( 0 );
	Gel::cUberShader::EnableAttrib( 0 );
}
// - ------------------------------------------------------------------------------------------ - //
void gelShaderExit() {
	delete Gel::Default;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // defined(USES_OPENGL_2_FAMILY) //
// - ------------------------------------------------------------------------------------------ - //
