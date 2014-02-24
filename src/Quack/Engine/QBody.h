// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QBODY_H__
#define __QUACK_ENGINE_QBODY_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
template<typename T1>
inline bool DoStep_Body( T1& A, const QProp& Prop ) {
	QVec Velocity = A.GetVelocity();
	A.Old = A.Pos;
	// Accum is (Accum * TimeStep * TimeStep), but TimeStep is 1 so it cancels out. //
	A.Pos += Velocity + A.Accum;
	
	// Instead of setting the Accumulator to 0, set it equal to Gravity //
	A.Accum = Prop.Gravity;
	
	return true;	
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T1, typename T2>
inline bool FinishSolve_Body( T1& A, T2& B, QVec Line, const QFloat& RadiusSum ) {
	QFloat MassSum = B.InvMass + A.InvMass;
	return_if_value( false, MassSum == QFloat::Zero );

	QFloat Mag = Line.MagnitudeSquared();
	
	if ( Mag < (RadiusSum*RadiusSum) ) {
		Mag = RadiusSum - Line.NormalizeRet();
		A.Pos -= (Line * Mag) * (A.InvMass / MassSum);
		B.Pos += (Line * Mag) * (B.InvMass / MassSum);
		return true;
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
