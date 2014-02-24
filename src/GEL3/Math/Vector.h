// - ------------------------------------------------------------------------------------------ - //
// Vector //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector_H__
#define __Geometry_Vector_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Vector/Vector2D.h"
#include "Vector/Vector3D.h"
#include "Vector/Vector4D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
Vector3D Vector2D::ToVector3D() const {
	return Vector3D( x, y, Real::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
Vector3D Vector2D::ToHomoVector3D() const {
	return Vector3D( x, y, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //
Vector4D Vector2D::ToVector4D() const {
	return Vector4D( x, y, Real::Zero, Real::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
Vector4D Vector2D::ToHomoVector4D() const {
	return Vector4D( x, y, Real::One, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
Vector2D Vector3D::ToVector2D() const {
	return Vector2D( x, y );
}
// - ------------------------------------------------------------------------------------------ - //
Vector3D Vector3D::ToHomoVector3D() const {
	return Vector3D( x, y, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //
Vector4D Vector3D::ToVector4D() const {
	return Vector4D( x, y, z, Real::Zero );
}
// - ------------------------------------------------------------------------------------------ - //
Vector4D Vector3D::ToHomoVector4D() const {
	return Vector4D( x, y, z, Real::One );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
Vector2D Vector4D::ToVector2D() const {
	return Vector2D( x, y );
}
// - ------------------------------------------------------------------------------------------ - //
Vector3D Vector4D::ToVector3D() const {
	return Vector3D( x, y, z );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define SWIZZLE2( _TYPE, _RETURNTYPE, _A, _B ) \
	const _RETURNTYPE _TYPE::_A ## _B () const { return _RETURNTYPE(_A,_B); }
#define SWIZZLE3( _TYPE, _RETURNTYPE, _A, _B, _C ) \
	const _RETURNTYPE _TYPE::_A ## _B ## _C () const { return _RETURNTYPE(_A,_B,_C); }
#define SWIZZLE4( _TYPE, _RETURNTYPE, _A, _B, _C, _D ) \
	const _RETURNTYPE _TYPE::_A ## _B ## _C ## _D() const { return _RETURNTYPE(_A,_B,_C,_D); }
// - ------------------------------------------------------------------------------------------ - //
#define _SWIZZLE2( _TYPE, _RETURNTYPE, _A, _B ) \
	const _RETURNTYPE _TYPE::_ ## _A ## _B () const { return _RETURNTYPE(_A,_B); }
#define _SWIZZLE3( _TYPE, _RETURNTYPE, _A, _B, _C ) \
	const _RETURNTYPE _TYPE::_ ## _A ## _B ## _C () const { return _RETURNTYPE(_A,_B,_C); }
#define _SWIZZLE4( _TYPE, _RETURNTYPE, _A, _B, _C, _D ) \
	const _RETURNTYPE _TYPE::_ ## _A ## _B ## _C ## _D() const { return _RETURNTYPE(_A,_B,_C,_D); }
// - ------------------------------------------------------------------------------------------ - //
SWIZZLE2( Real, Vector2D, x,x );
SWIZZLE3( Real, Vector3D, x,x,x );
SWIZZLE4( Real, Vector4D, x,x,x,x );

_SWIZZLE2( Real, Vector2D, x,x );
_SWIZZLE2( Real, Vector2D, x,0 );
_SWIZZLE2( Real, Vector2D, x,1 );
_SWIZZLE2( Real, Vector2D, 0,x );
_SWIZZLE2( Real, Vector2D, 0,0 );
_SWIZZLE2( Real, Vector2D, 0,1 );
_SWIZZLE2( Real, Vector2D, 1,x );
_SWIZZLE2( Real, Vector2D, 1,0 );
_SWIZZLE2( Real, Vector2D, 1,1 );

_SWIZZLE3( Real, Vector3D, x,x,x );
_SWIZZLE3( Real, Vector3D, x,x,0 );
_SWIZZLE3( Real, Vector3D, x,x,1 );
_SWIZZLE3( Real, Vector3D, x,0,x );
_SWIZZLE3( Real, Vector3D, x,0,0 );
_SWIZZLE3( Real, Vector3D, x,0,1 );
_SWIZZLE3( Real, Vector3D, x,1,x );
_SWIZZLE3( Real, Vector3D, x,1,0 );
_SWIZZLE3( Real, Vector3D, x,1,1 );
_SWIZZLE3( Real, Vector3D, 0,x,x );
_SWIZZLE3( Real, Vector3D, 0,x,0 );
_SWIZZLE3( Real, Vector3D, 0,x,1 );
_SWIZZLE3( Real, Vector3D, 0,0,x );
_SWIZZLE3( Real, Vector3D, 0,0,0 );
_SWIZZLE3( Real, Vector3D, 0,0,1 );
_SWIZZLE3( Real, Vector3D, 0,1,x );
_SWIZZLE3( Real, Vector3D, 0,1,0 );
_SWIZZLE3( Real, Vector3D, 0,1,1 );
_SWIZZLE3( Real, Vector3D, 1,x,x );
_SWIZZLE3( Real, Vector3D, 1,x,0 );
_SWIZZLE3( Real, Vector3D, 1,x,1 );
_SWIZZLE3( Real, Vector3D, 1,0,x );
_SWIZZLE3( Real, Vector3D, 1,0,0 );
_SWIZZLE3( Real, Vector3D, 1,0,1 );
_SWIZZLE3( Real, Vector3D, 1,1,x );
_SWIZZLE3( Real, Vector3D, 1,1,0 );
_SWIZZLE3( Real, Vector3D, 1,1,1 );

_SWIZZLE4( Real, Vector4D, x,x,x,x );	// *** //
_SWIZZLE4( Real, Vector4D, x,x,x,0 );
_SWIZZLE4( Real, Vector4D, x,x,x,1 );
_SWIZZLE4( Real, Vector4D, x,x,0,x );
_SWIZZLE4( Real, Vector4D, x,x,0,0 );
_SWIZZLE4( Real, Vector4D, x,x,0,1 );
_SWIZZLE4( Real, Vector4D, x,x,1,x );
_SWIZZLE4( Real, Vector4D, x,x,1,0 );
_SWIZZLE4( Real, Vector4D, x,x,1,1 );
_SWIZZLE4( Real, Vector4D, x,0,x,x );
_SWIZZLE4( Real, Vector4D, x,0,x,0 );
_SWIZZLE4( Real, Vector4D, x,0,x,1 );
_SWIZZLE4( Real, Vector4D, x,0,0,x );
_SWIZZLE4( Real, Vector4D, x,0,0,0 );
_SWIZZLE4( Real, Vector4D, x,0,0,1 );
_SWIZZLE4( Real, Vector4D, x,0,1,x );
_SWIZZLE4( Real, Vector4D, x,0,1,0 );
_SWIZZLE4( Real, Vector4D, x,0,1,1 );
_SWIZZLE4( Real, Vector4D, x,1,x,x );
_SWIZZLE4( Real, Vector4D, x,1,x,0 );
_SWIZZLE4( Real, Vector4D, x,1,x,1 );
_SWIZZLE4( Real, Vector4D, x,1,0,x );
_SWIZZLE4( Real, Vector4D, x,1,0,0 );
_SWIZZLE4( Real, Vector4D, x,1,0,1 );
_SWIZZLE4( Real, Vector4D, x,1,1,x );
_SWIZZLE4( Real, Vector4D, x,1,1,0 );
_SWIZZLE4( Real, Vector4D, x,1,1,1 );
_SWIZZLE4( Real, Vector4D, 0,x,x,x );	// *** //
_SWIZZLE4( Real, Vector4D, 0,x,x,0 );
_SWIZZLE4( Real, Vector4D, 0,x,x,1 );
_SWIZZLE4( Real, Vector4D, 0,x,0,x );
_SWIZZLE4( Real, Vector4D, 0,x,0,0 );
_SWIZZLE4( Real, Vector4D, 0,x,0,1 );
_SWIZZLE4( Real, Vector4D, 0,x,1,x );
_SWIZZLE4( Real, Vector4D, 0,x,1,0 );
_SWIZZLE4( Real, Vector4D, 0,x,1,1 );
_SWIZZLE4( Real, Vector4D, 0,0,x,x );
_SWIZZLE4( Real, Vector4D, 0,0,x,0 );
_SWIZZLE4( Real, Vector4D, 0,0,x,1 );
_SWIZZLE4( Real, Vector4D, 0,0,0,x );
_SWIZZLE4( Real, Vector4D, 0,0,0,0 );
_SWIZZLE4( Real, Vector4D, 0,0,0,1 );
_SWIZZLE4( Real, Vector4D, 0,0,1,x );
_SWIZZLE4( Real, Vector4D, 0,0,1,0 );
_SWIZZLE4( Real, Vector4D, 0,0,1,1 );
_SWIZZLE4( Real, Vector4D, 0,1,x,x );
_SWIZZLE4( Real, Vector4D, 0,1,x,0 );
_SWIZZLE4( Real, Vector4D, 0,1,x,1 );
_SWIZZLE4( Real, Vector4D, 0,1,0,x );
_SWIZZLE4( Real, Vector4D, 0,1,0,0 );
_SWIZZLE4( Real, Vector4D, 0,1,0,1 );
_SWIZZLE4( Real, Vector4D, 0,1,1,x );
_SWIZZLE4( Real, Vector4D, 0,1,1,0 );
_SWIZZLE4( Real, Vector4D, 0,1,1,1 );
_SWIZZLE4( Real, Vector4D, 1,x,x,x );	// *** //
_SWIZZLE4( Real, Vector4D, 1,x,x,0 );
_SWIZZLE4( Real, Vector4D, 1,x,x,1 );
_SWIZZLE4( Real, Vector4D, 1,x,0,x );
_SWIZZLE4( Real, Vector4D, 1,x,0,0 );
_SWIZZLE4( Real, Vector4D, 1,x,0,1 );
_SWIZZLE4( Real, Vector4D, 1,x,1,x );
_SWIZZLE4( Real, Vector4D, 1,x,1,0 );
_SWIZZLE4( Real, Vector4D, 1,x,1,1 );
_SWIZZLE4( Real, Vector4D, 1,0,x,x );
_SWIZZLE4( Real, Vector4D, 1,0,x,0 );
_SWIZZLE4( Real, Vector4D, 1,0,x,1 );
_SWIZZLE4( Real, Vector4D, 1,0,0,x );
_SWIZZLE4( Real, Vector4D, 1,0,0,0 );
_SWIZZLE4( Real, Vector4D, 1,0,0,1 );
_SWIZZLE4( Real, Vector4D, 1,0,1,x );
_SWIZZLE4( Real, Vector4D, 1,0,1,0 );
_SWIZZLE4( Real, Vector4D, 1,0,1,1 );
_SWIZZLE4( Real, Vector4D, 1,1,x,x );
_SWIZZLE4( Real, Vector4D, 1,1,x,0 );
_SWIZZLE4( Real, Vector4D, 1,1,x,1 );
_SWIZZLE4( Real, Vector4D, 1,1,0,x );
_SWIZZLE4( Real, Vector4D, 1,1,0,0 );
_SWIZZLE4( Real, Vector4D, 1,1,0,1 );
_SWIZZLE4( Real, Vector4D, 1,1,1,x );
_SWIZZLE4( Real, Vector4D, 1,1,1,0 );
_SWIZZLE4( Real, Vector4D, 1,1,1,1 );	
// - ------------------------------------------------------------------------------------------ - //
SWIZZLE2( Vector2D, Vector2D, x,x );
SWIZZLE2( Vector2D, Vector2D, x,y );
SWIZZLE2( Vector2D, Vector2D, y,x );
SWIZZLE2( Vector2D, Vector2D, y,y );

_SWIZZLE2( Vector2D, Vector2D, x,x );
_SWIZZLE2( Vector2D, Vector2D, x,y );
_SWIZZLE2( Vector2D, Vector2D, x,0 );
_SWIZZLE2( Vector2D, Vector2D, x,1 );
_SWIZZLE2( Vector2D, Vector2D, y,x );
_SWIZZLE2( Vector2D, Vector2D, y,y );
_SWIZZLE2( Vector2D, Vector2D, y,0 );
_SWIZZLE2( Vector2D, Vector2D, y,1 );
_SWIZZLE2( Vector2D, Vector2D, 0,x );
_SWIZZLE2( Vector2D, Vector2D, 0,y );
_SWIZZLE2( Vector2D, Vector2D, 0,0 );
_SWIZZLE2( Vector2D, Vector2D, 0,1 );
_SWIZZLE2( Vector2D, Vector2D, 1,x );
_SWIZZLE2( Vector2D, Vector2D, 1,y );
_SWIZZLE2( Vector2D, Vector2D, 1,0 );
_SWIZZLE2( Vector2D, Vector2D, 1,1 );

SWIZZLE3( Vector2D, Vector3D, x,x,x );
SWIZZLE3( Vector2D, Vector3D, x,x,y );
SWIZZLE3( Vector2D, Vector3D, x,y,x );
SWIZZLE3( Vector2D, Vector3D, x,y,y );
SWIZZLE3( Vector2D, Vector3D, y,x,x );
SWIZZLE3( Vector2D, Vector3D, y,x,y );
SWIZZLE3( Vector2D, Vector3D, y,y,x );
SWIZZLE3( Vector2D, Vector3D, y,y,y );

_SWIZZLE3( Vector2D, Vector3D, x,x,x );
_SWIZZLE3( Vector2D, Vector3D, x,x,y );
_SWIZZLE3( Vector2D, Vector3D, x,x,0 );
_SWIZZLE3( Vector2D, Vector3D, x,x,1 );
_SWIZZLE3( Vector2D, Vector3D, x,y,x );
_SWIZZLE3( Vector2D, Vector3D, x,y,y );
_SWIZZLE3( Vector2D, Vector3D, x,y,0 );
_SWIZZLE3( Vector2D, Vector3D, x,y,1 );
_SWIZZLE3( Vector2D, Vector3D, x,0,x );
_SWIZZLE3( Vector2D, Vector3D, x,0,y );
_SWIZZLE3( Vector2D, Vector3D, x,0,0 );
_SWIZZLE3( Vector2D, Vector3D, x,0,1 );
_SWIZZLE3( Vector2D, Vector3D, x,1,x );
_SWIZZLE3( Vector2D, Vector3D, x,1,y );
_SWIZZLE3( Vector2D, Vector3D, x,1,0 );
_SWIZZLE3( Vector2D, Vector3D, x,1,1 );
_SWIZZLE3( Vector2D, Vector3D, y,x,x );
_SWIZZLE3( Vector2D, Vector3D, y,x,y );
_SWIZZLE3( Vector2D, Vector3D, y,x,0 );
_SWIZZLE3( Vector2D, Vector3D, y,x,1 );
_SWIZZLE3( Vector2D, Vector3D, y,y,x );
_SWIZZLE3( Vector2D, Vector3D, y,y,y );
_SWIZZLE3( Vector2D, Vector3D, y,y,0 );
_SWIZZLE3( Vector2D, Vector3D, y,y,1 );
_SWIZZLE3( Vector2D, Vector3D, y,0,x );
_SWIZZLE3( Vector2D, Vector3D, y,0,y );
_SWIZZLE3( Vector2D, Vector3D, y,0,0 );
_SWIZZLE3( Vector2D, Vector3D, y,0,1 );
_SWIZZLE3( Vector2D, Vector3D, y,1,x );
_SWIZZLE3( Vector2D, Vector3D, y,1,y );
_SWIZZLE3( Vector2D, Vector3D, y,1,0 );
_SWIZZLE3( Vector2D, Vector3D, y,1,1 );
_SWIZZLE3( Vector2D, Vector3D, 0,x,x );
_SWIZZLE3( Vector2D, Vector3D, 0,x,y );
_SWIZZLE3( Vector2D, Vector3D, 0,x,0 );
_SWIZZLE3( Vector2D, Vector3D, 0,x,1 );
_SWIZZLE3( Vector2D, Vector3D, 0,y,x );
_SWIZZLE3( Vector2D, Vector3D, 0,y,y );
_SWIZZLE3( Vector2D, Vector3D, 0,y,0 );
_SWIZZLE3( Vector2D, Vector3D, 0,y,1 );
_SWIZZLE3( Vector2D, Vector3D, 0,0,x );
_SWIZZLE3( Vector2D, Vector3D, 0,0,y );
_SWIZZLE3( Vector2D, Vector3D, 0,0,0 );
_SWIZZLE3( Vector2D, Vector3D, 0,0,1 );
_SWIZZLE3( Vector2D, Vector3D, 0,1,x );
_SWIZZLE3( Vector2D, Vector3D, 0,1,y );
_SWIZZLE3( Vector2D, Vector3D, 0,1,0 );
_SWIZZLE3( Vector2D, Vector3D, 0,1,1 );
_SWIZZLE3( Vector2D, Vector3D, 1,x,x );
_SWIZZLE3( Vector2D, Vector3D, 1,x,y );
_SWIZZLE3( Vector2D, Vector3D, 1,x,0 );
_SWIZZLE3( Vector2D, Vector3D, 1,x,1 );
_SWIZZLE3( Vector2D, Vector3D, 1,y,x );
_SWIZZLE3( Vector2D, Vector3D, 1,y,y );
_SWIZZLE3( Vector2D, Vector3D, 1,y,0 );
_SWIZZLE3( Vector2D, Vector3D, 1,y,1 );
_SWIZZLE3( Vector2D, Vector3D, 1,0,x );
_SWIZZLE3( Vector2D, Vector3D, 1,0,y );
_SWIZZLE3( Vector2D, Vector3D, 1,0,0 );
_SWIZZLE3( Vector2D, Vector3D, 1,0,1 );
_SWIZZLE3( Vector2D, Vector3D, 1,1,x );
_SWIZZLE3( Vector2D, Vector3D, 1,1,y );
_SWIZZLE3( Vector2D, Vector3D, 1,1,0 );
_SWIZZLE3( Vector2D, Vector3D, 1,1,1 );

SWIZZLE4( Vector2D, Vector4D, x,x,x,x );
SWIZZLE4( Vector2D, Vector4D, x,x,x,y );
SWIZZLE4( Vector2D, Vector4D, x,x,y,x );
SWIZZLE4( Vector2D, Vector4D, x,x,y,y );
SWIZZLE4( Vector2D, Vector4D, x,y,x,x );
SWIZZLE4( Vector2D, Vector4D, x,y,x,y );
SWIZZLE4( Vector2D, Vector4D, x,y,y,x );
SWIZZLE4( Vector2D, Vector4D, x,y,y,y );
SWIZZLE4( Vector2D, Vector4D, y,x,x,x );
SWIZZLE4( Vector2D, Vector4D, y,x,x,y );
SWIZZLE4( Vector2D, Vector4D, y,x,y,x );
SWIZZLE4( Vector2D, Vector4D, y,x,y,y );
SWIZZLE4( Vector2D, Vector4D, y,y,x,x );
SWIZZLE4( Vector2D, Vector4D, y,y,x,y );
SWIZZLE4( Vector2D, Vector4D, y,y,y,x );
SWIZZLE4( Vector2D, Vector4D, y,y,y,y );

_SWIZZLE4( Vector2D, Vector4D, x,x,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, x,x,x,y );
_SWIZZLE4( Vector2D, Vector4D, x,x,x,0 );
_SWIZZLE4( Vector2D, Vector4D, x,x,x,1 );
_SWIZZLE4( Vector2D, Vector4D, x,x,y,x );
_SWIZZLE4( Vector2D, Vector4D, x,x,y,y );
_SWIZZLE4( Vector2D, Vector4D, x,x,y,0 );
_SWIZZLE4( Vector2D, Vector4D, x,x,y,1 );
_SWIZZLE4( Vector2D, Vector4D, x,x,0,x );
_SWIZZLE4( Vector2D, Vector4D, x,x,0,y );
_SWIZZLE4( Vector2D, Vector4D, x,x,0,0 );
_SWIZZLE4( Vector2D, Vector4D, x,x,0,1 );
_SWIZZLE4( Vector2D, Vector4D, x,x,1,x );
_SWIZZLE4( Vector2D, Vector4D, x,x,1,y );
_SWIZZLE4( Vector2D, Vector4D, x,x,1,0 );
_SWIZZLE4( Vector2D, Vector4D, x,x,1,1 );
_SWIZZLE4( Vector2D, Vector4D, x,y,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, x,y,x,y );
_SWIZZLE4( Vector2D, Vector4D, x,y,x,0 );
_SWIZZLE4( Vector2D, Vector4D, x,y,x,1 );
_SWIZZLE4( Vector2D, Vector4D, x,y,y,x );
_SWIZZLE4( Vector2D, Vector4D, x,y,y,y );
_SWIZZLE4( Vector2D, Vector4D, x,y,y,0 );
_SWIZZLE4( Vector2D, Vector4D, x,y,y,1 );
_SWIZZLE4( Vector2D, Vector4D, x,y,0,x );
_SWIZZLE4( Vector2D, Vector4D, x,y,0,y );
_SWIZZLE4( Vector2D, Vector4D, x,y,0,0 );
_SWIZZLE4( Vector2D, Vector4D, x,y,0,1 );
_SWIZZLE4( Vector2D, Vector4D, x,y,1,x );
_SWIZZLE4( Vector2D, Vector4D, x,y,1,y );
_SWIZZLE4( Vector2D, Vector4D, x,y,1,0 );
_SWIZZLE4( Vector2D, Vector4D, x,y,1,1 );
_SWIZZLE4( Vector2D, Vector4D, x,0,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, x,0,x,y );
_SWIZZLE4( Vector2D, Vector4D, x,0,x,0 );
_SWIZZLE4( Vector2D, Vector4D, x,0,x,1 );
_SWIZZLE4( Vector2D, Vector4D, x,0,y,x );
_SWIZZLE4( Vector2D, Vector4D, x,0,y,y );
_SWIZZLE4( Vector2D, Vector4D, x,0,y,0 );
_SWIZZLE4( Vector2D, Vector4D, x,0,y,1 );
_SWIZZLE4( Vector2D, Vector4D, x,0,0,x );
_SWIZZLE4( Vector2D, Vector4D, x,0,0,y );
_SWIZZLE4( Vector2D, Vector4D, x,0,0,0 );
_SWIZZLE4( Vector2D, Vector4D, x,0,0,1 );
_SWIZZLE4( Vector2D, Vector4D, x,0,1,x );
_SWIZZLE4( Vector2D, Vector4D, x,0,1,y );
_SWIZZLE4( Vector2D, Vector4D, x,0,1,0 );
_SWIZZLE4( Vector2D, Vector4D, x,0,1,1 );
_SWIZZLE4( Vector2D, Vector4D, x,1,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, x,1,x,y );
_SWIZZLE4( Vector2D, Vector4D, x,1,x,0 );
_SWIZZLE4( Vector2D, Vector4D, x,1,x,1 );
_SWIZZLE4( Vector2D, Vector4D, x,1,y,x );
_SWIZZLE4( Vector2D, Vector4D, x,1,y,y );
_SWIZZLE4( Vector2D, Vector4D, x,1,y,0 );
_SWIZZLE4( Vector2D, Vector4D, x,1,y,1 );
_SWIZZLE4( Vector2D, Vector4D, x,1,0,x );
_SWIZZLE4( Vector2D, Vector4D, x,1,0,y );
_SWIZZLE4( Vector2D, Vector4D, x,1,0,0 );
_SWIZZLE4( Vector2D, Vector4D, x,1,0,1 );
_SWIZZLE4( Vector2D, Vector4D, x,1,1,x );
_SWIZZLE4( Vector2D, Vector4D, x,1,1,y );
_SWIZZLE4( Vector2D, Vector4D, x,1,1,0 );
_SWIZZLE4( Vector2D, Vector4D, x,1,1,1 );
_SWIZZLE4( Vector2D, Vector4D, y,x,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, y,x,x,y );
_SWIZZLE4( Vector2D, Vector4D, y,x,x,0 );
_SWIZZLE4( Vector2D, Vector4D, y,x,x,1 );
_SWIZZLE4( Vector2D, Vector4D, y,x,y,x );
_SWIZZLE4( Vector2D, Vector4D, y,x,y,y );
_SWIZZLE4( Vector2D, Vector4D, y,x,y,0 );
_SWIZZLE4( Vector2D, Vector4D, y,x,y,1 );
_SWIZZLE4( Vector2D, Vector4D, y,x,0,x );
_SWIZZLE4( Vector2D, Vector4D, y,x,0,y );
_SWIZZLE4( Vector2D, Vector4D, y,x,0,0 );
_SWIZZLE4( Vector2D, Vector4D, y,x,0,1 );
_SWIZZLE4( Vector2D, Vector4D, y,x,1,x );
_SWIZZLE4( Vector2D, Vector4D, y,x,1,y );
_SWIZZLE4( Vector2D, Vector4D, y,x,1,0 );
_SWIZZLE4( Vector2D, Vector4D, y,x,1,1 );
_SWIZZLE4( Vector2D, Vector4D, y,y,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, y,y,x,y );
_SWIZZLE4( Vector2D, Vector4D, y,y,x,0 );
_SWIZZLE4( Vector2D, Vector4D, y,y,x,1 );
_SWIZZLE4( Vector2D, Vector4D, y,y,y,x );
_SWIZZLE4( Vector2D, Vector4D, y,y,y,y );
_SWIZZLE4( Vector2D, Vector4D, y,y,y,0 );
_SWIZZLE4( Vector2D, Vector4D, y,y,y,1 );
_SWIZZLE4( Vector2D, Vector4D, y,y,0,x );
_SWIZZLE4( Vector2D, Vector4D, y,y,0,y );
_SWIZZLE4( Vector2D, Vector4D, y,y,0,0 );
_SWIZZLE4( Vector2D, Vector4D, y,y,0,1 );
_SWIZZLE4( Vector2D, Vector4D, y,y,1,x );
_SWIZZLE4( Vector2D, Vector4D, y,y,1,y );
_SWIZZLE4( Vector2D, Vector4D, y,y,1,0 );
_SWIZZLE4( Vector2D, Vector4D, y,y,1,1 );
_SWIZZLE4( Vector2D, Vector4D, y,0,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, y,0,x,y );
_SWIZZLE4( Vector2D, Vector4D, y,0,x,0 );
_SWIZZLE4( Vector2D, Vector4D, y,0,x,1 );
_SWIZZLE4( Vector2D, Vector4D, y,0,y,x );
_SWIZZLE4( Vector2D, Vector4D, y,0,y,y );
_SWIZZLE4( Vector2D, Vector4D, y,0,y,0 );
_SWIZZLE4( Vector2D, Vector4D, y,0,y,1 );
_SWIZZLE4( Vector2D, Vector4D, y,0,0,x );
_SWIZZLE4( Vector2D, Vector4D, y,0,0,y );
_SWIZZLE4( Vector2D, Vector4D, y,0,0,0 );
_SWIZZLE4( Vector2D, Vector4D, y,0,0,1 );
_SWIZZLE4( Vector2D, Vector4D, y,0,1,x );
_SWIZZLE4( Vector2D, Vector4D, y,0,1,y );
_SWIZZLE4( Vector2D, Vector4D, y,0,1,0 );
_SWIZZLE4( Vector2D, Vector4D, y,0,1,1 );
_SWIZZLE4( Vector2D, Vector4D, y,1,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, y,1,x,y );
_SWIZZLE4( Vector2D, Vector4D, y,1,x,0 );
_SWIZZLE4( Vector2D, Vector4D, y,1,x,1 );
_SWIZZLE4( Vector2D, Vector4D, y,1,y,x );
_SWIZZLE4( Vector2D, Vector4D, y,1,y,y );
_SWIZZLE4( Vector2D, Vector4D, y,1,y,0 );
_SWIZZLE4( Vector2D, Vector4D, y,1,y,1 );
_SWIZZLE4( Vector2D, Vector4D, y,1,0,x );
_SWIZZLE4( Vector2D, Vector4D, y,1,0,y );
_SWIZZLE4( Vector2D, Vector4D, y,1,0,0 );
_SWIZZLE4( Vector2D, Vector4D, y,1,0,1 );
_SWIZZLE4( Vector2D, Vector4D, y,1,1,x );
_SWIZZLE4( Vector2D, Vector4D, y,1,1,y );
_SWIZZLE4( Vector2D, Vector4D, y,1,1,0 );
_SWIZZLE4( Vector2D, Vector4D, y,1,1,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, 0,0,x,y );
_SWIZZLE4( Vector2D, Vector4D, 0,0,x,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,x,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,y,x );
_SWIZZLE4( Vector2D, Vector4D, 0,0,y,y );
_SWIZZLE4( Vector2D, Vector4D, 0,0,y,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,y,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,0,x );
_SWIZZLE4( Vector2D, Vector4D, 0,0,0,y );
_SWIZZLE4( Vector2D, Vector4D, 0,0,0,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,0,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,1,x );
_SWIZZLE4( Vector2D, Vector4D, 0,0,1,y );
_SWIZZLE4( Vector2D, Vector4D, 0,0,1,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,0,1,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, 0,1,x,y );
_SWIZZLE4( Vector2D, Vector4D, 0,1,x,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,x,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,y,x );
_SWIZZLE4( Vector2D, Vector4D, 0,1,y,y );
_SWIZZLE4( Vector2D, Vector4D, 0,1,y,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,y,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,0,x );
_SWIZZLE4( Vector2D, Vector4D, 0,1,0,y );
_SWIZZLE4( Vector2D, Vector4D, 0,1,0,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,0,1 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,1,x );
_SWIZZLE4( Vector2D, Vector4D, 0,1,1,y );
_SWIZZLE4( Vector2D, Vector4D, 0,1,1,0 );
_SWIZZLE4( Vector2D, Vector4D, 0,1,1,1 );	
_SWIZZLE4( Vector2D, Vector4D, 1,0,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, 1,0,x,y );
_SWIZZLE4( Vector2D, Vector4D, 1,0,x,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,x,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,y,x );
_SWIZZLE4( Vector2D, Vector4D, 1,0,y,y );
_SWIZZLE4( Vector2D, Vector4D, 1,0,y,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,y,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,0,x );
_SWIZZLE4( Vector2D, Vector4D, 1,0,0,y );
_SWIZZLE4( Vector2D, Vector4D, 1,0,0,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,0,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,1,x );
_SWIZZLE4( Vector2D, Vector4D, 1,0,1,y );
_SWIZZLE4( Vector2D, Vector4D, 1,0,1,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,0,1,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,x,x );	// *** //
_SWIZZLE4( Vector2D, Vector4D, 1,1,x,y );
_SWIZZLE4( Vector2D, Vector4D, 1,1,x,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,x,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,y,x );
_SWIZZLE4( Vector2D, Vector4D, 1,1,y,y );
_SWIZZLE4( Vector2D, Vector4D, 1,1,y,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,y,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,0,x );
_SWIZZLE4( Vector2D, Vector4D, 1,1,0,y );
_SWIZZLE4( Vector2D, Vector4D, 1,1,0,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,0,1 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,1,x );
_SWIZZLE4( Vector2D, Vector4D, 1,1,1,y );
_SWIZZLE4( Vector2D, Vector4D, 1,1,1,0 );
_SWIZZLE4( Vector2D, Vector4D, 1,1,1,1 );
// - ------------------------------------------------------------------------------------------ - //
SWIZZLE2( Vector3D, Vector2D, x,x );
SWIZZLE2( Vector3D, Vector2D, x,y );
SWIZZLE2( Vector3D, Vector2D, x,z );
SWIZZLE2( Vector3D, Vector2D, y,x );
SWIZZLE2( Vector3D, Vector2D, y,y );
SWIZZLE2( Vector3D, Vector2D, y,z );
SWIZZLE2( Vector3D, Vector2D, z,x );
SWIZZLE2( Vector3D, Vector2D, z,y );
SWIZZLE2( Vector3D, Vector2D, z,z );

_SWIZZLE2( Vector3D, Vector2D, x,x );	// *** //
_SWIZZLE2( Vector3D, Vector2D, x,y );
_SWIZZLE2( Vector3D, Vector2D, x,z );
_SWIZZLE2( Vector3D, Vector2D, x,0 );
_SWIZZLE2( Vector3D, Vector2D, x,1 );
_SWIZZLE2( Vector3D, Vector2D, y,x );	// *** //
_SWIZZLE2( Vector3D, Vector2D, y,y );
_SWIZZLE2( Vector3D, Vector2D, y,z );
_SWIZZLE2( Vector3D, Vector2D, y,0 );
_SWIZZLE2( Vector3D, Vector2D, y,1 );
_SWIZZLE2( Vector3D, Vector2D, z,x );	// *** //
_SWIZZLE2( Vector3D, Vector2D, z,y );
_SWIZZLE2( Vector3D, Vector2D, z,z );
_SWIZZLE2( Vector3D, Vector2D, z,0 );
_SWIZZLE2( Vector3D, Vector2D, z,1 );
_SWIZZLE2( Vector3D, Vector2D, 0,x );	// *** //
_SWIZZLE2( Vector3D, Vector2D, 0,y );
_SWIZZLE2( Vector3D, Vector2D, 0,z );
_SWIZZLE2( Vector3D, Vector2D, 0,0 );
_SWIZZLE2( Vector3D, Vector2D, 0,1 );
_SWIZZLE2( Vector3D, Vector2D, 1,x );	// *** //
_SWIZZLE2( Vector3D, Vector2D, 1,y );
_SWIZZLE2( Vector3D, Vector2D, 1,z );
_SWIZZLE2( Vector3D, Vector2D, 1,0 );
_SWIZZLE2( Vector3D, Vector2D, 1,1 );

SWIZZLE3( Vector3D, Vector3D, x,x,x );
SWIZZLE3( Vector3D, Vector3D, x,x,y );
SWIZZLE3( Vector3D, Vector3D, x,x,z );
SWIZZLE3( Vector3D, Vector3D, x,y,x );
SWIZZLE3( Vector3D, Vector3D, x,y,y );
SWIZZLE3( Vector3D, Vector3D, x,y,z );
SWIZZLE3( Vector3D, Vector3D, x,z,x );
SWIZZLE3( Vector3D, Vector3D, x,z,y );
SWIZZLE3( Vector3D, Vector3D, x,z,z );
SWIZZLE3( Vector3D, Vector3D, y,x,x );
SWIZZLE3( Vector3D, Vector3D, y,x,y );
SWIZZLE3( Vector3D, Vector3D, y,x,z );
SWIZZLE3( Vector3D, Vector3D, y,y,x );
SWIZZLE3( Vector3D, Vector3D, y,y,y );
SWIZZLE3( Vector3D, Vector3D, y,y,z );
SWIZZLE3( Vector3D, Vector3D, y,z,x );
SWIZZLE3( Vector3D, Vector3D, y,z,y );
SWIZZLE3( Vector3D, Vector3D, y,z,z );
SWIZZLE3( Vector3D, Vector3D, z,x,x );
SWIZZLE3( Vector3D, Vector3D, z,x,y );
SWIZZLE3( Vector3D, Vector3D, z,x,z );
SWIZZLE3( Vector3D, Vector3D, z,y,x );
SWIZZLE3( Vector3D, Vector3D, z,y,y );
SWIZZLE3( Vector3D, Vector3D, z,y,z );
SWIZZLE3( Vector3D, Vector3D, z,z,x );
SWIZZLE3( Vector3D, Vector3D, z,z,y );
SWIZZLE3( Vector3D, Vector3D, z,z,z );

_SWIZZLE3( Vector3D, Vector3D, x,x,x );	// *** //
_SWIZZLE3( Vector3D, Vector3D, x,x,y );
_SWIZZLE3( Vector3D, Vector3D, x,x,z );
_SWIZZLE3( Vector3D, Vector3D, x,x,0 );
_SWIZZLE3( Vector3D, Vector3D, x,x,1 );
_SWIZZLE3( Vector3D, Vector3D, x,y,x );
_SWIZZLE3( Vector3D, Vector3D, x,y,y );
_SWIZZLE3( Vector3D, Vector3D, x,y,z );
_SWIZZLE3( Vector3D, Vector3D, x,y,0 );
_SWIZZLE3( Vector3D, Vector3D, x,y,1 );
_SWIZZLE3( Vector3D, Vector3D, x,z,x );
_SWIZZLE3( Vector3D, Vector3D, x,z,y );
_SWIZZLE3( Vector3D, Vector3D, x,z,z );
_SWIZZLE3( Vector3D, Vector3D, x,z,0 );
_SWIZZLE3( Vector3D, Vector3D, x,z,1 );
_SWIZZLE3( Vector3D, Vector3D, x,0,x );
_SWIZZLE3( Vector3D, Vector3D, x,0,y );
_SWIZZLE3( Vector3D, Vector3D, x,0,z );
_SWIZZLE3( Vector3D, Vector3D, x,0,0 );
_SWIZZLE3( Vector3D, Vector3D, x,0,1 );
_SWIZZLE3( Vector3D, Vector3D, x,1,x );
_SWIZZLE3( Vector3D, Vector3D, x,1,y );
_SWIZZLE3( Vector3D, Vector3D, x,1,z );
_SWIZZLE3( Vector3D, Vector3D, x,1,0 );
_SWIZZLE3( Vector3D, Vector3D, x,1,1 );
_SWIZZLE3( Vector3D, Vector3D, y,x,x );	// *** //
_SWIZZLE3( Vector3D, Vector3D, y,x,y );
_SWIZZLE3( Vector3D, Vector3D, y,x,z );
_SWIZZLE3( Vector3D, Vector3D, y,x,0 );
_SWIZZLE3( Vector3D, Vector3D, y,x,1 );
_SWIZZLE3( Vector3D, Vector3D, y,y,x );
_SWIZZLE3( Vector3D, Vector3D, y,y,y );
_SWIZZLE3( Vector3D, Vector3D, y,y,z );
_SWIZZLE3( Vector3D, Vector3D, y,y,0 );
_SWIZZLE3( Vector3D, Vector3D, y,y,1 );
_SWIZZLE3( Vector3D, Vector3D, y,z,x );
_SWIZZLE3( Vector3D, Vector3D, y,z,y );
_SWIZZLE3( Vector3D, Vector3D, y,z,z );
_SWIZZLE3( Vector3D, Vector3D, y,z,0 );
_SWIZZLE3( Vector3D, Vector3D, y,z,1 );
_SWIZZLE3( Vector3D, Vector3D, y,0,x );
_SWIZZLE3( Vector3D, Vector3D, y,0,y );
_SWIZZLE3( Vector3D, Vector3D, y,0,z );
_SWIZZLE3( Vector3D, Vector3D, y,0,0 );
_SWIZZLE3( Vector3D, Vector3D, y,0,1 );
_SWIZZLE3( Vector3D, Vector3D, y,1,x );
_SWIZZLE3( Vector3D, Vector3D, y,1,y );
_SWIZZLE3( Vector3D, Vector3D, y,1,z );
_SWIZZLE3( Vector3D, Vector3D, y,1,0 );
_SWIZZLE3( Vector3D, Vector3D, y,1,1 );
_SWIZZLE3( Vector3D, Vector3D, z,x,x );	// *** //
_SWIZZLE3( Vector3D, Vector3D, z,x,y );
_SWIZZLE3( Vector3D, Vector3D, z,x,z );
_SWIZZLE3( Vector3D, Vector3D, z,x,0 );
_SWIZZLE3( Vector3D, Vector3D, z,x,1 );
_SWIZZLE3( Vector3D, Vector3D, z,y,x );
_SWIZZLE3( Vector3D, Vector3D, z,y,y );
_SWIZZLE3( Vector3D, Vector3D, z,y,z );
_SWIZZLE3( Vector3D, Vector3D, z,y,0 );
_SWIZZLE3( Vector3D, Vector3D, z,y,1 );
_SWIZZLE3( Vector3D, Vector3D, z,z,x );
_SWIZZLE3( Vector3D, Vector3D, z,z,y );
_SWIZZLE3( Vector3D, Vector3D, z,z,z );
_SWIZZLE3( Vector3D, Vector3D, z,z,0 );
_SWIZZLE3( Vector3D, Vector3D, z,z,1 );
_SWIZZLE3( Vector3D, Vector3D, z,0,x );
_SWIZZLE3( Vector3D, Vector3D, z,0,y );
_SWIZZLE3( Vector3D, Vector3D, z,0,z );
_SWIZZLE3( Vector3D, Vector3D, z,0,0 );
_SWIZZLE3( Vector3D, Vector3D, z,0,1 );
_SWIZZLE3( Vector3D, Vector3D, z,1,x );
_SWIZZLE3( Vector3D, Vector3D, z,1,y );
_SWIZZLE3( Vector3D, Vector3D, z,1,z );
_SWIZZLE3( Vector3D, Vector3D, z,1,0 );
_SWIZZLE3( Vector3D, Vector3D, z,1,1 );	
_SWIZZLE3( Vector3D, Vector3D, 0,x,x );	// *** //
_SWIZZLE3( Vector3D, Vector3D, 0,x,y );
_SWIZZLE3( Vector3D, Vector3D, 0,x,z );
_SWIZZLE3( Vector3D, Vector3D, 0,x,0 );
_SWIZZLE3( Vector3D, Vector3D, 0,x,1 );
_SWIZZLE3( Vector3D, Vector3D, 0,y,x );
_SWIZZLE3( Vector3D, Vector3D, 0,y,y );
_SWIZZLE3( Vector3D, Vector3D, 0,y,z );
_SWIZZLE3( Vector3D, Vector3D, 0,y,0 );
_SWIZZLE3( Vector3D, Vector3D, 0,y,1 );
_SWIZZLE3( Vector3D, Vector3D, 0,z,x );
_SWIZZLE3( Vector3D, Vector3D, 0,z,y );
_SWIZZLE3( Vector3D, Vector3D, 0,z,z );
_SWIZZLE3( Vector3D, Vector3D, 0,z,0 );
_SWIZZLE3( Vector3D, Vector3D, 0,z,1 );
_SWIZZLE3( Vector3D, Vector3D, 0,0,x );
_SWIZZLE3( Vector3D, Vector3D, 0,0,y );
_SWIZZLE3( Vector3D, Vector3D, 0,0,z );
_SWIZZLE3( Vector3D, Vector3D, 0,0,0 );
_SWIZZLE3( Vector3D, Vector3D, 0,0,1 );
_SWIZZLE3( Vector3D, Vector3D, 0,1,x );
_SWIZZLE3( Vector3D, Vector3D, 0,1,y );
_SWIZZLE3( Vector3D, Vector3D, 0,1,z );
_SWIZZLE3( Vector3D, Vector3D, 0,1,0 );
_SWIZZLE3( Vector3D, Vector3D, 0,1,1 );
_SWIZZLE3( Vector3D, Vector3D, 1,x,x );	// *** //
_SWIZZLE3( Vector3D, Vector3D, 1,x,y );
_SWIZZLE3( Vector3D, Vector3D, 1,x,z );
_SWIZZLE3( Vector3D, Vector3D, 1,x,0 );
_SWIZZLE3( Vector3D, Vector3D, 1,x,1 );
_SWIZZLE3( Vector3D, Vector3D, 1,y,x );
_SWIZZLE3( Vector3D, Vector3D, 1,y,y );
_SWIZZLE3( Vector3D, Vector3D, 1,y,z );
_SWIZZLE3( Vector3D, Vector3D, 1,y,0 );
_SWIZZLE3( Vector3D, Vector3D, 1,y,1 );
_SWIZZLE3( Vector3D, Vector3D, 1,z,x );
_SWIZZLE3( Vector3D, Vector3D, 1,z,y );
_SWIZZLE3( Vector3D, Vector3D, 1,z,z );
_SWIZZLE3( Vector3D, Vector3D, 1,z,0 );
_SWIZZLE3( Vector3D, Vector3D, 1,z,1 );
_SWIZZLE3( Vector3D, Vector3D, 1,0,x );
_SWIZZLE3( Vector3D, Vector3D, 1,0,y );
_SWIZZLE3( Vector3D, Vector3D, 1,0,z );
_SWIZZLE3( Vector3D, Vector3D, 1,0,0 );
_SWIZZLE3( Vector3D, Vector3D, 1,0,1 );
_SWIZZLE3( Vector3D, Vector3D, 1,1,x );
_SWIZZLE3( Vector3D, Vector3D, 1,1,y );
_SWIZZLE3( Vector3D, Vector3D, 1,1,z );
_SWIZZLE3( Vector3D, Vector3D, 1,1,0 );
_SWIZZLE3( Vector3D, Vector3D, 1,1,1 );

SWIZZLE4( Vector3D, Vector4D, x,x,x,x );	// *** //
SWIZZLE4( Vector3D, Vector4D, x,x,x,y );
SWIZZLE4( Vector3D, Vector4D, x,x,x,z );
SWIZZLE4( Vector3D, Vector4D, x,x,y,x );
SWIZZLE4( Vector3D, Vector4D, x,x,y,y );
SWIZZLE4( Vector3D, Vector4D, x,x,y,z );
SWIZZLE4( Vector3D, Vector4D, x,x,z,x );
SWIZZLE4( Vector3D, Vector4D, x,x,z,y );
SWIZZLE4( Vector3D, Vector4D, x,x,z,z );
SWIZZLE4( Vector3D, Vector4D, x,y,x,x );
SWIZZLE4( Vector3D, Vector4D, x,y,x,y );
SWIZZLE4( Vector3D, Vector4D, x,y,x,z );
SWIZZLE4( Vector3D, Vector4D, x,y,y,x );
SWIZZLE4( Vector3D, Vector4D, x,y,y,y );
SWIZZLE4( Vector3D, Vector4D, x,y,y,z );
SWIZZLE4( Vector3D, Vector4D, x,y,z,x );
SWIZZLE4( Vector3D, Vector4D, x,y,z,y );
SWIZZLE4( Vector3D, Vector4D, x,y,z,z );
SWIZZLE4( Vector3D, Vector4D, x,z,x,x );
SWIZZLE4( Vector3D, Vector4D, x,z,x,y );
SWIZZLE4( Vector3D, Vector4D, x,z,x,z );
SWIZZLE4( Vector3D, Vector4D, x,z,y,x );
SWIZZLE4( Vector3D, Vector4D, x,z,y,y );
SWIZZLE4( Vector3D, Vector4D, x,z,y,z );
SWIZZLE4( Vector3D, Vector4D, x,z,z,x );
SWIZZLE4( Vector3D, Vector4D, x,z,z,y );
SWIZZLE4( Vector3D, Vector4D, x,z,z,z );
SWIZZLE4( Vector3D, Vector4D, y,x,x,x );	// *** //
SWIZZLE4( Vector3D, Vector4D, y,x,x,y );
SWIZZLE4( Vector3D, Vector4D, y,x,x,z );
SWIZZLE4( Vector3D, Vector4D, y,x,y,x );
SWIZZLE4( Vector3D, Vector4D, y,x,y,y );
SWIZZLE4( Vector3D, Vector4D, y,x,y,z );
SWIZZLE4( Vector3D, Vector4D, y,x,z,x );
SWIZZLE4( Vector3D, Vector4D, y,x,z,y );
SWIZZLE4( Vector3D, Vector4D, y,x,z,z );
SWIZZLE4( Vector3D, Vector4D, y,y,x,x );
SWIZZLE4( Vector3D, Vector4D, y,y,x,y );
SWIZZLE4( Vector3D, Vector4D, y,y,x,z );
SWIZZLE4( Vector3D, Vector4D, y,y,y,x );
SWIZZLE4( Vector3D, Vector4D, y,y,y,y );
SWIZZLE4( Vector3D, Vector4D, y,y,y,z );
SWIZZLE4( Vector3D, Vector4D, y,y,z,x );
SWIZZLE4( Vector3D, Vector4D, y,y,z,y );
SWIZZLE4( Vector3D, Vector4D, y,y,z,z );
SWIZZLE4( Vector3D, Vector4D, y,z,x,x );
SWIZZLE4( Vector3D, Vector4D, y,z,x,y );
SWIZZLE4( Vector3D, Vector4D, y,z,x,z );
SWIZZLE4( Vector3D, Vector4D, y,z,y,x );
SWIZZLE4( Vector3D, Vector4D, y,z,y,y );
SWIZZLE4( Vector3D, Vector4D, y,z,y,z );
SWIZZLE4( Vector3D, Vector4D, y,z,z,x );
SWIZZLE4( Vector3D, Vector4D, y,z,z,y );
SWIZZLE4( Vector3D, Vector4D, y,z,z,z );
SWIZZLE4( Vector3D, Vector4D, z,x,x,x );	// *** //
SWIZZLE4( Vector3D, Vector4D, z,x,x,y );
SWIZZLE4( Vector3D, Vector4D, z,x,x,z );
SWIZZLE4( Vector3D, Vector4D, z,x,y,x );
SWIZZLE4( Vector3D, Vector4D, z,x,y,y );
SWIZZLE4( Vector3D, Vector4D, z,x,y,z );
SWIZZLE4( Vector3D, Vector4D, z,x,z,x );
SWIZZLE4( Vector3D, Vector4D, z,x,z,y );
SWIZZLE4( Vector3D, Vector4D, z,x,z,z );
SWIZZLE4( Vector3D, Vector4D, z,y,x,x );
SWIZZLE4( Vector3D, Vector4D, z,y,x,y );
SWIZZLE4( Vector3D, Vector4D, z,y,x,z );
SWIZZLE4( Vector3D, Vector4D, z,y,y,x );
SWIZZLE4( Vector3D, Vector4D, z,y,y,y );
SWIZZLE4( Vector3D, Vector4D, z,y,y,z );
SWIZZLE4( Vector3D, Vector4D, z,y,z,x );
SWIZZLE4( Vector3D, Vector4D, z,y,z,y );
SWIZZLE4( Vector3D, Vector4D, z,y,z,z );
SWIZZLE4( Vector3D, Vector4D, z,z,x,x );
SWIZZLE4( Vector3D, Vector4D, z,z,x,y );
SWIZZLE4( Vector3D, Vector4D, z,z,x,z );
SWIZZLE4( Vector3D, Vector4D, z,z,y,x );
SWIZZLE4( Vector3D, Vector4D, z,z,y,y );
SWIZZLE4( Vector3D, Vector4D, z,z,y,z );
SWIZZLE4( Vector3D, Vector4D, z,z,z,x );
SWIZZLE4( Vector3D, Vector4D, z,z,z,y );
SWIZZLE4( Vector3D, Vector4D, z,z,z,z );

_SWIZZLE4( Vector3D, Vector4D, x,x,x,x );	// *** //
_SWIZZLE4( Vector3D, Vector4D, x,x,x,y );
_SWIZZLE4( Vector3D, Vector4D, x,x,x,z );
_SWIZZLE4( Vector3D, Vector4D, x,x,x,0 );
_SWIZZLE4( Vector3D, Vector4D, x,x,x,1 );
_SWIZZLE4( Vector3D, Vector4D, x,x,y,x );
_SWIZZLE4( Vector3D, Vector4D, x,x,y,y );
_SWIZZLE4( Vector3D, Vector4D, x,x,y,z );
_SWIZZLE4( Vector3D, Vector4D, x,x,y,0 );
_SWIZZLE4( Vector3D, Vector4D, x,x,y,1 );
_SWIZZLE4( Vector3D, Vector4D, x,x,z,x );
_SWIZZLE4( Vector3D, Vector4D, x,x,z,y );
_SWIZZLE4( Vector3D, Vector4D, x,x,z,z );
_SWIZZLE4( Vector3D, Vector4D, x,x,z,0 );
_SWIZZLE4( Vector3D, Vector4D, x,x,z,1 );
_SWIZZLE4( Vector3D, Vector4D, x,x,0,x );
_SWIZZLE4( Vector3D, Vector4D, x,x,0,y );
_SWIZZLE4( Vector3D, Vector4D, x,x,0,z );
_SWIZZLE4( Vector3D, Vector4D, x,x,0,0 );
_SWIZZLE4( Vector3D, Vector4D, x,x,0,1 );
_SWIZZLE4( Vector3D, Vector4D, x,x,1,x );
_SWIZZLE4( Vector3D, Vector4D, x,x,1,y );
_SWIZZLE4( Vector3D, Vector4D, x,x,1,z );
_SWIZZLE4( Vector3D, Vector4D, x,x,1,0 );
_SWIZZLE4( Vector3D, Vector4D, x,x,1,1 );
_SWIZZLE4( Vector3D, Vector4D, x,y,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, x,y,x,y );
_SWIZZLE4( Vector3D, Vector4D, x,y,x,z );
_SWIZZLE4( Vector3D, Vector4D, x,y,x,0 );
_SWIZZLE4( Vector3D, Vector4D, x,y,x,1 );
_SWIZZLE4( Vector3D, Vector4D, x,y,y,x );
_SWIZZLE4( Vector3D, Vector4D, x,y,y,y );
_SWIZZLE4( Vector3D, Vector4D, x,y,y,z );
_SWIZZLE4( Vector3D, Vector4D, x,y,y,0 );
_SWIZZLE4( Vector3D, Vector4D, x,y,y,1 );
_SWIZZLE4( Vector3D, Vector4D, x,y,z,x );
_SWIZZLE4( Vector3D, Vector4D, x,y,z,y );
_SWIZZLE4( Vector3D, Vector4D, x,y,z,z );
_SWIZZLE4( Vector3D, Vector4D, x,y,z,0 );
_SWIZZLE4( Vector3D, Vector4D, x,y,z,1 );
_SWIZZLE4( Vector3D, Vector4D, x,y,0,x );
_SWIZZLE4( Vector3D, Vector4D, x,y,0,y );
_SWIZZLE4( Vector3D, Vector4D, x,y,0,z );
_SWIZZLE4( Vector3D, Vector4D, x,y,0,0 );
_SWIZZLE4( Vector3D, Vector4D, x,y,0,1 );
_SWIZZLE4( Vector3D, Vector4D, x,y,1,x );
_SWIZZLE4( Vector3D, Vector4D, x,y,1,y );
_SWIZZLE4( Vector3D, Vector4D, x,y,1,z );
_SWIZZLE4( Vector3D, Vector4D, x,y,1,0 );
_SWIZZLE4( Vector3D, Vector4D, x,y,1,1 );
_SWIZZLE4( Vector3D, Vector4D, x,z,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, x,z,x,y );
_SWIZZLE4( Vector3D, Vector4D, x,z,x,z );
_SWIZZLE4( Vector3D, Vector4D, x,z,x,0 );
_SWIZZLE4( Vector3D, Vector4D, x,z,x,1 );
_SWIZZLE4( Vector3D, Vector4D, x,z,y,x );
_SWIZZLE4( Vector3D, Vector4D, x,z,y,y );
_SWIZZLE4( Vector3D, Vector4D, x,z,y,z );
_SWIZZLE4( Vector3D, Vector4D, x,z,y,0 );
_SWIZZLE4( Vector3D, Vector4D, x,z,y,1 );
_SWIZZLE4( Vector3D, Vector4D, x,z,z,x );
_SWIZZLE4( Vector3D, Vector4D, x,z,z,y );
_SWIZZLE4( Vector3D, Vector4D, x,z,z,z );
_SWIZZLE4( Vector3D, Vector4D, x,z,z,0 );
_SWIZZLE4( Vector3D, Vector4D, x,z,z,1 );
_SWIZZLE4( Vector3D, Vector4D, x,z,0,x );
_SWIZZLE4( Vector3D, Vector4D, x,z,0,y );
_SWIZZLE4( Vector3D, Vector4D, x,z,0,z );
_SWIZZLE4( Vector3D, Vector4D, x,z,0,0 );
_SWIZZLE4( Vector3D, Vector4D, x,z,0,1 );
_SWIZZLE4( Vector3D, Vector4D, x,z,1,x );
_SWIZZLE4( Vector3D, Vector4D, x,z,1,y );
_SWIZZLE4( Vector3D, Vector4D, x,z,1,z );
_SWIZZLE4( Vector3D, Vector4D, x,z,1,0 );
_SWIZZLE4( Vector3D, Vector4D, x,z,1,1 );
_SWIZZLE4( Vector3D, Vector4D, x,0,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, x,0,x,y );
_SWIZZLE4( Vector3D, Vector4D, x,0,x,z );
_SWIZZLE4( Vector3D, Vector4D, x,0,x,0 );
_SWIZZLE4( Vector3D, Vector4D, x,0,x,1 );
_SWIZZLE4( Vector3D, Vector4D, x,0,y,x );
_SWIZZLE4( Vector3D, Vector4D, x,0,y,y );
_SWIZZLE4( Vector3D, Vector4D, x,0,y,z );
_SWIZZLE4( Vector3D, Vector4D, x,0,y,0 );
_SWIZZLE4( Vector3D, Vector4D, x,0,y,1 );
_SWIZZLE4( Vector3D, Vector4D, x,0,z,x );
_SWIZZLE4( Vector3D, Vector4D, x,0,z,y );
_SWIZZLE4( Vector3D, Vector4D, x,0,z,z );
_SWIZZLE4( Vector3D, Vector4D, x,0,z,0 );
_SWIZZLE4( Vector3D, Vector4D, x,0,z,1 );
_SWIZZLE4( Vector3D, Vector4D, x,0,0,x );
_SWIZZLE4( Vector3D, Vector4D, x,0,0,y );
_SWIZZLE4( Vector3D, Vector4D, x,0,0,z );
_SWIZZLE4( Vector3D, Vector4D, x,0,0,0 );
_SWIZZLE4( Vector3D, Vector4D, x,0,0,1 );
_SWIZZLE4( Vector3D, Vector4D, x,0,1,x );
_SWIZZLE4( Vector3D, Vector4D, x,0,1,y );
_SWIZZLE4( Vector3D, Vector4D, x,0,1,z );
_SWIZZLE4( Vector3D, Vector4D, x,0,1,0 );
_SWIZZLE4( Vector3D, Vector4D, x,0,1,1 );
_SWIZZLE4( Vector3D, Vector4D, x,1,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, x,1,x,y );
_SWIZZLE4( Vector3D, Vector4D, x,1,x,z );
_SWIZZLE4( Vector3D, Vector4D, x,1,x,0 );
_SWIZZLE4( Vector3D, Vector4D, x,1,x,1 );
_SWIZZLE4( Vector3D, Vector4D, x,1,y,x );
_SWIZZLE4( Vector3D, Vector4D, x,1,y,y );
_SWIZZLE4( Vector3D, Vector4D, x,1,y,z );
_SWIZZLE4( Vector3D, Vector4D, x,1,y,0 );
_SWIZZLE4( Vector3D, Vector4D, x,1,y,1 );
_SWIZZLE4( Vector3D, Vector4D, x,1,z,x );
_SWIZZLE4( Vector3D, Vector4D, x,1,z,y );
_SWIZZLE4( Vector3D, Vector4D, x,1,z,z );
_SWIZZLE4( Vector3D, Vector4D, x,1,z,0 );
_SWIZZLE4( Vector3D, Vector4D, x,1,z,1 );
_SWIZZLE4( Vector3D, Vector4D, x,1,0,x );
_SWIZZLE4( Vector3D, Vector4D, x,1,0,y );
_SWIZZLE4( Vector3D, Vector4D, x,1,0,z );
_SWIZZLE4( Vector3D, Vector4D, x,1,0,0 );
_SWIZZLE4( Vector3D, Vector4D, x,1,0,1 );
_SWIZZLE4( Vector3D, Vector4D, x,1,1,x );
_SWIZZLE4( Vector3D, Vector4D, x,1,1,y );
_SWIZZLE4( Vector3D, Vector4D, x,1,1,z );
_SWIZZLE4( Vector3D, Vector4D, x,1,1,0 );
_SWIZZLE4( Vector3D, Vector4D, x,1,1,1 );
_SWIZZLE4( Vector3D, Vector4D, y,x,x,x );	// *** //
_SWIZZLE4( Vector3D, Vector4D, y,x,x,y );
_SWIZZLE4( Vector3D, Vector4D, y,x,x,z );
_SWIZZLE4( Vector3D, Vector4D, y,x,x,0 );
_SWIZZLE4( Vector3D, Vector4D, y,x,x,1 );
_SWIZZLE4( Vector3D, Vector4D, y,x,y,x );
_SWIZZLE4( Vector3D, Vector4D, y,x,y,y );
_SWIZZLE4( Vector3D, Vector4D, y,x,y,z );
_SWIZZLE4( Vector3D, Vector4D, y,x,y,0 );
_SWIZZLE4( Vector3D, Vector4D, y,x,y,1 );
_SWIZZLE4( Vector3D, Vector4D, y,x,z,x );
_SWIZZLE4( Vector3D, Vector4D, y,x,z,y );
_SWIZZLE4( Vector3D, Vector4D, y,x,z,z );
_SWIZZLE4( Vector3D, Vector4D, y,x,z,0 );
_SWIZZLE4( Vector3D, Vector4D, y,x,z,1 );
_SWIZZLE4( Vector3D, Vector4D, y,x,0,x );
_SWIZZLE4( Vector3D, Vector4D, y,x,0,y );
_SWIZZLE4( Vector3D, Vector4D, y,x,0,z );
_SWIZZLE4( Vector3D, Vector4D, y,x,0,0 );
_SWIZZLE4( Vector3D, Vector4D, y,x,0,1 );
_SWIZZLE4( Vector3D, Vector4D, y,x,1,x );
_SWIZZLE4( Vector3D, Vector4D, y,x,1,y );
_SWIZZLE4( Vector3D, Vector4D, y,x,1,z );
_SWIZZLE4( Vector3D, Vector4D, y,x,1,0 );
_SWIZZLE4( Vector3D, Vector4D, y,x,1,1 );
_SWIZZLE4( Vector3D, Vector4D, y,y,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, y,y,x,y );
_SWIZZLE4( Vector3D, Vector4D, y,y,x,z );
_SWIZZLE4( Vector3D, Vector4D, y,y,x,0 );
_SWIZZLE4( Vector3D, Vector4D, y,y,x,1 );
_SWIZZLE4( Vector3D, Vector4D, y,y,y,x );
_SWIZZLE4( Vector3D, Vector4D, y,y,y,y );
_SWIZZLE4( Vector3D, Vector4D, y,y,y,z );
_SWIZZLE4( Vector3D, Vector4D, y,y,y,0 );
_SWIZZLE4( Vector3D, Vector4D, y,y,y,1 );
_SWIZZLE4( Vector3D, Vector4D, y,y,z,x );
_SWIZZLE4( Vector3D, Vector4D, y,y,z,y );
_SWIZZLE4( Vector3D, Vector4D, y,y,z,z );
_SWIZZLE4( Vector3D, Vector4D, y,y,z,0 );
_SWIZZLE4( Vector3D, Vector4D, y,y,z,1 );
_SWIZZLE4( Vector3D, Vector4D, y,y,0,x );
_SWIZZLE4( Vector3D, Vector4D, y,y,0,y );
_SWIZZLE4( Vector3D, Vector4D, y,y,0,z );
_SWIZZLE4( Vector3D, Vector4D, y,y,0,0 );
_SWIZZLE4( Vector3D, Vector4D, y,y,0,1 );
_SWIZZLE4( Vector3D, Vector4D, y,y,1,x );
_SWIZZLE4( Vector3D, Vector4D, y,y,1,y );
_SWIZZLE4( Vector3D, Vector4D, y,y,1,z );
_SWIZZLE4( Vector3D, Vector4D, y,y,1,0 );
_SWIZZLE4( Vector3D, Vector4D, y,y,1,1 );
_SWIZZLE4( Vector3D, Vector4D, y,z,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, y,z,x,y );
_SWIZZLE4( Vector3D, Vector4D, y,z,x,z );
_SWIZZLE4( Vector3D, Vector4D, y,z,x,0 );
_SWIZZLE4( Vector3D, Vector4D, y,z,x,1 );
_SWIZZLE4( Vector3D, Vector4D, y,z,y,x );
_SWIZZLE4( Vector3D, Vector4D, y,z,y,y );
_SWIZZLE4( Vector3D, Vector4D, y,z,y,z );
_SWIZZLE4( Vector3D, Vector4D, y,z,y,0 );
_SWIZZLE4( Vector3D, Vector4D, y,z,y,1 );
_SWIZZLE4( Vector3D, Vector4D, y,z,z,x );
_SWIZZLE4( Vector3D, Vector4D, y,z,z,y );
_SWIZZLE4( Vector3D, Vector4D, y,z,z,z );
_SWIZZLE4( Vector3D, Vector4D, y,z,z,0 );
_SWIZZLE4( Vector3D, Vector4D, y,z,z,1 );
_SWIZZLE4( Vector3D, Vector4D, y,z,0,x );
_SWIZZLE4( Vector3D, Vector4D, y,z,0,y );
_SWIZZLE4( Vector3D, Vector4D, y,z,0,z );
_SWIZZLE4( Vector3D, Vector4D, y,z,0,0 );
_SWIZZLE4( Vector3D, Vector4D, y,z,0,1 );
_SWIZZLE4( Vector3D, Vector4D, y,z,1,x );
_SWIZZLE4( Vector3D, Vector4D, y,z,1,y );
_SWIZZLE4( Vector3D, Vector4D, y,z,1,z );
_SWIZZLE4( Vector3D, Vector4D, y,z,1,0 );
_SWIZZLE4( Vector3D, Vector4D, y,z,1,1 );
_SWIZZLE4( Vector3D, Vector4D, y,0,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, y,0,x,y );
_SWIZZLE4( Vector3D, Vector4D, y,0,x,z );
_SWIZZLE4( Vector3D, Vector4D, y,0,x,0 );
_SWIZZLE4( Vector3D, Vector4D, y,0,x,1 );
_SWIZZLE4( Vector3D, Vector4D, y,0,y,x );
_SWIZZLE4( Vector3D, Vector4D, y,0,y,y );
_SWIZZLE4( Vector3D, Vector4D, y,0,y,z );
_SWIZZLE4( Vector3D, Vector4D, y,0,y,0 );
_SWIZZLE4( Vector3D, Vector4D, y,0,y,1 );
_SWIZZLE4( Vector3D, Vector4D, y,0,z,x );
_SWIZZLE4( Vector3D, Vector4D, y,0,z,y );
_SWIZZLE4( Vector3D, Vector4D, y,0,z,z );
_SWIZZLE4( Vector3D, Vector4D, y,0,z,0 );
_SWIZZLE4( Vector3D, Vector4D, y,0,z,1 );
_SWIZZLE4( Vector3D, Vector4D, y,0,0,x );
_SWIZZLE4( Vector3D, Vector4D, y,0,0,y );
_SWIZZLE4( Vector3D, Vector4D, y,0,0,z );
_SWIZZLE4( Vector3D, Vector4D, y,0,0,0 );
_SWIZZLE4( Vector3D, Vector4D, y,0,0,1 );
_SWIZZLE4( Vector3D, Vector4D, y,0,1,x );
_SWIZZLE4( Vector3D, Vector4D, y,0,1,y );
_SWIZZLE4( Vector3D, Vector4D, y,0,1,z );
_SWIZZLE4( Vector3D, Vector4D, y,0,1,0 );
_SWIZZLE4( Vector3D, Vector4D, y,0,1,1 );
_SWIZZLE4( Vector3D, Vector4D, y,1,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, y,1,x,y );
_SWIZZLE4( Vector3D, Vector4D, y,1,x,z );
_SWIZZLE4( Vector3D, Vector4D, y,1,x,0 );
_SWIZZLE4( Vector3D, Vector4D, y,1,x,1 );
_SWIZZLE4( Vector3D, Vector4D, y,1,y,x );
_SWIZZLE4( Vector3D, Vector4D, y,1,y,y );
_SWIZZLE4( Vector3D, Vector4D, y,1,y,z );
_SWIZZLE4( Vector3D, Vector4D, y,1,y,0 );
_SWIZZLE4( Vector3D, Vector4D, y,1,y,1 );
_SWIZZLE4( Vector3D, Vector4D, y,1,z,x );
_SWIZZLE4( Vector3D, Vector4D, y,1,z,y );
_SWIZZLE4( Vector3D, Vector4D, y,1,z,z );
_SWIZZLE4( Vector3D, Vector4D, y,1,z,0 );
_SWIZZLE4( Vector3D, Vector4D, y,1,z,1 );
_SWIZZLE4( Vector3D, Vector4D, y,1,0,x );
_SWIZZLE4( Vector3D, Vector4D, y,1,0,y );
_SWIZZLE4( Vector3D, Vector4D, y,1,0,z );
_SWIZZLE4( Vector3D, Vector4D, y,1,0,0 );
_SWIZZLE4( Vector3D, Vector4D, y,1,0,1 );
_SWIZZLE4( Vector3D, Vector4D, y,1,1,x );
_SWIZZLE4( Vector3D, Vector4D, y,1,1,y );
_SWIZZLE4( Vector3D, Vector4D, y,1,1,z );
_SWIZZLE4( Vector3D, Vector4D, y,1,1,0 );
_SWIZZLE4( Vector3D, Vector4D, y,1,1,1 );
_SWIZZLE4( Vector3D, Vector4D, z,x,x,x );	// *** //
_SWIZZLE4( Vector3D, Vector4D, z,x,x,y );
_SWIZZLE4( Vector3D, Vector4D, z,x,x,z );
_SWIZZLE4( Vector3D, Vector4D, z,x,x,0 );
_SWIZZLE4( Vector3D, Vector4D, z,x,x,1 );
_SWIZZLE4( Vector3D, Vector4D, z,x,y,x );
_SWIZZLE4( Vector3D, Vector4D, z,x,y,y );
_SWIZZLE4( Vector3D, Vector4D, z,x,y,z );
_SWIZZLE4( Vector3D, Vector4D, z,x,y,0 );
_SWIZZLE4( Vector3D, Vector4D, z,x,y,1 );
_SWIZZLE4( Vector3D, Vector4D, z,x,z,x );
_SWIZZLE4( Vector3D, Vector4D, z,x,z,y );
_SWIZZLE4( Vector3D, Vector4D, z,x,z,z );
_SWIZZLE4( Vector3D, Vector4D, z,x,z,0 );
_SWIZZLE4( Vector3D, Vector4D, z,x,z,1 );
_SWIZZLE4( Vector3D, Vector4D, z,x,0,x );
_SWIZZLE4( Vector3D, Vector4D, z,x,0,y );
_SWIZZLE4( Vector3D, Vector4D, z,x,0,z );
_SWIZZLE4( Vector3D, Vector4D, z,x,0,0 );
_SWIZZLE4( Vector3D, Vector4D, z,x,0,1 );
_SWIZZLE4( Vector3D, Vector4D, z,x,1,x );
_SWIZZLE4( Vector3D, Vector4D, z,x,1,y );
_SWIZZLE4( Vector3D, Vector4D, z,x,1,z );
_SWIZZLE4( Vector3D, Vector4D, z,x,1,0 );
_SWIZZLE4( Vector3D, Vector4D, z,x,1,1 );
_SWIZZLE4( Vector3D, Vector4D, z,y,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, z,y,x,y );
_SWIZZLE4( Vector3D, Vector4D, z,y,x,z );
_SWIZZLE4( Vector3D, Vector4D, z,y,x,0 );
_SWIZZLE4( Vector3D, Vector4D, z,y,x,1 );
_SWIZZLE4( Vector3D, Vector4D, z,y,y,x );
_SWIZZLE4( Vector3D, Vector4D, z,y,y,y );
_SWIZZLE4( Vector3D, Vector4D, z,y,y,z );
_SWIZZLE4( Vector3D, Vector4D, z,y,y,0 );
_SWIZZLE4( Vector3D, Vector4D, z,y,y,1 );
_SWIZZLE4( Vector3D, Vector4D, z,y,z,x );
_SWIZZLE4( Vector3D, Vector4D, z,y,z,y );
_SWIZZLE4( Vector3D, Vector4D, z,y,z,z );
_SWIZZLE4( Vector3D, Vector4D, z,y,z,0 );
_SWIZZLE4( Vector3D, Vector4D, z,y,z,1 );
_SWIZZLE4( Vector3D, Vector4D, z,y,0,x );
_SWIZZLE4( Vector3D, Vector4D, z,y,0,y );
_SWIZZLE4( Vector3D, Vector4D, z,y,0,z );
_SWIZZLE4( Vector3D, Vector4D, z,y,0,0 );
_SWIZZLE4( Vector3D, Vector4D, z,y,0,1 );
_SWIZZLE4( Vector3D, Vector4D, z,y,1,x );
_SWIZZLE4( Vector3D, Vector4D, z,y,1,y );
_SWIZZLE4( Vector3D, Vector4D, z,y,1,z );
_SWIZZLE4( Vector3D, Vector4D, z,y,1,0 );
_SWIZZLE4( Vector3D, Vector4D, z,y,1,1 );
_SWIZZLE4( Vector3D, Vector4D, z,z,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, z,z,x,y );
_SWIZZLE4( Vector3D, Vector4D, z,z,x,z );
_SWIZZLE4( Vector3D, Vector4D, z,z,x,0 );
_SWIZZLE4( Vector3D, Vector4D, z,z,x,1 );
_SWIZZLE4( Vector3D, Vector4D, z,z,y,x );
_SWIZZLE4( Vector3D, Vector4D, z,z,y,y );
_SWIZZLE4( Vector3D, Vector4D, z,z,y,z );
_SWIZZLE4( Vector3D, Vector4D, z,z,y,0 );
_SWIZZLE4( Vector3D, Vector4D, z,z,y,1 );
_SWIZZLE4( Vector3D, Vector4D, z,z,z,x );
_SWIZZLE4( Vector3D, Vector4D, z,z,z,y );
_SWIZZLE4( Vector3D, Vector4D, z,z,z,z );
_SWIZZLE4( Vector3D, Vector4D, z,z,z,0 );
_SWIZZLE4( Vector3D, Vector4D, z,z,z,1 );
_SWIZZLE4( Vector3D, Vector4D, z,z,0,x );
_SWIZZLE4( Vector3D, Vector4D, z,z,0,y );
_SWIZZLE4( Vector3D, Vector4D, z,z,0,z );
_SWIZZLE4( Vector3D, Vector4D, z,z,0,0 );
_SWIZZLE4( Vector3D, Vector4D, z,z,0,1 );
_SWIZZLE4( Vector3D, Vector4D, z,z,1,x );
_SWIZZLE4( Vector3D, Vector4D, z,z,1,y );
_SWIZZLE4( Vector3D, Vector4D, z,z,1,z );
_SWIZZLE4( Vector3D, Vector4D, z,z,1,0 );
_SWIZZLE4( Vector3D, Vector4D, z,z,1,1 );
_SWIZZLE4( Vector3D, Vector4D, z,0,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, z,0,x,y );
_SWIZZLE4( Vector3D, Vector4D, z,0,x,z );
_SWIZZLE4( Vector3D, Vector4D, z,0,x,0 );
_SWIZZLE4( Vector3D, Vector4D, z,0,x,1 );
_SWIZZLE4( Vector3D, Vector4D, z,0,y,x );
_SWIZZLE4( Vector3D, Vector4D, z,0,y,y );
_SWIZZLE4( Vector3D, Vector4D, z,0,y,z );
_SWIZZLE4( Vector3D, Vector4D, z,0,y,0 );
_SWIZZLE4( Vector3D, Vector4D, z,0,y,1 );
_SWIZZLE4( Vector3D, Vector4D, z,0,z,x );
_SWIZZLE4( Vector3D, Vector4D, z,0,z,y );
_SWIZZLE4( Vector3D, Vector4D, z,0,z,z );
_SWIZZLE4( Vector3D, Vector4D, z,0,z,0 );
_SWIZZLE4( Vector3D, Vector4D, z,0,z,1 );
_SWIZZLE4( Vector3D, Vector4D, z,0,0,x );
_SWIZZLE4( Vector3D, Vector4D, z,0,0,y );
_SWIZZLE4( Vector3D, Vector4D, z,0,0,z );
_SWIZZLE4( Vector3D, Vector4D, z,0,0,0 );
_SWIZZLE4( Vector3D, Vector4D, z,0,0,1 );
_SWIZZLE4( Vector3D, Vector4D, z,0,1,x );
_SWIZZLE4( Vector3D, Vector4D, z,0,1,y );
_SWIZZLE4( Vector3D, Vector4D, z,0,1,z );
_SWIZZLE4( Vector3D, Vector4D, z,0,1,0 );
_SWIZZLE4( Vector3D, Vector4D, z,0,1,1 );
_SWIZZLE4( Vector3D, Vector4D, z,1,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, z,1,x,y );
_SWIZZLE4( Vector3D, Vector4D, z,1,x,z );
_SWIZZLE4( Vector3D, Vector4D, z,1,x,0 );
_SWIZZLE4( Vector3D, Vector4D, z,1,x,1 );
_SWIZZLE4( Vector3D, Vector4D, z,1,y,x );
_SWIZZLE4( Vector3D, Vector4D, z,1,y,y );
_SWIZZLE4( Vector3D, Vector4D, z,1,y,z );
_SWIZZLE4( Vector3D, Vector4D, z,1,y,0 );
_SWIZZLE4( Vector3D, Vector4D, z,1,y,1 );
_SWIZZLE4( Vector3D, Vector4D, z,1,z,x );
_SWIZZLE4( Vector3D, Vector4D, z,1,z,y );
_SWIZZLE4( Vector3D, Vector4D, z,1,z,z );
_SWIZZLE4( Vector3D, Vector4D, z,1,z,0 );
_SWIZZLE4( Vector3D, Vector4D, z,1,z,1 );
_SWIZZLE4( Vector3D, Vector4D, z,1,0,x );
_SWIZZLE4( Vector3D, Vector4D, z,1,0,y );
_SWIZZLE4( Vector3D, Vector4D, z,1,0,z );
_SWIZZLE4( Vector3D, Vector4D, z,1,0,0 );
_SWIZZLE4( Vector3D, Vector4D, z,1,0,1 );
_SWIZZLE4( Vector3D, Vector4D, z,1,1,x );
_SWIZZLE4( Vector3D, Vector4D, z,1,1,y );
_SWIZZLE4( Vector3D, Vector4D, z,1,1,z );
_SWIZZLE4( Vector3D, Vector4D, z,1,1,0 );
_SWIZZLE4( Vector3D, Vector4D, z,1,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,x,x );	// *** //
_SWIZZLE4( Vector3D, Vector4D, 0,x,x,y );
_SWIZZLE4( Vector3D, Vector4D, 0,x,x,z );
_SWIZZLE4( Vector3D, Vector4D, 0,x,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,y,x );
_SWIZZLE4( Vector3D, Vector4D, 0,x,y,y );
_SWIZZLE4( Vector3D, Vector4D, 0,x,y,z );
_SWIZZLE4( Vector3D, Vector4D, 0,x,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,z,x );
_SWIZZLE4( Vector3D, Vector4D, 0,x,z,y );
_SWIZZLE4( Vector3D, Vector4D, 0,x,z,z );
_SWIZZLE4( Vector3D, Vector4D, 0,x,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,0,x );
_SWIZZLE4( Vector3D, Vector4D, 0,x,0,y );
_SWIZZLE4( Vector3D, Vector4D, 0,x,0,z );
_SWIZZLE4( Vector3D, Vector4D, 0,x,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,1,x );
_SWIZZLE4( Vector3D, Vector4D, 0,x,1,y );
_SWIZZLE4( Vector3D, Vector4D, 0,x,1,z );
_SWIZZLE4( Vector3D, Vector4D, 0,x,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,x,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 0,y,x,y );
_SWIZZLE4( Vector3D, Vector4D, 0,y,x,z );
_SWIZZLE4( Vector3D, Vector4D, 0,y,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,y,x );
_SWIZZLE4( Vector3D, Vector4D, 0,y,y,y );
_SWIZZLE4( Vector3D, Vector4D, 0,y,y,z );
_SWIZZLE4( Vector3D, Vector4D, 0,y,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,z,x );
_SWIZZLE4( Vector3D, Vector4D, 0,y,z,y );
_SWIZZLE4( Vector3D, Vector4D, 0,y,z,z );
_SWIZZLE4( Vector3D, Vector4D, 0,y,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,0,x );
_SWIZZLE4( Vector3D, Vector4D, 0,y,0,y );
_SWIZZLE4( Vector3D, Vector4D, 0,y,0,z );
_SWIZZLE4( Vector3D, Vector4D, 0,y,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,1,x );
_SWIZZLE4( Vector3D, Vector4D, 0,y,1,y );
_SWIZZLE4( Vector3D, Vector4D, 0,y,1,z );
_SWIZZLE4( Vector3D, Vector4D, 0,y,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,y,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 0,z,x,y );
_SWIZZLE4( Vector3D, Vector4D, 0,z,x,z );
_SWIZZLE4( Vector3D, Vector4D, 0,z,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,y,x );
_SWIZZLE4( Vector3D, Vector4D, 0,z,y,y );
_SWIZZLE4( Vector3D, Vector4D, 0,z,y,z );
_SWIZZLE4( Vector3D, Vector4D, 0,z,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,z,x );
_SWIZZLE4( Vector3D, Vector4D, 0,z,z,y );
_SWIZZLE4( Vector3D, Vector4D, 0,z,z,z );
_SWIZZLE4( Vector3D, Vector4D, 0,z,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,0,x );
_SWIZZLE4( Vector3D, Vector4D, 0,z,0,y );
_SWIZZLE4( Vector3D, Vector4D, 0,z,0,z );
_SWIZZLE4( Vector3D, Vector4D, 0,z,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,1,x );
_SWIZZLE4( Vector3D, Vector4D, 0,z,1,y );
_SWIZZLE4( Vector3D, Vector4D, 0,z,1,z );
_SWIZZLE4( Vector3D, Vector4D, 0,z,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,z,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 0,0,x,y );
_SWIZZLE4( Vector3D, Vector4D, 0,0,x,z );
_SWIZZLE4( Vector3D, Vector4D, 0,0,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,y,x );
_SWIZZLE4( Vector3D, Vector4D, 0,0,y,y );
_SWIZZLE4( Vector3D, Vector4D, 0,0,y,z );
_SWIZZLE4( Vector3D, Vector4D, 0,0,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,z,x );
_SWIZZLE4( Vector3D, Vector4D, 0,0,z,y );
_SWIZZLE4( Vector3D, Vector4D, 0,0,z,z );
_SWIZZLE4( Vector3D, Vector4D, 0,0,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,0,x );
_SWIZZLE4( Vector3D, Vector4D, 0,0,0,y );
_SWIZZLE4( Vector3D, Vector4D, 0,0,0,z );
_SWIZZLE4( Vector3D, Vector4D, 0,0,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,1,x );
_SWIZZLE4( Vector3D, Vector4D, 0,0,1,y );
_SWIZZLE4( Vector3D, Vector4D, 0,0,1,z );
_SWIZZLE4( Vector3D, Vector4D, 0,0,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,0,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 0,1,x,y );
_SWIZZLE4( Vector3D, Vector4D, 0,1,x,z );
_SWIZZLE4( Vector3D, Vector4D, 0,1,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,y,x );
_SWIZZLE4( Vector3D, Vector4D, 0,1,y,y );
_SWIZZLE4( Vector3D, Vector4D, 0,1,y,z );
_SWIZZLE4( Vector3D, Vector4D, 0,1,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,z,x );
_SWIZZLE4( Vector3D, Vector4D, 0,1,z,y );
_SWIZZLE4( Vector3D, Vector4D, 0,1,z,z );
_SWIZZLE4( Vector3D, Vector4D, 0,1,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,0,x );
_SWIZZLE4( Vector3D, Vector4D, 0,1,0,y );
_SWIZZLE4( Vector3D, Vector4D, 0,1,0,z );
_SWIZZLE4( Vector3D, Vector4D, 0,1,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,1,x );
_SWIZZLE4( Vector3D, Vector4D, 0,1,1,y );
_SWIZZLE4( Vector3D, Vector4D, 0,1,1,z );
_SWIZZLE4( Vector3D, Vector4D, 0,1,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 0,1,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,x,x );	// *** //
_SWIZZLE4( Vector3D, Vector4D, 1,x,x,y );
_SWIZZLE4( Vector3D, Vector4D, 1,x,x,z );
_SWIZZLE4( Vector3D, Vector4D, 1,x,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,y,x );
_SWIZZLE4( Vector3D, Vector4D, 1,x,y,y );
_SWIZZLE4( Vector3D, Vector4D, 1,x,y,z );
_SWIZZLE4( Vector3D, Vector4D, 1,x,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,z,x );
_SWIZZLE4( Vector3D, Vector4D, 1,x,z,y );
_SWIZZLE4( Vector3D, Vector4D, 1,x,z,z );
_SWIZZLE4( Vector3D, Vector4D, 1,x,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,0,x );
_SWIZZLE4( Vector3D, Vector4D, 1,x,0,y );
_SWIZZLE4( Vector3D, Vector4D, 1,x,0,z );
_SWIZZLE4( Vector3D, Vector4D, 1,x,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,1,x );
_SWIZZLE4( Vector3D, Vector4D, 1,x,1,y );
_SWIZZLE4( Vector3D, Vector4D, 1,x,1,z );
_SWIZZLE4( Vector3D, Vector4D, 1,x,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,x,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 1,y,x,y );
_SWIZZLE4( Vector3D, Vector4D, 1,y,x,z );
_SWIZZLE4( Vector3D, Vector4D, 1,y,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,y,x );
_SWIZZLE4( Vector3D, Vector4D, 1,y,y,y );
_SWIZZLE4( Vector3D, Vector4D, 1,y,y,z );
_SWIZZLE4( Vector3D, Vector4D, 1,y,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,z,x );
_SWIZZLE4( Vector3D, Vector4D, 1,y,z,y );
_SWIZZLE4( Vector3D, Vector4D, 1,y,z,z );
_SWIZZLE4( Vector3D, Vector4D, 1,y,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,0,x );
_SWIZZLE4( Vector3D, Vector4D, 1,y,0,y );
_SWIZZLE4( Vector3D, Vector4D, 1,y,0,z );
_SWIZZLE4( Vector3D, Vector4D, 1,y,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,1,x );
_SWIZZLE4( Vector3D, Vector4D, 1,y,1,y );
_SWIZZLE4( Vector3D, Vector4D, 1,y,1,z );
_SWIZZLE4( Vector3D, Vector4D, 1,y,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,y,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 1,z,x,y );
_SWIZZLE4( Vector3D, Vector4D, 1,z,x,z );
_SWIZZLE4( Vector3D, Vector4D, 1,z,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,y,x );
_SWIZZLE4( Vector3D, Vector4D, 1,z,y,y );
_SWIZZLE4( Vector3D, Vector4D, 1,z,y,z );
_SWIZZLE4( Vector3D, Vector4D, 1,z,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,z,x );
_SWIZZLE4( Vector3D, Vector4D, 1,z,z,y );
_SWIZZLE4( Vector3D, Vector4D, 1,z,z,z );
_SWIZZLE4( Vector3D, Vector4D, 1,z,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,0,x );
_SWIZZLE4( Vector3D, Vector4D, 1,z,0,y );
_SWIZZLE4( Vector3D, Vector4D, 1,z,0,z );
_SWIZZLE4( Vector3D, Vector4D, 1,z,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,1,x );
_SWIZZLE4( Vector3D, Vector4D, 1,z,1,y );
_SWIZZLE4( Vector3D, Vector4D, 1,z,1,z );
_SWIZZLE4( Vector3D, Vector4D, 1,z,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,z,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 1,0,x,y );
_SWIZZLE4( Vector3D, Vector4D, 1,0,x,z );
_SWIZZLE4( Vector3D, Vector4D, 1,0,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,y,x );
_SWIZZLE4( Vector3D, Vector4D, 1,0,y,y );
_SWIZZLE4( Vector3D, Vector4D, 1,0,y,z );
_SWIZZLE4( Vector3D, Vector4D, 1,0,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,z,x );
_SWIZZLE4( Vector3D, Vector4D, 1,0,z,y );
_SWIZZLE4( Vector3D, Vector4D, 1,0,z,z );
_SWIZZLE4( Vector3D, Vector4D, 1,0,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,0,x );
_SWIZZLE4( Vector3D, Vector4D, 1,0,0,y );
_SWIZZLE4( Vector3D, Vector4D, 1,0,0,z );
_SWIZZLE4( Vector3D, Vector4D, 1,0,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,1,x );
_SWIZZLE4( Vector3D, Vector4D, 1,0,1,y );
_SWIZZLE4( Vector3D, Vector4D, 1,0,1,z );
_SWIZZLE4( Vector3D, Vector4D, 1,0,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,0,1,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,x,x );	// * //
_SWIZZLE4( Vector3D, Vector4D, 1,1,x,y );
_SWIZZLE4( Vector3D, Vector4D, 1,1,x,z );
_SWIZZLE4( Vector3D, Vector4D, 1,1,x,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,x,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,y,x );
_SWIZZLE4( Vector3D, Vector4D, 1,1,y,y );
_SWIZZLE4( Vector3D, Vector4D, 1,1,y,z );
_SWIZZLE4( Vector3D, Vector4D, 1,1,y,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,y,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,z,x );
_SWIZZLE4( Vector3D, Vector4D, 1,1,z,y );
_SWIZZLE4( Vector3D, Vector4D, 1,1,z,z );
_SWIZZLE4( Vector3D, Vector4D, 1,1,z,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,z,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,0,x );
_SWIZZLE4( Vector3D, Vector4D, 1,1,0,y );
_SWIZZLE4( Vector3D, Vector4D, 1,1,0,z );
_SWIZZLE4( Vector3D, Vector4D, 1,1,0,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,0,1 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,1,x );
_SWIZZLE4( Vector3D, Vector4D, 1,1,1,y );
_SWIZZLE4( Vector3D, Vector4D, 1,1,1,z );
_SWIZZLE4( Vector3D, Vector4D, 1,1,1,0 );
_SWIZZLE4( Vector3D, Vector4D, 1,1,1,1 );
// - ------------------------------------------------------------------------------------------ - //
// TODO: Vector4D Swizzles
// - ------------------------------------------------------------------------------------------ - //
#undef _SWIZZLE4
#undef _SWIZZLE3
#undef _SWIZZLE2
// - ------------------------------------------------------------------------------------------ - //
#undef SWIZZLE4
#undef SWIZZLE3
#undef SWIZZLE2
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline Vector2D NearestPoint_on_Line( const Vector2D& A, const Vector2D& B, const Vector2D& Pt ) {
	Vector2D Line = B - A;
	Vector2D LineNormal = Line;
	Real LineLength = LineNormal.NormalizeRet();
	
	Vector2D Ray = Pt - A;
	
	Real PosOnLine = dot(LineNormal, Ray);
	
	if ( PosOnLine < Real::Zero ) {
		PosOnLine = Real::Zero;
	}
	if ( PosOnLine > LineLength ) {
		PosOnLine = LineLength;
	}
	
	return A + (LineNormal * PosOnLine);
}
// - ------------------------------------------------------------------------------------------ - //
struct Vec2CPOL {
	Vector2D LineNormal;
	Real LineLength;
	Real PosOnLine;
};
// - ------------------------------------------------------------------------------------------ - //
inline Vec2CPOL Calc_NearestPoint_on_Line( const Vector2D& A, const Vector2D& B, const Vector2D& Pt ) {
	Vec2CPOL Ret;
	
	Vector2D Line = B - A;
	Ret.LineNormal = Line;
	Ret.LineLength = Ret.LineNormal.NormalizeRet();
	
	Vector2D Ray = Pt - A;
	
	Ret.PosOnLine = dot(Ret.LineNormal, Ray);
	
	if ( Ret.PosOnLine < Real::Zero ) {
		Ret.PosOnLine = Real::Zero;
	}
	if ( Ret.PosOnLine > Ret.LineLength ) {
		Ret.PosOnLine = Ret.LineLength;
	}
	
	return Ret;
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector_H__ //
// - ------------------------------------------------------------------------------------------ - //
