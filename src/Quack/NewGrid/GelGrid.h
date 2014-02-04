// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRID_GELGRID_H__
#define __GEL_GRID_GELGRID_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelSubGrid;	// Prototype //
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelGrid {
	typedef GelGrid thistype;

	st32 w,h;		// Shape //
	std::vector<T> Data;
	
	friend GelSubGrid<T>;
public:
	typedef T Type;
	
	inline GelGrid( const st _w = 0, const st _h = 0 ) :
		w(_w),
		h(_h),
		Data(_w*_h)
	{
	}
	
	// Fast Version //
	inline int _Index( const int _x, const int _y ) const {
		return _x + (_y * w);
	}
	// The default behavior is Wrapping //
	inline int Index( int _x, int _y ) const {
		while ( _x >= w ) { _x -= w; };
		while ( _x < 0 )  { _x += w; };
		while ( _y >= h ) { _y -= h; };
		while ( _y < 0 )  { _y += h; };
		return _Index(_x,_y);
	}

	// Function Operator -- i.e. Normal Usage //	
	inline T& operator () ( const st _x, const st _y ) {
		return Data[ Index(_x,_y) ];
	}
	inline const T& operator () ( const st _x, const st _y ) const {
		return Data[ Index(_x,_y) ];
	}
	
	// Array Operator -- Only if you know the Index //
	inline T& operator [] ( const st _idx ) {
		return Data[ _idx ];
	}
	inline const T& operator [] ( const st _idx ) const {
		return Data[ _idx ];
	}
	
	// How many elements //
	inline st Size() const {
		return Data.size();
	}
	inline st SizeOf() const {
		return Size() * sizeof(T);
	}

	// Width and Height //
	inline st32 Width() const {
		return w;
	}
	inline st32 Height() const {
		return h;
	}
	inline st32 HalfWidth() const {
		return w >> 1;
	}
	inline st32 HalfHeight() const {
		return h >> 1;
	}
	inline st32 Area() const {
		return w*h;
	}
	
public:
	inline void Resize( const st _w, const st _h ) {
		w = _w;
		h = _h;
		// NOTE: Invalidates Data. If you want to preserve, copy to new, use a .swap() //
		Data.resize(_w*_h);
	}

public:
	// Wrap Around as if the data looped back to the start after the end //
	inline st LoopIndex( const int _x, const int _y ) const {
		return abs(_Index(_x,_y)) % Size();
	}
	// Align to edges instead of wrapping //
	inline st SaturateIndex( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return _Index( _x, _y );
	}
	// Return a specific value if outside //
	inline st DeadIndex( const int _x, const int _y, const st DeadValue = ST_MAX ) const {
		if ( _x >= (int)Width() )
			return DeadValue;
		else if ( _x < 0 )
			return DeadValue;
			
		if ( _y >= (int)Height() )
			return DeadValue;
		else if ( _y < 0 )
			return DeadValue;
			
		return _Index( _x, _y );
	}

	// Extract X or Y values from an Index //
	inline int IndexToX( const st _idx ) const {
		// TODO: Assert > 0 (i.e. ABS) //
		return _idx % w;
	}
	inline int IndexToY( const st _idx ) const {
		// TODO: Assert > 0 (i.e. ABS) //
		return _idx / w;
	}

	
public:
	// Generate a Sub Grid //
	inline GelSubGrid<T> GetSubGrid( const int _x, const int _y, const st _w, const st _h );
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELGRID_H__ //
// - ------------------------------------------------------------------------------------------ - //
