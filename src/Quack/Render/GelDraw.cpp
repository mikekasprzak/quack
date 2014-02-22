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

_PRIMITIVE_DRAW_RADIUS(gelDrawCircleFill,Circle,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawSquareFill,RadiusRect,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawDiamondFill,Diamond,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(gelDrawTriangleFill,Circle,GEL_TRIANGLE_FAN,3);
// - ------------------------------------------------------------------------------------------ - //
#undef _PRIMITIVE_DRAW_RADIUS
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//#define _PRIMITIVE_DRAW_CAPSULE(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ... ) \
//SQInteger _FUNCNAME_( HSQUIRRELVM v ) { \
//	Vector3D PosA(0,0); \
//	float RadiusA = 10.0f; \
//	Vector3D PosB(0,0); \
//	float RadiusB = 10.0f; \
//	\
//	Matrix4x4* uMatrix = 0; \
//	\
//	GelColor Color = GEL_RGB_WHITE; \
//	\
//	int NumArgs = sq_gettop(v); \
//	if ( NumArgs >= 2 ) { \
//		/* ARG1: Matrix */ \
//		sq_getinstanceup(v,2,(void**)&uMatrix,NULL); \
//		\
//		/* ARG2: Position */ \
//		if ( NumArgs >= 3 ) { \
//			void* UserPointer; \
//			sq_getinstanceup(v,3,(void**)&UserPointer,NULL); \
//			\
//			/* TODO: Check type (vec2, vec3) */ \
//			\
//			Vector2D* Vec = (Vector2D*)UserPointer; \
//			PosA = Vec->ToVector3D(); \
//		} \
//		\
//		/* ARG3: Radius */ \
//		if ( NumArgs >= 4 ) { \
//			sq_getfloat(v,4,&RadiusA); \
//		} \
//		\
//		/* ARG2: Position */ \
//		if ( NumArgs >= 5 ) { \
//			void* UserPointer; \
//			sq_getinstanceup(v,5,(void**)&UserPointer,NULL); \
//			\
//			/* TODO: Check type (vec2, vec3) */ \
//			\
//			Vector2D* Vec = (Vector2D*)UserPointer; \
//			PosB = Vec->ToVector3D(); \
//		} \
//		\
//		/* ARG3: Radius */ \
//		if ( NumArgs >= 6 ) { \
//			sq_getfloat(v,6,&RadiusB); \
//		} \
//		\
//		/* ARG4: Color */ \
//		if ( NumArgs >= 7 ) { \
//			GelColor* ColorArg; \
//			sq_getinstanceup(v,7,(void**)&ColorArg,0); \
//			Color = *ColorArg; \
//		} \
//		\
//		const st32 VertCount = size_Vertex3D_ ## _PRIMNAME_( __VA_ARGS__ ); \
//		Vector3D Verts[ VertCount ]; \
//		generate_Vertex3D_ ## _PRIMNAME_( Verts, PosA, Real(RadiusA), PosB, Real(RadiusB), ## __VA_ARGS__ ); \
//		\
//		Gel::RenderFlat( _DRAWMODE_, *uMatrix, Color, Verts, VertCount ); \
//	} \
//	else { \
//		Log("! " #_FUNCNAME_ " -- Not enough arguments"); \
//	} \
//	\
//	return SQ_VOID; \
//}
//// - ------------------------------------------------------------------------------------------ - //
//_PRIMITIVE_DRAW_CAPSULE(qkDrawCapsule,Capsule,GEL_LINE_LOOP);
//_PRIMITIVE_DRAW_CAPSULE(qkDrawDiamondCapsule,DiamondCapsule,GEL_LINE_LOOP);
//_PRIMITIVE_DRAW_CAPSULE(qkDrawFlatCapsule,FlatCapsule,GEL_LINE_LOOP);
//
//_PRIMITIVE_DRAW_CAPSULE(qkDrawCapsuleFill,Capsule,GEL_TRIANGLE_FAN);
//_PRIMITIVE_DRAW_CAPSULE(qkDrawDiamondCapsuleFill,DiamondCapsule,GEL_TRIANGLE_FAN);
//_PRIMITIVE_DRAW_CAPSULE(qkDrawFlatCapsuleFill,FlatCapsule,GEL_TRIANGLE_FAN);
//// - ------------------------------------------------------------------------------------------ - //
//#undef _PRIMITIVE_DRAW_CAPSULE
// - ------------------------------------------------------------------------------------------ - //

