// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QBODYOBB_H__
#define __QUACK_ENGINE_QBODYOBB_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QBodyOBB {
	typedef QBodyOBB thistype;
public:
	static void InitBody( QBody* self ) {
		self->Type = QB_OBB;
		
		self->_GetInvMass = (QBody::QGetInvMassFunc)_GetInvMass;
	}
public:
	// OBB //
	QVec 	Pos;
	QVec	Shape;
	QVec	Normal;			// Orientation //
	
	// Verlet Physics //
	QVec 	Old;
	QFloat	InvMass;
	
	QFloat	Friction;		// 0 - Ice; 1 - Super Sticky //
	QFloat	Restitution;	// Elasticity. 1 is perfectly elastic physics (pool ball). 0 is inelastic (pushing). //
	QVec 	Accum;			// Accumulator (Impulse Forces) //

public:
	inline QBodyOBB( const QVec& _Pos, const QVec& _Shape, const QVec& _Normal = QVec(0,1), const QFloat& _InvMass = QFloat::One ) :
		Pos( _Pos ),
		Shape( _Shape ),
		Normal( _Normal ),
		Old( _Pos ),
		InvMass( _InvMass ),
		Friction( QFloat::Zero ),
		Restitution( QFloat::One ),
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
//inline bool Solve_Body( QBodyOBB& A, QBodyOBB& B ) {
//	return FinishSolve_Body( A, B, B.Pos-A.Pos, B.Radius+A.Radius );
//}
// - ------------------------------------------------------------------------------------------ - //
//inline bool Solve_Body( QBodyAABB& A, QBodyOBB& B ) {
//	QVec ANearestPoint = A.GetRect().NearestPoint( B.Pos );
//
//	return FinishSolve_Body( A, B, B.Pos-ANearestPoint, B.Radius );
//}
// - ------------------------------------------------------------------------------------------ - //
inline bool Solve_Body( QBodySphere& A, QBodyOBB& B ) {
	// 2x2 Matrix //
	QVec  Row1 = -B.Normal.Tangent();
	QVec& Row2 = B.Normal;
	
	QVec Line = B.Pos-A.Pos;
	
	// Rotate Point about OBB's Center (2x2 Matrix Multiply) //
	QVec NewLine( 
		(Row1.x * Line.x) + (Row1.y * Line.y), 
		(Row2.x * Line.x) + (Row2.y * Line.y)
		);
	QRect NewA( B.Pos + NewLine, A.Shape );
	
	// Test is now an AABB test //
	QVec ANearestPoint = NewA.NearestPoint( B.Pos );

	return FinishSolve_Body( A, B, B.Pos-ANearestPoint, A.Radius );
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYSPHERE_H__ //
// - ------------------------------------------------------------------------------------------ - //
