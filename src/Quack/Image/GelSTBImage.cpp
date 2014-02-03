// - ------------------------------------------------------------------------------------------ - //
#include "GelSTBImage.h"
#include <External/STB/stb_image.h>
// - ------------------------------------------------------------------------------------------ - //
bool is_STBTexture( const void* const Data, const st Size ) {
	const unsigned char* const Buffer = (const unsigned char* const)Data;
	
	if ( stbi_jpeg_test_memory(Buffer,Size) )
		return true;
	if ( stbi_png_test_memory(Buffer,Size) )
		return true;
	if ( stbi_bmp_test_memory(Buffer,Size) )
		return true;
	if ( stbi_psd_test_memory(Buffer,Size) )
		return true;
#ifndef STBI_NO_HDR
	if ( stbi_hdr_test_memory(Buffer,Size) )
		return true;
#endif // STBI_NO_HDR //
	if ( stbi_tga_test_memory(Buffer,Size) )
		return true;
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
GelSTBImage new_GelSTBImage( const void* const Data, const st Size ) {
	GelSTBImage Image;
	
	Image.Data = stbi_load_from_memory( 
		(unsigned char*)Data, Size,
		&Image.Width, &Image.Height, &Image.Info, 0 );
	
	return Image;
}
// - ------------------------------------------------------------------------------------------ - //
void delete_GelSTBImage( GelSTBImage& Image ) {
	if ( Image.Data ) {
		stbi_image_free( Image.Data );
		Image.Data = 0;
	}
}
// - ------------------------------------------------------------------------------------------ - //
