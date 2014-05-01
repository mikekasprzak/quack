// - ------------------------------------------------------------------------------------------ - //
#include "GelDraw.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/Asset.h>
#include <Graphics/Graphics.h>
#include <Render/Render.h>
#include <Font/Font.h>
#include <Model/Model.h>

#include <Generate/Generate.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _PRIMITIVE_DRAW_RADIUS(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ...) \
void _FUNCNAME_( const Matrix4x4& Mat, const Vector3D& Pos, const Vector2D& Radius, const GelColor Color ) { \
	const st32 VertCount = size_Vertex3D_ ## _PRIMNAME_( __VA_ARGS__ ); \
	Vector3D Verts[ VertCount ]; \
	generate_Vertex3D_ ## _PRIMNAME_( Verts, Pos, Radius, ## __VA_ARGS__ ); \
	\
	Gel::RenderFlat( _DRAWMODE_, Mat, Color, Verts, VertCount ); \
} \
void _FUNCNAME_( const Matrix4x4& Mat, const Vector3D& Pos, const Real& Radius, const GelColor Color ) { \
	_FUNCNAME_(Mat,Pos,Vector2D(Radius,Radius),Color); \
}
// - ------------------------------------------------------------------------------------------ - //
_PRIMITIVE_DRAW_RADIUS(gelDrawCircle,Circle,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(gelDrawSquare,RadiusRect,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(gelDrawDiamond,Diamond,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(gelDrawTriangle,Circle,GEL_LINE_LOOP,3);
_PRIMITIVE_DRAW_RADIUS(gelDrawCross,Cross,GEL_LINES);
_PRIMITIVE_DRAW_RADIUS(gelDrawX,X,GEL_LINES);
_PRIMITIVE_DRAW_RADIUS(gelDrawRect,Rect,GEL_LINE_LOOP);

_PRIMITIVE_DRAW_RADIUS(gelDrawCircleFill,Circle,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawSquareFill,RadiusRect,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawDiamondFill,Diamond,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawTriangleFill,Circle,GEL_TRIANGLE_FAN,3);
_PRIMITIVE_DRAW_RADIUS(gelDrawRectFill,Rect,GEL_TRIANGLE_FAN);
// - ------------------------------------------------------------------------------------------ - //
#undef _PRIMITIVE_DRAW_RADIUS
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _PRIMITIVE_DRAW_CAPSULE(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ... ) \
void _FUNCNAME_( const Matrix4x4& Mat, const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const GelColor Color ) { \
	const st32 VertCount = size_Vertex3D_ ## _PRIMNAME_( __VA_ARGS__ ); \
	Vector3D Verts[ VertCount ]; \
	generate_Vertex3D_ ## _PRIMNAME_( Verts, PosA, RadiusA, PosB, RadiusB, ## __VA_ARGS__ ); \
	\
	Gel::RenderFlat( _DRAWMODE_, Mat, Color, Verts, VertCount ); \
}
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

