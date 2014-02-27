// - ------------------------------------------------------------------------------------------ - //
#ifndef __SEED_GEN_ADJACENCYGRID_H__
#define __SEED_GEN_ADJACENCYGRID_H__
// - ------------------------------------------------------------------------------------------ - //
#include "VecTile.h"
// - ------------------------------------------------------------------------------------------ - //
template<typename T1, typename T2>
inline void Gen_AdjacencyGrid( GelGrid<T1>& Out, const GelGrid<T2>& In ) {
	Out.Clear();
	Out.Resize( In.Width, In.Height, VecTile() );

	for ( st y = 0; y < In.Height; y++ ) {
		for ( st y = 0; y < In.Width; y++ ) {
			//Out(w,h) = In(w*StepX,h*StepY);
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T2>
inline AdjacencyGrid Gen_AdjacencyGrid( const GelGrid<T2>& In ) {
	AdjacencyGrid Ret;
	Gen_AdjacencyGrid(Ret,In);
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
typedef GelGrid<VecTile> AdjacencyGrid;
// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_GEN_ADJACENCYGRID_H__ //
// - ------------------------------------------------------------------------------------------ - //
