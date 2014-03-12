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
	typedef QBodyAABB BodyT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_BOXY_STATIC;

		self->_GetArt = (QObj::QGetArtFunc)_GetArt;
		self->_GetSensor = (QObj::QGetSensorFunc)_GetSensor;

		self->_GetRect = (QObj::QGetRectFunc)_GetRect;

		self->_GetBody = (QObj::QGetBodyFunc)_GetBody;
		self->_GetPos = (QObj::QGetPosFunc)_GetPos;
		self->_GetVelocity = (QObj::QGetVelocityFunc)_GetVelocity;
		self->_GetInvMass = (QObj::QGetInvMassFunc)_GetInvMass;
		self->_AddForce = (QObj::QAddForceFunc)_AddForce;
		self->_Contact = (QObj::QContactFunc)_Contact;
		self->_Notify = (QObj::QNotifyFunc)_Notify;

		self->_Init = (QObj::QInitFunc)_Init;
		self->_Step = (QObj::QStepFunc)_Step;
		self->_Draw = (QObj::QDrawFunc)_Draw;
	}
public:
	BodyT	Body;		// Actual Physical Properties //
	QBody	BodyType;	// Signature type understood by the engine //

public:
	inline QObjBoxyStatic( const QVec& _Pos, const QVec& _Shape ) :
		Body( _Pos, _Shape, 0 ) 
	{
		BodyT::InitBody( &BodyType );
		BodyType.Data = &Body;
	}

public:
	static QRect _GetRect( thistype* self ) { return self->GetRect(); }
	inline QRect GetRect() {
		return Body.GetRect();
	}

	static QSensor* _GetSensor( thistype* self ) { return self->GetSensor(); }
	inline QSensor* GetSensor() {
		return 0;
	}
	static QArt* _GetArt( thistype* self ) { return self->GetArt(); }
	inline QArt* GetArt() {
		return 0;
	}

	static QBody* _GetBody( thistype* self ) { return self->GetBody(); }
	inline QBody* GetBody() {
		return &BodyType;
	}
	static QVec _GetPos( thistype* self ) { return self->GetPos(); }
	inline QVec GetPos() {
		return Body.GetPos();
	}
	static QVec _GetVelocity( thistype* self ) { return self->GetVelocity(); }
	inline QVec GetVelocity() {
		return Body.GetVelocity();
	}
	static QFloat _GetInvMass( thistype* self ) { return self->GetInvMass(); }
	inline QFloat GetInvMass() {
		return Body.GetInvMass();
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
