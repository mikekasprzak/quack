// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJBALLY_H__
#define __QUACK_ENGINE_QOBJBALLY_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjBally {
	typedef QObjBally thistype;
	typedef QBodySphere BodyT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_BALLY;

		self->_GetArt = (QObj::QGetArtFunc)_GetArt;
		self->_GetSensor = (QObj::QGetSensorFunc)_GetSensor;

		self->_GetRect = (QObj::QGetRectFunc)_GetRect;
		self->_GetBodyRect = (QObj::QGetRectFunc)_GetRect;

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
	inline QObjBally( const QVec& _Pos, const QFloat& _Radius ) :
		Body( _Pos, _Radius, QFloat::One / (_Radius*_Radius*Real::Pi) ) 
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
//		Log("Bonk!");
	}

	static void _Notify( thistype* self, QObj& Obj, QObj& Sender, const int Message ) { self->Notify( Obj, Sender, Message ); }
	inline void Notify( QObj& Obj, QObj& Sender, const int Message ) {
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
		gelDrawCircleFill(Mat,Body.Pos.ToVector3D(),Body.Radius,GEL_RGBA(64,128,64,128));
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddBally_QEngine( QEngine& Engine, const QVec& _Pos, const QFloat& _Radius = QFloat(8) ) {
	QObj& Ob = Engine.Add();
	QObjBally::InitObj( &Ob );
	Ob.Data = new QObjBally( _Pos, _Radius );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJBALLY_H__ //
// - ------------------------------------------------------------------------------------------ - //
