// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GENERATE_VERTEX_CIRCLE_H__
#define __GEL_GENERATE_VERTEX_CIRCLE_H__
// - ------------------------------------------------------------------------------------------ - //
// action_OutputVertexType_Shape
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Circle( T* Dest, const Vector3D& Pos, const Vector2D& Radius, const st32 Steps = GEL_GENERATE_DEFAULT_CIRCLE_STEPS ) {
	Vector3D* Out;

	float FloatSteps = 1.0f / (float)Steps;
    
	for ( st32 idx = 0; idx < Steps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = Pos.x + (Real::Cos(idx * FloatSteps) * Radius.x);
		Out->y = Pos.y + (Real::Sin(idx * FloatSteps) * Radius.y);
		Out->z = Pos.z;
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Circle( T* Dest, const Vector3D& Pos, const Real& Radius, const st32 Steps = GEL_GENERATE_DEFAULT_CIRCLE_STEPS ) {
	generate_Vertex3D_Circle( Dest, Pos, Vector3D(Radius,Radius), Steps );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Circle( const st32 Steps = GEL_GENERATE_DEFAULT_CIRCLE_STEPS ) {
	return Steps;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_CircleNormals( T* Dest, const Vector3D& Pos, const Vector2D& = Vector2D::One, const Real NormalLength = Real(4) ) {
	Vector3D* Out;

	Out = (Vector3D*)Dest++;
	*Out = Pos - Vector3D(0,0,NormalLength);
	Out = (Vector3D*)Dest++;
	*Out = Pos + Vector3D(0,0,NormalLength);
}
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_CircleNormals( T* Dest, const Vector3D& Pos, const Real& Radius = Real::One, const Real NormalLength = Real(4) ) {
	generate_Vertex3D_CircleNormals( Dest, Pos, Vector2D(Radius,Radius), NormalLength );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_CircleNormals() {
	return 2;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GENERATE_VERTEX_CIRCLE_H__ //
// - ------------------------------------------------------------------------------------------ - //
