// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_VERT_GELVERT_H__
#define __GEL_VERT_GELVERT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Graphics/Graphics.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
// GelVert??   - Array of elements
// GelVertex?? - Single element
// GelVert     - Base Template of all GelVert?? types
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
// GUIDE: //
// 1 -- 1D Position (Real)
// 2 -- 2D Position
// 3 -- 3D Position
// 4 -- 4D Position
// N -- Normal (same dimensions as Position)
// U -- UV Coordinate
// C -- Color
// R -- Radius
// D? - Data, where ? is a number from 1-4 (Real to Vector4D)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_START( _sym ) \
struct GelVertex ## _sym {
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_END( _sym ) \
}; \
typedef GelVert<GelVertex ## _sym> GelVert ## _sym;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// 2D Versions //
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2 )
	Vector2D Pos;
__GelVertex_END( 2 )
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2N )
	Vector2D Pos;
	Vector2D Normal;
__GelVertex_END( 2N )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2U )
	Vector2D Pos;
	GelUV UV;
__GelVertex_END( 2U )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2C )
	Vector2D Pos;
	GelColor Color;
__GelVertex_END( 2C )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2R )
	Vector2D Pos;
	Real Radius;
__GelVertex_END( 2R )
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NU )
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
__GelVertex_END( 2NU )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NC )
	Vector2D Pos;
	Vector2D Normal;
	GelColor Color;
__GelVertex_END( 2NC )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NR )
	Vector2D Pos;
	Vector2D Normal;
	Real Radius;
__GelVertex_END( 2NR )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2UC )
	Vector2D Pos;
	GelUV UV;
	GelColor Color;
__GelVertex_END( 2UC )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2UR )
	Vector2D Pos;
	GelUV UV;
	Real Radius;
__GelVertex_END( 2UR )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2CR )
	Vector2D Pos;
	GelColor Color;
	Real Radius;
__GelVertex_END( 2CR )
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NUC )
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
	GelColor Color;
__GelVertex_END( 2NUC )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NUR )
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
	Real Radius;
__GelVertex_END( 2NUR )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NCR )
	Vector2D Pos;
	Vector2D Normal;
	GelColor Color;
	Real Radius;
__GelVertex_END( 2NCR )
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2UCR )
	Vector2D Pos;
	GelUV UV;
	GelColor Color;
	Real Radius;
__GelVertex_END( 2UCR )
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
__GelVertex_START( 2NUCR )
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
	GelColor Color;
	Real Radius;
__GelVertex_END( 2NUCR )
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// 3D Versions //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex3 {
	Vector3D Pos;
};
typedef GelVert<GelVertex3> GelVert3;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex3C {
	Vector3D Pos;
	GelColor Color;
};
typedef GelVert<GelVertex3C> GelVert3C;
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_VERT_GELVERT_H__ //
// - ------------------------------------------------------------------------------------------ - //
