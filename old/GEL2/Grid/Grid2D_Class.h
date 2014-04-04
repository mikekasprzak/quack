// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL2_GRID_GRID2D_CLASS_H__
#define __GEL2_GRID_GRID2D_CLASS_H__
// - ------------------------------------------------------------------------------------------ - //
#include <math.h>
#include <Style/Style.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Math Functions, Insert (creating rows and columns to fit, X/YAxis Only)
//   Rename Resize to Canvas and/or Clip. 
//   Make Resize do scaling, providing scaling algorithm choices. Pixel, Bilinear.
//   Make SetWidth make more sense (i.e. what SetW does).

// TODO: Rename all functions that change the data to "ActionData". 
// - ------------------------------------------------------------------------------------------ - //
template< typename tType = int >
class Grid2DRef;
// - ------------------------------------------------------------------------------------------ - //
template< typename tType = int >
class SubGrid2D;
// - ------------------------------------------------------------------------------------------ - //
template< typename tType = int >
class Grid2D;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
class Grid2D {
	// - -------------------------------------------------------------------------------------- - //	
	szt w, h;		// Dimensions //
	tType* Data;	// Data Array //
	// - -------------------------------------------------------------------------------------- - //
	friend class SubGrid2D<tType>;
	friend class Grid2DRef<tType>;
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D() :
		w( 0 ),
		h( 0 ),
		Data( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D( const szt _w, const szt _h ) :
		w( _w ),
		h( _h ),
		Data( new tType[w*h] )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D( const szt _w, const szt _h, const tType& InitValue ) :
		w( _w ),
		h( _h ),
		Data( new tType[ _w * _h] )
	{
		fill_Data<tType>( InitValue, Data, Size() );
	}
	// - -------------------------------------------------------------------------------------- - //
//	// For building from pointers //
//	inline Grid2D( const szt _w, const szt _h, tType* _Data ) :
//		w( _w ),
//		h( _h ),
//		Data( _Data )
//	{
//	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D( const Grid2D<tType>& Orig ) :
		w( Orig.w ),
		h( Orig.h ),
		Data( new tType[Orig.Size()] )
	{
		copy_Data( Orig.Data, Data, Orig.SizeOf() );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2D<tType>& operator = (const Grid2D<tType>& Orig) {
		if ( this != &Orig ) {
			// If we just happen to be the same total size //
			if ( Orig.Size() == Size() ) {
				w = Orig.w;
				h = Orig.h;

				// Copy our data and don't delete it //
				copy_Data( Orig.Data, Data, Orig.SizeOf() );
			}
			// If different size, or no size //
			else {
				// Toast our data, if we have one //
				if ( Data )
					delete [] Data;
				
				w = Orig.w;
				h = Orig.h;
				
				// Create and copy the data //
				Data = new tType[ Orig.Size() ];
				copy_Data( Orig.Data, Data, Orig.SizeOf() );
			}
		}
		
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline ~Grid2D() {
		if ( Data ) {
			delete [] Data;
			Data = 0;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	// Removes the data from itself, but doesn't free it. //
	// TODO: come up with a better name for this //
	inline Grid2D<tType> Move() {
		Grid2D<tType> Ret( w, h, Data );
		w = 0;
		h = 0;
		Data = 0;
		return Ret;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const szt Width() const {
		return w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Height() const {
		return h;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt HalfWidth() const {
		return w >> 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt HalfHeight() const {
		return h >> 1;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Size() const {
		return w * h;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt SizeOf() const {
		return Size() * sizeof(tType);
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	inline void Fill( const tType& Value = tType() ) {
		fill_Data( Value, Data, Size() );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Used Internally to explicitly change the Data pointer //
	inline void SetData( tType* NewData ) {
		if ( Data )
			delete [] Data;
			
		Data = NewData;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidth( const szt _w ) {
		w = _w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeight( const szt _h ) {
		h = _h;
	}
	// - -------------------------------------------------------------------------------------- - //
	const tType* operator *() const {
		return Data;
	}
	// - -------------------------------------------------------------------------------------- - //
	tType* operator *() {
		return Data;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Index Generating functions.  Return a valid index for [] operator. //
	// - -------------------------------------------------------------------------------------- - //
	inline const szt Index( const int _x, const int _y ) const {
		// TODO: Assert out of bounds 
		return _x + (_y * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrap( int _x, int _y ) const {
		if ( _x < 0 )
			_x = Width() - ((-_x) % Width());
		else
			_x %= Width();
		
		if ( _y < 0 )
			_y = Height() - ((-_y) % Height());
		else
			_y %= Height();
		
		return _x + (_y * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrapX( int _x, const int _y ) const {
		if ( _x < 0 )
			_x = Width() - ((-_x) % Width());
		else
			_x %= Width();

		return _x + (_y * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexWrapY( const int _x, int _y ) const {
		if ( _y < 0 )
			_y = Height() - ((-_y) % Height());
		else
			_y %= Height();

		return _x + (_y * Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	// Wraps linearly to the next line, but around to the top //
	inline const szt IndexNextWrap( const int _x, const int _y ) const {
		return abs(Index(_x,_y)) % Size();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const szt IndexSaturate( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const szt IndexSaturateX( int _x, int _y ) const {
		if ( _x >= Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const szt IndexSaturateY( int _x, int _y ) const {
		if ( _y >= Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexToX( const int _Index ) const {
		// TODO: Assert out of bounds 
		return _Index % Width();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt IndexToY( const int _Index ) const {
		// TODO: Assert out of bounds 
		return _Index / Width();
	}
	// - -------------------------------------------------------------------------------------- - //

	
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator () ( const szt _x, const szt _y ) {
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator () ( const szt _x, const szt _y ) const {
		return Data[ Index( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& operator [] ( const szt _Index ) {
		// TODO: Assert out of bounds 
		return Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType& operator [] ( const szt _Index ) const {
		// TODO: Assert out of bounds 
		return Data[ _Index ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& Wrap( const int _x, const int _y ) {
		return Data[ IndexWrap( _x, _y ) ];
	}
	inline const tType& Wrap( const int _x, const int _y ) const {
		return Data[ IndexWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& WrapX( const int _x, const int _y ) {
		return Data[ IndexWrapX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& WrapX( const int _x, const int _y ) const {
		return Data[ IndexWrapX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline tType& WrapY( const int _x, const int _y ) {
		return Data[ IndexWrapY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with axis wrapping //
	inline const tType& WrapY( const int _x, const int _y ) const {
		return Data[ IndexWrapY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline tType& NextWrap( const int _x, const int _y ) {
		return Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, with next line/first line wrapping //
	inline const tType& NextWrap( const int _x, const int _y ) const {
		return Data[ IndexNextWrap( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& Saturate( const int _x, const int _y ) {
		return Data[ IndexSaturate( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& Saturate( const int _x, const int _y ) const {	
		return Data[ IndexSaturate( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& SaturateX( const int _x, const int _y ) {
		return Data[ IndexSaturateX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& SaturateX( const int _x, const int _y ) const {	
		return Data[ IndexSaturateX( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline tType& SaturateY( const int _x, const int _y ) {
		return Data[ IndexSaturateY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const tType& SaturateY( const int _x, const int _y ) const {	
		return Data[ IndexSaturateY( _x, _y ) ];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// These are for converting explicit X and Y values in to ones that fit within grid ranges //
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const int AxisSaturateX( int _x ) const {
		if ( _x >= (int)Width() )
			_x = Width() - 1;
		else if ( _x < 0 )
			_x = 0;
		
		return _x;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, aligning to edges //
	inline const int AxisSaturateY( int _y ) const {
		if ( _y >= (int)Height() )
			_y = Height() - 1;
		else if ( _y < 0 )
			_y = 0;
			
		return _y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt AxisWrapX( int _x ) const {
		if ( _x < 0 )
			_x = -_x;
		return (_x % Width());
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const szt AxisWrapY( int _y ) const {
		if ( _y < 0 )
			_y = -_y;
		return (_y % Height());
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Get the position, returning the dead value if over //
	inline const szt DeadIndex( const int _x, const int _y, const szt DeadValue = SZT_MAX ) const {
		if ( _x >= (int)Width() )
			return DeadValue;
		else if ( _x < 0 )
			return DeadValue;
			
		if ( _y >= (int)Height() )
			return DeadValue;
		else if ( _y < 0 )
			return DeadValue;
			
		return Index( _x, _y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Get the position, returning the dead value if over //
	inline const tType& Dead( const int _x, const int _y, const tType& DeadValue = tType() ) const {
		szt DIndex = DeadIndex(_x,_y);
		
		if ( DIndex != SZT_MAX )
			return Data[ DIndex ];
		else
			return DeadValue;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Given an edge described by OffsetX and OffsetY (Top=(0,1) Left=(1,0) ...), Index along it. //
	inline const int EdgeIndex( const int _Index, const int OffsetX, const int OffsetY ) {
		int x, y;
		
		if ( OffsetX < 0 ) {
			x = Width() - 1;
			y = _Index;
		}
		else if ( OffsetX > 0 ) {
			x = 0;
			y = _Index;
		}
		else if ( OffsetY < 0 ) {
			x = _Index;
			y = Height() - 1;
		}
		else  if ( OffsetY > 0 ) {
			x = _Index;
			y = 0;
		}
		
		return IndexSaturate(x,y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline tType& Edge( const int _Index, const int OffsetX, const int OffsetY ) {
		return Data[ EdgeIndex( _Index, OffsetX, OffsetY ) ];
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Exchange two values given their coordinates //
	inline void _Swap( const int x1, const int y1, const int x2, const int y2 ) {
		tType Temp = operator()(x1,y1);
		operator()(x1,y1) = operator()(x2,y2);
		operator()(x2,y2) = Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Swap( int x1, int y1, int x2, int y2 ) {
		x1 = AxisSaturateX( x1 );
		y1 = AxisSaturateY( y1 );
		
		x2 = AxisSaturateX( x2 );
		y2 = AxisSaturateY( y2 );
		
		_Swap(x1,y1,x2,y2);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the passed value with the value at the coordinate, returning the coordinate's value //
	inline const tType _Swap( const int x1, const int y1, const tType& Value ) {
		tType Temp = operator()(x1,y1);
		operator()(x1,y1) = Value;
		
		return Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType Swap( int x1, int y1, const tType& Value ) {
		x1 = AxisSaturateX( x1 );
		y1 = AxisSaturateY( y1 );

		return _Swap(x1,y1,Value);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Exchange the passed value with the value at the Index, returning the value at the Index //
	inline const tType Swap( int _Index, const tType& Value ) {
		tType Temp = operator[](_Index);
		operator[](_Index) = Value;
		
		return Temp;
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	static inline void Copy(
		const Grid2D<tType>& Src,
		Grid2D<tType>& Dest,
		int SrcX,
		int SrcY,
		int DestX,
		int DestY,
		int Width = -1,
		int Height = -1
		)
	{
		// Saturate the data, to make sure it's within range //
		SrcX = Src.AxisSaturateX( SrcX );
		SrcY = Src.AxisSaturateY( SrcY );
		DestX = Src.AxisSaturateX( DestX );
		DestY = Src.AxisSaturateY( DestY );
		
		// Saturate the width //
		if ( (Width == -1) || (DestX+Width > (int)Dest.Width()) ) {
			Width = Dest.Width() - DestX;
		}
		if ( SrcX+Width > (int)Src.Width() ) {
			Width = Src.Width() - SrcX;
		}
	
		// Saturate the height //
		if ( (Height == -1) || (DestY+Height > (int)Dest.Height()) ) {
			Height = Dest.Height() - DestY;
		}
		if ( SrcY+Height > (int)Src.Height() ) {
			Height = Src.Height() - SrcY;
		}
		
		// Copy Data //
		for ( szt y = Height; y--; ) {
			for ( szt x = Width; x--; ) {
				Dest(DestX + x, DestY + y) = Src(SrcX + x, SrcY + y);
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Copy( Grid2D<tType>& Dest, const int SrcX, const int SrcY, const int DestX, const int DestY, const int _Width = -1, const int _Height = -1 ) {
		return Copy( *this, Dest, SrcX, SrcY, DestX, DestY, _Width, _Height );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Wrapped version. Cannot determine the size of the box automatically. Size must be provided.
	static inline void CopyWrap(
		const Grid2D<tType>& Src,
		Grid2D<tType>& Dest,
		int SrcX,
		int SrcY,
		int DestX,
		int DestY,
		int Width,
		int Height
		)
	{		
		// Copy Data //
		for ( szt y = Height; y--; ) {
			for ( szt x = Width; x--; ) {
				Dest.Wrap(DestX + x, DestY + y) = Src.Wrap(SrcX + x, SrcY + y);
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void CopyWrap( Grid2D<tType>& Dest, const int SrcX, const int SrcY, const int DestX, const int DestY, const int _Width = -1, const int _Height = -1 ) {
		return CopyWrap( *this, Dest, SrcX, SrcY, DestX, DestY, _Width, _Height );
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> Copy(
		const Grid2D<tType>& Src,
		int SrcX,
		int SrcY,
		int Width = -1,
		int Height = -1
		)
	{
		// Saturate the data, to make sure it's within range //
		SrcX = Src.AxisSaturateX( SrcX );
		SrcY = Src.AxisSaturateY( SrcY );
		
		// Saturate the width //
		if ( (Width == -1) || (SrcX+Width > (int)Src.Width()) ) {
			Width = Src.Width() - SrcX;
		}
	
		// Saturate the height //
		if ( (Height == -1) || (SrcY+Height > (int)Src.Height()) ) {
			Height = Src.Height() - SrcY;
		}
		
		Grid2D<tType> Dest(Width,Height);
		
		// Copy Data //
		for ( szt y = Height; y--; ) {
			for ( szt x = Width; x--; ) {
				Dest(x,y) = Src(SrcX + x, SrcY + y);
			}
		}
		
		return Dest;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> Copy( const int SrcX, const int SrcY, const int _Width = -1, const int _Height = -1 ) {
		return Copy( *this, SrcX, SrcY, _Width, _Height );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Wrapped version. Cannot determine the size of the box automatically. Size must be provided.
	static inline const Grid2D<tType> CopyWrap(
		const Grid2D<tType>& Src,
		int SrcX,
		int SrcY,
		int Width,
		int Height
		)
	{		
		Grid2D<tType> Dest(Width,Height);
		
		// Copy Data //
		for ( szt y = Height; y--; ) {
			for ( szt x = Width; x--; ) {
				Dest(x,y) = Src.Wrap(SrcX + x, SrcY + y);
			}
		}
		
		return Dest;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> CopyWrap( const int SrcX, const int SrcY, const int _Width = -1, const int _Height = -1 ) {
		return CopyWrap( *this, SrcX, SrcY, _Width, _Height );
	}
	// - -------------------------------------------------------------------------------------- - //	

public:
	// - -------------------------------------------------------------------------------------- - //
	// Like copy, but the surface created is large enough to contain both. May not be useful. //
	// - -------------------------------------------------------------------------------------- - //	
	static inline const Grid2D<tType> Merge(
		const Grid2D<tType>& GridA,
		const Grid2D<tType>& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& InitValue = tType()
		);
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> MergeBlend(
		const Grid2D<tType>& GridA,
		const Grid2D<tType>& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& InitValue = tType()
		);
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> MergeBlendOnly(
		const Grid2D<tType>& GridA,
		const Grid2D<tType>& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& InitValue = tType()
		);
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> MergeBlendOnlyMask(
		const Grid2D<tType>& GridA,
		const Grid2D<tType>& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& MaskValue = tType(),
		const tType& InitValue = tType()
		);
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> MergeBlendMask(
		const Grid2D<tType>& GridA,
		const Grid2D<tType>& GridB,
		const int GridAX,
		const int GridAY,
		const int GridBX,
		const int GridBY,
		const tType& TestValue = tType(),
		const tType& MaskValue = tType(),
		const tType& InitValue = tType()
		);
	// - -------------------------------------------------------------------------------------- - //

public:	
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> RotateCW( const Grid2D<tType>& Src ) {
		// NOTE: Height Width, not Width Height, due to rotation //
		Grid2D<tType> NewGrid( Src.Height(), Src.Width() );
		
		szt SrcHeight = Src.Height();
		for ( szt _y = SrcHeight; _y--; ) {
			for ( szt _x = Src.Width(); _x--; ) {
				NewGrid( (SrcHeight-1)-_y, _x ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> RotateCCW( const Grid2D<tType>& Src ) {
		// NOTE: Height Width, not Width Height, due to rotation //
		Grid2D<tType> NewGrid( Src.Height(), Src.Width() );
		
		szt SrcWidth = Src.Width();
		for ( szt _y = Src.Height(); _y--; ) {
			for ( szt _x = SrcWidth; _x--; ) {
				NewGrid( _y, (SrcWidth-1)-_x ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> RotateCW( ) {
		return RotateCW( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> RotateCCW( ) {
		return RotateCCW( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> FlipX( const Grid2D<tType>& Src ) {
		Grid2D<tType> NewGrid( Src.Width(), Src.Height() );
		
		szt SrcWidth = Src.Width();
		szt SrcHeight = Src.Height();
		for ( szt _y = SrcHeight; _y--; ) {
			for ( szt _x = SrcWidth; _x--; ) {
				NewGrid( (SrcWidth-1)-_x, _y ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;		
	}
	// - -------------------------------------------------------------------------------------- - //
	static inline const Grid2D<tType> FlipY( const Grid2D<tType>& Src ) {
		Grid2D<tType> NewGrid( Src.Width(), Src.Height() );
		
		szt SrcWidth = Src.Width();
		szt SrcHeight = Src.Height();
		for ( szt _y = SrcHeight; _y--; ) {
			for ( szt _x = SrcWidth; _x--; ) {
				NewGrid( _x, (SrcHeight-1)-_y ) = Src( _x, _y );
			}
		}		
		
		return NewGrid;		
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> FlipX( ) {
		return FlipX( *this );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> FlipY( ) {
		return FlipY( *this );
	}
	// - -------------------------------------------------------------------------------------- - //	

public:
	// - -------------------------------------------------------------------------------------- - //
	// Used by Trim. Determines the first rows and columns containing something not "Unused". //
	// - -------------------------------------------------------------------------------------- - //	
	inline const szt FindUnusedX1( const tType& Unused = tType() ) const {
		szt x1 = 0;
		
		bool BlockFound = false;
		for ( szt _x = 0; _x < Width(); _x++ ) {
			x1 = _x;
			// For every item in the vertical row //
			for ( szt _y = Height(); _y--; ) {
				// Test if it's not our Unused //
				if ( operator()( _x, _y ) != Unused )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return x1;
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const szt FindUnusedY1( const tType& Unused = tType() ) const {
		szt y1 = 0;
		
		bool BlockFound = false;
		for ( szt _y = 0; _y < Height(); _y++ ) {
			y1 = _y;
			// For every item in the vertical row //
			for ( szt _x = Width(); _x--; ) {
				// Test if it's not our Unused //
				if ( operator()( _x, _y ) != Unused )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return y1;
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const szt FindUnusedX2( const tType& Unused = tType() ) const {
		szt x2 = 0;
		
		bool BlockFound = false;
		for ( int _x = Width() - 1; _x >= 0; _x-- ) {
			x2 = _x;
			// For every item in the vertical row //
			for ( szt _y = Height(); _y--; ) {
				// Test if it's not our Unused //
				if ( operator()( _x, _y ) != Unused )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return x2;
	}
	// - -------------------------------------------------------------------------------------- - //	
	inline const szt FindUnusedY2( const tType& Unused = tType() ) const {
		szt y2 = 0;
		
		bool BlockFound = false;
		for ( int _y = Height() - 1; _y >= 0; _y-- ) {
			y2 = _y;
			// For every item in the vertical row //
			for ( int _x = Width(); _x--; ) {
				// Test if it's not our Unused //
				if ( operator()( _x, _y ) != Unused )
					BlockFound = true;
			}
			// If a block was found, bail from this //
			if ( BlockFound )
				break;
		}
		
		return y2;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Used to remove (trim) unused space around edge of a grid. //
	// i.e. Like Paint Shop Pro's copy->paste new->copy->paste new trick. //
	// - -------------------------------------------------------------------------------------- - //	
	static inline const Grid2D<tType> Trim( const Grid2D<tType>& Src, const tType& Unused = tType() ) {
		szt x1 = Src.FindUnusedX1(Unused);
		szt y1 = Src.FindUnusedY1(Unused);
		szt x2 = Src.FindUnusedX2(Unused);
		szt y2 = Src.FindUnusedY2(Unused);

		// Plus one, because we're doing x&y pairs, not width&height //
		szt NewWidth = x2 - x1 + 1;
		szt NewHeight = y2 - y1 + 1;
	
		return Copy( Src, x1, y1, NewWidth, NewHeight );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> Trim( const tType& Unused = tType() ) {
		return Trim( *this, Unused );
	}
	// - -------------------------------------------------------------------------------------- - //	

/*
	// - -------------------------------------------------------------------------------------- - //	
	// NOTE: This returns a cropped region... is this unnecessary? //
	// - -------------------------------------------------------------------------------------- - //	
	static inline const Grid2D<tType> Crop( const Grid2D<tType>& Src, int x1, int y1, int x2, int y2 ) {
		// Saturate the coordinates (i.e. make them fit within (0->Width,0->Height) range) //
		x1 = Src.AxisSaturateX( x1 );
		y1 = Src.AxisSaturateY( y1 );
		x2 = Src.AxisSaturateX( x2 );
		y2 = Src.AxisSaturateY( y2 );
		
		Sort( x1, x2 );
		Sort( y1, y2 );
		
		// This is plus one because it's X+Y pairs, not Width+Height. //
		szt Width = x2 - x1 + 1;
		szt Height = y2 - y1 + 1;
			
		Grid2D<tType> Ret( Width, Height );
		Copy( Src, Ret, x1, y1, 0, 0 );
		return Ret;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType> Crop( const int x1, const int y1, const int x2, const int y2 ) {	
		return Crop( *this, x1, y1, x2, y2 );
	}
	// - -------------------------------------------------------------------------------------- - //
*/		
public:
	// - -------------------------------------------------------------------------------------- - //
	// Like a Canvas Resize in Paint Shop Pro (i.e. no filtering, no scaling, just cropping) //
	// TopLeft is (-1,-1), Center is (0,0), BottomRight is (+1,+1) //
	inline void Resize( const szt NewWidth, const szt NewHeight, const int XAlign = 0, const int YAlign = 0, const tType& InitValue = tType() ) {
		int SrcStartX;
		int DestStartX;

		// Align the X Axis //
		if ( XAlign == 0 ) {
			// Center the X //
			if ( NewWidth > Width() ) {
				SrcStartX = 0;
				DestStartX = (NewWidth - Width()) >> 1;
			}
			else {
				SrcStartX = (Width() - NewWidth) >> 1;
				DestStartX = 0;
			}
		}
		else if ( XAlign < 0 ) {
			// Left Align the Positions //
			SrcStartX = 0;
			DestStartX = 0;
		}
		else if ( XAlign > 0 ) {
			// Right Align the Positions //
			if ( NewWidth > Width() ) {
				SrcStartX = 0;
				DestStartX = (NewWidth - Width());
			}
			else {
				SrcStartX = (Width() - NewWidth);
				DestStartX = 0;
			}			
		}
		
		
		int SrcStartY;
		int DestStartY;

		// Align the Y Axis //
		if ( YAlign == 0 ) {
			// Center the Y //
			if ( NewHeight > Height() ) {
				SrcStartY = 0;
				DestStartY = (NewHeight - Height()) >> 1;
			}
			else {
				SrcStartY = (Height() - NewHeight) >> 1;
				DestStartY = 0;
			}
		}
		else if ( YAlign < 0 ) {
			// Left Align the Positions //
			SrcStartY = 0;
			DestStartY = 0;
		}
		else if ( YAlign > 0 ) {
			// Right Align the Positions //
			if ( NewHeight > Height() ) {
				SrcStartY = 0;
				DestStartY = NewHeight - Height();
			}
			else {
				SrcStartY = (Height() - NewHeight);
				DestStartY = 0;
			}	
		}		
		
		// Copy the data //
		Grid2D<tType> Ret( NewWidth, NewHeight, InitValue );
		Copy( *this, Ret, SrcStartX, SrcStartY, DestStartX, DestStartY );
		*this = Ret;
	}
	// - -------------------------------------------------------------------------------------- - //

	// NOTE: I'm almost certain these are useless //
/*
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidth( const szt NewWidth, const tType& InitValue = tType() ) {
		SetWidthCenter( NewWidth, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthCenter( const szt NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Center the Positions //
		if ( NewWidth > Width() ) {
			SrcStart = 0;
			DestStart = (NewWidth - Width()) >> 1;
		}
		else {
			SrcStart = (Width() - NewWidth) >> 1;
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, Height(), SrcStart, 0, DestStart, 0, InitValue ) );
		w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthLeft( const szt NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Left Align the Positions //
		SrcStart = 0;
		DestStart = 0;

		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, Height(), SrcStart, 0, DestStart, 0, InitValue ) );
		w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetWidthRight( const szt NewWidth, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Right Align the Positions //
		if ( NewWidth > Width() ) {
			SrcStart = 0;
			DestStart = (NewWidth - Width());
		}
		else {
			SrcStart = (Width() - NewWidth);
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, NewWidth, Height(), SrcStart, 0, DestStart, 0, InitValue ) );
		w = NewWidth;
	}
	// - -------------------------------------------------------------------------------------- - //
	

	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeight( const szt NewHeight, const tType& InitValue = tType() ) {
		SetHeightCenter( NewHeight, InitValue );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightCenter( const szt NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Center the Positions //
		if ( NewHeight > Height() ) {
			SrcStart = 0;
			DestStart = (NewHeight - Height()) >> 1;
		}
		else {
			SrcStart = (Height() - NewHeight) >> 1;
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, Width(), NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightTop( const szt NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Left Align the Positions //
		SrcStart = 0;
		DestStart = 0;

		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, Width(), NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SetHeightBottom( const szt NewHeight, const tType& InitValue = tType() ) {
		int SrcStart;
		int DestStart;
		
		// Right Align the Positions //
		if ( NewHeight > Height() ) {
			SrcStart = 0;
			DestStart = (NewHeight - Height());
		}
		else {
			SrcStart = (Height() - NewHeight);
			DestStart = 0;
		}
		
		// Copy the data and set the new dimensions //
		SetData( CopyData( *this, Width(), NewHeight, 0, SrcStart, 0, DestStart, InitValue ) );
		h = NewHeight;
	}
	// - -------------------------------------------------------------------------------------- - //
*/
public:
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of instances of a value //
	inline const szt CountEq( const tType& Value ) const {
		szt CurrentCount = 0;

		for ( szt idx = Size(); idx--; ) {
			if ( Data[idx] == Value )
				CurrentCount++;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const szt CountNEq( const tType& Value ) const {
		szt CurrentCount = 0;

		for ( szt idx = Size(); idx--; ) {
			if ( Data[idx] != Value )
				CurrentCount++;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const szt CountGt( const tType& Value ) const {
		szt CurrentCount = 0;

		for ( szt idx = Size(); idx--; ) {
			if ( Data[idx] > Value )
				CurrentCount++;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const szt CountLt( const tType& Value ) const {
		szt CurrentCount = 0;

		for ( szt idx = Size(); idx--; ) {
			if ( Data[idx] < Value )
				CurrentCount++;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const szt CountGte( const tType& Value ) const {
		szt CurrentCount = 0;

		for ( szt idx = Size(); idx--; ) {
			if ( Data[idx] >= Value )
				CurrentCount++;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the number of non instances of a value //
	inline const szt CountLte( const tType& Value ) const {
		szt CurrentCount = 0;

		for ( szt idx = Size(); idx--; ) {
			if ( Data[idx] <= Value )
				CurrentCount++;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const szt CountAdjacentX( int x, int y ) const {
		szt CurrentCount = 1;
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		tType Value = operator()( x, y );

		for ( int _x = x; _x-- > 0; ) {
			if ( operator()( _x, y ) == Value )
				CurrentCount++;
			else
				break;
		}

		for ( int _x = x; ++_x < Width(); ) {
			if ( operator()( _x, y ) == Value )
				CurrentCount++;
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const szt CountAdjacentY( int x, int y ) const {
		szt CurrentCount = 1;
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		tType Value = operator()( x, y );

		for ( int _y = y; _y-- > 0; ) {
			if ( operator()( x, _y ) == Value )
				CurrentCount++;
			else
				break;
		}

		for ( int _y = y; ++_y < Height(); ) {
			if ( operator()( x, _y ) == Value )
				CurrentCount++;
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const szt CountAdjacentX( int x, int y, const tType& Value ) const  {
		if ( Saturate( x, y ) != Value )
			return 0;
		else
			return CountAdjacentX( x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles equal to the tile we point to. //
	inline const szt CountAdjacentY( int x, int y, const tType& Value ) const {
		if ( Saturate( x, y ) != Value )
			return 0;
		else
			return CountAdjacentY( x, y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Clear the number of instances of tiles equal to the tile we point to. //
	inline const szt ClearAdjacentX( int x, int y ) const {
		szt CurrentCount = 1;
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		tType Value = operator()( x, y );
		operator()( x, y ) = 0;

		for ( int _x = x; _x-- > 0; ) {
			if ( operator()( _x, y ) == Value ) {
				operator()( _x, y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}

		for ( int _x = x; ++_x < Width(); ) {
			if ( operator()( _x, y ) == Value ) {
				operator()( _x, y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Clear the number of instances of tiles equal to the tile we point to. //
	inline const szt ClearAdjacentY( int x, int y ) const {
		szt CurrentCount = 1;
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		tType Value = operator()( x, y );
		operator()( x, y ) = 0; 

		for ( int _y = y; _y-- > 0; ) {
			if ( operator()( x, _y ) == Value ) {
				operator()( x, _y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}

		for ( int _y = y; ++_y < Height(); ) {
			if ( operator()( x, _y ) == Value ) {
				operator()( x, _y ) = 0;
				CurrentCount++;
			}
			else
				break;
		}
		
		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles on a line //
	inline const szt CountLineX( int y, const tType& Value ) const {
		szt CurrentCount = 0;
		y = AxisSaturateY( y );

		for ( int _x = Width(); _x--; ) {
			if ( operator()( _x, y ) == Value )
				CurrentCount++;
		}

		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Count the number of instances of tiles on a line //
	inline const szt CountLineY( int x, const tType& Value ) const {
		szt CurrentCount = 0;
		x = AxisSaturateY( x );

		for ( int _y = Height(); _y--; ) {
			if ( operator()( x, _y ) == Value )
				CurrentCount++;
		}

		return CurrentCount;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first occurence of Value starting at point x,y //
	inline const int FirstX( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; x < Width(); x++ ) {
			if ( operator()( x, y ) == Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first occurence of Value starting at point x,y //
	inline const int FirstY( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; y < Height(); y++ ) {
			if ( operator()( x, y ) == Value )
				return y;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last occurence of Value starting at point x,y //
	inline const int LastX( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; x--; ) {
			if ( operator()( x, y ) == Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last occurence of Value starting at point x,y //
	inline const int LastY( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; y--; ) {
			if ( operator()( x, y ) == Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// NOTE: The "Not" may be confusing, since it's Not Equality, not Not X (i.e. Y). //
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first non occurence of Value starting at point x,y //
	inline const int FirstNotX( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; x < Width(); x++ ) {
			if ( operator()( x, y ) != Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first non occurence of Value starting at point x,y //
	inline const int FirstNotY( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; y < Height(); y++ ) {
			if ( operator()( x, y ) != Value )
				return y;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last non occurence of Value starting at point x,y //
	inline const int LastNotX( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; x--; ) {
			if ( operator()( x, y ) != Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last non occurence of Value starting at point x,y //
	inline const int LastNotY( int x, int y, const tType& Value ) const {
		x = AxisSaturateX( x );
		y = AxisSaturateY( y );
		for ( ; y--; ) {
			if ( operator()( x, y ) != Value )
				return x;
		}
		return -1;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first occurence of Value on a line //
	inline const int FirstXOnLine( int y, const tType& Value ) const {
		return FirstX( 0, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first occurence of Value on a line //
	inline const int FirstYOnLine( int x, const tType& Value ) const {
		return FirstY( x, 0, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last occurence of Value on a line //
	inline const int LastXOnLine( int y, const tType& Value ) const {
		// NOTE: 'cause LastX does clipping, you could technically pass Width directly // 
		return LastX( Width() - 1, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last occurence of Value on a line //
	inline const int LastYOnLine( int x, const tType& Value ) const {
		// NOTE: 'cause LastY does clipping, you could technically pass Height directly //
		return LastY( x, Height() - 1, Value );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// NOTE: The "Not" may be confusing, since it's Not Equality, not Not X (i.e. Y). //
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the first occurence of not Value on a line //
	inline const int FirstNotXOnLine( int y, const tType& Value ) const {
		return FirstNotX( 0, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the first occurence of not Value on a line //
	inline const int FirstNotYOnLine( int x, const tType& Value ) const {
		return FirstNotY( x, 0, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "x index" of the last occurence of not Value on a line //
	inline const int LastNotXOnLine( int y, const tType& Value ) const {
		// NOTE: 'cause LastX does clipping, you could technically pass Width directly // 
		return LastNotX( Width() - 1, y, Value );
	}
	// - -------------------------------------------------------------------------------------- - //
	// Return the "y index" of the last occurence of not Value on a line //
	inline const int LastNotYOnLine( int x, const tType& Value ) const {
		// NOTE: 'cause LastY does clipping, you could technically pass Height directly //
		return LastNotY( x, Height() - 1, Value );
	}
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Grid2D_Class_Adjacency.h //
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<int> GenerateAdjacentXAdjacencyGrid( int x, int y, const tType& Value ) const;
	inline const Grid2D<int> GenerateAdjacentYAdjacencyGrid( int x, int y, const tType& Value ) const;
	inline const Grid2D<int> GenerateAdjacentXAdjacencyGrid( const int x, const int y ) const;
	inline const Grid2D<int> GenerateAdjacentYAdjacencyGrid( const int x, const int y ) const;
	// In the case of rows and columns, an Adjacency Grid is exactly the same as a Distance Grid (i.e. wrappers) //
	inline const Grid2D<int> GenerateAdjacentXDistanceGrid( const int x, const int y, const tType& Value ) const;
	inline const Grid2D<int> GenerateAdjacentYDistanceGrid( const int x, const int y, const tType& Value ) const;
	inline const Grid2D<int> GenerateAdjacentXDistanceGrid( const int x, const int y ) const;
	inline const Grid2D<int> GenerateAdjacentYDistanceGrid( const int x, const int y ) const;
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Grid2D_Class_Draw.h //
	// - -------------------------------------------------------------------------------------- - //
	inline void _DrawHLine( const int x, const int y, const int _w, const tType& Value = tType() );
	inline void DrawHLine( int x, const int y, int _w, const tType& Value = tType() );
	inline void _DrawVLine( const int x, const int y, const int _h, const tType& Value = tType() );
	inline void DrawVLine( const int x, int y, int _h, const tType& Value = tType() );
	inline void DrawRect( const int x, const int y, const int _w, const int _h, const tType& Value = tType() );
	inline void DrawRectFill( int x, int y, int _w, int _h, const tType& Value = tType() );
	inline void DrawLine( int x1, int y1, int x2, int y2, const tType& Value = tType() );
	// - -------------------------------------------------------------------------------------- - //

public:
	// - -------------------------------------------------------------------------------------- - //
	// Grid2D_Class_Drop.h //
	// - -------------------------------------------------------------------------------------- - //
	inline const int CanDrop( int x, int y, const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const;
	inline const int CanRockfordDrop( int x, int y, const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const;
	inline const int CalcDropDistance( int x, int y, int OffsetX = 0, int OffsetY = 1, const tType& Value = tType() ) const;
	inline const Grid2D<int> GenerateDropGrid( const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const;
	inline const Grid2D<int> GenerateRockfordDropGrid( const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const;
	inline const Grid2D<int> GenerateDropDistanceGrid( const int OffsetX = 0, const int OffsetY = 1, const tType& Value = tType() ) const;
	// - -------------------------------------------------------------------------------------- - //
	inline void ApplyDrop( const int x, const int y, const int OffsetX = 0, const int OffsetY = 1 );
	inline void ApplyDropDistance( const int x, const int y, const int Distance, const int OffsetX = 0, const int OffsetY = 1 );
	inline void ApplyRockfordDrop( const int x, const int y, const int DropType, const int OffsetX = 0, const int OffsetY = 1 );
	inline void Drop( const int OffsetX = 0, const int OffsetY = 1 );
	inline void DoDropDistance( const int OffsetX = 0, const int OffsetY = 1 );
	inline void RockfordDrop( const int OffsetX = 0, const int OffsetY = 1 );
	inline const bool CanISet( const int x, const int y, const tType Value = 0 ) const;
	inline const bool CanIDrop( const int _Index, const int OffsetX, const int OffsetY ) const;
	inline bool AddDrop( const int _Index, const int OffsetX, const int OffsetY, const tType& Value );
	inline bool AddDropDistance( const int _Index, const int OffsetX, const int OffsetY, const tType& Value );
	inline bool AddRockfordDrop( const int _Index, const int OffsetX, const int OffsetY, const tType& Value );
	// - -------------------------------------------------------------------------------------- - //
	inline const int EdgeDistanceIndex( const int _Index, const int OffsetX, const int OffsetY );
	inline tType& EdgeDistance( const int _Index, const int OffsetX, const int OffsetY );
	// - -------------------------------------------------------------------------------------- - //


public:
	// - -------------------------------------------------------------------------------------- - //
	inline const tType GetLowest() const {
		tType Value;
		if ( Size() ) {
			Value = Data[0];
			for ( szt idx = 1; idx < Size(); idx++ ) {
				if ( Data[idx] < Value ) {
					Value = Data[idx];
				}
			}
		}
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const tType GetHighest() const {
		tType Value;
		if ( Size() ) {
			Value = Data[0];
			for ( szt idx = 1; idx < Size(); idx++ ) {
				if ( Data[idx] > Value ) {
					Value = Data[idx];
				}
			}
		}
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const ABSet<tType> GetRange() const {
		ABSet<tType> Value;
		if ( Size() ) {
			Value.a = Data[0];
			Value.b = Data[0];
			for ( szt idx = 1; idx < Size(); idx++ ) {
				if ( Data[idx] < Value.a ) {
					Value.a = Data[idx];
				}
				else if ( Data[idx] > Value.b ) {
					Value.b = Data[idx];
				}
			}
		}
		return Value;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Uses Reciprocal Optimization //
	inline void _EqualizeData( const tType One = 1.0f, const tType Zero = 0.0f ) {
		ABSet<tType> Range = GetRange();
		tType Diff = Range.b - Range.a;
		if ( Diff != Zero ) {
			tType DiffR = One / Diff;
	
			for ( szt idx = 0; idx < Size(); idx++ ) {
				Data[idx] = (Data[idx] - Range.a) * DiffR;
			}
		}
		else {
			// In the rare case there is no actual difference, make all 0.5 //
			tType Half = One / (One+One);
			
			for ( szt idx = 0; idx < Size(); idx++ ) {
				Data[idx] = Half;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void EqualizeData( const tType One = 1.0f, const tType Zero = 0.0f ) {
		ABSet<tType> Range = GetRange();
		tType Diff = Range.b - Range.a;
		if ( Diff != Zero ) {	
			for ( szt idx = 0; idx < Size(); idx++ ) {
				Data[idx] = (Data[idx] - Range.a) / Diff;
			}
		}
		else {
			// In the rare case there is no actual difference, make all 0.5 //
			tType Half = One / (One+One);
			
			for ( szt idx = 0; idx < Size(); idx++ ) {
				Data[idx] = Half;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	// Was ClipData //
	inline void SaturateData( const tType Low = 0.0f, const tType High = 1.0f ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			if ( Data[idx] < Low ) {
				Data[idx] = Low;
			}
			else if ( Data[idx] > High ) {
				Data[idx] = High;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void RoundData( const tType Middle = 0.5f, const tType Min = 0.0f, const tType Max = 1.0f ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			if ( Data[idx] >= Middle ) {
				Data[idx] = Max;
			}
			else if ( Data[idx] < Middle ) {
				Data[idx] = Min;
			}
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	// Steps will be the number of different values to have between 0 and 1 (inclusive) //
	inline void StepData( const int Steps, const tType One = 1.0f ) {
		Assert( Steps <= 1, "Steps must be 2 or more" );
		tType StepSize = One / (tType)(Steps-1);
		
		for ( szt idx = 0; idx < Size(); idx++ ) {
			tType Val = Data[idx];
			Val /= StepSize;
			
			Data[idx] = round(Val) * StepSize;
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void SoftenRigidData( const int Threshold = 2 ) {
		// Fill in holes and hills that are alone //
		for ( szt y = 0; y < Height(); y++ ) {
			for ( szt x = 0; x < Width(); x++ ) {
				int Common = 1;
				tType No = Wrap(x-1,y);
				
				if ( Wrap(x-1,y) == operator()(x,y) )
					Common++;
//				else
//					No = Wrap(x-1,y)
				if ( Wrap(x+1,y) == operator()(x,y) )
					Common++;
				else
					No = Wrap(x+1,y);
				if ( Wrap(x,y-1) == operator()(x,y) )
					Common++;
				else
					No = Wrap(x,y-1);
				if ( Wrap(x,y+1) == operator()(x,y) )
					Common++;
				else
					No = Wrap(x,y+1);

				if ( Wrap(x-1,y-1) == operator()(x,y) )
					Common++;
				if ( Wrap(x+1,y-1) == operator()(x,y) )
					Common++;
				if ( Wrap(x-1,y+1) == operator()(x,y) )
					Common++;
				if ( Wrap(x+1,y+1) == operator()(x,y) )
					Common++;
				
				// NOTE: This isn't perfect. The data read should be a NOT tile. //
				if ( Common <= Threshold ) {
					operator()(x,y) = No;
				}
			}		
		}
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator += ( const tType Value ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] += Value;
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator -= ( const tType Value ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] -= Value;
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator *= ( const tType Value ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] *= Value;
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator /= ( const tType Value ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] /= Value;
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator += ( const Grid2D<tType>& Vs ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] += Vs[idx];
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator -= ( const Grid2D<tType>& Vs ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] -= Vs[idx];
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator *= ( const Grid2D<tType>& Vs ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] *= Vs[idx];
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Grid2D<tType>& operator /= ( const Grid2D<tType>& Vs ) {
		for ( szt idx = 0; idx < Size(); idx++ ) {
			Data[idx] /= Vs[idx];
		}
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A type for creating a reference or fake Grid2D //
// It exists to be used as a proxy for calling Grid2D functions on arbitrary data. //
// i.e. Grid2DRef MyGrid(10,10,Blah); return MyGrid.ToGrid2D()->GetLowest();
// - ------------------------------------------------------------------------------------------ - //
template< typename tType >
class Grid2DRef {
public:
	szt w, h;		// Dimensions //
	tType* Data;	// Data Array //	

public:
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2DRef( const szt _w, const szt _h ) :
		w( _w ),
		h( _h ),
		Data( 0 )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2DRef( const szt _w, const szt _h, tType* _Data ) :
		w( _w ),
		h( _h ),
		Data( _Data )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Grid2DRef( const Grid2D<tType>& Orig ) :
		w( Orig.Width() ),
		h( Orig.Height() ),
		Data( *Orig )
	{
	}
	// - -------------------------------------------------------------------------------------- - //		

public:
	inline Grid2D<tType>* ToGrid2D() {
		return (Grid2D<tType>*)this;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL2_GRID_GRID2D_CLASS_H__ //
// - ------------------------------------------------------------------------------------------ - //
