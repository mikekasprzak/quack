// - ------------------------------------------------------------------------------------------ - //
// Vector2D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector2D_H__
#define __Geometry_Vector2D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>
#include <External/boost/operators.hpp>

#include <Math/Real.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Vector2D& operator _OP_ ( const Vector2D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Vector2D& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class Vector2D : 
	boost::additive<Vector2D,
	boost::arithmetic2<Vector2D, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real x, y;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Vector2D Identity;
	static const Vector2D One;
	static const Vector2D Zero;
	static const Vector2D Half;
	static const Vector2D Quarter;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Vector2D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector2D( const Real& _x, const Real& _y ) :
		x( _x ),
		y( _y )
	{
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Set( const Real& _x, const Real& _y ) {
		x = _x;
		y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Set( const Vector2D& _v ) {
		*this = _v;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators - The rest will be handled by Boost //
	// - -------------------------------------------------------------------------------------- - //
	// Vector //
	OVERLOAD_SYMBOLEQUALS_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( -= );
	// OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	// OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Real dot( const Vector2D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Real dot( const Vector2D& a, const Vector2D& b ) {
		return (a.x * b.x) + (a.y * b.y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Component-wise Multipy (no longer dot product) //
//	inline const Vector2D operator * ( const Vector2D& _Vs ) const {
//		return Vector2D( (x * _Vs.x), (y * _Vs.y) );
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Like the GLSL parallel, blends between two vectors by alpha (0 = a returned, 1 = b returned) //
	inline const Vector2D mix( const Vector2D& _Vs, const Real Alpha ) const {
		return ((*this) * (Real::One - Alpha)) + (_Vs * Alpha);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline static const Vector2D mix( const Vector2D& a, const Vector2D& b, const Real Alpha ) {
		return (a * (Real::One - Alpha)) + (b * Alpha);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const Vector2D operator - ( ) const {
		return Vector2D( -x, -y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Real SumOf() const {
		return x+y;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real ProductOf() const {
		return x*y;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Scalar //
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline bool operator == ( const Vector2D& _Vs ) const {
		if ( (x - _Vs.x).IsZero() )
			return (y - _Vs.y).IsZero();
		return false;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& Normalize() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real NormalizeRet() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Vector2D Normal() const {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
		
		Vector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Real Magnitude() const {
		Real Mag( MagnitudeSquared() );
//		Mag = Mag.Sqrt();
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
		else
			return Mag.Sqrt_();
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Real MagnitudeSquared() const {
		return (x * x) + (y * y);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Manhattan Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& ManhattanNormalize() {
		Real Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real ManhattanNormalizeRet() {
		Real Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Vector2D ManhattanNormal() const {
		Real Mag( Manhattan() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
		
		Vector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return x.Abs() + y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Maxitude Functions -- Chebyshev Distance, Uniform Normal -- http://en.wikipedia.org/wiki/Chebyshev_distance //
	// http://en.wikipedia.org/wiki/Norm_%28mathematics%29#Maximum_norm_.28special_case_of:_infinity_norm.2C_uniform_norm.2C_or_supremum_norm.29 //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MaxitudeNormalize() {
		Real Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real MaxitudeNormalizeRet() {
		Real Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Vector2D MaxitudeNormal() const {
		Real Mag( Maxitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
		
		Vector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The greatest absolute value part //
	inline const Real Maxitude() const {
		return x.Abs() > y.Abs() ? x.Abs() : y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Minitude Functions (Axitude? Always the distance from the axis (i.e. 0 if on axis)) //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MinitudeNormalize() {
		Real Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real MinitudeNormalizeRet() {
		Real Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Real::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Vector2D MinitudeNormal() const {
		Real Mag( Minitude() );
	
		if ( Mag.IsZeroOrLess() )
			return Vector2D::Zero;
		
		Vector2D Result( *this );
		Result /= Mag;
		
		return Result;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The smallest absolute value part //
	inline const Real Minitude() const {
		return x.Abs() < y.Abs() ? x.Abs() : y.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// No Cross product, as we instead have tangents //
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MinClamp( const Vector2D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MaxClamp( const Vector2D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MinClamp( const Real& _x, const Real& _y ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D& MaxClamp( const Real& _x, const Real& _y ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Min( const Vector2D& _Vs ) const {
		Vector2D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Max( const Vector2D& _Vs ) const {
		Vector2D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Min( const Real& _x, const Real& _y ) const {
		Vector2D Vec = *this;
		Vec.MinClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D Max( const Real& _x, const Real& _y ) const {
		Vector2D Vec = *this;
		Vec.MaxClamp( _x, _y );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const Vector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()) > Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const Vector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()) < Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const Vector2D& _Vs ) const {
		return dot((*this), _Vs.Tangent()).IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		return x.IsZero() && y.IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroOrLess() const {
		return x.IsZeroOrLess() && y.IsZeroOrLess();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Returns true if this vector is axis aligned, but false if a zero vector //
	inline const bool IsAxisAligned() const {
		int Zeroes = 0;
		if ( x.IsZero() )
			Zeroes++;
		if ( y.IsZero() )
			Zeroes++;
			
		return Zeroes == 1;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Return a special vector only with the x or y part that is largest //
	// If you want this normalized, you must normalize it yourself, appropriately //
	inline const Vector2D AxisAligned() const {
		if ( x.Abs() >= y.Abs() )
			return Vector2D( x, 0 );
		else
			return Vector2D( 0, y );
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// Specific Functions that apply to this type //
	// - -------------------------------------------------------------------------------------- - //
	// Normally I have clockwise and counterclockwise variants, but potential changes in the //
	//   Mapping co-ordinates make counterclockwise clockwise, and vice versa.  So instead, use //
	//   Tangent() and -Tangent() for the respected sides. //
	inline const Vector2D Tangent() const {
		return Vector2D( y, -x );
	}
	// - -------------------------------------------------------------------------------------- - //
	// A 45 degree rotation of a vector.  Negating doesn't flip this, you want the -Tangent() of //
	//   the rotation. i.e. -v.Rotate45().Tangent().  Alternatively, RotateNegative45() does this //
	inline const Vector2D Rotate45() const {
		return Vector2D( x + y, y - x ) * Real::Sine45;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D RotateNegative45() const {
		return Vector2D( x - y, y + x ) * Real::Sine45;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline static const Vector2D Angle( const Real _Angle ) {
		return Vector2D( Real::Sin(_Angle), -Real::Cos(_Angle) );
	}
	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D FlipX() {
		return Vector2D( -x, y );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D FlipY() {
		return Vector2D( x, -y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// WARNING: A limit of 64 ToString calls can be made at a time, otherwise returned values may be bad //
	inline const char* ToString() const {
		static char Text[64][128];		// 64 slots, 128 chars long (8,192 bytes). An Int is 10 chars long max. //
		static int CurrentText = 0;
		CurrentText++;
		CurrentText &= 63;
		
		safe_sprintf( Text[CurrentText], sizeof(Text[CurrentText]), "%f,%f", x.ToFloat(), y.ToFloat() );
		return Text[CurrentText];
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Explicit Conversion Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const class Vector3D ToVector3D() const;
	inline const class Vector4D ToVector4D() const;
	inline const class Vector3D ToHomoVector3D() const;
	inline const class Vector4D ToHomoVector4D() const;

	
	inline const class Matrix2x1& ToMatrix2x1() const;
	inline const class Matrix1x2& ToMatrix1x2() const;
//	inline const class Matrix3x1& ToMatrix3x1() const;
//	inline const class Matrix1x3& ToMatrix1x3() const;
//	inline const class Matrix3x1& ToMatrix4x1() const;
//	inline const class Matrix1x3& ToMatrix1x4() const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Projection //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D ApplyMatrix( const class Matrix2x2& ) const;
	inline const Vector2D ApplyMatrix( const class Matrix3x3& ) const;
//	inline const Vector2D ApplyMatrix( const class Matrix2x3& ) const;
//	inline const Vector2D ApplyMatrix( const class Matrix3x2& ) const;
	inline const Vector2D ApplyMatrix( const class Matrix4x4& ) const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D XAxis() const {
		return Vector2D( x, Real::Zero );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector2D YAxis() const {
		return Vector2D( Real::Zero, y );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	#define SWIZZLE2_PROTO( _TYPE, _A, _B ) \
		inline const _TYPE _A ## _B () const;
	#define SWIZZLE3_PROTO( _TYPE, _A, _B, _C ) \
		inline const _TYPE _A ## _B ## _C () const;
	#define SWIZZLE4_PROTO( _TYPE, _A, _B, _C, _D ) \
		inline const _TYPE _A ## _B ## _C ## _D() const;
	// - -------------------------------------------------------------------------------------- - //
	#define _SWIZZLE2_PROTO( _TYPE, _A, _B ) \
		inline const _TYPE _ ## _A ## _B () const;
	#define _SWIZZLE3_PROTO( _TYPE, _A, _B, _C ) \
		inline const _TYPE _ ## _A ## _B ## _C () const;
	#define _SWIZZLE4_PROTO( _TYPE, _A, _B, _C, _D ) \
		inline const _TYPE _ ## _A ## _B ## _C ## _D() const;
	// - -------------------------------------------------------------------------------------- - //
	SWIZZLE2_PROTO( Vector2D, x,x );
	SWIZZLE2_PROTO( Vector2D, x,y );
	SWIZZLE2_PROTO( Vector2D, y,x );
	SWIZZLE2_PROTO( Vector2D, y,y );

	_SWIZZLE2_PROTO( Vector2D, x,x );
	_SWIZZLE2_PROTO( Vector2D, x,y );
	_SWIZZLE2_PROTO( Vector2D, x,0 );
	_SWIZZLE2_PROTO( Vector2D, x,1 );
	_SWIZZLE2_PROTO( Vector2D, y,x );
	_SWIZZLE2_PROTO( Vector2D, y,y );
	_SWIZZLE2_PROTO( Vector2D, y,0 );
	_SWIZZLE2_PROTO( Vector2D, y,1 );
	_SWIZZLE2_PROTO( Vector2D, 0,x );
	_SWIZZLE2_PROTO( Vector2D, 0,y );
	_SWIZZLE2_PROTO( Vector2D, 0,0 );
	_SWIZZLE2_PROTO( Vector2D, 0,1 );
	_SWIZZLE2_PROTO( Vector2D, 1,x );
	_SWIZZLE2_PROTO( Vector2D, 1,y );
	_SWIZZLE2_PROTO( Vector2D, 1,0 );
	_SWIZZLE2_PROTO( Vector2D, 1,1 );

	SWIZZLE3_PROTO( Vector3D, x,x,x );
	SWIZZLE3_PROTO( Vector3D, x,x,y );
	SWIZZLE3_PROTO( Vector3D, x,y,x );
	SWIZZLE3_PROTO( Vector3D, x,y,y );
	SWIZZLE3_PROTO( Vector3D, y,x,x );
	SWIZZLE3_PROTO( Vector3D, y,x,y );
	SWIZZLE3_PROTO( Vector3D, y,y,x );
	SWIZZLE3_PROTO( Vector3D, y,y,y );

	_SWIZZLE3_PROTO( Vector3D, x,x,x );
	_SWIZZLE3_PROTO( Vector3D, x,x,y );
	_SWIZZLE3_PROTO( Vector3D, x,x,0 );
	_SWIZZLE3_PROTO( Vector3D, x,x,1 );
	_SWIZZLE3_PROTO( Vector3D, x,y,x );
	_SWIZZLE3_PROTO( Vector3D, x,y,y );
	_SWIZZLE3_PROTO( Vector3D, x,y,0 );
	_SWIZZLE3_PROTO( Vector3D, x,y,1 );
	_SWIZZLE3_PROTO( Vector3D, x,0,x );
	_SWIZZLE3_PROTO( Vector3D, x,0,y );
	_SWIZZLE3_PROTO( Vector3D, x,0,0 );
	_SWIZZLE3_PROTO( Vector3D, x,0,1 );
	_SWIZZLE3_PROTO( Vector3D, x,1,x );
	_SWIZZLE3_PROTO( Vector3D, x,1,y );
	_SWIZZLE3_PROTO( Vector3D, x,1,0 );
	_SWIZZLE3_PROTO( Vector3D, x,1,1 );
	_SWIZZLE3_PROTO( Vector3D, y,x,x );
	_SWIZZLE3_PROTO( Vector3D, y,x,y );
	_SWIZZLE3_PROTO( Vector3D, y,x,0 );
	_SWIZZLE3_PROTO( Vector3D, y,x,1 );
	_SWIZZLE3_PROTO( Vector3D, y,y,x );
	_SWIZZLE3_PROTO( Vector3D, y,y,y );
	_SWIZZLE3_PROTO( Vector3D, y,y,0 );
	_SWIZZLE3_PROTO( Vector3D, y,y,1 );
	_SWIZZLE3_PROTO( Vector3D, y,0,x );
	_SWIZZLE3_PROTO( Vector3D, y,0,y );
	_SWIZZLE3_PROTO( Vector3D, y,0,0 );
	_SWIZZLE3_PROTO( Vector3D, y,0,1 );
	_SWIZZLE3_PROTO( Vector3D, y,1,x );
	_SWIZZLE3_PROTO( Vector3D, y,1,y );
	_SWIZZLE3_PROTO( Vector3D, y,1,0 );
	_SWIZZLE3_PROTO( Vector3D, y,1,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,x,x );
	_SWIZZLE3_PROTO( Vector3D, 0,x,y );
	_SWIZZLE3_PROTO( Vector3D, 0,x,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,x,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,y,x );
	_SWIZZLE3_PROTO( Vector3D, 0,y,y );
	_SWIZZLE3_PROTO( Vector3D, 0,y,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,y,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,0,x );
	_SWIZZLE3_PROTO( Vector3D, 0,0,y );
	_SWIZZLE3_PROTO( Vector3D, 0,0,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,0,1 );
	_SWIZZLE3_PROTO( Vector3D, 0,1,x );
	_SWIZZLE3_PROTO( Vector3D, 0,1,y );
	_SWIZZLE3_PROTO( Vector3D, 0,1,0 );
	_SWIZZLE3_PROTO( Vector3D, 0,1,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,x,x );
	_SWIZZLE3_PROTO( Vector3D, 1,x,y );
	_SWIZZLE3_PROTO( Vector3D, 1,x,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,x,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,y,x );
	_SWIZZLE3_PROTO( Vector3D, 1,y,y );
	_SWIZZLE3_PROTO( Vector3D, 1,y,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,y,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,0,x );
	_SWIZZLE3_PROTO( Vector3D, 1,0,y );
	_SWIZZLE3_PROTO( Vector3D, 1,0,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,0,1 );
	_SWIZZLE3_PROTO( Vector3D, 1,1,x );
	_SWIZZLE3_PROTO( Vector3D, 1,1,y );
	_SWIZZLE3_PROTO( Vector3D, 1,1,0 );
	_SWIZZLE3_PROTO( Vector3D, 1,1,1 );
	
	SWIZZLE4_PROTO( Vector4D, x,x,x,x );	// *** //
	SWIZZLE4_PROTO( Vector4D, x,x,x,y );
	SWIZZLE4_PROTO( Vector4D, x,x,y,x );
	SWIZZLE4_PROTO( Vector4D, x,x,y,y );
	SWIZZLE4_PROTO( Vector4D, x,y,x,x );
	SWIZZLE4_PROTO( Vector4D, x,y,x,y );
	SWIZZLE4_PROTO( Vector4D, x,y,y,x );
	SWIZZLE4_PROTO( Vector4D, x,y,y,y );
	SWIZZLE4_PROTO( Vector4D, y,x,x,x );
	SWIZZLE4_PROTO( Vector4D, y,x,x,y );
	SWIZZLE4_PROTO( Vector4D, y,x,y,x );
	SWIZZLE4_PROTO( Vector4D, y,x,y,y );
	SWIZZLE4_PROTO( Vector4D, y,y,x,x );
	SWIZZLE4_PROTO( Vector4D, y,y,x,y );
	SWIZZLE4_PROTO( Vector4D, y,y,y,x );
	SWIZZLE4_PROTO( Vector4D, y,y,y,y );

	_SWIZZLE4_PROTO( Vector4D, x,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, x,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, x,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, x,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, x,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, x,1,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, y,x,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,x,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, y,y,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,y,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, y,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, y,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, y,1,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 0,1,1,1 );	
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,0,1,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,x );	// *** //
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,x,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,y,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,0,1 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,x );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,y );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,0 );
	_SWIZZLE4_PROTO( Vector4D, 1,1,1,1 );
	// - -------------------------------------------------------------------------------------- - //
	#undef _SWIZZLE4_PROTO
	#undef _SWIZZLE3_PROTO
	#undef _SWIZZLE2_PROTO
	// - -------------------------------------------------------------------------------------- - //
	#undef SWIZZLE4_PROTO
	#undef SWIZZLE3_PROTO
	#undef SWIZZLE2_PROTO
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D operator - ( const Real& a, const Vector2D& b ) {
	Vector2D Ret( a - b.x, a - b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector2D operator / ( const Real& a, const Vector2D& b ) {
	Vector2D Ret( a / b.x, a / b.y );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// -- ---------------------------------------------------------------------------------------- -- //
// External Vector Operations, for GLSL familiar syntax //
// -- ---------------------------------------------------------------------------------------- -- //
inline const Real dot( const Vector2D& a, const Vector2D& b ) {
	return (a.x * b.x) + (a.y * b.y);
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector2D mix( const Vector2D& a, const Vector2D& b, const Real Alpha ) {
	return (a * (Real::One - Alpha)) + (b * Alpha);
}
// -- ---------------------------------------------------------------------------------------- -- //


// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector2D_H__ //
// - ------------------------------------------------------------------------------------------ - //
