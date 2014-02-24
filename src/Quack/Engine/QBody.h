// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QBODY_H__
#define __QUACK_ENGINE_QBODY_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
template<typename T1, typename T2>
inline bool FinishSolve_Body( T1& A, T2& B, QVec Line, const QFloat& RadiusSum, const QFloat& MassSum ) {
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
