// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QBODYSPHERE_H__
#define __QUACK_ENGINE_QBODYSPHERE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QBodySphere {
	typedef QBodySphere thistype;
public:
	static void InitBody( QBody* self ) {
		self->Type = QB_SPHERE;
		self->GetInvMass = (QBody::QGetInvMassFunc)_GetInvMass;
//		self->Step = (QBody::QStepFunc)_Step;
	}
public:
	// Sphere //
	QVec 	Pos;
	QFloat	Radius;
	
	// Verlet Physics //
	QVec 	Old;
	QFloat	InvMass;
	
	QFloat	Friction;		// 0 - Ice; 1 - Super Sticky //
	QFloat	Restitution;	// Elasticity. 1 is perfectly elastic physics (pool ball). 0 is inelastic (pushing). //
	QVec 	Accum;			// Accumulator (Impulse Forces) //

public:
	inline QBodySphere( const QVec& _Pos, const QFloat& _Radius, const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Old( _Pos ),
		InvMass( _InvMass ),
		Accum( QVec::Zero )
	{
	}
	
	inline QRect GetRect() {
		QVec RadiusVec(Radius,Radius);
		return QRect( Pos - RadiusVec, RadiusVec + RadiusVec );
	}

public:
	// NOTE: This explicitly sets the velocity property. It does not accumulate! //
	inline void SetVelocity( const QVec& _Velocity ) {
		Old = Pos - _Velocity;
	}
	inline void SetMass( const QFloat& _Mass ) {
		InvMass = QFloat::One / _Mass;
	}
	inline void SetFriction( const QFloat& _Friction ) {
		Friction = _Friction;
	}
	inline void SetRestitution( const QFloat& _Restitution ) {
		Restitution = _Restitution;
	}

	inline const QVec GetVelocity() const {
		return Pos - Old; // Old -> Pos, Start -> Dest, A -> B, Dest (B) always goes first //
	}

public:
	static QFloat _GetInvMass( const thistype* self ) { return self->GetInvMass(); }
	inline QFloat GetInvMass() const {
		return InvMass;
	}

//	static bool _Step( thistype* self, const QProp& Prop ) { return self->Step( Prop ); }
	inline bool Step( const QProp& Prop ) {
		QVec Velocity = GetVelocity();
		Old = Pos;
		// Accum is (Accum * TimeStep * TimeStep), but TimeStep is 1 so it cancels out. //
		Pos += Velocity + Accum;
		
		// Instead of setting the Accumulator to 0, set it equal to Gravity //
		Accum = Prop.Gravity;
		
		return true;
	}

	inline void AddForce( const QVec& Force ) {
		Accum += Force;
	}
};
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodySphere& A, QBodySphere& B ) {
	QFloat MassSum = B.InvMass + A.InvMass;
	return_if_value( false, MassSum == QFloat::Zero );

	return FinishSolve_Body( A, B, B.Pos-A.Pos, B.Radius+A.Radius, MassSum );
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
}
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodyAABB& A, QBodySphere& B ) {
	QFloat MassSum = B.InvMass + A.InvMass;
	return_if_value( false, MassSum == QFloat::Zero );

	QVec ANearestPoint = A.GetRect().NearestPoint( B.Pos );

	return FinishSolve_Body( A, B, B.Pos-ANearestPoint, B.Radius, MassSum );

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
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYSPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
