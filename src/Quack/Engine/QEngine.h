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

#include <Skel/Skel.h>	// Temp //
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <algorithm>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// QBody Types -- Quack Body (Collision) //
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
	// NOTE: Obsolete? //
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
// QObj Types -- Quack Object (Entity) //
enum {
	QO_NULL = 0,
	
	QO_DUMMY = 1,		// Dumb Static Example Object //
	QO_BOXY,			// Dumb Simple Box Shaped Physical Object //
	QO_BOXY_STATIC,		// Dumb Simple Box Shaped Static Solid Object //
	QO_BALLY,			// Dumb Simple Ball Shaped Physical Object //
	QO_CAPPY,			// Dumb Simple Capsule Shaped Physical Object (Does not physically rotate) //
	QO_CAPPY_STATIC,	// Dumb Simple Capsule Shaped Solid Object //
	
	QO_BOXOBJ,			// Box Object, with Squirrel Hooks //
};
// - ------------------------------------------------------------------------------------------ - //
// QArt Types -- Quack Art //
enum {
	QA_NULL = 0,
	
	QA_DUMMY = 1,		// Placeholder //
	QA_SPINE,
};
// - ------------------------------------------------------------------------------------------ - //
// QSensor Types -- Quack Sensors (Test-only Collision) //
enum {
	QS_NULL = 0,
	
	QS_DUMMY = 1,		// Placeholder //
	SQ_BODY,			// Use the body as a sensor //
	QS_SPINE_BB,		// Use Spine Bounding Boxes (Polygons) //
};
// - ------------------------------------------------------------------------------------------ - //
// QSensorInfo Type -- Additional Data for Sense function //
enum {
	QSI_HURTBOX = 10000,
	QSI_HITBOX,
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
	bool ShowRects;
	
public:
	// 9.80665f -- Earth's Gravity (Meters per Second Squared) //
	// 3.13155f -- Earth's Gravity (Meters per Second) //
	// 60.0f    -- Frames Per Second //
	QProp( const QVec& _Gravity = QVec(0, -3.13155f / (60.0f/2.0f)) ) :
		Gravity( _Gravity ),
		ShowRects( false )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Body (Collision) //
class QBody {
public:
	typedef QFloat (*QGetInvMassFunc)( const void* self );

public:
	int		Type;
	void*	Data;

	QGetInvMassFunc 	_GetInvMass;

public:	
	inline bool HasInfiniteMass() const {
		return GetInvMass() == QFloat::Zero;
	}
	inline QFloat GetMass() const {
		return_if_value( QFloat::Zero, HasInfiniteMass() );		
		return QFloat::One / GetInvMass();
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
	inline int GetType() const { return Type; }
	inline void* Get() { return Data; }

	inline QFloat GetInvMass() const { return _GetInvMass(Data); }

};
// - ------------------------------------------------------------------------------------------ - //
bool Solve_Body( QBody& A, QBody& B ); // Solve/Resolve Collisions //
// - ------------------------------------------------------------------------------------------ - //
// Quack Art (Thing that handles art and animation) //
class QArt {
public:
	//typedef void* (*QGetFunc)( void* self );
	
public:
	int		Type;
	void*	Data;

public:
	inline int GetType() const { return Type; }
	inline void* Get() { return Data; }

	//inline void Step( ... ) { }
	//inline void Draw( ... ) const { ... }
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Sensors (Test-Only Collisions) //
class QSensor {
public:
	typedef QRect (*QGetRectFunc)( void* self );
	
public:
	int		Type;
	void*	Data;
	
	QRect	Rect;	

public:	
	QGetRectFunc		_GetRect;

public:
	inline int GetType() const { return Type; }
	inline void* Get() { return Data; }

