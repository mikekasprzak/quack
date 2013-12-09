// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GENERATE_VERTEX_DIAMONDCAPSULE_H__
#define __GEL_GENERATE_VERTEX_DIAMONDCAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
// Diamond Capsule has a singe point at radius distance as an End Cap //
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
// - ------------------------------------------------------------------------------------------ - //
template< typename T >
inline void generate_Vertex3D_DiamondCapsule( T* Dest, const Vector3D& PosA, const Real& RadiusA, const Vector3D& PosB, const Real& RadiusB ) {
	Vector3D* Out;

	Vector3D Line = PosB - PosA;
	Vector3D Tangent = cross(Line,Vector3D(0,0,1)).Normal();
	Vector3D LineNormal = Line.Normal();
	
	// Side //
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosA.x + (RadiusA * Tangent.x), PosA.y + (RadiusA * Tangent.y), PosA.z );
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosB.x + (RadiusB * Tangent.x), PosB.y + (RadiusB * Tangent.y), PosB.z );
	// End Cap //
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosB.x + (RadiusB * LineNormal.x), PosB.y + (RadiusB * LineNormal.y), PosB.z );
	// Side //
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosB.x - (RadiusB * Tangent.x), PosB.y - (RadiusB * Tangent.y), PosB.z );
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosA.x - (RadiusA * Tangent.x), PosA.y - (RadiusA * Tangent.y), PosA.z );
	// End Cap //
	Out = (Vector3D*)Dest++;
	*Out = Vector3D( PosA.x - (RadiusA * LineNormal.x), PosA.y - (RadiusA * LineNormal.y), PosA.z );
}
// - ------------------------------------------------------------------------------------------ - //
inline const st32 size_Vertex3D_DiamondCapsule() {
	return 6;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GENERATE_VERTEX_DIAMONDCAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
