// - ------------------------------------------------------------------------------------------ - //
// VecTile is an info structure for building Line Segments that wrap around chunks of tile map //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __SEED_VECTILE_H__
#define __SEED_VECTILE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Array/Array.h>
// - ------------------------------------------------------------------------------------------ - //
struct VecTile {
	u16 Side[4];	// Length of the Vector pointing out each side //
	
public:	
	inline u16& operator [] ( const st idx ) {
		return Side[idx&3];
	}
	inline const u16& operator [] ( const st idx ) const {
		return Side[idx&3];
	}
	
	inline static Vector2D _Vector( const st idx ) {
		static float VecX[] = { 1, 0,-1, 0 };
		static float VecY[] = { 0, 1, 0,-1 };
		return Vector2D( VecX[idx&3], VecY[idx&3] );
	}
	
	inline Vector2D Vector( const st idx ) const {
		return _Vector(idx) * Real(operator[](idx));
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_VECTILE_H__ //
// - ------------------------------------------------------------------------------------------ - //
