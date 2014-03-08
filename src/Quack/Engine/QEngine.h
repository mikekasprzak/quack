// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QENGINE_H__
#define __QUACK_ENGINE_QENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Geometry/Rect.h>

#include <Render/GelDraw.h>
#include <RTCD/RTCD.h>
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
		QB_CAPSULE,					// Capsule //
//		QB_POLY,					// Polygon (mesh?) //
	QB_NORMAL_END,

	// Statics -- Immoble Objects of Infinite Mass //
	QB_STATIC_START,
		QB_STATIC_AABB = QB_STATIC_START,
		QB_STATIC_SPHERE,
		QB_STATIC_CAPSULE,
		QB_STATIC_POLY,
	QB_STATIC_END,

	// Sensors -- Detect Collisions only, and send messages //
	QB_SENSOR_START,
		QB_SENSOR_AABB = QB_SENSOR_START,
		QB_SENSOR_SPHERE,
		QB_SENSOR_CAPSULE,
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
	
	QO_DUMMY = 1,		// Dumb Static Example Object //
	QO_BOXY,			// Dumb Simple Box Shaped Physical Object //
	QO_BOXY_STATIC,		// Dumb Simple Box Shaped Static Solid Object //
	QO_BALLY,			// Dumb Simple Ball Shaped Physical Object //
	QO_CAPPY,			// Dumb Simple Capsule Shaped Physical Object (Does not physically rotate) //
	QO_CAPPY_STATIC,	// Dumb Simple Capsule Shaped Solid Object //
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
	typedef void (*QAddForceFunc)( void* self, const QVec& Force );
	typedef void (*QContactFunc)( void* self, QObj& Vs );
	typedef void (*QNotifyFunc)( void* self, QObj& Sender, const int Message );

	typedef bool (*QStepFunc)( void* self, const QProp& );
	typedef void (*QDrawFunc)( void* self, const Matrix4x4& );

public:
	int		Type;
	void*	Data;

	QRect	Rect;

	QGetRectFunc	_GetRect;
	QGetBodyFunc	_GetBody;
	QAddForceFunc	_AddForce;
	QContactFunc	_Contact;
	QNotifyFunc		_Notify;

	QStepFunc		_Step;
	QDrawFunc		_Draw;

public:
	inline QRect GetRect() { return _GetRect(Data); }
	inline QBody* GetBody() { return _GetBody(Data); }
	inline void AddForce( const QVec& Force ) { _AddForce(Data,Force); }
	inline void Contact( QObj& Vs ) { _Contact(Data,Vs); }
	inline void Notify( QObj& Sender, const int Message ) { _Notify(Data,Sender,Message); }

	inline bool Step( const QProp& Prop ) { return _Step(Data,Prop); }
	inline void Draw( const Matrix4x4& Mat ) { _Draw(Data,Mat); }

public:
	inline void UpdateRect() {
		Rect = GetRect();
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Engine //
// TODO: Client and Server Engines //
class QEngine {
public:
	QProp Prop;
	std::vector<QObj> Obj;	// An Engine contains Objects //

public:
	inline QEngine() {
		Log("** Engine Created %x",this);
	}
//	inline void Death() {
//		Log("** Engine Deleted");
//	}
	inline ~QEngine() {
		Log("** Engine Deleted %x",this);
	}

public:
	inline QObj& Add() {
		Obj.push_back( QObj() );
		return Obj.back();
	}
	inline QObj& Back() {
		return Obj.back();
	}
	inline QObj& Front() {
		return Obj.front();
	}
	inline st Size() {
		return Obj.size();
	}

	inline QObj& operator [] ( const st Index ) {
		return Obj[Index];
	}
	inline const QObj& operator [] ( const st Index ) const {
		return Obj[Index];
	}
		
public:
	void Step() {
		// Step Objects //
		// TODO: Only if an active region (could cycle/sleep regions and update less often) //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			QObj& Ob = Obj[idx];

			// Step Object //
			if ( Ob.Step( Prop ) ) {
				// If the Object moved, update the Rectangle //
				Ob.Rect = Ob.GetRect();
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
					QBody* BodyA = ObA.GetBody();
					QBody* BodyB = ObB.GetBody();
					
					// Only if Objects have Bodies //
					if ( BodyA && BodyB ) {
						// Solve/Resolve Collision //
						if ( BodyA->Solve( *BodyB ) ) {
							// If a collision was solved/resolved, trigger Contact events //
							ObA.Contact( ObB );
							ObB.Contact( ObA );						
							// Update Rectangles //
							ObA.Rect = ObA.GetRect();
							ObB.Rect = ObB.GetRect();
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
				Ob.Draw( Mat );
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
