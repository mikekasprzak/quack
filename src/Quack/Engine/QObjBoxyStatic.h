// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJBOXYSTATIC_H__
#define __QUACK_ENGINE_QOBJBOXYSTATIC_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjBoxyStatic {
	typedef QObjBoxyStatic thistype;
	typedef QBodyAABB BT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_BOXY_STATIC;
		self->_GetRect = (QObj::QGetRectFunc)_GetRect;
		self->_GetBody = (QObj::QGetBodyFunc)_GetBody;
		self->_AddForce = (QObj::QAddForceFunc)_AddForce;
		self->_Contact = (QObj::QContactFunc)_Contact;
		self->_Notify = (QObj::QNotifyFunc)_Notify;

		self->_Step = (QObj::QStepFunc)_Step;
		self->_Draw = (QObj::QDrawFunc)_Draw;
	}
public:
	BT 		Body;		// Actual Physical Properties //
	QBody	BodyType;	// Signature type understood by the engine //

public:
	inline QObjBoxyStatic( const QVec& _Pos, const QVec& _Shape ) :
		Body( _Pos, _Shape, 0 ) 
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

	static bool _Step( thistype* self, const QProp& Prop ) { return self->Step( Prop ); }
	inline bool Step( const QProp& /*Prop*/ ) {
		return false;
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		gelDrawSquareFill(Mat,GetRect().Center().ToVector3D(),GetRect().HalfShape(),GEL_RGBA(128,64,64,128));
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddBoxyStatic_QEngine( QEngine& Engine, const QVec& _Pos, const QVec& _Shape = QVec(16,16) ) {
	QObj& Ob = Engine.Add();
	QObjBoxyStatic::InitObj( &Ob );
	Ob.Data = new QObjBoxyStatic( _Pos, _Shape );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJBOXYSTATIC_H__ //
// - ------------------------------------------------------------------------------------------ - //