	inline QRect GetRect() { return _GetRect(Data); }

public:
	inline void UpdateRect() {
		Rect = GetRect();
	}
};
// - ------------------------------------------------------------------------------------------ - //
bool Sense_Sensor( class QObj& ObA,QSensor& A, class QObj& ObB,QSensor& B );
// - ------------------------------------------------------------------------------------------ - //
class QSensorInfo {
public:
	int 			Type;	// Type of Sensor (0-9999, 10000 for HURTBOX, 10001 for HITBOX) //
	class QObj* 	Obj;	// Object //
	
public:
	inline QSensorInfo() { }
	inline QSensorInfo( QObj* const _Obj, const int _Type = 0 ) :
		Obj(_Obj),
		Type(_Type)
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Object (Engine Entity) //
class QObj {
public:
	typedef void (*QSetArtFunc)( void* self, const char* ArtFile );
	typedef void* (*QGetArtFunc)( void* self );
	typedef void (*QSetArtScaleFunc)( void* self, const QVec& _Scale );

	typedef QRect (*QGetRectFunc)( void* self );

	typedef QBody* (*QGetBodyFunc)( void* self );
	typedef QVec (*QGetPosFunc)( void* self );
	typedef QVec (*QGetVelocityFunc)( void* self );
	typedef QFloat (*QGetInvMassFunc)( void* self );
	typedef void (*QSetMassFunc)( void* self, const QFloat Mass );
	typedef void (*QSetShapeFunc)( void* self, const QVec& Shape );

	typedef void (*QAddForceFunc)( void* self, const QVec& Force );
	typedef void (*QContactFunc)( void* self, QObj& Obj, QObj& Vs );
	typedef void (*QNotifyFunc)( void* self, QObj& Obj, QObj& Sender, const int Message );

	typedef QSensor* (*QGetSensorFunc)( void* self );
	typedef void (*QSenseFunc)( void* self, QObj& Obj, QObj& Vs );

	typedef bool (*QInitFunc)( void* self, QObj& Obj );
	typedef bool (*QStepFunc)( void* self, QObj& Obj, const QProp& );
	typedef void (*QDrawFunc)( void* self, const Matrix4x4& );

public:
	int		Type;
	void*	Data;

	QRect	Rect;

public:
	QGetArtFunc			_GetArt; // Add a header? //
	QSetArtFunc			_SetArt;
	QSetArtScaleFunc	_SetArtScale; // Odd scope? //
	
	QGetRectFunc		_GetRect;

	QGetBodyFunc		_GetBody;
	// TODO: Move all of the following to the Body (perhaps a single member of Body, i.e. vtable) //
	QGetPosFunc			_GetPos;
	QGetVelocityFunc	_GetVelocity;
	QGetInvMassFunc		_GetInvMass;
	QSetMassFunc		_SetMass;
	QSetShapeFunc		_SetShape;
	QAddForceFunc		_AddForce;

	QGetSensorFunc		_GetSensor;
	QSenseFunc			_Sense;

	QContactFunc		_Contact;
	QNotifyFunc			_Notify;

	QInitFunc			_Init; // Doesn't Constructor do this? //
	QStepFunc			_Step;
	QDrawFunc			_Draw;

public:
	inline int GetType() const { return Type; }
	inline void* Get() { return Data; }

	inline void* GetArt() { return _GetArt(Data); }
	inline void SetArt( const char* ArtFile ) { _SetArt(Data,ArtFile); }
	inline void SetArtScale( const QVec& _Scale ) { _SetArtScale(Data,_Scale); }

	inline QRect GetRect() { return _GetRect(Data); }

	inline QBody* GetBody() { return _GetBody(Data); }
	inline QVec GetPos() { return _GetPos(Data); }
	inline QVec GetVelocity() { return _GetVelocity(Data); }
	inline QFloat GetInvMass() { return _GetInvMass(Data); }
	inline void SetMass( const QFloat Mass ) { _SetMass(Data,Mass); }
	inline void SetShape( const QVec& Shape ) { _SetShape(Data,Shape); }
	inline void AddForce( const QVec& Force ) { _AddForce(Data,Force); }

	inline QSensor* GetSensor() { return _GetSensor(Data); }
	inline void Sense( QObj& Vs ) { _Sense(Data,*this,Vs); }

