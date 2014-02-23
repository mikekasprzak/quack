// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QBODYCAPSULE_H__
#define __QUACK_ENGINE_QBODYCAPSULE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QBodyCapsule {
	typedef QBodyCapsule thistype;
public:
	static void InitBody( QBody* self ) {
		self->Type = QB_CAPSULE;
		self->GetInvMass = (QBody::QGetInvMassFunc)_GetInvMass;
//		self->Step = (QBody::QStepFunc)_Step;
	}
public:
	// Capsule //
	QVec 	Pos;
	QFloat	RadiusA;
	QVec	Line;		// Ray of the direction and length of the capsule shape //
	QFloat	RadiusB;
	
	// Verlet Physics //
	QVec 	Old;
	QFloat	InvMass;

public:
	inline QBodyCapsule( const QVec& _Pos, const QFloat& _RadiusA, const QVec& _Line, const QFloat& _RadiusB, const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		RadiusA( _RadiusA ),
		Line( _Line ),
		RadiusB( _RadiusB ),
		Old( _Pos ),
		InvMass( _InvMass )
	{
	}
	
	inline QRect GetRect() {
		QVec RadiusVecA(RadiusA,RadiusA);
		QRect Ret( Pos - RadiusVecA, RadiusVecA + RadiusVecA );
		QVec RadiusVecB(RadiusB,RadiusB);
		Ret += QRect( Pos + Line - RadiusVecB, RadiusVecB + RadiusVecB );
		return Ret;
	}

public:
	static QFloat _GetInvMass( const thistype* self ) { return self->GetInvMass(); }
	inline QFloat GetInvMass() const {
		return InvMass;
	}

//	static bool _Step( thistype* self, const QProp& Prop ) { return self->Step( Prop ); }
	inline bool Step( const QProp& Prop ) {
		QVec Velocity = Pos - Old;
		Old = Pos;
		Pos += Velocity + Prop.Gravity;
		
		return true;
	}
};
// - ------------------------------------------------------------------------------------------ - //
//inline bool Solve_Body( QBodyCapsule& A, QBodyCapsule& B ) {
//	QFloat MassSum = B.InvMass + A.InvMass;
//	return_if_value( false, MassSum == QFloat::Zero );
//
//	QFloat RadiusSum = B.Radius + A.Radius; // Larger than Magnitude //
//
//	QVec Line = B.Pos - A.Pos;
//	QFloat Mag = Line.MagnitudeSquared();
//	
//	if ( Mag < (RadiusSum*RadiusSum) ) {
//		Mag = RadiusSum - Line.NormalizeRet();
//		A.Pos -= (Line * Mag) * (A.InvMass / MassSum);
//		B.Pos += (Line * Mag) * (B.InvMass / MassSum);
//		return true;
//	}
//	return false;
//}
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodySphere& A, QBodyCapsule& B ) {
	QFloat MassSum = B.InvMass + A.InvMass;
	return_if_value( false, MassSum == QFloat::Zero );

	QVec BPos = NearestPoint_on_Line(B.Pos,B.Pos+B.Line,A.Pos);
	QFloat BRadius = B.RadiusA; // FIX ME //

	QFloat RadiusSum = BRadius + A.Radius; // Larger than Magnitude //

	QVec Line = BPos - A.Pos;
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
//inline bool Solve_Body( QBodyAABB& A, QBodySphere& B ) {
//	QFloat MassSum = B.InvMass + A.InvMass;
//	return_if_value( false, MassSum == QFloat::Zero );
//
//	QFloat RadiusSum = B.Radius; // Larger than Magnitude //
//
//	QVec ANearestPoint = A.GetRect().NearestPoint( B.Pos );
//	
//	QVec Line = B.Pos - ANearestPoint;
//	QFloat Mag = Line.MagnitudeSquared();
//	
//	if ( Mag < (RadiusSum*RadiusSum) ) {
//		Mag = RadiusSum - Line.NormalizeRet();
//		A.Pos -= (Line * Mag) * (A.InvMass / MassSum);
//		B.Pos += (Line * Mag) * (B.InvMass / MassSum);
//		return true;
//	}
//	return false;
//}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYCAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
