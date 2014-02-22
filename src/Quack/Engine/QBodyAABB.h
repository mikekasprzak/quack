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
	QVec Pos;
	QVec Shape;
	
	QVec Old;		// Verlet //
	
	QFloat InvMass;

public:
	inline QBodyAABB( const QVec& _Pos, const QVec& _Shape ) :
		Pos( _Pos ),
		Shape( _Shape )
	{
	}
	
	inline QRect GetRect() {
		return QRect( Pos, Shape );
	}

	static QFloat _GetInvMass( const thistype* self ) { return self->GetInvMass(); }
	inline QFloat GetInvMass() const {
		return InvMass;
	}

//	static bool _Step( thistype* self ) { return self->Step(); }
	inline bool Step() {
		return true;
	}
};
// - ------------------------------------------------------------------------------------------ - //
//inline void AddDummy_QEngine( QEngine& Engine, const QVec& _Pos ) {
//	QObj& Ob = Engine.Add();
//	QObjDummy::InitObj( &Ob );
//	Ob.Data = new QObjDummy( _Pos );
//}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QBODYAABB_H__ //
// - ------------------------------------------------------------------------------------------ - //
