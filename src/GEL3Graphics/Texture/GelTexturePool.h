// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_GELTEXTUREPOOL_H__
#define __GEL_TEXTURE_GELTEXTUREPOOL_H__
// - ------------------------------------------------------------------------------------------ - //
// A Smart System built on top of Texture that is indiffent of texture format, and caches the
//   data so multiple requests for the same data do not waste VRAM.

// TODO: Make it so the new TexturePool can actually be instanced. Smaller pools of textures. //
// MAYBE: No top level Texture Pool. Part of Texture instead.
// NOPE: GelTextureHandle's rely on an internal active Texture Unit and Handle. Not really viable.
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a listener for OnReload.
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelTexture.h"
// - ------------------------------------------------------------------------------------------ - //
class GelTexturePool: public GelPool<GelTexture> {
public:
	_GELPOOL_LOAD_FUNC( const bool Smooth = true, const bool Flip = true, const bool PreMultiplyAlpha = true )
	_GELPOOL_LOAD_BODY( "Texture",GelTexture, Smooth, Flip, PreMultiplyAlpha )
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_GELTEXTUREPOOL_H__ //
// - ------------------------------------------------------------------------------------------ - //
