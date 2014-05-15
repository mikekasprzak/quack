// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJSTATICBOXOBJ_H__
#define __QUACK_ENGINE_QOBJSTATICBOXOBJ_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjStaticBoxObj {
	typedef QObjStaticBoxObj thistype;
	typedef QBodyAABB BodyT;
	typedef GelAtlasPool::UID ArtT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_STATICBOXOBJ;

		self->_GetArt = (QObj::QGetArtFunc)_GetArt;
		self->_SetArt = (QObj::QSetArtFunc)_SetArt;
//		self->_SetArtScale = (QObj::QSetArtScaleFunc)_SetArtScale;
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

//		self->_Init = (QObj::QInitFunc)_Init;
		self->_Step = (QObj::QStepFunc)_Step;
		self->_Draw = (QObj::QDrawFunc)_Draw;
	}
public:
	BodyT	Body;		// Actual Physical Properties //
	QBody	BodyType;	// Signature type understood by the engine //

	ArtT 		Art;
	int			ArtIndex;
//	QArt		ArtType;
//	QVec 		ArtScale; 	// Hack //

	HSQOBJECT SqHookObj;
	HSQMEMBERHANDLE SqInitFunc;	// ?? //
	HSQMEMBERHANDLE SqStepFunc;
	HSQMEMBERHANDLE SqContactFunc;
	HSQMEMBERHANDLE SqSenseFunc;
	HSQMEMBERHANDLE SqNoticeFunc;

	HSQOBJECT SqObj;

public:
	inline QObjStaticBoxObj( const QVec& _Pos, const char* _Class ) :
		Body( _Pos, QVec(24,24), 0 ),
		Art( 0 ),
		ArtIndex( -1 )
	{
		BodyT::InitBody( &BodyType );
		BodyType.Data = &Body;

		// ** Squirrel Setup *********************** //
		// ** SqObj Holder (Pointer is assigned before calls) ** //
		sq_resetobject(&SqObj);
		// Instance the Class //		
		sq_pushroottable(vm);
		sq_pushstring(vm,_SC("QkObj"),-1);
		sq_get(vm,-2);
		sq_createinstance(vm,-1);
		// Store the Instance, add a reference //
		sq_getstackobj(vm,-1,&SqObj);
		sq_addref(vm,&SqObj);
//		sq_pop(vm,3);


		// ** Class Instance Holder ** //
		// Clear the Instance Storage //
		sq_resetobject(&SqHookObj);
				
		// Instance the Class //		
		sq_pushroottable(vm);
		sq_pushstring(vm,_SC(_Class),-1);
		sq_get(vm,-2);
		sq_createinstance(vm,-1);
		// Store the Instance, add a reference //
		sq_getstackobj(vm,-1,&SqHookObj);
		sq_addref(vm,&SqHookObj);

		// Get Members (with Class index, not the instance index) //
		sq_pushstring(vm,_SC("Init"),-1);
		sq_getmemberhandle(vm,-3,&SqInitFunc);
//		sq_pushstring(vm,_SC("Step"),-1);
//		sq_getmemberhandle(vm,-3,&SqStepFunc);
//		sq_pushstring(vm,_SC("Contact"),-1);
//		sq_getmemberhandle(vm,-3,&SqContactFunc);
//		sq_pushstring(vm,_SC("Sense"),-1);
//		sq_getmemberhandle(vm,-3,&SqSenseFunc);
//		sq_pushstring(vm,_SC("Notice"),-1);
//		sq_getmemberhandle(vm,-3,&SqNoticeFunc);
		// Finished, clean up the stack //
//		sq_pop(vm,3);

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


	static void _SetArt( thistype* self, const char* ArtFile ) { self->SetArt( ArtFile ); }
	inline void SetArt( const char* ArtFile ) {
		Art = Gel::AtlasPool.LoadAndIndex( ArtFile, &ArtIndex );

//		if ( Art ) {
//			delete Art;
//		}
		//Art = new ArtT();
//		Art->Load( Gel::SkelPool.Load( ArtFile ) );

		// Store copies of the pointer in Art and Sensor Types //		
//		ArtType.Data = Art;
//		Sensor.Set( Art );
	}



	inline bool Init( QObj* Obj, const HSQOBJECT& SqArgs ) {
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqInitFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //
		sq_setinstanceup(vm,-1,(SQUserPointer)Obj);
		
		sq_pushobject(vm,SqArgs);		// ARG2 - Arguments //

		sq_call(vm,3,false,false);
		sq_pop(vm,3);
		
		return true;
	}

	static bool _Step( thistype* self, QObj& Obj, const QProp& Prop ) { return self->Step( Obj, Prop ); }
	inline bool Step( QObj& /*Obj*/, const QProp& /*Prop*/ ) {
		return false;
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		if ( ArtIndex >= 0 ) {
			GelAtlas& Atlas = Gel::AtlasPool[Art];
			
			Matrix4x4 MyMat = Matrix4x4::ScalarMatrix( Vector3D(0.5f, 0.5f, 1.0f) );
			MyMat *= Matrix4x4::TranslationMatrix( GetPos() );
			MyMat *= Mat;
				
			Atlas.Draw( MyMat, ArtIndex );
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddStaticBoxObj_QEngine( QEngine& Engine, const QVec& _Pos, const char* _Class, const HSQOBJECT& SqArgs ) {
	QObj& Ob = Engine.Add();
	QObjStaticBoxObj::InitObj( &Ob );
	Ob.Data = new QObjStaticBoxObj( _Pos, _Class );
	((QObjStaticBoxObj*)Ob.Data)->Init( &Ob, SqArgs );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJSTATICBOXOBJ_H__ //
// - ------------------------------------------------------------------------------------------ - //
