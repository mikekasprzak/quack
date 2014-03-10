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
		Friction( QFloat::Zero ),
		Restitution( QFloat::One ),
		Accum( QVec::Zero )
	{
	}
	
	inline QRect GetRect() {
		return QRect( Pos - HalfShape, HalfShape+HalfShape );
	}
	inline void SetShape( const QVec& Shape ) {
		HalfShape = Shape * QFloat::Half;
	}
	
	// Linear Momentum sets motion in whole units //
	inline void SetLinearMomentum( const QVec& Ray, const QFloat Rate ) {
		QVec Line = Ray - GetVelocity();
		QFloat Length = Line.NormalizeRet();
		if ( Rate > Length )
			AddForce( Line * Length );
		else
			AddForce( Line * Rate );
	}
	inline void SetLinearXMomentum( const QVec& Ray, const QFloat Rate ) {
		QFloat Line = Ray.x - GetVelocity().x;
		QFloat Length = Line.NormalizeRet();
		if ( Rate > Length )
			AddForce( QVec(Line,0) * Length );
		else
			AddForce( QVec(Line,0) * Rate );
	}
	inline void SetLinearYMomentum( const QVec& Ray, const QFloat Rate ) {
		QFloat Line = Ray.y - GetVelocity().y;
		QFloat Length = Line.NormalizeRet();
		if ( Rate > Length )
			AddForce( QVec(0,Line) * Length );
		else
			AddForce( QVec(0,Line) * Rate );
	}
	
	// Momentum sets motion in Fractional Units (i.e. 0.25 to step a quarter) //
	inline void SetMomentum( const QVec& Ray, const QFloat Amount ) {
		QVec Line = Ray - GetVelocity();
		AddForce( Line * Amount );
	}
	inline void SetXMomentum( const QVec& Ray, const QFloat Amount ) {
		QFloat Line = Ray.x - GetVelocity().x;
		AddForce( QVec(Line,0) * Amount );
	}
	inline void SetYMomentum( const QVec& Ray, const QFloat Amount ) {
		QFloat Line = Ray.y - GetVelocity().y;
		AddForce( QVec(0,Line) * Amount );
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
	
	inline QVec GetBasePoint() const {
		return QVec(Pos.x,Pos.y-HalfShape.y);
	}
	inline const QVec& GetPos() const {
		return Pos;
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
