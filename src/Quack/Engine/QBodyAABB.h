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
	QVec HalfShape;
	
	// Verlet Physics //
	QVec 	Old;
	QFloat	InvMass;

	QFloat	Friction;		// 0 - Ice; 1 - Super Sticky //
	QFloat	Restitution;	// Elasticity. 1 is perfectly elastic physics (pool ball). 0 is inelastic (pushing). //
	QVec 	Accum;			// Accumulator (Impulse Forces) //

public:
	inline QBodyAABB( const QVec& _Pos, const QVec& _HalfShape, const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		HalfShape( _HalfShape ),
		Old( _Pos ),
		InvMass( _InvMass ),
		Friction( QFloat::One ),
		Restitution( QFloat::Zero ),
		Accum( QVec::Zero )
	{
	}
	
	inline QRect GetRect() {
		return QRect( Pos - HalfShape, HalfShape+HalfShape );
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

	inline QVec GetVelocity() const {
		return Pos - Old; // Old -> Pos, Start -> Dest, A -> B, Dest (B) always goes first //
	}
	inline QFloat GetMass() const {
		return QFloat::One / InvMass;
	}
	inline const QFloat& GetFriction() const {
		return Friction;
	}
	inline const QFloat& GetRestitution() const {
		return Restitution;
	}

	inline void AddForce( const QVec& Force ) {
		Accum += Force;
	}	

public:
	static QFloat _GetInvMass( const thistype* self ) { return self->GetInvMass(); }
	inline QFloat GetInvMass() const {
		return InvMass;
	}

//	static bool _Step( thistype* self, const QProp& Prop ) { return self->Step( Prop ); }
	inline bool Step( const QProp& Prop ) {
		return DoStep_Body( *this, Prop );
	}
};
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodyAABB& A, QBodyAABB& B ) {
	QRect Diff = B.GetRect() - A.GetRect();
	QVec Line = B.Pos - A.Pos;
	// The Size of the overlap region (Diff) determines which direction we push //
	if ( Diff.Width() < Diff.Height() ) {
		// The +One compensates for the length of 1 introduced by the Normal() //
		return FinishSolve_Body( A, B, QVec(Line.x.Normal(),0), Diff.Width()+QFloat::One );
	}
	else {
		// The +One compensates for the length of 1 introduced by the Normal() //
		return FinishSolve_Body( A, B, QVec(0,Line.y.Normal()), Diff.Height()+QFloat::One );
	}
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYAABB_H__ //
// - ------------------------------------------------------------------------------------------ - //
