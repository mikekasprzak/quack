// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GENERATE_VERTEX_RADIUSRECT_H__
#define __GEL_GENERATE_VERTEX_RADIUSRECT_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_RadiusRect( T* Dest, const Vector3D& Pos, const Vector2D& HalfShape ) {
	Vector3D* Out;
	
	Out = (Vector3D*)Dest++;
	*Out = Pos - HalfShape.ToVector3D();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(+HalfShape.x,-HalfShape.y);
	Out = (Vector3D*)Dest++;
	*Out = Pos + HalfShape.ToVector3D();
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(-HalfShape.x,+HalfShape.y);
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_RadiusRect( T* Dest, const Vector3D& Pos, const Real& Radius ) {
	generate_Vertex3D_RadiusRect( Dest, Pos, Vector2D(Radius,Radius) );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_RadiusRect() {
	return 4;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GENERATE_VERTEX_RADIUSRECT_H__ //
// - ------------------------------------------------------------------------------------------ - //
