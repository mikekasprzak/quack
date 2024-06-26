// - ------------------------------------------------------------------------------------------ - //
// ABSet //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_ABSet_H__
#define __Geometry_ABSet_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template <class T>
class ABSet {
public:
	T a, b;

public:
	ABSet() {
	}

	ABSet( T _a, T _b ) :
		a( _a ),
		b( _b )
	{
	}
	
	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const ABSet& _Vs ) const {
		if ( (a == _Vs.a) )
			return (b == _Vs.b);
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
#endif // __Geometry_ABSet_H__ //
// - ------------------------------------------------------------------------------------------ - //
