// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJBOXOBJ_H__
#define __QUACK_ENGINE_QOBJBOXOBJ_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>

#include <Lib/Lib.h>
#include <API/API_Squirrel.h>

#include <Skel/Skel.h>
// - ------------------------------------------------------------------------------------------ - //
extern HSQUIRRELVM vm;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QObjBoxObj {
	typedef QObjBoxObj thistype;
	typedef QBodyAABB BodyT;
	typedef GelSkelAnimator ArtT;
	typedef QSensorSpineBB SensorT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_BOXOBJ;

		self->_GetArt = (QObj::QGetArtFunc)_GetArt;
		self->_SetArt = (QObj::QSetArtFunc)_SetArt;
		self->_SetArtScale = (QObj::QSetArtScaleFunc)_SetArtScale;

		self->_GetRect = (QObj::QGetRectFunc)_GetRect;
		self->_GetBodyRect = (QObj::QGetRectFunc)_GetBodyRect;
			
		self->_GetBody = (QObj::QGetBodyFunc)_GetBody;
		self->_GetPos = (QObj::QGetPosFunc)_GetPos;
		self->_GetVelocity = (QObj::QGetVelocityFunc)_GetVelocity;
		self->_GetInvMass = (QObj::QGetInvMassFunc)_GetInvMass;
		self->_SetMass = (QObj::QSetMassFunc)_SetMass;
		self->_SetShape = (QObj::QSetShapeFunc)_SetShape;
		self->_AddForce = (QObj::QAddForceFunc)_AddForce;

		self->_GetSensor = (QObj::QGetSensorFunc)_GetSensor;
		self->_Sense = (QObj::QSenseFunc)_Sense;

		self->_Contact = (QObj::QContactFunc)_Contact;
		self->_Notify = (QObj::QNotifyFunc)_Notify;

//		self->_Init = (QObj::QInitFunc)_Init;	// ?? //
		self->_Step = (QObj::QStepFunc)_Step;
		self->_Draw = (QObj::QDrawFunc)_Draw;
	}
public:
	BodyT 		Body;		// Actual Physical Properties //
	QBody		BodyType;	// Signature type understood by the engine //

	ArtT* 		Art;		// Pointer
	QArt		ArtType;
	QVec 		ArtScale; 	// Hack //

	SensorT		Sensor;		// Actual (reference) to Sensing Data //
	QSensor		SensorType;	// Signature type understood by the engine //

	HSQOBJECT SqHookObj;
	HSQMEMBERHANDLE SqInitFunc;	// ?? //
	HSQMEMBERHANDLE SqStepFunc;
	HSQMEMBERHANDLE SqContactFunc;
	HSQMEMBERHANDLE SqSenseFunc;
	HSQMEMBERHANDLE SqNoticeFunc;

	HSQOBJECT SqObj;
	HSQOBJECT SqObj2;
	HSQOBJECT SqInfo;
	HSQOBJECT SqInfo2;

public:
	inline QObjBoxObj( const QVec& _Pos, const char* _Class ) :
		Body( _Pos, QVec(8,8) ),
		ArtScale(1,1),
		Art( 0 )
	{
		BodyT::InitBody( &BodyType );
		BodyType.Data = &Body;

		ArtType.Type = QA_SPINE;
		//ArtType.Data = Art;

		SensorT::InitSensor( &SensorType );
		SensorType.Data = &Sensor;
		
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

		// ** SqObj Holder (Pointer is assigned before calls) ** //
		sq_resetobject(&SqObj2);
		// Instance the Class //		
		sq_pushroottable(vm);
		sq_pushstring(vm,_SC("QkObj"),-1);
		sq_get(vm,-2);
		sq_createinstance(vm,-1);
		// Store the Instance, add a reference //
		sq_getstackobj(vm,-1,&SqObj2);
		sq_addref(vm,&SqObj2);
//		sq_pop(vm,3);

		// ** SQInfo Holder (Pointer is assigned before calls) ** //
		sq_resetobject(&SqInfo);
		// Instance the Class //		
		sq_pushroottable(vm);
		sq_pushstring(vm,_SC("QkContactInfo"),-1);
		sq_get(vm,-2);
		sq_createinstance(vm,-1);
		// Store the Instance, add a reference //
		sq_getstackobj(vm,-1,&SqInfo);
		sq_addref(vm,&SqInfo);
//		sq_pop(vm,3);

		// ** SQInfo2 Holder (Pointer is assigned before calls) ** //
		sq_resetobject(&SqInfo2);
		// Instance the Class //		
		sq_pushroottable(vm);
		sq_pushstring(vm,_SC("QkSensorInfo"),-1);
		sq_get(vm,-2);
		sq_createinstance(vm,-1);
		// Store the Instance, add a reference //
		sq_getstackobj(vm,-1,&SqInfo2);
		sq_addref(vm,&SqInfo2);
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
		sq_pushstring(vm,_SC("Step"),-1);
		sq_getmemberhandle(vm,-3,&SqStepFunc);
		sq_pushstring(vm,_SC("Contact"),-1);
		sq_getmemberhandle(vm,-3,&SqContactFunc);
		sq_pushstring(vm,_SC("Sense"),-1);
		sq_getmemberhandle(vm,-3,&SqSenseFunc);
		sq_pushstring(vm,_SC("Notice"),-1);
		sq_getmemberhandle(vm,-3,&SqNoticeFunc);
		// Finished, clean up the stack //
//		sq_pop(vm,3);
	}
	
	inline ~QObjBoxObj() {
		sq_release(vm,&SqHookObj);
		sq_release(vm,&SqObj2);
		sq_release(vm,&SqObj);

		if ( Art ) {
			delete Art;
		}
	}

