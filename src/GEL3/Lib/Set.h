// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_SET_H__
#define __GEL_LIB_SET_H__
// - ------------------------------------------------------------------------------------------ - //
#define _IF_INDEX_RET( _idx, _vs, _var ) \
	if ( (_idx) == (_vs) ) \
		return _var
// - ------------------------------------------------------------------------------------------ - //
#define _RET( _var ) \
	return _var
// - ------------------------------------------------------------------------------------------ - //
#define _RET_DUMMY() \
	{ \
		static T Dummy; \
		return Dummy; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define _IF_OP( _op, _var ) \
	if ( _var _op Vs._var )
// - ------------------------------------------------------------------------------------------ - //
#define _RET_OP( _op, _var ) \
	return ( _var _op Vs._var )
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// ASet -> ABCDESet //
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class ASet {
	typedef ASet TypeName;
public:
	T a;

	inline ASet( const T _a = T() ) :
		a(_a)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, a );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, a );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_RET_OP( ==, a );
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class ABSet {
	typedef ABSet TypeName;
public:
	T a;
	T b;

	inline ABSet( const T _a = T(), const T _b = T() ) :
		a(_a),
		b(_b)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, a )
		_RET_OP( ==, b );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class ABCSet {
	typedef ABCSet TypeName;
public:
	T a;
	T b;
	T c;

	inline ABCSet( const T _a = T(), const T _b = T(), const T _c = T() ) :
		a(_a),
		b(_b),
		c(_c)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _IF_INDEX_RET( Index, 2, c );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _IF_INDEX_RET( Index, 2, c );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, a )
		_IF_OP( ==, b )
		_RET_OP( ==, c );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class ABCDSet {
	typedef ABCDSet TypeName;
public:
	T a;
	T b;
	T c;
	T d;

	inline ABCDSet( const T _a = T(), const T _b = T(), const T _c = T(), const T _d = T() ) :
		a(_a),
		b(_b),
		c(_c),
		d(_d)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _IF_INDEX_RET( Index, 2, c );
		else _IF_INDEX_RET( Index, 3, d );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _IF_INDEX_RET( Index, 2, c );
		else _IF_INDEX_RET( Index, 3, d );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, a )
		_IF_OP( ==, b )
		_IF_OP( ==, c )
		_RET_OP( ==, d );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class ABCDESet {
	typedef ABCDESet TypeName;
public:
	T a;
	T b;
	T c;
	T d;
	T e;

	inline ABCDESet( const T _a = T(), const T _b = T(), const T _c = T(), const T _d = T(), const T _e = T() ) :
		a(_a),
		b(_b),
		c(_c),
		d(_d),
		e(_e)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _IF_INDEX_RET( Index, 2, c );
		else _IF_INDEX_RET( Index, 3, d );
		else _IF_INDEX_RET( Index, 4, e );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, a );
		else _IF_INDEX_RET( Index, 1, b );
		else _IF_INDEX_RET( Index, 2, c );
		else _IF_INDEX_RET( Index, 3, d );
		else _IF_INDEX_RET( Index, 4, e );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, a )
		_IF_OP( ==, b )
		_IF_OP( ==, c )
		_IF_OP( ==, d )
		_RET_OP( ==, e );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// XSet -> XYZWSet //
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class XSet {
	typedef XSet TypeName;
public:
	T x;

	inline XSet( const T _x = T() ) :
		x(_x)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, x );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, x );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_RET_OP( ==, x );
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class XYSet {
	typedef XYSet TypeName;
public:
	T x;
	T y;

	inline XYSet( const T _x = T(), const T _y = T() ) :
		x(_x),
		y(_y)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, x );
		else _IF_INDEX_RET( Index, 1, y );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, x );
		else _IF_INDEX_RET( Index, 1, y );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, x )
		_RET_OP( ==, y );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class XYZSet {
	typedef XYZSet TypeName;
public:
	T x;
	T y;
	T z;

	inline XYZSet( const T _x = T(), const T _y = T(), const T _z = T() ) :
		x(_x),
		y(_y),
		z(_z)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, x );
		else _IF_INDEX_RET( Index, 1, y );
		else _IF_INDEX_RET( Index, 2, z );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, x );
		else _IF_INDEX_RET( Index, 1, y );
		else _IF_INDEX_RET( Index, 2, z );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, x )
		_IF_OP( ==, y )
		_RET_OP( ==, z );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class XYZWSet {
	typedef XYZWSet TypeName;
public:
	T x;
	T y;
	T z;
	T w;

	inline XYZWSet( const T _x = T(), const T _y = T(), const T _z = T(), const T _w = T() ) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, x );
		else _IF_INDEX_RET( Index, 1, y );
		else _IF_INDEX_RET( Index, 2, z );
		else _IF_INDEX_RET( Index, 3, w );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, x );
		else _IF_INDEX_RET( Index, 1, y );
		else _IF_INDEX_RET( Index, 2, z );
		else _IF_INDEX_RET( Index, 3, w );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, x )
		_IF_OP( ==, y )
		_IF_OP( ==, z )
		_RET_OP( ==, w );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// R, RG, RGB and RGBA //
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class RSet {
	typedef RSet TypeName;
public:
	T r;

	inline RSet( const T _r = T() ) :
		r(_r)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, r );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, r );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_RET_OP( ==, r );
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class RGSet {
	typedef RGSet TypeName;
public:
	T r;
	T g;

	inline RGSet( const T _r = T(), const T _g = T() ) :
		r(_r),
		g(_g)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, r );
		else _IF_INDEX_RET( Index, 1, g );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, r );
		else _IF_INDEX_RET( Index, 1, g );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, r )
		_RET_OP( ==, g );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class RGBSet {
	typedef RGBSet TypeName;
public:
	T r;
	T g;
	T b;

	inline RGBSet( const T _r = T(), const T _g = T(), const T _b = T() ) :
		r(_r),
		g(_g),
		b(_b)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, r );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, b );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, r );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, b );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, r )
		_IF_OP( ==, g )
		_RET_OP( ==, b );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class RGBASet {
	typedef RGBASet TypeName;
public:
	T r;
	T g;
	T b;
	T a;

	inline RGBASet( const T _r = T(), const T _g = T(), const T _b = T(), const T _a = T() ) :
		r(_r),
		g(_g),
		b(_b),
		a(_a)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, r );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, b );
		else _IF_INDEX_RET( Index, 3, a );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, r );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, b );
		else _IF_INDEX_RET( Index, 3, a );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, r )
		_IF_OP( ==, g )
		_IF_OP( ==, b )
		_RET_OP( ==, a );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// B, BG, BGR and BGRA //
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class BSet {
	typedef BSet TypeName;
public:
	T b;

	inline BSet( const T _b = T() ) :
		b(_b)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, b );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, b );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_RET_OP( ==, b );
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class BGSet {
	typedef BGSet TypeName;
public:
	T b;
	T g;

	inline BGSet( const T _b = T(), const T _g = T() ) :
		b(_b),
		g(_g)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, b );
		else _IF_INDEX_RET( Index, 1, g );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, b );
		else _IF_INDEX_RET( Index, 1, g );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, b )
		_RET_OP( ==, g );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class BGRSet {
	typedef BGRSet TypeName;
public:
	T b;
	T g;
	T r;

	inline BGRSet( const T _b = T(), const T _g = T(), const T _r = T() ) :
		b(_b),
		g(_g),
		r(_r)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, b );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, r );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, b );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, r );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, b )
		_IF_OP( ==, g )
		_RET_OP( ==, r );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class BGRASet {
	typedef BGRASet TypeName;
public:
	T b;
	T g;
	T r;
	T a;

	inline BGRASet( const T _b = T(), const T _g = T(), const T _r = T(), const T _a = T() ) :
		b(_b),
		g(_g),
		r(_r),
		a(_a)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, b );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, r );
		else _IF_INDEX_RET( Index, 3, a );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, b );
		else _IF_INDEX_RET( Index, 1, g );
		else _IF_INDEX_RET( Index, 2, r );
		else _IF_INDEX_RET( Index, 3, a );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, b )
		_IF_OP( ==, g )
		_IF_OP( ==, r )
		_RET_OP( ==, a );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// USet -> UVWSet //
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class USet {
	typedef USet TypeName;
public:
	T u;

	inline USet( const T _u = T() ) :
		u(_u)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, u );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, u );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_RET_OP( ==, u );
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class UVSet {
	typedef UVSet TypeName;
public:
	T u;
	T v;

	inline UVSet( const T _u = T(), const T _v = T() ) :
		u(_u),
		v(_v)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, u );
		else _IF_INDEX_RET( Index, 1, v );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, u );
		else _IF_INDEX_RET( Index, 1, v );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, u )
		_RET_OP( ==, v );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class UVWSet {
	typedef UVWSet TypeName;
public:
	T u;
	T v;
	T w;

	inline UVWSet( const T _u = T(), const T _v = T(), const T _w = T() ) :
		u(_u),
		v(_v),
		w(_w)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, u );
		else _IF_INDEX_RET( Index, 1, v );
		else _IF_INDEX_RET( Index, 2, w );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, u );
		else _IF_INDEX_RET( Index, 1, v );
		else _IF_INDEX_RET( Index, 2, w );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, u )
		_IF_OP( ==, v )
		_RET_OP( ==, w );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// WSet -> WHLSet //
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class WSet {
	typedef WSet TypeName;
public:
	T w;

	inline WSet( const T _w = T() ) :
		w(_w)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, w );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, w );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_RET_OP( ==, w );
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class WHSet {
	typedef WHSet TypeName;
public:
	T w;
	T h;

	inline WHSet( const T _w = T(), const T _h = T() ) :
		w(_w),
		h(_h)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, w );
		else _IF_INDEX_RET( Index, 1, h );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, w );
		else _IF_INDEX_RET( Index, 1, h );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, w )
		_RET_OP( ==, h );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
