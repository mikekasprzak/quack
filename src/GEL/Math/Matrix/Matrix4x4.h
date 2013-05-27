// - ------------------------------------------------------------------------------------------ - //
// Matrix4x4 //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Matrix4x4_H__
#define __Geometry_Matrix4x4_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define NOT_GCC
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <External/boost/operators.hpp>

#include <Math/Real.h>
#include <Math/Vector.h>
#include <Math/Matrix/Matrix3x3.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Matrix4x4& operator _OP_ ( const Real& _Vs ) { \
		Array[0] _OP_ _Vs; \
		Array[1] _OP_ _Vs; \
		Array[2] _OP_ _Vs; \
		Array[3] _OP_ _Vs; \
		Array[4] _OP_ _Vs; \
		Array[5] _OP_ _Vs; \
		Array[6] _OP_ _Vs; \
		Array[7] _OP_ _Vs; \
		Array[8] _OP_ _Vs; \
		Array[9] _OP_ _Vs; \
		Array[10] _OP_ _Vs; \
		Array[11] _OP_ _Vs; \
		Array[12] _OP_ _Vs; \
		Array[13] _OP_ _Vs; \
		Array[14] _OP_ _Vs; \
		Array[15] _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// 4 part 4x4 Matrix class //
// - ------------------------------------------------------------------------------------------ - //
class Matrix4x4 :
	boost::multipliable<Matrix4x4,
	boost::arithmetic2<Matrix4x4, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real Array[16];
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Matrix4x4 Identity;
	static const Matrix4x4 Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
