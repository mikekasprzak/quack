// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Asset/Asset.h>
#include <Texture/Texture.h>
// - ------------------------------------------------------------------------------------------ - //
#include <spine/spine.h>
#include <spine/extension.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void _spAtlasPage_createTexture( spAtlasPage* self, const char* path ) {
	Log( "! SPINE ATLAS createTexture: Atlas: 0x%x  \"%s\"", self, path );
	
	// TODO: Read Atlas information to determine if we should smooth or not //
	
	/*GelTexturePool::UID*/ st Asset = Gel::TexturePool.Load( path, true, false );
	self->rendererObject = (void*)Asset;
	self->width = Gel::TexturePool[Asset].GetWidth();
	self->height = Gel::TexturePool[Asset].GetHeight();
}
// - ------------------------------------------------------------------------------------------ - //
void _spAtlasPage_disposeTexture( spAtlasPage* self ) {
	Log( "! SPINE ATLAS disposeTexture: Atlas: 0x%x", self );
}
// - ------------------------------------------------------------------------------------------ - //
char* _spUtil_readFile (const char* path, int* length ) {
	Log( "! SPINE ATLAS readFile: \"%s\"  LengthPtr: 0x%x", path, length );
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //

