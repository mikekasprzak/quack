// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJBOXY_H__
#define __QUACK_ENGINE_QOBJBOXY_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjBoxy {
	typedef QObjBoxy thistype;
	typedef QBodyAABB BT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_BOXY;
		self->_GetRect = (QObj::QGetRectFunc)_GetRect;
		self->_GetBody = (QObj::QGetBodyFunc)_GetBody;
		self->_AddForce = (QObj::QAddForceFunc)_AddForce;
		self->_Contact = (QObj::QContactFunc)_Contact;
		self->_Notify = (QObj::QNotifyFunc)_Notify;

		self->_Init = (QObj::QInitFunc)_Init;
		self->_Step = (QObj::QStepFunc)_Step;
		self->_Draw = (QObj::QDrawFunc)_Draw;
	}
public:
	BT 		Body;		// Actual Physical Properties //
	QBody	BodyType;	// Signature type understood by the engine //

public:
	inline QObjBoxy( const QVec& _Pos, const QVec& _Shape ) :
		Body( _Pos, _Shape, QFloat::One / (_Shape.x*_Shape.y) ) 
	{
		BodyType.Type = QB_AABB;
		BodyType.Data = &Body;
		BodyType.GetInvMass = (QBody::QGetInvMassFunc)BT::_GetInvMass;
	}

public:
	static QRect _GetRect( thistype* self ) { return self->GetRect(); }
	inline QRect GetRect() {
		return Body.GetRect();
	}

	static QBody* _GetBody( thistype* self ) { return self->GetBody(); }
	inline QBody* GetBody() {
		return &BodyType;
	}

	static void _AddForce( thistype* self, const QVec& Force ) { self->AddForce( Force ); }
	inline void AddForce( const QVec& Force ) {
		Body.AddForce( Force );
	}

	static void _Contact( thistype* self, QObj& Vs ) { self->Contact( Vs ); }
	inline void Contact( QObj& Vs ) {
	}

	static void _Notify( thistype* self, QObj& Sender, const int Message ) { self->Notify( Sender, Message ); }
	inline void Notify( QObj& Sender, const int Message ) {
	}


	static bool _Init( thistype* self, QObj& Obj ) { return self->Init( Obj ); }
	inline bool Init( QObj& /*Obj*/ ) {
		return false;
	}

	static bool _Step( thistype* self, QObj& Obj, const QProp& Prop ) { return self->Step( Obj, Prop ); }
	inline bool Step( QObj& /*Obj*/, const QProp& Prop ) {
		return Body.Step( Prop );
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		gelDrawSquareFill(Mat,GetRect().Center().ToVector3D(),GetRect().HalfShape(),GEL_RGBA(128,128,128,128));
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddBoxy_QEngine( QEngine& Engine, const QVec& _Pos, const QVec& _Shape = QVec(16,16) ) {
	QObj& Ob = Engine.Add();
	QObjBoxy::InitObj( &Ob );
	Ob.Data = new QObjBoxy( _Pos, _Shape );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJBOXY_H__ //
// - ------------------------------------------------------------------------------------------ - //