public:
	static QRect _GetRect( thistype* self ) { return self->GetRect(); }
	inline QRect GetRect() {
//		QRect Ret = GetBodyRect();
////		Ret += 
//		Ret = Sensor.GetRect();
//		return Ret;
		return GetBodyRect();
	}

	static QRect _GetBodyRect( thistype* self ) { return self->GetBodyRect(); }
	inline QRect GetBodyRect() {
		return Body.GetRect();
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
	static void _SetMass( thistype* self, const QFloat Mass ) { self->SetMass( Mass ); }
	inline void SetMass( const QFloat Mass ) {
		Body.SetMass( Mass );
	}
	static void _SetShape( thistype* self, const QVec& _Shape ) { self->SetShape( _Shape ); }
	inline void SetShape( const QVec& _Shape ) {
		Body.SetShape( _Shape );
	}

	static void _SetArt( thistype* self, const char* ArtFile ) { self->SetArt( ArtFile ); }
	inline void SetArt( const char* ArtFile ) {
		if ( Art ) {
			delete Art;
		}
		Art = new ArtT();
		Art->Load( Gel::SkelPool.Load( ArtFile ) );

		// Store copies of the pointer in Art and Sensor Types //		
		ArtType.Data = Art;
		Sensor.Set( Art );
	}
	static void* _GetArt( thistype* self ) { return self->GetArt(); }
	inline void* GetArt() {
		return (void*)Art;
	}

	static void _SetArtScale( thistype* self, const QVec& _Scale ) { self->SetArtScale( _Scale ); }
	inline void SetArtScale( const QVec& _Scale ) {
		ArtScale = _Scale;
	}
	

	static void _AddForce( thistype* self, const QVec& Force ) { self->AddForce( Force ); }
	inline void AddForce( const QVec& Force ) {
		Body.AddForce( Force );
	}


	static QSensor* _GetSensor( thistype* self ) { return self->GetSensor(); }
	inline QSensor* GetSensor() {
		return &SensorType;
	}

	static void _Contact( thistype* self, QObj& Obj, QObj& Vs, QContactInfo& Info ) { self->Contact( Obj, Vs, Info ); }
	inline void Contact( QObj& Obj, QObj& Vs, QContactInfo& Info ) {
		// Do Step Function //
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqContactFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //

//		QObjHandle* ObjHandle;
//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Obj.Parent;
//		ObjHandle->Index = Obj.MyIndex;
//		ObjHandle->Ptr = &Obj;

		sq_setinstanceup(vm,-1,(SQUserPointer)&Obj);
		sq_pushobject(vm,SqObj2);		// ARG2 - Vs //

//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Vs.Parent;
//		ObjHandle->Index = Vs.MyIndex;
//		ObjHandle->Ptr = &Vs;

		sq_setinstanceup(vm,-1,(SQUserPointer)&Vs);
		sq_pushobject(vm,SqInfo);		// ARG3 - Info //
		sq_setinstanceup(vm,-1,(SQUserPointer)&Info);
		sq_call(vm,4,false,false);
		sq_pop(vm,2);
	}

	static void _Sense( thistype* self, QObj& Obj, QObj& Vs, QSensorInfo& Info ) { self->Sense( Obj, Vs, Info ); }
	inline void Sense( QObj& Obj, QObj& Vs, QSensorInfo& Info ) {
		// Do Step Function //
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqSenseFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);			// ARG0 - this //
		sq_pushobject(vm,SqObj);				// ARG1 - Obj //
		
//		QObjHandle* ObjHandle;
//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Obj.Parent;
//		ObjHandle->Index = Obj.MyIndex;
//		ObjHandle->Ptr = &Obj;
		
		sq_setinstanceup(vm,-1,(SQUserPointer)&Obj);
		sq_pushobject(vm,SqObj2);				// ARG2 - Vs //
		
//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Vs.Parent;
//		ObjHandle->Index = Vs.MyIndex;
//		ObjHandle->Ptr = &Vs;
		
		sq_setinstanceup(vm,-1,(SQUserPointer)&Vs);
		sq_pushobject(vm,SqInfo2);				// ARG3 - Info //
		sq_setinstanceup(vm,-1,(SQUserPointer)&Info);
		sq_call(vm,4,false,false);
		sq_pop(vm,2);
	}

	static void _Notify( thistype* self, QObj& Obj, QObj& Sender, const int Message ) { self->Notify( Obj, Sender, Message ); }
	inline void Notify( QObj& Obj, QObj& Sender, const int Message ) {
		// Do Step Function //
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqNoticeFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //

//		QObjHandle* ObjHandle;
//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Obj.Parent;
//		ObjHandle->Index = Obj.MyIndex;
//		ObjHandle->Ptr = &Obj;

		sq_setinstanceup(vm,-1,(SQUserPointer)&Obj);
		sq_pushobject(vm,SqObj2);		// ARG2 - Sender //

//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Sender.Parent;
//		ObjHandle->Index = Sender.MyIndex;
//		ObjHandle->Ptr = &Sender;

		sq_setinstanceup(vm,-1,(SQUserPointer)&Sender);
		sq_pushinteger(vm,Message);		// ARG3 - Message //
		sq_call(vm,4,false,false);
		sq_pop(vm,2);
	}

