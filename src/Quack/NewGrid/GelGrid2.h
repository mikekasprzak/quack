// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRID_GELGRID2_H__
#define __GEL_GRID_GELGRID2_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelSubGrid2;	// Prototype //
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelGrid2 {
	typedef GelGrid2 thistype;

	st32 w,h;		// Shape //
	std::vector<T> Data;
	
	friend GelSubGrid2<T>;
public:
	typedef T Type;
	
	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELGRID2_H__ //
// - ------------------------------------------------------------------------------------------ - //
