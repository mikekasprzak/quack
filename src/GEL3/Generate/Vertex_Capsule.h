// - ------------------------------------------------------------------------------------------ - //
// NOTE: This is not perfect. With different radius, at a shallow angle it looks wrong (nubby).
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GENERATE_VERTEX_CAPSULE_H__
#define __GEL_GENERATE_VERTEX_CAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_Capsule( T* Dest, const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB, const st32 Steps = GEL_GENERATE_DEFAULT_CIRCLE_STEPS ) {
	Vector3D* Out;

	Vector3D Line = PosB - PosA;
	Vector3D Normal = Line.Normal();

	float FloatSteps = 1.0f / (float)Steps;
	st32 HalfSteps = Steps >> 1;
	
	float BaseAngle = ArcTan2( Normal.x, -Normal.y ).ToFloat();
    
    // NOTE: <= is not < //
	for ( st32 idx = 0; idx <= HalfSteps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = PosA.x + (Real::Cos(idx * FloatSteps + BaseAngle) * RadiusA);
		Out->y = PosA.y + (Real::Sin(idx * FloatSteps + BaseAngle) * RadiusA);
		Out->z = PosA.z;
	}

	for ( st32 idx = HalfSteps; idx <= Steps; idx++ ) {
		Out = (Vector3D*)Dest++;
		Out->x = PosB.x + (Real::Cos(idx * FloatSteps + BaseAngle) * RadiusB);
		Out->y = PosB.y + (Real::Sin(idx * FloatSteps + BaseAngle) * RadiusB);
		Out->z = PosB.z;
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_Capsule( const st32 Steps = GEL_GENERATE_DEFAULT_CIRCLE_STEPS ) {
	return Steps+2;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GENERATE_VERTEX_CAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