class WHLSet {
	typedef WHLSet TypeName;
public:
	T w;
	T h;
	T l;

	inline WHLSet( const T _w = T(), const T _h = T(), const T _l = T() ) :
		w(_w),
		h(_h),
		l(_l)
	{
	}
	
public:
	inline const T& operator[]( const size_t Index ) const {
		_IF_INDEX_RET( Index, 0, w );
		else _IF_INDEX_RET( Index, 1, h );
		else _IF_INDEX_RET( Index, 2, l );
		else _RET_DUMMY();
	}
	inline T& operator[]( const size_t Index ) {
		_IF_INDEX_RET( Index, 0, w );
		else _IF_INDEX_RET( Index, 1, h );
		else _IF_INDEX_RET( Index, 2, l );
		else _RET_DUMMY();
	}
	inline bool operator==( const TypeName& Vs ) const {
		_IF_OP( ==, w )
		_IF_OP( ==, h )
		_RET_OP( ==, l );
		return false;
	}
	inline bool operator!=( const TypeName& Vs ) const {
		return !operator==(Vs);
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#undef _RET_OP
#undef _IF_OP
#undef _RET_DUMMY
#undef _RET
#undef _IF_INDEX_RET
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_SET_H__ //
// - ------------------------------------------------------------------------------------------ - //