	inline void Contact( QObj& Vs ) { _Contact(Data,*this,Vs); }
	inline void Notify( QObj& Sender, const int Message ) { _Notify(Data,*this,Sender,Message); }

	inline bool Init() { return _Init(Data,*this); }
	inline bool Step( const QProp& Prop ) { return _Step(Data,*this,Prop); }
	inline void Draw( const Matrix4x4& Mat ) { _Draw(Data,Mat); }

public:
	inline void UpdateRect() {
		Rect = GetRect();

		QSensor* Sensor = GetSensor();
		if ( Sensor ) {
			Sensor->UpdateRect();
//			Log("+%f %f", Sensor->Rect.P1().x.ToFloat(), Sensor->Rect.P1().y.ToFloat() );
			Sensor->Rect.P1() *= QFloat::Half;
			Sensor->Rect.Shape() *= QFloat::Half;
			Sensor->Rect.P1() += GetPos();
//			Log("-%f %f", Sensor->Rect.P1().x.ToFloat(), Sensor->Rect.P1().y.ToFloat() );
		}
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
		// Do Collisions First //
		// TODO: Broad Phase: Test only against objects in same region //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			// To eliminitae != self check, start at idx+1 //
			for ( st idx2 = idx+1; idx2 < Obj.size(); idx2++ ) {
				QObj& ObA = Obj[idx];
				QObj& ObB = Obj[idx2];
				
				// Narrow Phase //
				if ( ObA.Rect == ObB.Rect ) {
					QBody* BodyA = ObA.GetBody();
					QBody* BodyB = ObB.GetBody();
					
					// Only if Objects have Bodies //
					if ( BodyA && BodyB ) {
						// Solve/Resolve Collision //
						if ( Solve_Body(*BodyA,*BodyB) ) {
							// If a collision was solved/resolved, trigger Contact events //
							ObA.Contact( ObB );
							ObB.Contact( ObA );						
							// Update Rectangles //
							ObA.UpdateRect();
							ObB.UpdateRect();
						}
					}
				}
				
				QSensor* SensorA = ObA.GetSensor();
				QSensor* SensorB = ObB.GetSensor();

				// Only Sense if both Objects have Sensors //
				if ( SensorA && SensorB ) {
					// Narrow Phase //
					if ( SensorA->Rect == SensorB->Rect ) {
						// Compare Sensors //
						if ( Sense_Sensor(ObA,*SensorA, ObB,*SensorB) ) {
							// Sense Functions are called in Sense_Sensor //
						}
					}
				}
			}
		}

		// Step Objects Next //
		// TODO: Only if an active region (could cycle/sleep regions and update less often) //
		for ( st idx = 0; idx < Obj.size(); idx++ ) {
			QObj& Ob = Obj[idx];

			// Step Object //
			if ( Ob.Step( Prop ) ) {
				// If the Object moved, update the Rectangle //
				Ob.UpdateRect();
			}
		}
		
		// Reorganize Objects in a better order //
		Optimize();
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
			
//			if ( Prop.ShowRects )
			{
				gelDrawSquare(Mat,Ob.Rect.Center().ToVector3D(),Ob.Rect.HalfShape(),GEL_RGBA(96,96,0,96));

				QSensor* Sensor = Ob.GetSensor();
				if ( Sensor ) {
					gelDrawSquare(Mat,Sensor->Rect.Center().ToVector3D(),Sensor->Rect.HalfShape(),GEL_RGBA(32,96,32,96));
				}
			}
		}
	}
	
	void Optimize() {
		int Swaps = 0;
		// Reorganize so that Infinite Mass Objects go last //
		for ( st idx = 1; idx < Obj.size(); idx++ ) {
			if ( Obj[idx-1].GetInvMass() == Real::Zero ) {
				if ( Obj[idx].GetInvMass() != Real::Zero ) {
					std::swap(Obj[idx-1],Obj[idx]);
					Swaps++;
				}
			}
		}
		if ( Swaps ) {
			Log("Optimized: %i Object Swaps", Swaps);
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
