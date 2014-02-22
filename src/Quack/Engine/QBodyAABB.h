// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QBODYAABB_H__
#define __QUACK_ENGINE_QBODYAABB_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QBodyAABB {
	typedef QBodyAABB thistype;
public:
	static void InitBody( QBody* self ) {
		self->Type = QB_AABB;
		self->GetInvMass = (QBody::QGetInvMassFunc)_GetInvMass;
//		self->Step = (QBody::QStepFunc)_Step;
	}
public:
	// Rectangle //
	QVec Pos;
	QVec Shape;
	
	// Verlet Physics //
	QVec 	Old;
	QFloat	InvMass;

public:
	inline QBodyAABB( const QVec& _Pos, const QVec& _Shape, const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		Shape( _Shape ),
		Old( _Pos ),
		InvMass( _InvMass )
	{
	}
	
	inline QRect GetRect() {
		return QRect( Pos, Shape );
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
inline bool Solve_Body( QBodyAABB& A, QBodyAABB& B ) {
//	QVec Vel = A.Pos - A.Old;
//	Log("HERM %f %f", Vel.x.ToFloat(),Vel.y.ToFloat() );
	
	QFloat MassSum = B.InvMass + A.InvMass;
	return_if_value( false, MassSum == QFloat::Zero );

	QRect Diff = B.GetRect() - A.GetRect();
	QVec Line = B.GetRect().Center() - A.GetRect().Center();
	if ( Line.x.Abs() > Line.y.Abs() ) {
		Line.x = Line.x.Normal();
		Line.y = QFloat::Zero;
	}
	else {
		Line.x = QFloat::Zero;
		Line.y = Line.y.Normal();
	}

//	Log("A: %f %f -- %f %f", A.GetRect().P1().x.ToFloat(),A.GetRect().P1().y.ToFloat(), A.GetRect().Width().ToFloat(),A.GetRect().Height().ToFloat() );
//	Log("B: %f %f -- %f %f", B.GetRect().P1().x.ToFloat(),B.GetRect().P1().y.ToFloat(), B.GetRect().Width().ToFloat(),B.GetRect().Height().ToFloat() );
//	Log("VER: %f %f -- %f %f", Diff.P1().x.ToFloat(),Diff.P1().y.ToFloat(), Diff.Width().ToFloat(),Diff.Height().ToFloat() );

//	A.Pos.x += (Line.x * Diff.Shape().x);// * Real::Half;// * (A.InvMass / MassSum);
//	A.Pos.y -= (Line.y * Diff.Shape().y);// * (A.InvMass / MassSum);
		
	A.Pos -= (Line * Diff.Shape()) * (A.InvMass / MassSum);
	B.Pos += (Line * Diff.Shape()) * (B.InvMass / MassSum);
	return true;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYAABB_H__ //
// - ------------------------------------------------------------------------------------------ - //
