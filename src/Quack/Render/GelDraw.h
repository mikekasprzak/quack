// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_RENDER_GELDRAW_H__
#define __GEL_RENDER_GELDRAW_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Math.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _PRIMITIVE_DRAW_RADIUS(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ...) \
void _FUNCNAME_( const Matrix4x4& Mat, const Vector3D& Pos = Vector3D(0,0), const Vector2D& Radius = Vector2D(10,10), const GelColor Color = GEL_RGB_WHITE ); \
void _FUNCNAME_( const Matrix4x4& Mat, const Vector3D& Pos = Vector3D(0,0), const Real& Radius = Real(10), const GelColor Color = GEL_RGB_WHITE );
// - ------------------------------------------------------------------------------------------ - //
_PRIMITIVE_DRAW_RADIUS(gelDrawCircle,Circle,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(gelDrawSquare,RadiusRect,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(gelDrawDiamond,Diamond,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(gelDrawTriangle,Circle,GEL_LINE_LOOP,3);
_PRIMITIVE_DRAW_RADIUS(gelDrawCross,Cross,GEL_LINES);
_PRIMITIVE_DRAW_RADIUS(gelDrawX,X,GEL_LINES);

_PRIMITIVE_DRAW_RADIUS(gelDrawCircleFill,Circle,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawSquareFill,RadiusRect,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawDiamondFill,Diamond,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawTriangleFill,Circle,GEL_TRIANGLE_FAN,3);
// - ------------------------------------------------------------------------------------------ - //
#undef _PRIMITIVE_DRAW_RADIUS
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _PRIMITIVE_DRAW_CAPSULE(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ... ) \
void _FUNCNAME_( const Matrix4x4& Mat, const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const GelColor Color );
// - ------------------------------------------------------------------------------------------ - //
_PRIMITIVE_DRAW_CAPSULE(gelDrawCapsule,Capsule,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_CAPSULE(gelDrawDiamondCapsule,DiamondCapsule,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_CAPSULE(gelDrawFlatCapsule,FlatCapsule,GEL_LINE_LOOP);

_PRIMITIVE_DRAW_CAPSULE(gelDrawCapsuleFill,Capsule,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_CAPSULE(gelDrawDiamondCapsuleFill,DiamondCapsule,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_CAPSULE(gelDrawFlatCapsuleFill,FlatCapsule,GEL_TRIANGLE_FAN);
// - ------------------------------------------------------------------------------------------ - //
#undef _PRIMITIVE_DRAW_CAPSULE
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_RENDER_GELDRAW_H__ //
// - ------------------------------------------------------------------------------------------ - //
