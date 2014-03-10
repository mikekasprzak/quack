// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJCAPPYSTATIC_H__
#define __QUACK_ENGINE_QOBJCAPPYSTATIC_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjCappyStatic {
	typedef QObjCappyStatic thistype;
	typedef QBodyCapsule BT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_CAPPY_STATIC;
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
	inline QObjCappyStatic( const QVec& _Pos, const QFloat& _RadiusA, const QVec& _Line, const QFloat& _RadiusB ) :
		Body( _Pos, _RadiusA, _Line, _RadiusB, 0 ) 
	{
		BodyType.Type = QB_CAPSULE;
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

	static void _Contact( thistype* self, QObj& Obj, QObj& Vs ) { self->Contact( Obj, Vs ); }
	inline void Contact( QObj& Obj, QObj& Vs ) {
	}

	static void _Notify( thistype* self, QObj& Obj, QObj& Sender, const int Message ) { self->Notify( Obj, Sender, Message ); }
	inline void Notify( QObj& Obj, QObj& Sender, const int Message ) {
	}


	static bool _Init( thistype* self, QObj& Obj ) { return self->Init( Obj ); }
	inline bool Init( QObj& /*Obj*/ ) {
		return false;
	}

	static bool _Step( thistype* self, QObj& Obj, const QProp& Prop ) { return self->Step( Obj, Prop ); }
	inline bool Step( QObj& /*Obj*/, const QProp& /*Prop*/ ) {
		return false;
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		gelDrawCapsuleFill(Mat,Body.Pos.ToVector3D(),Body.RadiusA,(Body.Pos+Body.Line).ToVector3D(),Body.RadiusB,GEL_RGBA(128,64,128,128));
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddCappyStatic_QEngine( QEngine& Engine, const QVec& _Pos, const QFloat& _RadiusA = QFloat(8), const QVec& _Line = QVec(0,16), const QFloat& _RadiusB = QFloat(8) ) {
	QObj& Ob = Engine.Add();
	QObjCappyStatic::InitObj( &Ob );
	Ob.Data = new QObjCappyStatic( _Pos, _RadiusA, _Line, _RadiusB );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJCAPPYSTATIC_H__ //
// - ------------------------------------------------------------------------------------------ - //
