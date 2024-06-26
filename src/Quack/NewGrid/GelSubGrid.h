// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRID_GELSUBGRID_H__
#define __GEL_GRID_GELSUBGRID_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelGrid.h"
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelSubGrid {
	typedef GelSubGrid thistype;
	typedef GelGrid<T> ParentType;

	st32 w,h;		// Shape (first, to be consistent with GelGrid) //
	int x,y;		// Offset //
	ParentType* Parent;
public:
	typedef T Type;

	inline GelSubGrid( ParentType* _Parent, const int _x = 0, const int _y = 0, const st _w = 0, const st _h = 0 ) :
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
		while ( _x >= (int)w )	{ _x -= (int)w; }
		while ( _x < 0 )		{ _x += (int)w; }
		while ( _y >= (int)h )	{ _y -= (int)h; }
		while ( _y < 0 )		{ _y += (int)h; }
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
		while ( _x > (int)w )	{ _x -= (int)w; _y++; };
		while ( _x < 0 )		{ _x += (int)w; _y--; };
		return Parent->LoopIndex(x+_x,y+_y);
	}
	// Align to edges instead of wrapping //
	inline st SaturateIndex( int _x, int _y ) const {
		if ( _x >= (int)Width() )
			_x = (int)Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		if ( _y >= (int)Height() )
			_y = (int)Height() - 1;
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
	inline GelSubGrid<T> GetSubGrid( const int _x, const int _y, const st _w, const st _h );	
};
// - ------------------------------------------------------------------------------------------ - //
// Sub Grids of a Grid //
template<typename T>
GelSubGrid<T> GelGrid<T>::GetSubGrid( const int _x, const int _y, const st _w, const st _h ) {
	return GelSubGrid<T>( this, _x, _y, _w, _h );
}
// - ------------------------------------------------------------------------------------------ - //
// Sub Grids of Sub Grids //
template<typename T>
GelSubGrid<T> GelSubGrid<T>::GetSubGrid( const int _x, const int _y, const st _w, const st _h ) {
	return GelSubGrid<T>( Parent, x+_x, y+_y, _w, _h );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELSUBGRID_H__ //
// - ------------------------------------------------------------------------------------------ - //