#ifdef NOT_GCC
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4()
	{
		Array[0] = Real::One;
		Array[1] = Real::Zero;
		Array[2] = Real::Zero;
		Array[3] = Real::Zero;

		Array[4] = Real::Zero;
		Array[5] = Real::One;
		Array[6] = Real::Zero;
		Array[7] = Real::Zero;

		Array[8] = Real::Zero;
		Array[9] = Real::Zero;
		Array[10] = Real::One;
		Array[11] = Real::Zero;

		Array[12] = Real::Zero;
		Array[13] = Real::Zero;
		Array[14] = Real::Zero;
		Array[15] = Real::One;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( const Vector2D& _v1, const Vector2D& _v2 = Vector2D::Zero, const Vector2D& _v3 = Vector2D::Zero, const Vector2D& _v4 = Vector2D::Zero )
	{
		Array[0] = _v1.x;
		Array[1] = _v1.y;
		Array[2] = Real::Zero;
		Array[3] = Real::Zero;

		Array[4] = _v2.x;
		Array[5] = _v2.y;
		Array[6] = Real::Zero;
		Array[7] = Real::Zero;

		Array[8] = _v3.x;
		Array[9] = _v3.y;
		Array[10] = Real::Zero;
		Array[11] = Real::Zero;

		Array[12] = _v4.x;
		Array[13] = _v4.y;
		Array[14] = Real::Zero;
		Array[15] = Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( const Vector3D& _v1, const Vector3D& _v2 = Vector3D::Zero, const Vector3D& _v3 = Vector3D::Zero, const Vector3D& _v4 = Vector3D::Zero )
	{
		Array[0] = _v1.x;
		Array[1] = _v1.y;
		Array[2] = _v1.z;
		Array[3] = Real::Zero;

		Array[4] = _v2.x;
		Array[5] = _v2.y;
		Array[6] = _v2.z;
		Array[7] = Real::Zero;

		Array[8] = _v3.x;
		Array[9] = _v3.y;
		Array[10] = _v3.z;
		Array[11] = Real::Zero;

		Array[12] = _v4.x;
		Array[13] = _v4.y;
		Array[14] = _v4.z;
		Array[15] = Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( const Vector4D& _v1, const Vector4D& _v2 = Vector4D::Zero, const Vector4D& _v3 = Vector4D::Zero, const Vector4D& _v4 = Vector4D::Zero )
	{
		Array[0] = _v1.x;
		Array[1] = _v1.y;
		Array[2] = _v1.z;
		Array[3] = _v1.w;

		Array[4] = _v2.x;
		Array[5] = _v2.y;
		Array[6] = _v2.z;
		Array[7] = _v2.w;

		Array[8] = _v3.x;
		Array[9] = _v3.y;
		Array[10] = _v3.z;
		Array[11] = _v3.w;

		Array[12] = _v4.x;
		Array[13] = _v4.y;
		Array[14] = _v4.z;
		Array[15] = _v4.w;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( 
		const Real& _e1, const Real& _e2, const Real& _e3, const Real& _e4, 
		const Real& _e5, const Real& _e6, const Real& _e7, const Real& _e8, 
		const Real& _e9, const Real& _e10, const Real& _e11, const Real& _e12, 
		const Real& _e13, const Real& _e14, const Real& _e15, const Real& _e16 
		)
	{
		Array[0] = _e1;
		Array[1] = _e2;
		Array[2] = _e3;
		Array[3] = _e4;

		Array[4] = _e5;
		Array[5] = _e6;
		Array[6] = _e7;
		Array[7] = _e8;

		Array[8] = _e9;
		Array[9] = _e10;
		Array[10] = _e11;
		Array[11] = _e12;

		Array[12] = _e13;
		Array[13] = _e14;
		Array[14] = _e15;
		Array[15] = _e16;
	}
	// - -------------------------------------------------------------------------------------- - //	
//	inline Matrix4x4( const Matrix4x4& Copy ) {
//		Array[0] = Copy.Array[0];
//		Array[1] = Copy.Array[1];
//		Array[2] = Copy.Array[2];
//		Array[3] = Copy.Array[3];
//		
//		Array[4] = Copy.Array[4];
//		Array[5] = Copy.Array[5];
//		Array[6] = Copy.Array[6];
//		Array[7] = Copy.Array[7];		
//
//		Array[8] = Copy.Array[8];
//		Array[9] = Copy.Array[9];
//		Array[10] = Copy.Array[10];
//		Array[11] = Copy.Array[11];	
//
//		Array[12] = Copy.Array[12];
//		Array[13] = Copy.Array[13];
//		Array[14] = Copy.Array[14];
//		Array[15] = Copy.Array[15];
//	}
	// - -------------------------------------------------------------------------------------- - //	
#else // NOT_GCC //
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4():
		Array( (Real[]) { 
			Real::One, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One, Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( const Vector2D& _v1, const Vector2D& _v2 = Vector2D::Zero, const Vector2D& _v3 = Vector2D::Zero, const Vector2D& _v4 = Vector2D::Zero ) :
		Array( (Real[]) { 
			_v1.x, _v1.y, Real::Zero, Real::Zero,
			_v2.x, _v2.y, Real::Zero, Real::Zero,
			_v3.x, _v3.y, Real::Zero, Real::Zero,
			_v4.x, _v4.y, Real::Zero, Real::Zero
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( const Vector3D& _v1, const Vector3D& _v2 = Vector3D::Zero, const Vector3D& _v3 = Vector3D::Zero, const Vector3D& _v4 = Vector3D::Zero ) :
		Array( (Real[]) { 
			_v1.x, _v1.y, _v1.z, Real::Zero,
			_v2.x, _v2.y, _v2.z, Real::Zero,
			_v3.x, _v3.y, _v3.z, Real::Zero,
			_v4.x, _v4.y, _v4.z, Real::Zero
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( const Vector4D& _v1, const Vector4D& _v2 = Vector4D::Zero, const Vector4D& _v3 = Vector4D::Zero, const Vector4D& _v4 = Vector4D::Zero ) :
		Array( (Real[]) { 
			_v1.x, _v1.y, _v1.z, _v1.w,
			_v2.x, _v2.y, _v2.z, _v2.w,
			_v3.x, _v3.y, _v3.z, _v3.w,
			_v4.x, _v4.y, _v4.z, _v4.w
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Matrix4x4( 
		const Real& _e1, const Real& _e2, const Real& _e3, const Real& _e4, 
		const Real& _e5, const Real& _e6, const Real& _e7, const Real& _e8, 
		const Real& _e9, const Real& _e10, const Real& _e11, const Real& _e12, 
		const Real& _e13, const Real& _e14, const Real& _e15, const Real& _e16 
		) :
		Array( (Real[]) {
			_e1, _e2, _e3, _e4, 
			_e5, _e6, _e7, _e8, 
			_e9, _e10, _e11, _e12,
			_e13, _e14, _e15, _e16
			} )
	{
	}
	// - -------------------------------------------------------------------------------------- - //	
//	inline Matrix4x4( const Matrix4x4& Copy ) :
//		Array( (Real[]) {
//			Copy.Array[0], Copy.Array[1], Copy.Array[2], Copy.Array[3],
//			Copy.Array[4], Copy.Array[5], Copy.Array[6], Copy.Array[7],
//			Copy.Array[8], Copy.Array[9], Copy.Array[10], Copy.Array[11],
//			Copy.Array[12], Copy.Array[13], Copy.Array[14], Copy.Array[15]
//			} )
//	{
//	}
	// - -------------------------------------------------------------------------------------- - //	
#endif // NOT_GCC //
	// - -------------------------------------------------------------------------------------- - //	

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators - The rest will be handled by Boost //
	// - -------------------------------------------------------------------------------------- - //
	// Indexing //
	inline Real& operator [] ( const int& idx ) {
		return Array[ idx ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& operator [] ( const int& idx ) const {
		return Array[ idx ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& operator () ( const int& _x, const int& _y ) {
		return Array[ (_y << 2) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& operator () ( const int& _x, const int& _y ) const {
		return Array[ (_y << 2) + _x ];
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Real& Matrix( const int& _x, const int& _y ) {
		return Array[ (_y << 2) + _x ];
	}	
	// - -------------------------------------------------------------------------------------- - //
	inline const Real& Matrix( const int& _x, const int& _y ) const {
		return Array[ (_y << 2) + _x ];
	}	
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Row0() const {
		return Vector4D( Matrix(0,0), Matrix(1,0), Matrix(2,0), Matrix(3,0) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Row1() const {
		return Vector4D( Matrix(0,1), Matrix(1,1), Matrix(2,1), Matrix(3,1) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Row2() const {
		return Vector4D( Matrix(0,2), Matrix(1,2), Matrix(2,2), Matrix(3,2) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Row3() const {
		return Vector4D( Matrix(0,3), Matrix(1,3), Matrix(2,3), Matrix(3,3) );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Column0() const {
		return Vector4D( Matrix(0,0), Matrix(0,1), Matrix(0,2), Matrix(0,3) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Column1() const {
		return Vector4D( Matrix(1,0), Matrix(1,1), Matrix(1,2), Matrix(1,3) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Column2() const {
		return Vector4D( Matrix(2,0), Matrix(2,1), Matrix(2,2), Matrix(2,3) );
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Column3() const {
		return Vector4D( Matrix(3,0), Matrix(3,1), Matrix(3,2), Matrix(3,3) );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Negation Operator //
	inline const Matrix4x4 operator - ( ) const {
		return Matrix4x4(
			-Array[0], -Array[1], -Array[2], -Array[3], 
			-Array[4], -Array[5], -Array[6], -Array[7], 
			-Array[8], -Array[9], -Array[10], -Array[11], 
			-Array[12], -Array[13], -Array[14], -Array[15]
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Matrix //
	// [ 0  1  2  3  ] //
	// [ 4  5  6  7  ] //
	// [ 8  9  10 11 ] //
	// [ 12 13 14 15 ] //
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix4x4& operator *= ( const Matrix4x4& _Vs ) {
		Matrix4x4 Temp;
		// Top Row //
		Temp.Array[ 0 ] = (Matrix( 0, 0 ) * _Vs( 0, 0 )) + (Matrix( 1, 0 ) * _Vs( 0, 1 )) + (Matrix( 2, 0 ) * _Vs( 0, 2 )) + (Matrix( 3, 0 ) * _Vs( 0, 3 ));
		Temp.Array[ 1 ] = (Matrix( 0, 0 ) * _Vs( 1, 0 )) + (Matrix( 1, 0 ) * _Vs( 1, 1 )) + (Matrix( 2, 0 ) * _Vs( 1, 2 )) + (Matrix( 3, 0 ) * _Vs( 1, 3 ));
		Temp.Array[ 2 ] = (Matrix( 0, 0 ) * _Vs( 2, 0 )) + (Matrix( 1, 0 ) * _Vs( 2, 1 )) + (Matrix( 2, 0 ) * _Vs( 2, 2 )) + (Matrix( 3, 0 ) * _Vs( 2, 3 ));
		Temp.Array[ 3 ] = (Matrix( 0, 0 ) * _Vs( 3, 0 )) + (Matrix( 1, 0 ) * _Vs( 3, 1 )) + (Matrix( 2, 0 ) * _Vs( 3, 2 )) + (Matrix( 3, 0 ) * _Vs( 3, 3 ));

		// Top Middle Row //
		Temp.Array[ 4 ] = (Matrix( 0, 1 ) * _Vs( 0, 0 )) + (Matrix( 1, 1 ) * _Vs( 0, 1 )) + (Matrix( 2, 1 ) * _Vs( 0, 2 )) + (Matrix( 3, 1 ) * _Vs( 0, 3 ));
		Temp.Array[ 5 ] = (Matrix( 0, 1 ) * _Vs( 1, 0 )) + (Matrix( 1, 1 ) * _Vs( 1, 1 )) + (Matrix( 2, 1 ) * _Vs( 1, 2 )) + (Matrix( 3, 1 ) * _Vs( 1, 3 ));
		Temp.Array[ 6 ] = (Matrix( 0, 1 ) * _Vs( 2, 0 )) + (Matrix( 1, 1 ) * _Vs( 2, 1 )) + (Matrix( 2, 1 ) * _Vs( 2, 2 )) + (Matrix( 3, 1 ) * _Vs( 2, 3 ));
		Temp.Array[ 7 ] = (Matrix( 0, 1 ) * _Vs( 3, 0 )) + (Matrix( 1, 1 ) * _Vs( 3, 1 )) + (Matrix( 2, 1 ) * _Vs( 3, 2 )) + (Matrix( 3, 1 ) * _Vs( 3, 3 ));

		// Bottom Middle Row //
		Temp.Array[ 8 ] =  (Matrix( 0, 2 ) * _Vs( 0, 0 )) + (Matrix( 1, 2 ) * _Vs( 0, 1 )) + (Matrix( 2, 2 ) * _Vs( 0, 2 )) + (Matrix( 3, 2 ) * _Vs( 0, 3 ));
		Temp.Array[ 9 ] =  (Matrix( 0, 2 ) * _Vs( 1, 0 )) + (Matrix( 1, 2 ) * _Vs( 1, 1 )) + (Matrix( 2, 2 ) * _Vs( 1, 2 )) + (Matrix( 3, 2 ) * _Vs( 1, 3 ));
		Temp.Array[ 10 ] = (Matrix( 0, 2 ) * _Vs( 2, 0 )) + (Matrix( 1, 2 ) * _Vs( 2, 1 )) + (Matrix( 2, 2 ) * _Vs( 2, 2 )) + (Matrix( 3, 2 ) * _Vs( 2, 3 ));
		Temp.Array[ 11 ] = (Matrix( 0, 2 ) * _Vs( 3, 0 )) + (Matrix( 1, 2 ) * _Vs( 3, 1 )) + (Matrix( 2, 2 ) * _Vs( 3, 2 )) + (Matrix( 3, 2 ) * _Vs( 3, 3 ));

		// Bottom Row //
		Temp.Array[ 12 ] = (Matrix( 0, 3 ) * _Vs( 0, 0 )) + (Matrix( 1, 3 ) * _Vs( 0, 1 )) + (Matrix( 2, 3 ) * _Vs( 0, 2 )) + (Matrix( 3, 3 ) * _Vs( 0, 3 ));
		Temp.Array[ 13 ] = (Matrix( 0, 3 ) * _Vs( 1, 0 )) + (Matrix( 1, 3 ) * _Vs( 1, 1 )) + (Matrix( 2, 3 ) * _Vs( 1, 2 )) + (Matrix( 3, 3 ) * _Vs( 1, 3 ));
		Temp.Array[ 14 ] = (Matrix( 0, 3 ) * _Vs( 2, 0 )) + (Matrix( 1, 3 ) * _Vs( 2, 1 )) + (Matrix( 2, 3 ) * _Vs( 2, 2 )) + (Matrix( 3, 3 ) * _Vs( 2, 3 ));
		Temp.Array[ 15 ] = (Matrix( 0, 3 ) * _Vs( 3, 0 )) + (Matrix( 1, 3 ) * _Vs( 3, 1 )) + (Matrix( 2, 3 ) * _Vs( 3, 2 )) + (Matrix( 3, 3 ) * _Vs( 3, 3 ));
		
		return *this = Temp;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline void Multiply( const Matrix4x4& _Vs ) {
		(*this) = _Vs * (*this);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate Transpose of a Matrix //
	inline const Matrix4x4 Transpose() const {
		return Matrix4x4(
			Array[0], Array[4], Array[8], Array[12],
			Array[1], Array[5], Array[9], Array[13],
			Array[2], Array[6], Array[10], Array[14],
			Array[3], Array[7], Array[11], Array[15]
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix4x4 OrthoNormal() const {
		return Matrix4x4( 
			Row0().Normal(),
			Row1().Normal(),
			Row2().Normal(),
			Row3().Normal()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate Adjoint of Matrix (Transpose of the Cofactors) //
	inline const Matrix4x4 Adjoint() const {
		return Matrix4x4(
			Cofactor11().Determinant(), Cofactor12().Determinant(), Cofactor13().Determinant(), Cofactor14().Determinant(),
			Cofactor21().Determinant(), Cofactor22().Determinant(), Cofactor23().Determinant(), Cofactor24().Determinant(),
			Cofactor31().Determinant(), Cofactor32().Determinant(), Cofactor33().Determinant(), Cofactor34().Determinant(),
			Cofactor41().Determinant(), Cofactor42().Determinant(), Cofactor43().Determinant(), Cofactor44().Determinant()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Calculate the determinant, for the inverse //
	inline const Real Determinant() const {
		return
			Matrix(0,0) * 
				(
					Matrix(1,1) * (Matrix(2,2)*Matrix(3,3) - Matrix(2,3)*Matrix(3,2)) -
					Matrix(2,1) * (Matrix(1,2)*Matrix(3,3) + Matrix(1,3)*Matrix(3,2)) +
					Matrix(3,1) * (Matrix(1,2)*Matrix(2,3) - Matrix(1,3)*Matrix(2,2))
				) -
			Matrix(1,0) * 
				(
					Matrix(0,1) * (Matrix(2,2)*Matrix(3,3) - Matrix(2,3)*Matrix(3,2)) -
					Matrix(2,1) * (Matrix(0,2)*Matrix(3,3) + Matrix(0,3)*Matrix(3,2)) +
					Matrix(3,1) * (Matrix(0,2)*Matrix(2,3) - Matrix(0,3)*Matrix(2,2))
				) +
			Matrix(2,0) * 
				(
					Matrix(0,1) * (Matrix(1,2)*Matrix(3,3) - Matrix(1,3)*Matrix(3,2)) -
					Matrix(1,1) * (Matrix(0,2)*Matrix(3,3) + Matrix(0,3)*Matrix(3,2)) +
					Matrix(3,1) * (Matrix(0,2)*Matrix(1,3) - Matrix(0,3)*Matrix(1,2))
				) -
			Matrix(3,0) * 
				(
					Matrix(0,1) * (Matrix(1,2)*Matrix(2,3) - Matrix(1,3)*Matrix(2,2)) -
					Matrix(1,1) * (Matrix(0,2)*Matrix(2,3) + Matrix(0,3)*Matrix(2,2)) +
					Matrix(2,1) * (Matrix(0,2)*Matrix(1,3) - Matrix(0,3)*Matrix(1,2))
				);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Calculate the Inverse //
	inline const Matrix4x4 Inverse() const {
		Real Det = Determinant();

		if ( Det == Real::Zero ) {
			// Something bad //
			return Matrix4x4::Zero;
		}
		
		Det = Real::One / Det;
		
		return Adjoint() * Det;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Element helper functions, for making some of the more complex code more readable //
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e11() const {
		return Matrix(0,0);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e21() const {
		return Matrix(1,0);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e31() const {
		return Matrix(2,0);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e41() const {
		return Matrix(3,0);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e12() const {
		return Matrix(0,1);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e22() const {
		return Matrix(1,1);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e32() const {
		return Matrix(2,1);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e42() const {
		return Matrix(3,1);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e13() const {
		return Matrix(0,2);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e23() const {
		return Matrix(1,2);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e33() const {
		return Matrix(2,2);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e43() const {
		return Matrix(3,2);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e14() const {
		return Matrix(0,3);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e24() const {
		return Matrix(1,3);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e34() const {
		return Matrix(2,3);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Real e44() const {
		return Matrix(3,3);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Minors are the resulting matrices when the specified row and column of an index are removed //
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor11() const {
		return Matrix3x3(
			e22(), e32(), e42(),
			e23(), e33(), e43(),
			e24(), e34(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor21() const {
		return Matrix3x3(
			e12(), e32(), e42(),
			e13(), e33(), e43(),
			e14(), e34(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor31() const {
		return Matrix3x3(
			e12(), e22(), e42(),
			e13(), e23(), e43(),
			e14(), e24(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor41() const {
		return Matrix3x3(
			e12(), e22(), e32(),
			e13(), e23(), e33(),
			e14(), e24(), e34()
			);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor12() const {
		return Matrix3x3(
			e21(), e31(), e41(),
			e23(), e33(), e43(),
			e24(), e34(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor22() const {
		return Matrix3x3(
			e11(), e31(), e41(),
			e13(), e33(), e43(),
			e14(), e34(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor32() const {
		return Matrix3x3(
			e11(), e21(), e41(),
			e13(), e23(), e43(),
			e14(), e24(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor42() const {
		return Matrix3x3(
			e11(), e21(), e31(),
			e13(), e23(), e33(),
			e14(), e24(), e34()
			);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor13() const {
		return Matrix3x3(
			e21(), e31(), e41(),
			e22(), e32(), e42(),
			e24(), e34(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor23() const {
		return Matrix3x3(
			e11(), e31(), e41(),
			e12(), e32(), e42(),
			e14(), e34(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor33() const {
		return Matrix3x3(
			e11(), e21(), e41(),
			e12(), e22(), e42(),
			e14(), e24(), e44()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor43() const {
		return Matrix3x3(
			e11(), e21(), e31(),
			e12(), e22(), e32(),
			e14(), e24(), e34()
			);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor14() const {
		return Matrix3x3(
			e21(), e31(), e41(),
			e22(), e32(), e42(),
			e23(), e33(), e43()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor24() const {
		return Matrix3x3(
			e11(), e31(), e41(),
			e12(), e32(), e42(),
			e13(), e33(), e43()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor34() const {
		return Matrix3x3(
			e11(), e21(), e41(),
			e12(), e22(), e42(),
			e13(), e23(), e43()
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Minor44() const {
		return Matrix3x3(
			e11(), e21(), e31(),
			e12(), e22(), e32(),
			e13(), e23(), e33()
			);
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Cofactors are Minors, but with the unusual property that every other is negated (checkerboard) //
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor11() const {
		return Minor11();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor21() const {
		return -Minor21();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor31() const {
		return Minor31();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor41() const {
		return -Minor41();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor12() const {
		return -Minor12();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor22() const {
		return Minor22();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor32() const {
		return -Minor32();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor42() const {
		return Minor42();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor13() const {
		return Minor13();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor23() const {
		return -Minor23();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor33() const {
		return Minor33();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor43() const {
		return -Minor43();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor14() const {
		return -Minor14();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor24() const {
		return Minor24();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor34() const {
		return -Minor34();
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Matrix3x3 Cofactor44() const {
		return Minor44();
	}
	// - -------------------------------------------------------------------------------------- - //



	// - -------------------------------------------------------------------------------------- - //
	// Scalar Operations //
	// - -------------------------------------------------------------------------------------- - //
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling matrix from a scalar //
	inline static const Matrix4x4 ScalarMatrix( const Real& Scalar ) {
		Matrix4x4 Matrix(
			Scalar, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Scalar, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Scalar, Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Scalar
			);	
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling Matrix from a vector //
	inline static const Matrix4x4 ScalarMatrix( const Vector2D& _Vs ) {
		Matrix4x4 Matrix(
			_Vs.x, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, _Vs.y, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One, Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling Matrix from a vector //
	inline static const Matrix4x4 ScalarMatrix( const Vector3D& _Vs ) {
		Matrix4x4 Matrix(
			_Vs.x, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, _Vs.y, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, _Vs.z, Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a scaling Matrix from a vector //
	inline static const Matrix4x4 ScalarMatrix( const Vector4D& _Vs ) {
		Matrix4x4 Matrix(
			_Vs.x, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, _Vs.y, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, _Vs.z, Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, _Vs.w
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Creates a translating Matrix from a vector //
	inline static const Matrix4x4 IdentityMatrix() {
		Matrix4x4 Matrix(
			Real::One, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One, Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Creates a translating Matrix from a vector //
	inline static const Matrix4x4 TranslationMatrix( const Vector2D& _Vs ) {
		Matrix4x4 Matrix(
			Real::One, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One, Real::Zero,
			_Vs.x, _Vs.y, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a translating Matrix from a vector //
	inline static const Matrix4x4 TranslationMatrix( const Vector3D& _Vs ) {
		Matrix4x4 Matrix(
			Real::One, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One, Real::Zero,
			_Vs.x, _Vs.y, _Vs.z, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a translating Matrix from a vector //
	inline static const Matrix4x4 TranslationMatrix( const Vector4D& _Vs ) {
		Matrix4x4 Matrix(
			Real::One, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Real::One, Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One, Real::Zero,
			_Vs.x, _Vs.y, _Vs.z, _Vs.w
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation Matrix from an angle scalar //
	inline static const Matrix4x4 RotationMatrixXY( Real Angle ) {
		Angle /= 360.0f;
		Matrix4x4 Matrix(
			Real::Cos(Angle), Real::Sin(Angle), Real::Zero, Real::Zero,
			-Real::Sin(Angle), Real::Cos(Angle),  Real::Zero, Real::Zero,
			Real::Zero, Real::Zero, Real::One,  Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation Matrix from an angle scalar //
	inline static const Matrix4x4 RotationMatrixXZ( Real Angle ) {
		Angle /= 360.0f;
		Matrix4x4 Matrix(
			Real::Cos(Angle), Real::Zero, Real::Sin(Angle), Real::Zero,
			Real::Zero, Real::One, Real::Zero, Real::Zero,
			-Real::Sin(Angle), Real::Zero, Real::Cos(Angle), Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Creates a rotation Matrix from an angle scalar //
	inline static const Matrix4x4 RotationMatrixYZ( Real Angle ) {
		Angle /= 360.0f;
		Matrix4x4 Matrix(
			Real::One, Real::Zero, Real::Zero, Real::Zero,
			Real::Zero, Real::Cos(Angle), Real::Sin(Angle), Real::Zero,
			Real::Zero, -Real::Sin(Angle), Real::Cos(Angle), Real::Zero,
			Real::Zero, Real::Zero, Real::Zero, Real::One
			);
		
		return Matrix;
	}
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix4x4 operator - ( const Real& a, const Matrix4x4& b ) {
	return Matrix4x4(
		a - b.Array[0], a - b.Array[1], a - b.Array[2], a - b.Array[3],
		a - b.Array[4], a - b.Array[5], a - b.Array[6], a - b.Array[7],
		a - b.Array[8], a - b.Array[9], a - b.Array[10], a - b.Array[11],
		a - b.Array[12], a - b.Array[13], a - b.Array[14], a - b.Array[15]
		);
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Matrix4x4 operator / ( const Real& a, const Matrix4x4& b ) {
	return Matrix4x4(
		a / b.Array[0], a / b.Array[1], a / b.Array[2], a / b.Array[3],
		a / b.Array[4], a / b.Array[5], a / b.Array[6], a / b.Array[7],
		a / b.Array[8], a / b.Array[9], a / b.Array[10], a / b.Array[11],
		a / b.Array[12], a / b.Array[13], a / b.Array[14], a / b.Array[15]
		);
}
// -- ---------------------------------------------------------------------------------------- -- //


// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Matrix4x4_H__ //
// - ------------------------------------------------------------------------------------------ - //
