// - ------------------------------------------------------------------------------------------ - //
// Dummy Object -- Primarily exists to act as an example for new object types //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJDUMMY_H__
#define __QUACK_ENGINE_QOBJDUMMY_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjDummy {
	typedef QObjDummy thistype;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_DUMMY;

		self->_GetRect = (QObj::QGetRectFunc)_GetRect;
		self->_GetBodyRect = (QObj::QGetRectFunc)_GetRect;

		self->_GetArt = (QObj::QGetArtFunc)_GetArt;
		self->_GetSensor = (QObj::QGetSensorFunc)_GetSensor;

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
	QVec Pos;

public:
	inline QObjDummy( const QVec& _Pos ) :
		Pos( _Pos ) 
	{
	}

public:
	static QRect _GetRect( thistype* self ) { return self->GetRect(); }
	inline QRect GetRect() {
		return QRect( Pos, QVec(0,0) );
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
		return (QBody*)0;
	}
	static QVec _GetPos( thistype* self ) { return self->GetPos(); }
	inline QVec GetPos() {
		return Pos;
	}
	static QVec _GetVelocity( thistype* self ) { return self->GetVelocity(); }
	inline QVec GetVelocity() {
		return QVec(0,0);
	}
	static QFloat _GetInvMass( thistype* self ) { return self->GetInvMass(); }
	inline QFloat GetInvMass() {
		return 0;
	}

	static void _AddForce( thistype* self, const QVec& Force ) { self->AddForce( Force ); }
	inline void AddForce( const QVec& ) {
		// No body, so nothing to do //
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
	inline void Draw( const Matrix4x4& /*Mat*/ ) {
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddDummy_QEngine( QEngine& Engine, const QVec& _Pos ) {
	QObj& Ob = Engine.Add();
	QObjDummy::InitObj( &Ob );
	Ob.Data = new QObjDummy( _Pos );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJDUMMY_H__ //
// - ------------------------------------------------------------------------------------------ - //