public:
	//static bool _Init( thistype* self, QObj* Obj ) { return self->Init( Obj ); }
	inline bool Init( QObj* Obj, const HSQOBJECT& SqArgs ) {
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqInitFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //
		sq_setinstanceup(vm,-1,(SQUserPointer)Obj);

//		QObjHandle* ObjHandle;
//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Obj->Parent;
//		ObjHandle->Index = Obj->MyIndex;
//		ObjHandle->Ptr = Obj;
//		sq_setinstanceup(vm,-1,(SQUserPointer)Obj);

		sq_pushobject(vm,SqArgs);		// ARG2 - Arguments //

		sq_call(vm,3,false,false);
		sq_pop(vm,3);
		
		return true;
	}

	static bool _Step( thistype* self, QObj& Obj, const QProp& Prop ) { return self->Step( Obj, Prop ); }
	inline bool Step( QObj& Obj, const QProp& Prop ) {
		if ( Art ) {
			Art->Step();
		}
		
		// Do Step Function //
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqStepFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //

//		QObjHandle* ObjHandle;
//		sq_getinstanceup(vm,-1,(void**)&ObjHandle,0);
//		ObjHandle->Engine = Obj.Parent;
//		ObjHandle->Index = Obj.MyIndex;
//		ObjHandle->Ptr = &Obj;

		sq_setinstanceup(vm,-1,(SQUserPointer)&Obj);
		sq_call(vm,2,false,false);
		sq_pop(vm,2);
		
		return Body.Step( Prop );
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		if ( Art ) {
			Matrix4x4 NewMat = Matrix4x4::ScalarMatrix( ArtScale * QFloat(0.5f) );
			NewMat *= Matrix4x4::TranslationMatrix( Body.GetBasePoint() );
			NewMat *= Mat;
			Art->Draw( NewMat );
		}
		else {
			gelDrawSquareFill(Mat,GetRect().Center().ToVector3D(),GetRect().HalfShape(),GEL_RGBA(64,192,64,192));
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddBoxObj_QEngine( QEngine& Engine, const QVec& _Pos, const char* _Class, const HSQOBJECT& SqArgs ) {
	QObj& Ob = Engine.Add();
	QObjBoxObj::InitObj( &Ob );
	Ob.Data = new QObjBoxObj( _Pos, _Class );
	((QObjBoxObj*)Ob.Data)->Init( &Ob, SqArgs );
	LogFlush();
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJBOXOBJ_H__ //
// - ------------------------------------------------------------------------------------------ - //
