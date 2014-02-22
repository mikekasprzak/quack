// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QENGINE_H__
#define __QUACK_ENGINE_QENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>

#include <Render/GelDraw.h>
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
	QB_NORMAL_START = 1,
		QB_AABB = QB_NORMAL_START, 	// Rectangle //
		QB_SPHERE,					// Circle //
		QB_POLY,					// Polygon (mesh?) //
	QB_NORMAL_END,

	// Statics -- Immoble Objects of Infinite Mass //
	QB_STATIC_START,
		QB_STATIC_AABB = QB_STATIC_START,
		QB_STATIC_SPHERE,
		QB_STATIC_POLY,
	QB_STATIC_END,

	// Sensors -- Detect Collisions only, and send messages //
	QB_SENSOR_START,
		QB_SENSOR_AABB = QB_SENSOR_START,
		QB_SENSOR_SPHERE,
		QB_SENSOR_POLY,
	QB_SENSOR_END,

	// More Constants //
	QB_SOLID_START =	QB_NORMAL_START,
	QB_SOLID_END = 		QB_STATIC_END,	

	QB_NORMAL_COUNT = QB_NORMAL_END - QB_NORMAL_START,
	QB_STATIC_COUNT = QB_STATIC_END - QB_STATIC_START,
	QB_SENSOR_COUNT = QB_SENSOR_END - QB_SENSOR_START,
};
// - ------------------------------------------------------------------------------------------ - //
// QObj -- Quack Object (Entity) //
enum {
	QO_NULL = 0,
	
	QO_DUMMY = 1,	// Dumb Static Example Object //
	QO_BOXY,		// Dumb Simple Box Shaped Physical Object //
	QO_BOXY_STATIC,	// Dumb Simple Box Shaped Static Solid Object //
	QO_BALLY,		// Dumb Simple Ball Shaped Physical Object //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Primitive Types //
typedef Real 		QFloat;
typedef Vector2D	QVec;
typedef Rect2D		QRect;
// - ------------------------------------------------------------------------------------------ - //
// Quack Simulation Properties -- i.e. Gravity //
class QProp {
public:
	QVec Gravity;
	
public:
	// 9.80665f -- Earth's Gravity (Meters per Second Squared) //
	// 3.13155f -- Earth's Gravity (Meters per Second) //
	// 60.0f    -- Frames Per Second //
	QProp( const QVec& _Gravity = QVec(0, -3.13155f / 60.0f) ) :
		Gravity( _Gravity )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Body (Collision) //
class QBody {
public:
	typedef QFloat (*QGetInvMassFunc)( const void* self );
//	typedef bool (*QStepFunc)( const void* self, const QProp& Prop );

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
	
	inline bool IsNormal() const {
		if ( Type >= QB_NORMAL_START )
			return Type < QB_NORMAL_END;
		return false;
	}
	inline bool IsSensor() const {
		if ( Type >= QB_SENSOR_START )
			return Type < QB_SENSOR_END;
		return false;
	}
	inline bool IsStatic() const {
		if ( Type >= QB_STATIC_START )
			return Type < QB_STATIC_END;
		return false;
	}
	inline bool IsSolid() const {
		if ( Type >= QB_SOLID_START )
			return Type < QB_SOLID_END;
		return false;
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
	typedef bool (*QStepFunc)( void* self, const QProp& );
	typedef void (*QDrawFunc)( void* self, const Matrix4x4& );

public:
	int		Type;
	void*	Data;

	QRect	Rect;

	QGetRectFunc	GetRect;
	QGetBodyFunc	GetBody;
	QStepFunc		Step;
	QDrawFunc		Draw;
	
public:
	inline void UpdateRect() {
		Rect = GetRect( Data );
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Engine //
// TODO: Client and Server Engines //
class QEngine {
public:
	QProp Prop;
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
			if ( Ob.Step( Ob.Data, Prop ) ) {
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
			
			gelDrawSquare(Mat,Ob.Rect.Center().ToVector3D(),Ob.Rect.HalfShape(),GEL_RGBA(64,64,0,64));
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
