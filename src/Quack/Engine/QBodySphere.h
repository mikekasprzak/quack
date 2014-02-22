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

public:
	inline QBodySphere( const QVec& _Pos, const QFloat& _Radius, const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		Radius( _Radius ),
		Old( _Pos ),
		InvMass( _InvMass )
	{
	}
	
	inline QRect GetRect() {
		QVec RadiusVec(Radius,Radius);
		return QRect( Pos - RadiusVec, RadiusVec + RadiusVec );
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
inline bool Solve_Body( QBodySphere& A, QBodySphere& B ) {
	QFloat MassSum = B.InvMass + A.InvMass;
	return_if_value( false, MassSum == QFloat::Zero );

	QFloat RadiusSum = B.Radius + A.Radius;

	QVec Line = B.Pos - A.Pos;
	QFloat Mag = Line.MagnitudeSquared();
	
	if ( Mag < (RadiusSum*RadiusSum) ) {
		Mag = Line.NormalizeRet() - RadiusSum;
		A.Pos -= (Line * Mag) * (A.InvMass / MassSum);
		B.Pos += (Line * Mag) * (B.InvMass / MassSum);
		return true;
	}
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYSPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
