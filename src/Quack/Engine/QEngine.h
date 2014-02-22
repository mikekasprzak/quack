// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QENGINE_H__
#define __QUACK_ENGINE_QENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
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

	// Normal -- Physical Objects //
	QB_AABB = 1, 	// Rectangle //
	QB_SPHERE,		// Circle //
	QB_POLY,		// Polygon (mesh?) //

	// Sensors -- Detect Collisions only, and send messages //
	QB_SENSOR_AABB,
	QB_SENSOR_SPHERE,
	QB_SENSOR_POLY,

	// Statics -- Immoble Objects of Infinite Mass //
	QB_STATIC_AABB,
	QB_STATIC_SPHERE,
	QB_STATIC_POLY,
};
// - ------------------------------------------------------------------------------------------ - //
// QObj -- Quack Object (Entity) //
enum {
	QO_NULL = 0,
	
	QO_DUMMY = 1,	// Dumb Static Example Object //
	QO_BOXY,		// Dumb Simple Box Shaped Physical Object //
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
	typedef QFloat (*QGetInvMassFunc)( const void* self );
//	typedef bool (*QStepFunc)( const void* self );

public:
	int		Type;
	void*	Data;

	QGetInvMassFunc 	GetInvMass;
//	QStepFunc 			Step;

public:	
	inline bool HasInfiniteMass() const {
		return GetInvMass( this ) == QFloat::Zero;
	}
	inline QFloat GetMass() const {
		return_if_value( QFloat::Zero, HasInfiniteMass() );		
		return QFloat::One / GetInvMass( this );
	}

public:	
	bool Solve( QBody& Vs ); // Solve/Resolve Collisions //
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Object (Engine Entity) //
class QObj {
public:
	typedef QRect (*QGetRectFunc)( void* self );
	typedef QBody* (*QGetBodyFunc)( void* self );
	typedef bool (*QStepFunc)( void* self );
	typedef void (*QDrawFunc)( void* self, const Matrix4x4& );

public:
	int		Type;
	void*	Data;

	QRect	Rect;

	QGetRectFunc	GetRect;
	QGetBodyFunc	GetBody;
	QStepFunc		Step;
	QDrawFunc		Draw;
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Engine //
// TODO: Client and Server Engines //
class QEngine {
public:
	std::vector<QObj> Obj;	// An Engine contains Objects //

	inline QObj& Add() {
		Obj.push_back( QObj() );
		return Obj.back();
	}
		
public:
	void Step() {
		// Step Objects //
		// TODO: Only if an active region (could cycle/sleep regions and update less often) //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			QObj& Ob = Obj[idx];

			// Step Object //
			if ( Ob.Step( Ob.Data ) ) {
				// If the Object moved, update the Rectangle //
				Ob.Rect = Ob.GetRect( Ob.Data );
			}
		}
		
		// Do Collision //
		// TODO: Only against objects in same region //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			// To eliminitae != self check, start at idx+1 //
			for ( st idx2 = idx+1; idx2 < Obj.size(); idx2++ ) {
				QObj& ObA = Obj[idx];
				QObj& ObB = Obj[idx2];
				
				// Broad Phase //
				if ( ObA.Rect == ObB.Rect ) {
					QBody* BodyA = ObA.GetBody( ObA.Data );
					QBody* BodyB = ObB.GetBody( ObB.Data );
					
					// Only if Objects have Bodies //
					if ( BodyA && BodyB ) {
						// Solve/Resolve Collision //
						if ( BodyA->Solve( *BodyB ) ) {
							// If a collision was solved/resolved, then update Rectangles //
							ObA.Rect = ObA.GetRect( ObA.Data );
							ObB.Rect = ObB.GetRect( ObB.Data );
						}
					}
				}
			}
		}
	}
	
	void Draw( const QRect& View, const Matrix4x4& Mat ) {
		// TODO: A Better Visibilty Check //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			QObj& Ob = Obj[idx];

			// If in the view (Rectangle Test) //
			if ( Ob.Rect == View ) {
				// TODO: Add to Draw Queue, to allow sorting/layering. //
				Ob.Draw( Ob.Data, Mat );
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
