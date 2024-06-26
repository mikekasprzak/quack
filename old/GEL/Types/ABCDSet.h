// - ------------------------------------------------------------------------------------------ - //
// ABCDSet //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_ABCDSet_H__
#define __Geometry_ABCDSet_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template <class T>
class ABCDSet {
public:
	T a, b, c, d;

public:
	ABCDSet() {
	}

	ABCDSet( T _a, T _b, T _c, T _d ) :
		a( _a ),
		b( _b ),
		c( _c ),
		d( _d )
	{
	}
	
	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const ABCDSet& _Vs ) const {
		if ( (a == _Vs.a) )
			if ( (b == _Vs.b) )
				if ( (c == _Vs.c) )
					return (d == _Vs.d);
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline T& operator [] ( const int Index ) {
		return *((&a)+Index);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const T& operator [] ( const int Index ) const {
		return *((&a)+Index);
	}
	// - -------------------------------------------------------------------------------------- - //	
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_ABCDSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
