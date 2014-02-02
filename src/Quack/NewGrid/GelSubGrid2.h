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
	st32 x,y;		// Offset //
	ParentType* Parent;
public:
	typedef T Type;

	inline GelSubGrid2( ParentType* _Parent, const st _x = 0, const st _y = 0, const st _w = 0, const st _h = 0 ) :
		w(_w),
		h(_h),
		x(_x),
		y(_y),
		Parent(_Parent)
	{
	}
	
	// Fast Version //
	inline st _Index( const st _x, const st _y ) const {
		return (x+_x) + ((y+_y) * Parent->w);
	}
	// The default behavior is Wrapping //
	inline st Index( st _x, st _y ) const {
		while ( _x > w ) { _x -= w; };
		while ( _x < 0 ) { _x += w; };
		while ( _y > h ) { _y -= h; };
		while ( _y < 0 ) { _y += h; };
		// TODO: Should I wrap to main map too? or Call parent's Index? //
		return _Index(_x,_y);
	}

	// Function Operator -- i.e. Normal Usage //	
	inline T& operator () ( const st _x, const st _y ) {
		return (*Parent)[ Index(_x,_y) ];
	}
	inline const T& operator () ( const st _x, const st _y ) const {
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
	// Same thing (really) //
	inline st Area() const {
		return w*h;
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

	inline void Set( ParentType* _Parent, const st _x = 0, const st _y = 0, const st _w = 0, const st _h = 0 ) {
		w = _w;
		h = _h;
		x = _x;
		y = _y;
		Parent = _Parent;
	}
	
};
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
GelSubGrid2<T> GelGrid2<T>::Sub( const st _x, const st _y, const st _w, const st _h ) {
	return Ret( this, _x, _y, _w, _h );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELSUBGRID2_H__ //
// - ------------------------------------------------------------------------------------------ - //
