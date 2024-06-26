// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TEXTURE_TEXTURE_H__
#define __GEL_TEXTURE_TEXTURE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelTexturePool.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
extern GelTexturePool 	TexturePool;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void gelTextureInit() {
	Log( "* GelTexture Init()..." );
	init_GelTextureHandle();
	atexit( exit_GelTextureHandle );
	Log( "* GelTexture Init() done." );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TEXTURE_TEXTURE_H__ //
// - ------------------------------------------------------------------------------------------ - //
