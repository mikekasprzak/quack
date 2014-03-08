// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QOBJBOXOBJ_H__
#define __QUACK_ENGINE_QOBJBOXOBJ_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
#include <Render/GelDraw.h>

#include <string>
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
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

	HSQOBJECT SqObj;
	HSQMEMBERHANDLE SqInitFunc;
	HSQMEMBERHANDLE SqStepFunc;
	HSQMEMBERHANDLE SqNotifyFunc;

public:
	inline QObjBoxObj( const QVec& _Pos, const char* _Class ) :
		Body( _Pos, Vector2D(8,8) ) 
	{
		BodyType.Type = QB_AABB;
		BodyType.Data = &Body;
		BodyType.GetInvMass = (QBody::QGetInvMassFunc)BT::_GetInvMass;
		
		
		// Clear the Instance Storage //
		sq_resetobject(&SqObj);
				
		// Instance the Class //		
		sq_pushroottable(vm);
		sq_pushstring(vm,_SC(_Class),-1);
		sq_get(vm,-2);
		sq_createinstance(vm,-1);
		// Store the Instance, add a reference //
		sq_getstackobj(vm,-1,&SqObj);
		sq_addref(vm,&SqObj);
		
		// Get Members //
		sq_pushstring(vm,_SC("Init"),-1);
		sq_getmemberhandle(vm,-3,&SqInitFunc);		// The Class, not the Instance //
		sq_pushstring(vm,_SC("Step"),-1);
		sq_getmemberhandle(vm,-3,&SqStepFunc);		// The Class, not the Instance //
		sq_pushstring(vm,_SC("Notify"),-1);
		sq_getmemberhandle(vm,-3,&SqNotifyFunc);	// The Class, not the Instance //
		// Finished, clean up the stack //
//		sq_pop(vm,3);
		

		Log("%i",sq_gettop(vm));		
		sq_pushobject(vm,SqObj);
		sq_getbyhandle(vm,-1,&SqInitFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqObj);	// ARG1 - this //
		sq_call(vm,1,false,false);
		sq_pop(vm,2);
		Log("%i",sq_gettop(vm));
	}
	
	inline ~QObjBoxObj() {
		sq_release(vm,&SqObj);
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
	inline bool Step( const QProp& Prop ) {
		sq_pushobject(vm,SqObj);
		sq_getbyhandle(vm,-1,&SqStepFunc);
		// ARGS (must be accurate) //
		sq_pushobject(vm,SqObj);	// ARG1 - this //
		sq_call(vm,1,false,false);
		sq_pop(vm,2);
		
		return Body.Step( Prop );
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		gelDrawSquareFill(Mat,GetRect().Center().ToVector3D(),GetRect().HalfShape(),GEL_RGBA(64,192,64,192));
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddBoxObj_QEngine( QEngine& Engine, const QVec& _Pos, const char* _Class ) {
	QObj& Ob = Engine.Add();
	QObjBoxObj::InitObj( &Ob );
	Ob.Data = new QObjBoxObj( _Pos, _Class );
	Ob.UpdateRect();
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QOBJBOXOBJ_H__ //
// - ------------------------------------------------------------------------------------------ - //
