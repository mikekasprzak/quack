// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_ENGINE_H__
#define __QUACK_ENGINE_ENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
SQInteger register_qkEngine(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class QkEngine {
public:
	typedef Vector2D EnVec;
	typedef Rect2D EnRect;
	
	enum {
		EO_NULL = 0,
		EO_COMMON = 1,
	};
	
	class EnObj {
	public:
		typedef EnRect (*EnGetRectFunc)( void* self );
		typedef void (*EnStepFunc)( void* self );
		typedef void (*EnDrawFunc)( void* self, const Matrix4x4& );
	
	public:
		int Type;
		EnRect Rect;
		void* Data;

		EnGetRectFunc GetRect;
		
		EnStepFunc Step;
		EnDrawFunc Draw;
	};

public:	
	std::vector<EnObj> Obj;
	inline EnObj& Add() {
		Obj.push_back( EnObj() );
		return Obj.back();
	}
		
public:
	void Step() {
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			EnObj& Ob = Obj[idx];

			Ob.Step( Ob.Data );
			Ob.Rect = Ob.GetRect( Ob.Data );
		}
	}
	
	void Draw( const EnRect& View, const Matrix4x4& Mat ) {
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			EnObj& Ob = Obj[idx];

			// Do Rectangle Test //
			{
				Ob.Draw( Ob.Data, Mat );
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
class QkObjCommon {
	typedef QkObjCommon thistype;
	typedef typename QkEngine::EnVec EnVec;
	typedef typename QkEngine::EnRect EnRect;
	typedef typename QkEngine::EnObj EnObj;
public:
	static void InitObj( EnObj* self ) {
		self->Type = QkEngine::EO_COMMON;
		self->GetRect = (EnObj::EnGetRectFunc)_GetRect;
		self->Step = (EnObj::EnStepFunc)_Step;
		self->Draw = (EnObj::EnDrawFunc)_Draw;
	}
public:
	EnVec Pos;

public:
	inline QkObjCommon( const EnVec& _Pos ) :
		Pos( _Pos ) 
	{
	}
	
	static EnRect _GetRect( thistype* self ) { return self->GetRect(); }
	inline EnRect GetRect() {
		return EnRect( Pos, EnVec(0,0) );
	}

	static void _Step( thistype* self ) { self->Step(); }
	inline void Step() {
		
	}

	static void _Draw( thistype* self, const Matrix4x4& Mat ) { self->Draw( Mat ); }
	inline void Draw( const Matrix4x4& Mat ) {
		
	}	
};
// - ------------------------------------------------------------------------------------------ - //
inline void AddCommon_QkEngine( QkEngine& Engine, const QkEngine::EnVec& _Pos ) {
	QkEngine::EnObj& Ob = Engine.Add();
	QkObjCommon::InitObj( &Ob );
	Ob.Data = new QkObjCommon( _Pos );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_ENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
