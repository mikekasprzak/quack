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
	typedef QBodyAABB BT;
public:
	static void InitObj( QObj* self ) {
		self->Type = QK::QO_BOXOBJ;

		self->_SetArt = (QObj::QSetArtFunc)_SetArt;
		self->_GetArt = (QObj::QGetArtFunc)_GetArt;
		self->_SetArtScale = (QObj::QSetArtScaleFunc)_SetArtScale;

		self->_GetRect = (QObj::QGetRectFunc)_GetRect;
			
		self->_GetBody = (QObj::QGetBodyFunc)_GetBody;
		self->_SetShape = (QObj::QSetShapeFunc)_SetShape;

		self->_AddForce = (QObj::QAddForceFunc)_AddForce;
		self->_Contact = (QObj::QContactFunc)_Contact;
		self->_Notify = (QObj::QNotifyFunc)_Notify;

		self->_Init = (QObj::QInitFunc)_Init;	// ?? //
		self->_Step = (QObj::QStepFunc)_Step;
		self->_Draw = (QObj::QDrawFunc)_Draw;
	}
public:
	BT 		Body;		// Actual Physical Properties //
	QBody	BodyType;	// Signature type understood by the engine //

	GelSkelAnimator* Skel;
	QVec ArtScale;

	HSQOBJECT SqHookObj;
	HSQMEMBERHANDLE SqInitFunc;	// ?? //
	HSQMEMBERHANDLE SqStepFunc;
	HSQMEMBERHANDLE SqNotifyFunc;

	HSQOBJECT SqObj;

public:
	inline QObjBoxObj( const QVec& _Pos, const char* _Class ) :
		Body( _Pos, QVec(8,8) ),
		ArtScale(1,1),
		Skel( 0 )
	{
		BodyType.Type = QB_AABB;
		BodyType.Data = &Body;
		BodyType.GetInvMass = (QBody::QGetInvMassFunc)BT::_GetInvMass;

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
		
		// Get Members //
		sq_pushstring(vm,_SC("Init"),-1);
		sq_getmemberhandle(vm,-3,&SqInitFunc);		// The Class, not the Instance //
		sq_pushstring(vm,_SC("Step"),-1);
		sq_getmemberhandle(vm,-3,&SqStepFunc);		// The Class, not the Instance //
		sq_pushstring(vm,_SC("Notify"),-1);
		sq_getmemberhandle(vm,-3,&SqNotifyFunc);	// The Class, not the Instance //
		// Finished, clean up the stack //
//		sq_pop(vm,3);
	}
	
	inline ~QObjBoxObj() {
		sq_release(vm,&SqHookObj);
		sq_release(vm,&SqObj);

		if ( Skel ) {
			delete Skel;
		}
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
	static void _SetShape( thistype* self, const QVec& _Shape ) { self->SetShape( _Shape ); }
	inline void SetShape( const QVec& _Shape ) {
		Body.SetShape( _Shape );
	}

	static void _SetArt( thistype* self, const char* ArtFile ) { self->SetArt( ArtFile ); }
	inline void SetArt( const char* ArtFile ) {
		if ( Skel ) {
			delete Skel;
		}
		Skel = new GelSkelAnimator();
		Skel->Load( Gel::SkelPool.Load( ArtFile ) );
	}
	static void* _GetArt( thistype* self ) { return self->GetArt(); }
	inline void* GetArt() {
		return (void*)Skel;
	}

	static void _SetArtScale( thistype* self, const QVec& _Scale ) { self->SetArtScale( _Scale ); }
	inline void SetArtScale( const QVec& _Scale ) {
		ArtScale = _Scale;
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

public:
	static bool _Init( thistype* self, QObj& Obj ) { return self->Init( Obj ); }
	inline bool Init( QObj& Obj ) {
		
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqInitFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //
		sq_setinstanceup(vm,-1,(SQUserPointer)&Obj);
		sq_call(vm,2,false,false);
		sq_pop(vm,2);
		
		return true;
	}

	static bool _Step( thistype* self, QObj& Obj, const QProp& Prop ) { return self->Step( Obj, Prop ); }
	inline bool Step( QObj& Obj, const QProp& Prop ) {
		if ( Skel ) {
			Skel->Step();
		}
		
		// Do Step Function //
		sq_pushobject(vm,SqHookObj);
		sq_getbyhandle(vm,-1,&SqStepFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqHookObj);	// ARG0 - this //
		sq_pushobject(vm,SqObj);		// ARG1 - Obj //
		sq_setinstanceup(vm,-1,(SQUserPointer)&Obj);
		sq_call(vm,2,false,false);
		sq_pop(vm,2);
		
		return Body.Step( Prop );
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		if ( Skel ) {
			Matrix4x4 NewMat = Matrix4x4::ScalarMatrix( ArtScale * QFloat(0.5f) );
			NewMat *= Matrix4x4::TranslationMatrix( Body.GetBasePoint() );
			NewMat *= Mat;
			Skel->Draw( NewMat );
		}
		else {
			gelDrawSquareFill(Mat,GetRect().Center().ToVector3D(),GetRect().HalfShape(),GEL_RGBA(64,192,64,192));
		}
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddBoxObj_QEngine( QEngine& Engine, const QVec& _Pos, const char* _Class ) {
	QObj& Ob = Engine.Add();
	QObjBoxObj::InitObj( &Ob );
	Ob.Data = new QObjBoxObj( _Pos, _Class );
	((QObjBoxObj*)Ob.Data)->Init(Ob);
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJBOXOBJ_H__ //
// - ------------------------------------------------------------------------------------------ - //
