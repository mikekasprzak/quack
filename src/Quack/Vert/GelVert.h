// - ------------------------------------------------------------------------------------------ - //
// USAGE: 
//   GelVert2 for an array of 2D elements containing just a Position
//   GelVert3NC for an array of 3D elements containing Position, a Normal, and a Color
// - ------------------------------------------------------------------------------------------ - //
// GUIDE:
// 1 -- 1D Position (Real)
// 2 -- 2D Position (Vector2D)
// 3 -- 3D Position (Vector3D)
// 4 -- 4D Position (Vector4D)
// N -- Normal (same as Position)
// U -- UV Coordinate (GelUV)
// C -- Color (GelColor)
// R -- Radius (Real)
// NN UU CC RR -- Include 2 sets of the primary types (Normal and Normal2, etc)
// - ------------------------------------------------------------------------------------------ - //
// TODO: //
// D? - Data, where ? is a number from 1-4 (Real to Vector4D)
// MultiPairs -- Currently only a single NN UU CC RR can be used.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_VERT_GELVERT_H__
#define __GEL_VERT_GELVERT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Graphics/Graphics.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
// GelVert?    - Array of elements. I.e. GelVert2 (Pos), GelVert3NC (Pos,Normal,Color)
// GelVertex?  - Single element (same naming scheme)
// GelVert     - Base Template of all GelVert? types
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelVert {
	typedef GelVert thistype;
	std::vector<T> Data;	
public:
	typedef T Type;
	
	inline GelVert( st _Size = 0 ) :
		Data(_Size)
	{
	}
	
	inline T& operator [] ( st Index ) {
		return Data[Index];
	}
	inline const T& operator [] ( st Index ) const {
		return Data[Index];
	}

public:
	st Size() const {
		return Data.size();
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define __CAT(a, ...) __PRIMITIVE_CAT(a, __VA_ARGS__)
#define __PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_START(_num,_sym) \
struct __CAT(GelVertex,__CAT(_num,_sym)) {
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_END(_num,_sym) \
}; \
typedef GelVert<__CAT(GelVertex,__CAT(_num,_sym))> __CAT(GelVert,__CAT(_num,_sym));
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Real
#define __GelVertex_NUMBER 1
#include "GelVert_GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Vector2D
#define __GelVertex_NUMBER 2
#include "GelVert_GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Vector3D
#define __GelVertex_NUMBER 3
#include "GelVert_GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Vector4D
#define __GelVertex_NUMBER 4
#include "GelVert_GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#undef __GelVertex_START
#undef __GelVertex_END
// - ------------------------------------------------------------------------------------------ - //
#undef __CAT
#undef __PRIMITIVE_CAT
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_VERT_GELVERT_H__ //
// - ------------------------------------------------------------------------------------------ - //
