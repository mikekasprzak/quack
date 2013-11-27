// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_GELTEXTURE_H__
#define __GEL_TEXTURE_GELTEXTURE_H__
// - ------------------------------------------------------------------------------------------ - //
// A Smart System built on top of Texture that is indiffent of texture format, and caches the
//   data so multiple requests for the same data do not waste VRAM.

// TODO: Make it so the new TexturePool can actually be instanced. Smaller pools of textures. //
// MAYBE: No top level Texture Pool. Part of Texture instead.
// NOPE: GelTextureHandle's rely on an internal active Texture Unit and Handle. Not really viable.
// - ------------------------------------------------------------------------------------------ - //
class GelTexturePool {
public:
	typedef int UID;
public:
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_TEXTUREPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
