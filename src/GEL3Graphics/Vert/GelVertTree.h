// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_VERT_GELVERTTREE_H__
#define __GEL_VERT_GELVERTTREE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelVert.h"
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelVertTree {
	typedef GelVertTree thistype;
	GelVert<T> Data;
public:
	typedef T Type;
	
	inline GelVertTree( const st _Size = 0 ) :
		Data(_Size)
	{
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_VERT_GELVERTTREE_H__ //
// - ------------------------------------------------------------------------------------------ - //