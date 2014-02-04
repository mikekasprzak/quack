// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRID_GELGRID2_FROM_GELIMAGE_H__
#define __GEL_GRID_GELGRID2_FROM_GELIMAGE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Image/Image.h>
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
inline void Gen_GelGrid2_from_GelImage( GelGrid2<T>& Out, const GelImage& In, const int StepX = 1, const int StepY = 1 ) {
	st Width = In.Width() / StepX;
	st Height = In.Height() / StepY;
	st Size = Width * Height;

	Out.Resize( Width, Height );

	for ( st h = 0; h < Height; h++ ) {
		for ( st w = 0; w < Width; w++ ) {
			Out(w,h) = In(w*StepX,h*StepY);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELGRID2_FROM_GELIMAGE_H__ //
// - ------------------------------------------------------------------------------------------ - //
