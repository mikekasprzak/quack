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

	inline GelGrid( const st _w, const st _h, const T& _Value ) :
		w(_w),
		h(_h),
		Data(_w*_h, _Value)
	{
	}
	
	// Fast Version //
	inline int _Index( const int _x, const int _y ) const {
		return _x + (_y * w);
	}
	// The default behavior is Wrapping //
	inline int Index( int _x, int _y ) const {
		while ( _x >= (int)w )	{ _x -= (int)w; }
		while ( _x < 0 )		{ _x += (int)w; }
		while ( _y >= (int)h )	{ _y -= (int)h; }
		while ( _y < 0 )		{ _y += (int)h; }
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
	inline void Clear() {
		w = 0;
		h = 0;
		Data.clear();
	}
	// NOTE: Invalidates Data. If you want to preserve, copy to new, use a .swap() //
	inline void Resize( const st _w, const st _h ) {
		w = _w;
		h = _h;
		Data.resize(_w*_h);
	}
	inline void Resize( const st _w, const st _h, const T& Value ) {
		w = _w;
		h = _h;
		Data.resize(_w*_h,Value);
	}

public:
	// Wrap Around as if the data looped back to the start after the end //
	inline st LoopIndex( const int _x, const int _y ) const {
		return abs(_Index(_x,_y)) % Size();
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
		// TODO: Assert > 0 (i.e. ABS) //
		return _idx % w;
	}
	inline int IndexToY( const st _idx ) const {
		// TODO: Assert > 0 (i.e. ABS) //
		return _idx / w;
	}


	inline void Fill( const T& _Value ) {
		Data.assign( Data.size(), _Value );
	}

	
public:
	// Generate a Sub Grid //
	inline GelSubGrid<T> GetSubGrid( const int _x, const int _y, const st _w, const st _h );
};
// - ------------------------------------------------------------------------------------------ - //
// http://stackoverflow.com/questions/1174169/function-passed-as-template-argument
// NOTE: "add3()" is the constructor, then after F(...) is the () operator.
// - ------------------------------------------------------------------------------------------ - //
// Functor for calling the Builtin Index type //
struct GelGrid_Index {
	template<typename T>
	inline int operator() ( const T& Grid, int _x, int _y ) const {
		return Grid.Index(_x,_y);
	}
};
struct GelGrid_LoopIndex {
	template<typename T>
	inline int operator() ( const T& Grid, int _x, int _y ) const {
		return Grid.LoopIndex(_x,_y);
	}
};
struct GelGrid_SaturateIndex {
	template<typename T>
	inline int operator() ( const T& Grid, int _x, int _y ) const {
		return Grid.SaturateIndex(_x,_y);
	}
};
struct GelGrid_DeadIndex {
	template<typename T>
	inline int operator() ( const T& Grid, int _x, int _y ) const {
		return Grid.DeadIndex(_x,_y);
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRID_GELGRID_H__ //
// - ------------------------------------------------------------------------------------------ - //
