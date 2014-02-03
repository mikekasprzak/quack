// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_IMAGE_GELSTBIMAGE_H__
#define __GEL_IMAGE_GELSTBIMAGE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Lib/DataBlock/DataBlock.h>
// - ------------------------------------------------------------------------------------------ - //
struct GelSTBImage {
	int Width;
	int Height;
	int Info;
	unsigned char* Data;

public:
	inline GelSTBImage() :
		Width(0),
		Height(0),
		Info(0),
		Data(0)
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
bool is_GelSTBImage( const void* const Data, const st Size );	// Is unprocessed Data an STBTexture?
// - ------------------------------------------------------------------------------------------ - //
GelSTBImage new_GelSTBImage( const void* const Data, const st Size );	// Read data in to a Structure.
inline GelSTBImage new_GelSTBImage( const DataBlock* const Data ) {
	return new_GelSTBImage( Data->Data, Data->Size );
}
// - ------------------------------------------------------------------------------------------ - //
void delete_GelSTBImage( GelSTBImage& Image );
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_IMAGE_GELSTBIMAGE_H__ //
// - ------------------------------------------------------------------------------------------ - //
