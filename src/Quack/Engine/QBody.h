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
	A.Pos += (Velocity + A.Accum);// * QFloat(0.999f);
	
	// Instead of setting the Accumulator to 0, set it equal to Gravity //
	A.Accum = Prop.Gravity;
	
	return true;	
}
// - ------------------------------------------------------------------------------------------ - //
// Simple Finish Function that handles Masses //
template<typename T1, typename T2>
inline bool _FinishSolve_Body( T1& A, T2& B, QVec Line, const QFloat& RadiusSum ) {
	QFloat InvMassSum = B.InvMass + A.InvMass;
	return_if_value( false, InvMassSum == QFloat::Zero );
	QFloat MassSum = QFloat::One / InvMassSum;

	QFloat Mag = Line.MagnitudeSquared();
	
	if ( Mag < (RadiusSum*RadiusSum) ) {
		Mag = RadiusSum - Line.NormalizeRet();
		A.Pos -= (Line * Mag) * (A.InvMass * MassSum);
		B.Pos += (Line * Mag) * (B.InvMass * MassSum);
		return true;
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T1, typename T2>
inline bool _Regular_FinishSolve_Body( T1& A, T2& B, QVec Line, const QFloat& RadiusSum ) {
	QFloat InvMassSum = B.InvMass + A.InvMass;
	return_if_value( false, InvMassSum == QFloat::Zero );
//	QFloat InvMassSum = QFloat::One / MassSum;
	
	if ( Line.MagnitudeSquared() < (RadiusSum*RadiusSum) ) {
		QFloat Diff = RadiusSum - Line.NormalizeRet();

		// TODO: Fix this code so that Penetrations after a collision work correctly. //
		//       If I don't do this, then objects solved without enough relaxation steps //
		//       will exhibit the bug I'm trying to avoid by doing this test. //
		if ( Diff > Real(0.1f) ) {
			// Take Velocities before we move Pos so we don't accidentially accumulate more force //
			QVec VelocityA = A.GetVelocity();
			QVec VelocityB = B.GetVelocity();

			// 50% solving, which is less error prone than using the mass here (use it later instead) //
			Diff *= QFloat::Half;
			A.Pos -= Line * Diff;
			B.Pos += Line * Diff;
	
			QFloat ContactA = dot(VelocityA,Line);
			QFloat ContactB = dot(VelocityB,-Line);
	
			QVec ImpactA = Line * ContactA;
			QVec ImpactB = -Line * ContactB;
			
			// When Velocity and Line are Parallel, the cross is 0 so Tangents cancel out // 
			QVec TangentA = VelocityA.Tangent().Normal();//cross(cross(VelocityA,Line),Line).Normal();
			QVec TangentB = VelocityB.Tangent().Normal();//cross(cross(VelocityB,-Line),-Line).Normal();
			
			QFloat AMass = A.GetMass();
			QFloat BMass = B.GetMass();
			QFloat MassSum = (AMass+BMass);
	
			QVec MomentumA = (AMass*ImpactA);
			QVec MomentumB = (BMass*ImpactB);
			QVec Momentum = MomentumA + MomentumB;
	
			QFloat Restitution = Real::Max( A.Restitution, B.Restitution );
			QFloat Friction = Real::Sqrt( A.Friction * B.Friction );
			
			QVec ContactVelocityA = ((Restitution*BMass*(ImpactB-ImpactA)+Momentum)/MassSum) * Friction;
			QVec ContactVelocityB = ((Restitution*AMass*(ImpactA-ImpactB)+Momentum)/MassSum) * Friction;
	
			QVec TangentVelocityA = TangentA * dot(VelocityA,TangentA);
			QVec TangentVelocityB = TangentB * dot(VelocityB,TangentB);
	
			A.Old = A.Pos - (TangentVelocityA+ContactVelocityA);
			B.Old = B.Pos - (TangentVelocityB+ContactVelocityB);

			return true;
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T1, typename T2>
inline bool _BInfinite_FinishSolve_Body( T1& A, T2& B, QVec Line, const QFloat& RadiusSum ) {
	QFloat InvMassSum = B.InvMass + A.InvMass;
	return_if_value( false, InvMassSum == QFloat::Zero );
//	QFloat InvMassSum = QFloat::One / MassSum;
	
	if ( Line.MagnitudeSquared() < (RadiusSum*RadiusSum) ) {
		QFloat Diff = RadiusSum - Line.NormalizeRet();

		// TODO: Fix this code so that Penetrations after a collision work correctly. //
		//       If I don't do this, then objects solved without enough relaxation steps //
		//       will exhibit the bug I'm trying to avoid by doing this test. //
		if ( Diff > Real(0.1f) ) {
			// Take Velocities before we move Pos so we don't accidentially accumulate more force //
			QVec VelocityA = A.GetVelocity();
			//QVec VelocityB = B.GetVelocity();

			// 100% solving //
			A.Pos -= Line * Diff;
			//B.Pos += Line * Diff;
	
			QFloat ContactA = dot(VelocityA,Line);
			//QFloat ContactB = Real::Zero;//dot(VelocityB,-Line);
	
			QVec ImpactA = Line * ContactA;
			QVec ImpactB = QVec::Zero;//-Line * ContactB;
			
			// When Velocity and Line are Parallel, the cross is 0 so Tangents cancel out // 
			QVec TangentA = VelocityA.Tangent().Normal();//cross(cross(VelocityA,Line),Line).Normal();
			//QVec TangentB = VelocityB.Tangent().Normal();//cross(cross(VelocityB,-Line),-Line).Normal();
			
			//QFloat AMass = A.GetMass();
			//QFloat BMass = B.GetMass();
			//QFloat MassSum = (AMass+BMass);
	
			//QVec MomentumA = (AMass*ImpactA);
			//QVec MomentumB = QVec::Zero;//(BMass*ImpactB);
			//QVec Momentum = MomentumA + MomentumB;
	
			QFloat Restitution = A.Restitution;//Real::Max( A.Restitution, B.Restitution );
			QFloat Friction = Real::Sqrt( A.Friction );// * B.Friction );
			
			// 1+Restitution may be wrong... it bounced off with 2x energy //
			QVec ContactVelocityA = (((QFloat::One+Restitution)*(ImpactB-ImpactA)+ImpactA)) * Friction;
			//QVec ContactVelocityA = ((Restitution*BMass*(ImpactB-ImpactA)+Momentum)/MassSum) * Friction;
			//QVec ContactVelocityB = ((Restitution*AMass*(ImpactA-ImpactB)+Momentum)/MassSum) * Friction;
	
			QVec TangentVelocityA = TangentA * dot(VelocityA,TangentA);
			//QVec TangentVelocityB = TangentB * dot(VelocityB,TangentB);
	
			A.Old = A.Pos - (TangentVelocityA+ContactVelocityA);
			//B.Old = B.Pos - (TangentVelocityB+ContactVelocityB);

			return true;
		}
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T1, typename T2>
inline bool FinishSolve_Body( T1& A, T2& B, QVec Line, const QFloat& RadiusSum ) {
	if ( A.InvMass == QFloat::Zero ) {
		return_if_value( false, B.InvMass == QFloat::Zero );
		return _BInfinite_FinishSolve_Body(B,A,-Line,RadiusSum);
//		return _FinishSolve_Body(A,B,Line,RadiusSum);
	}
	else if ( B.InvMass == QFloat::Zero ) {
		return_if_value( false, A.InvMass == QFloat::Zero );
		return _BInfinite_FinishSolve_Body(A,B,Line,RadiusSum);
//		return _FinishSolve_Body(A,B,Line,RadiusSum);
	}
	return _Regular_FinishSolve_Body(A,B,Line,RadiusSum);
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODY_H__ //
// - ------------------------------------------------------------------------------------------ - //
