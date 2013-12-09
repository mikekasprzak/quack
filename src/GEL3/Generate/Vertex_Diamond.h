// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GENERATE_VERTEX_DIAMOND_H__
#define __GEL_GENERATE_VERTEX_DIAMOND_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Diamond( T* Dest, const Vector3D& Pos, const Vector2D& HalfShape ) {
	Vector3D* Out;
	
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(+HalfShape.x,0);
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(0,-HalfShape.y);
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(-HalfShape.x,0);
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(0,+HalfShape.y);
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Diamond( T* Dest, const Vector2D& Pos, const Vector2D& HalfShape ) {
	generate_Vertex3D_Diamond( Dest, Pos.ToVector3D(), HalfShape.ToVector3D() );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Diamond( T* Dest, const Vector2D& Pos, const Real& Radius ) {
	generate_Vertex3D_Diamond( Dest, Pos.ToVector3D(), Vector2D(Radius,Radius) );
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Diamond( T* Dest, const Vector3D& Pos, const Real& Radius ) {
	generate_Vertex3D_Diamond( Dest, Pos, Vector2D(Radius,Radius) );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Diamond() {
	return 4;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GENERATE_VERTEX_DIAMOND_H__ //
// - ------------------------------------------------------------------------------------------ - //
