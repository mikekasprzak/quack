// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QENGINE_H__
#define __QUACK_ENGINE_QENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// QBody -- Quack Body (Collision) //
enum {
	QB_NULL = 0,
	QB_RECT = 1,
	QB_SPHERE,
	// ... //
};
// - ------------------------------------------------------------------------------------------ - //
// QObj -- Quack Object (Entity) //
enum {
	QO_NULL = 0,
	QO_DUMMY = 1,
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Primitive Types //
typedef Real 		QFloat;
typedef Vector2D	QVec;
typedef Rect2D		QRect;
// - ------------------------------------------------------------------------------------------ - //
// Quack Body (Collision) //
class QBody {
public:
	int Type;
	
};

// - ------------------------------------------------------------------------------------------ - //
// Quack Object //
class QObj {
public:
	typedef QRect (*QGetRectFunc)( void* self );
	typedef QBody* (*QGetBodyFunc)( void* self );
	typedef void (*QStepFunc)( void* self );
	typedef void (*QDrawFunc)( void* self, const Matrix4x4& );

public:
	int Type;
	QRect Rect;
	void* Data;

	QGetRectFunc GetRect;
	QGetBodyFunc GetBody;
	
	QStepFunc Step;
	QDrawFunc Draw;
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Engine //
class QEngine {
public:
	std::vector<QObj> Obj;	// An Engine contains Objects //

	inline QObj& Add() {
		Obj.push_back( QObj() );
		return Obj.back();
	}
		
public:
	void Step() {
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			QObj& Ob = Obj[idx];

			Ob.Step( Ob.Data );
			Ob.Rect = Ob.GetRect( Ob.Data );
		}
	}
	
	void Draw( const QRect& View, const Matrix4x4& Mat ) {
		// TODO: A Better Visibilty Check //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			QObj& Ob = Obj[idx];

			// If in the view //
			if ( Ob.Rect == View ) {
				Ob.Draw( Ob.Data, Mat );
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_ENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
