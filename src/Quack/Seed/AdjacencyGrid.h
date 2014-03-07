// - ------------------------------------------------------------------------------------------ - //
#ifndef __SEED_ADJACENCYGRID_H__
#define __SEED_ADJACENCYGRID_H__
// - ------------------------------------------------------------------------------------------ - //
#include "VecTile.h"
// - ------------------------------------------------------------------------------------------ - //
typedef GelGrid<VecTile> AdjacencyGrid;
// - ------------------------------------------------------------------------------------------ - //
// In should be a GelSubGrid //
template<typename T1, typename T2>
inline void Gen_AdjacencyGrid( GelGrid<T1>& Out, const T2& In ) {
	Out.Clear();
	Out.Resize( In.Width(), In.Height(), VecTile() );

	for ( st y = 0; y < In.Height(); y++ ) {
		for ( st x = 0; x < In.Width(); x++ ) {
			// Scan Upwards //
			for ( st yy = y-1; yy >= 0; yy-- ) {
				if ( In(x,yy) != VT_SIDE_MAX ) {
					
				}
				
			}
			//Out(w,h) = In(w*StepX,h*StepY);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T2>
inline AdjacencyGrid Gen_AdjacencyGrid( const T2& In ) {
	AdjacencyGrid Ret;
	Gen_AdjacencyGrid(Ret,In);
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_ADJACENCYGRID_H__ //
// - ------------------------------------------------------------------------------------------ - //
