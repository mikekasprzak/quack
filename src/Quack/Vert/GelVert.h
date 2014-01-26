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
//struct GelVertex2 {
__GelVertex_START( 2 )
	Vector2D Pos;
__GelVertex_END( 2 )
//};
//typedef GelVert<GelVertex2> GelVert2;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2N {
	Vector2D Pos;
	Vector2D Normal;
};
typedef GelVert<GelVertex2N> GelVert2N;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2U {
	Vector2D Pos;
	GelUV UV;
};
typedef GelVert<GelVertex2U> GelVert2U;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2C {
	Vector2D Pos;
	GelColor Color;
};
typedef GelVert<GelVertex2C> GelVert2C;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2R {
	Vector2D Pos;
	Real Radius;
};
typedef GelVert<GelVertex2R> GelVert2R;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NU {
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
};
typedef GelVert<GelVertex2NU> GelVert2NU;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NC {
	Vector2D Pos;
	Vector2D Normal;
	GelColor Color;
};
typedef GelVert<GelVertex2NC> GelVert2NC;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NR {
	Vector2D Pos;
	Vector2D Normal;
	Real Radius;
};
typedef GelVert<GelVertex2NR> GelVert2NR;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NUC {
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
	GelColor Color;
};
typedef GelVert<GelVertex2NUC> GelVert2NUC;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NUR {
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
	Real Radius;
};
typedef GelVert<GelVertex2NUR> GelVert2NUR;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NCR {
	Vector2D Pos;
	Vector2D Normal;
	GelColor Color;
	Real Radius;
};
typedef GelVert<GelVertex2NCR> GelVert2NCR;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2NUCR {
	Vector2D Pos;
	Vector2D Normal;
	GelUV UV;
	GelColor Color;
	Real Radius;
};
typedef GelVert<GelVertex2NUCR> GelVert2NUCR;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2UC {
	Vector2D Pos;
	GelUV UV;
	GelColor Color;
};
typedef GelVert<GelVertex2UC> GelVert2UC;
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2UR {
	Vector2D Pos;
	GelUV UV;
	Real Radius;
};
typedef GelVert<GelVertex2UR> GelVert2UR;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2UCR {
	Vector2D Pos;
	GelUV UV;
	GelColor Color;
	Real Radius;
};
typedef GelVert<GelVertex2UCR> GelVert2UCR;
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
struct GelVertex2CR {
	Vector2D Pos;
	GelColor Color;
	Real Radius;
};
typedef GelVert<GelVertex2CR> GelVert2CR;
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
