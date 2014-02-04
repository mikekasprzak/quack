// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRID_GELSUBGRID2_H__
#define __GEL_GRID_GELSUBGRID2_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelGrid2.h"
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelSubGrid2 {
	typedef GelSubGrid2 thistype;
	typedef GelGrid2<T> ParentType;

	st32 w,h;		// Shape (first, to be consistent with GelGrid2) //
	int x,y;		// Offset //
	ParentType* Parent;
public:
	typedef T Type;

	inline GelSubGrid2( ParentType* _Parent, const int _x = 0, const int _y = 0, const st _w = 0, const st _h = 0 ) :
		w(_w),
		h(_h),
		x(_x),
		y(_y),
		Parent(_Parent)
	{
	}
	
	// Fast Version (No Wrapping) //
	inline st __Index( const int _x, const int _y ) const {
		return Parent->_Index(x+_x,y+_y);
	}
	// Parent Wrapping //
	inline st _Index( const int _x, const int _y ) const {
		return Parent->Index(x+_x,y+_y);
	}
	// Local Wrapping //
	inline st Index( int _x, int _y ) const {
		while ( _x >= w ) { _x -= w; };
		while ( _x < 0 )  { _x += w; };
		while ( _y >= h ) { _y -= h; };
		while ( _y < 0 )  { _y += h; };
		return _Index(_x,_y);
	}

	// Function Operator -- i.e. Normal Usage //	
	inline T& operator () ( const int _x, const int _y ) {
		return (*Parent)[ Index(_x,_y) ];
	}
	inline const T& operator () ( const int _x, const int _y ) const {
		return (*Parent)[ Index(_x,_y) ];
	}
	
	// Array Operator -- Only if you know the Index //
	inline T& operator [] ( const st _idx ) {
		return (*Parent)[ _idx ];
	}
	inline const T& operator [] ( const st _idx ) const {
		return (*Parent)[ _idx ];
	}
	
	// How many elements //
	inline st Size() const {
		return Parent->Size();
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
	// NOTE: DOES NOT Invalidate Data //
	inline void Resize( const st _w, const st _h ) {
		w = _w;
		h = _h;
	}
	inline void SetPos( const st _x, const st _y ) {
		x = _x;
		y = _y;
	}

	inline void Set( ParentType* _Parent, const int _x = 0, const int _y = 0, const st _w = 0, const st _h = 0 ) {
		w = _w;
		h = _h;
		x = _x;
		y = _y;
		Parent = _Parent;
	}

public:
	// Wrap Around as if the data looped back to the start after the end //
	inline st LoopIndex( int _x, int _y ) const {
		while ( _x > w ) { _x -= w; _y++; };
		while ( _x < 0 ) { _x += w; _y--; };
		return Parent->LoopIndex(x+_x,y+_y);
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
		return Parent->IndexToX(_idx) - x;
	}
	inline int IndexToY( const st _idx ) const {
		return Parent->IndexToY(_idx) - y;
	}

public:
	inline GelSubGrid2<T> GetSubGrid( const int _x, const int _y, const st _w, const st _h );	
};
// - ------------------------------------------------------------------------------------------ - //
// Sub Grids of a Grid //
template<typename T>
GelSubGrid2<T> GelGrid2<T>::GetSubGrid( const int _x, const int _y, const st _w, const st _h ) {
	return GelSubGrid2<T>( this, _x, _y, _w, _h );
}
// - ------------------------------------------------------------------------------------------ - //
// Sub Grids of Sub Grids //
template<typename T>
GelSubGrid2<T> GelSubGrid2<T>::GetSubGrid( const int _x, const int _y, const st _w, const st _h ) {
	return GelSubGrid2<T>( Parent, x+_x, y+_y, _w, _h );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELSUBGRID2_H__ //
// - ------------------------------------------------------------------------------------------ - //
