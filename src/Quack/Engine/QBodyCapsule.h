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

	QFloat	Friction;		// 0 - Ice; 1 - Super Sticky //
	QFloat	Restitution;	// Elasticity. 1 is perfectly elastic physics (pool ball). 0 is inelastic (pushing). //
	QVec 	Accum;			// Accumulator (Impulse Forces) //

public:
	inline QBodyCapsule( const QVec& _Pos, const QFloat& _RadiusA, const QVec& _Line, const QFloat& _RadiusB, const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		RadiusA( _RadiusA ),
		Line( _Line ),
		RadiusB( _RadiusB ),
		Old( _Pos ),
		InvMass( _InvMass ),
		Friction( QFloat::Zero ),
		Restitution( QFloat::One ),
		Accum( QVec::Zero )
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
inline bool Solve_Body( QBodyCapsule& A, QBodyCapsule& B ) {
	if ( (A.InvMass == QFloat::Zero) && (B.InvMass == QFloat::Zero) )
		return false;
	
	Vec2CNLOL Line = Calc_NearestLine_on_Lines( A.Pos,A.Pos+A.Line, B.Pos,B.Pos+B.Line );
	Vector2D& C1 = Line.a;
	Vector2D& C2 = Line.b;
	
	Log("(%0.02f,%0.02f -> %0.02f,%0.02f) vs (%0.02f,%0.02f -> %0.02f,%0.02f) = (%0.02f,%0.02f -> %0.02f,%0.02f) [%0.02f,%0.02f]",
		A.Pos.x.ToFloat(),A.Pos.y.ToFloat(),
		(A.Pos+A.Line).x.ToFloat(),(A.Pos+A.Line).y.ToFloat(),
		B.Pos.x.ToFloat(),B.Pos.y.ToFloat(),
		(B.Pos+B.Line).x.ToFloat(),(B.Pos+B.Line).y.ToFloat(),
		C1.x.ToFloat(),C1.y.ToFloat(),
		C2.x.ToFloat(),C2.y.ToFloat(),
		Line.s.ToFloat(),Line.t.ToFloat()
		);

	// NOTE: Broken in parallel case //
	QFloat ARadius = A.RadiusA;// + ((A.RadiusB-A.RadiusA)*Line.s);
	QFloat BRadius = B.RadiusA;// + ((B.RadiusB-B.RadiusA)*Line.t);

	return FinishSolve_Body( A, B, Line.b-Line.a, BRadius+ARadius );
}
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodySphere& A, QBodyCapsule& B ) {
	QVec BPos = NearestPoint_on_Line(B.Pos,B.Pos+B.Line,A.Pos);
	QFloat BRadius = B.RadiusA; // FIX ME //

	return FinishSolve_Body( A, B, BPos-A.Pos, BRadius+A.Radius );
}
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodyAABB& A, QBodyCapsule& B ) {
	QVec BPos = NearestPoint_on_Line(B.Pos,B.Pos+B.Line,A.Pos);
	QFloat BRadius = B.RadiusA; // FIX ME //

	QVec ANearestPoint = A.GetRect().NearestPoint( BPos );

	return FinishSolve_Body( A, B, BPos-ANearestPoint, BRadius );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYCAPSULE_H__ //
// - ------------------------------------------------------------------------------------------ - //
