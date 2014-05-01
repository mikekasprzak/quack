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

#include <NewGrid/NewGrid.h>
#include <GelStamp/GelStamp.h>

#include <Skel/Skel.h>	// Temp //
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <list>
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

	QO_CAMERA,			// Camera //
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
typedef Matrix4x4	QMat;

typedef void*		QHandle;
// - ------------------------------------------------------------------------------------------ - //
// Quack Simulation Properties -- i.e. Gravity //
class QProp {
public:
	QVec Gravity;
	bool Debug;
	
public:
	// 9.80665f -- Earth's Gravity (Meters per Second Squared) //
	// 3.13155f -- Earth's Gravity (Meters per Second) //
	// 60.0f    -- Frames Per Second //
	QProp( const QVec& _Gravity = QVec(0, -3.13155f / (60.0f/2.0f)) ) :
		Gravity( _Gravity ),
		Debug( false )
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
bool Solve_Body( QBody& A, QBody& B, class QContactInfo& Info ); // Solve/Resolve Collisions //
// - ------------------------------------------------------------------------------------------ - //
// Quack Contact -- //
class QContact {
public:
	QVec		Point; // ? //
	QVec		Normal;
	QFloat		Length;
//	class QObj* Obj;
//	class QObj*	Vs;
};
// - ------------------------------------------------------------------------------------------ - //
class QContactInfo {
public:
	QContact Contact;
};
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
class QSensorData {
public:
	int Message;
	const char* Name;
};
// - ------------------------------------------------------------------------------------------ - //
class QSensorInfo {
public:
	QSensorData A;
	QSensorData B;
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
	typedef void (*QContactFunc)( void* self, QObj& Obj, QObj& Vs, QContactInfo& Info );
	typedef void (*QNotifyFunc)( void* self, QObj& Obj, QObj& Sender, const int Message );

	typedef QSensor* (*QGetSensorFunc)( void* self );
	typedef void (*QSenseFunc)( void* self, QObj& Obj, QObj& Vs, QSensorInfo& Info );

	typedef bool (*QInitFunc)( void* self, QObj& Obj );
	typedef bool (*QStepFunc)( void* self, QObj& Obj, const QProp& );
	typedef void (*QDrawFunc)( void* self, const Matrix4x4& );

public:
	int				Type;	
	GelStamp		Stamp;			// Step and Draw need to stamp me whenever I've been checked. //

	// NOTE NEW: MyIndex should be replaced by a unique Id. (a stamp?)
	// NOTE: MyIndex is unreliable as a reference due to the Optimize function reassigning them. //
//	st32 			MyIndex;		// Which Object I am in the Engine (by Index). //
	GelStamp		UID;			// Unique Identifier of this Object //
	
	// NOTE NEW: This can probable be removed //
//	class QEngine*	Parent;			// My Parent (Engine) //
	void*			Data;

	QRect			Rect;

public:
	QGetArtFunc			_GetArt; // Add a header? //
	QSetArtFunc			_SetArt;
	QSetArtScaleFunc	_SetArtScale; // Odd scope? //
	
	QGetRectFunc		_GetRect;
	QGetRectFunc		_GetBodyRect;
	QGetRectFunc		_GetSensorRect;

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
	inline QObj( const GelStamp _UID ) : // class QEngine* _Parent, const st32 _MyIndex ) :
		Stamp( 0 ),	// New Objects should be Zero Stamped //
		UID( _UID )
//		Parent(_Parent),
//		MyIndex(_MyIndex)
	{
	}

public:
	inline int GetType() const { return Type; }
	inline void* Get() { return Data; }

	inline void* GetArt() { return _GetArt(Data); }
	inline void SetArt( const char* ArtFile ) { _SetArt(Data,ArtFile); }
	inline void SetArtScale( const QVec& _Scale ) { _SetArtScale(Data,_Scale); }

	inline QRect GetRect() { return _GetRect(Data); }
	inline QRect GetBodyRect() { return _GetBodyRect(Data); }

	inline QBody* GetBody() { return _GetBody(Data); }
	inline QVec GetPos() { return _GetPos(Data); }
	inline QVec GetVelocity() { return _GetVelocity(Data); }
	inline QFloat GetInvMass() { return _GetInvMass(Data); }
	inline void SetMass( const QFloat Mass ) { _SetMass(Data,Mass); }
	inline void SetShape( const QVec& Shape ) { _SetShape(Data,Shape); }
	inline void AddForce( const QVec& Force ) { _AddForce(Data,Force); }

	inline QSensor* GetSensor() { return _GetSensor(Data); }
	inline void Sense( QObj& Vs, QSensorInfo& Info ) { _Sense(Data,*this,Vs,Info); }

	inline void Contact( QObj& Vs, QContactInfo& Info ) { _Contact(Data,*this,Vs,Info); }
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
// Quack Camera //
class QCamera { 
public:
	int		Type;			// Camera Type (not needed yet) //
	st32 	MyIndex;		// Which camera I am in the engine //
	QVec	Pos;
	QFloat	Scale;
	
	// TODO: Cameras need some reason (and way) to zoom in and out.

	// THIS WILL BE UNSAFE! THE POINTER INVALIDATES WHEN ENOUGH OBJECTS ARE ADDED TO THE ENGINE //	
	QObj* Target;
//	QHandle Target;
	// TODO: Add a way to target multiple objects (loosely).

	inline QCamera( QObj* _Target = 0 ) :
		Type( QO_CAMERA ),
		Scale( 256.0f ),
		Target( _Target )
	{
		if ( Target ) {
			Pos = Target->GetPos();
		}
	}

public:
	inline void Step() {
		if ( Target ) {
			QVec Diff = Target->GetPos() - Pos;
			Pos += Diff * QFloat(0.25f);
		}
	}

public:
	inline QMat GetMatrix( const int ViewportWidth, const int ViewportHeight ) const {
		QMat Ret = QMat::Identity;

		QFloat InvScale = QFloat::One / Scale;
		Ret *= QMat::TranslationMatrix( -Pos );
		Ret *= QMat::ScalarMatrix( InvScale );

		QFloat AspectRatio = QFloat( ViewportWidth / ViewportHeight );
		bool WideRatio = AspectRatio > QFloat::One;
		QVec AspectVec = QVec(AspectRatio,QFloat::One);
		if ( WideRatio )
			AspectVec = QVec(QFloat::One,QFloat::One/AspectRatio);
		QVec InvAspectVec = QFloat::One / AspectVec;

		Ret *= QMat::ScalarMatrix( InvAspectVec );
		
		return Ret;
	}
	
	inline QVec GetView( const int ViewportWidth, const int ViewportHeight ) const {
		QFloat AspectRatio = QFloat( ViewportWidth / ViewportHeight );
		bool WideRatio = AspectRatio > QFloat::One;
		QVec AspectVec = QVec(AspectRatio,QFloat::One);
		if ( WideRatio )
			AspectVec = QVec(QFloat::One,QFloat::One/AspectRatio);
		
		return QVec(Scale,Scale) * AspectVec;
	}
};
// - ------------------------------------------------------------------------------------------ - //
typedef std::list<QObj*> QObjList;
// - ------------------------------------------------------------------------------------------ - //
// Quack Object Grid (a Partitioning Scheme... gotta have something for now) //
template <typename T>
class QObjGrid {
	typedef std::list<T> QList;
protected:	
	GelGrid<QList> Data;
	
	st32 CellW, CellH;
	QRect Rect;
public:
	inline QObjGrid() :
		Data(128,128),
		CellW( 48+48 ),
		CellH( 48+48 ),
		//Rect( -((Data.Width()*CellW)>>1),-((Data.Height()*CellH)>>1), Data.Width()*CellW,Data.Height()*CellH )
		Rect( GridX(),GridY(), GridWidth(),GridHeight() )
	{
		// Things outside Rect are considered "in the void" //
	}

	inline QList& operator [] ( const int Index ) {
		return Data[Index];
	}
	inline const QList& operator [] ( const int Index ) const {
		return Data[Index];
	}
	
public:
	inline int GridX() const {
		return -((Data.Width()*CellW)>>1);
	}
	inline int GridY() const {
		return -((Data.Height()*CellH)>>1);
	}
	inline st32 GridWidth() const {
		return Data.Width()*CellW;
	}
	inline st32 GridHeight() const {
		return Data.Height()*CellH;
	}
	
	inline st32 Width() const {
		return Data.Width();
	}
	inline st32 Height() const {
		return Data.Height();
	}
	
	inline st32 CellWidth() const {
		return CellW;
	}
	inline st32 CellHeight() const {
		return CellH;
	}
	
	
	inline int Index( const int _x, const int _y ) const {
//		Log( "%i %i", _x,_y );
		return Data.Index(_x,_y);
	}

	inline st Size( const int idx ) const {
		if ( (idx >= 0) && (idx < Data.Size()) ) {
			return Data[idx].size();
		}
		return 0;
	}
	inline st Size( const int _x, const int _y ) const {
		return Size( Index(_x,_y) );
	}

public:
	inline void Clear() {
		for ( st idx = 0; idx < Data.Size(); idx++ ) {
			Data[idx].clear();
		}
	}

	inline bool IsInside( const QRect& VsRect ) const {
		return VsRect.IsInside( Rect );
	}
	
	inline int FindCellIndex( const QRect& VsRect ) const {
		//Log( "%f %f - %f %f", Rect.P1().x.ToFloat(),Rect.P1().y.ToFloat(), Rect.Width().ToFloat(),Rect.Height().ToFloat() );
		//Log( "%f %f", VsRect.P1().x.ToFloat(), VsRect.P1().y.ToFloat() );

		QVec Pos = VsRect.P1() - Rect.P1();
		Pos /= QVec(CellW,CellH); // TODO: Reciprocal //
//		Log( "%f %f", Pos.x.ToFloat(), Pos.y.ToFloat() );
		
		return Index( (int)(Pos.x.ToFloat()), (int)(Pos.y.ToFloat()) );
	}

	inline QVec FindCornerCellPos( const QRect& VsRect ) const {
		QVec Pos = VsRect.P1();// - Rect.P1();
		Pos /= QVec(CellW,CellH); // TODO: Reciprocal //
		Pos = QVec(Pos.x.Floor(),Pos.y.Floor());
		Pos *= QVec(CellW,CellH);
		return Pos;	
	}

	inline int FindCellWidth( const QRect& VsRect ) const {
		QVec Pos1 = VsRect.P1() - Rect.P1();
		Pos1 /= QVec(CellW,CellH); // TODO: Reciprocal //
		QVec Pos2 = VsRect.P2() - Rect.P1();
		Pos2 /= QVec(CellW,CellH); // TODO: Reciprocal //
//		Log( "%f %f vs %f %f", Pos1.x.ToFloat(), Pos1.y.ToFloat(), Pos2.x.ToFloat(), Pos2.y.ToFloat() );
		
		return (int)(ceil(Pos2.x.ToFloat())-floor(Pos1.x.ToFloat()));
	}
	inline int FindCellHeight( const QRect& VsRect ) const {
		QVec Pos1 = VsRect.P1() - Rect.P1();
		Pos1 /= QVec(CellW,CellH); // TODO: Reciprocal //
		QVec Pos2 = VsRect.P2() - Rect.P1();
		Pos2 /= QVec(CellW,CellH); // TODO: Reciprocal //
		
		return (int)(ceil(Pos2.y.ToFloat())-floor(Pos1.y.ToFloat()));
	}

	inline void Add( const QRect& VsRect, T Value ) {
		QVec Pos1 = VsRect.P1() - Rect.P1();
		Pos1 /= QVec(CellW,CellH); // TODO: Reciprocal //
		QVec Pos2 = VsRect.P2() - Rect.P1();
		Pos2 /= QVec(CellW,CellH); // TODO: Reciprocal //
		//Log( "%f %f", Pos.x.ToFloat(), Pos.y.ToFloat() );
		
		int X1 = (int)(Pos1.x.ToFloat());
		int Y1 = (int)(Pos1.y.ToFloat());
		int X2 = (int)(Pos2.x.ToFloat());
		int Y2 = (int)(Pos2.y.ToFloat());
		
		for ( int y = Y1; y <= Y2; ++y ) {
			for ( int x = X1; x <= X2; ++x ) {
				Data(x,y).push_front( Value );
			}
		}
	}

public:
	inline void Draw() {
		
	}
};
// - ------------------------------------------------------------------------------------------ - //
// Quack Engine //
// TODO: Client and Server Engines //
class QEngine {
public:
	QProp Prop;
	std::list<QObj> Obj;			// An Engine contains Objects //
	QObjGrid<QObj*> Grid;

	// NOTE: THIS IS A SOURCE OF SEGFALT! POINTERS TO CAMERAS in an STD::VECTOR! //
	std::vector<QCamera> Camera;	// It also contains Cameras //

	GelStamper Stamper;
	GelStamper UniqueID;

public:
	inline QEngine() {
		// Workaround for the Object Adding Segfault //
		// TODO: Add Dummy (Index 0) //
		Camera.reserve(4);

		Log("** Engine Created %x",this);
	}
	inline ~QEngine() {
		Log("** Engine Deleted %x",this);
	}

public:
	inline QObj& Add() {
		// TODO: Add an Object Recycling System. Deleted go on a list. //
		// NOTE: The UniqueID code runs a small risk of overflowing. 
		Obj.push_back( QObj( UniqueID.RetNewStamp() ) );
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
	
//	inline QCamera& AddCamera( Handle ) {
//		Camera.push_back( QCamera() );
//		return Camera.back();
//	}

//	inline QObj& operator [] ( const st Index ) {
//		return Obj[Index];
//	}
//	inline const QObj& operator [] ( const st Index ) const {
//		return Obj[Index];
//	}
		
public:
	void Step() {
		// Top of the frame, clear the grid. We'll be reinserting as we go. //
		Grid.Clear();

//		Log( "******" );
		// Broad Phase: Iterate for all elements. Check the cells they overlap, then add self. //
		for ( typename std::list<QObj>::iterator ItrA = Obj.begin(); ItrA != Obj.end(); ++ItrA ) {
			QRect RectA = ItrA->Rect;
			QSensor* Sensor = ItrA->GetSensor();
			if ( Sensor ) {
				RectA += Sensor->Rect;
			}

			if ( Grid.IsInside( RectA ) ) {
				int CellIndex = Grid.FindCellIndex( RectA );
				int CellWidth = Grid.FindCellWidth( RectA );
				int CellHeight = Grid.FindCellHeight( RectA );
	
	//			Log( "* [%llX] = %i (%i,%i)", &(*ItrA), CellIndex, CellWidth, CellHeight );
	
				for ( int y = 0; y < CellHeight; ++y ) {
					for ( int x = 0; x < CellWidth; ++x ) {
						int IndexItr = CellIndex + (y*Grid.Width()) + x;
						// Check against all objects in my cell //
						if ( Grid.Size( IndexItr ) ) {
							QObjList& VsList = Grid[ IndexItr ];
							for ( typename std::list<QObj*>::iterator ItrB = VsList.begin(); ItrB != VsList.end(); ++ItrB ) {
								if ( Stamper.Check( (**ItrB).Stamp ) ) {
									Solve( *ItrA, **ItrB );
								}
							}
						}
					}
				}

				if ( Stamper.NewStamp() ) {
					Log( "! OMG WE'RE FALL DEAD !" );
					for ( typename std::list<QObj>::iterator Itr = Obj.begin(); Itr != Obj.end(); ++Itr ) {
						Stamper.Clear( Itr->Stamp );
					}
				}

				// Add me to the cell //
				Grid.Add( RectA, &(*ItrA) );
			}
		}
		
		// Old Brute Force Collision Check Code //
		// TODO: Broad Phase 1 (Cells): Test only against objects in same region //
//		for ( typename std::list<QObj>::iterator ItrA = Obj.begin(); ItrA != Obj.end(); ++ItrA ) {
//			// To eliminitae != self check, start at idx+1 //
//			typename std::list<QObj>::iterator ItrB = ItrA;
//			for ( ItrB++; ItrB != Obj.end(); ++ItrB ) {
//				Solve( *ItrA, *ItrB );
//			}
//		}

		// Step Objects Next //
		// TODO: Only if an active region (could cycle/sleep regions and update less often) //
		for ( typename std::list<QObj>::iterator Itr = Obj.begin(); Itr != Obj.end(); ++Itr ) {
			// NOTE: This check should be the sum of all rectangles, but it's less important here as it's just step //
			if ( Grid.IsInside( Itr->Rect ) ) {
				// Step Object (Can't use a Reference here, as Obj can be resized by Step) //
				if ( Itr->Step( Prop ) ) {
					// If the Object moved, update the Rectangle //
					Itr->UpdateRect();
				}
			}
		}

		// Move Cameras //
		for ( st Cam = 0; Cam < Camera.size(); Cam++ ) {
			Camera[Cam].Step();
		}
		
		// NOTE: This is partitioning only! Optimizing the original list of objects is unnecessary and unsafe! //
		// Reorganize Objects in a better order //
		//Optimize();
	}


	void Solve( QObj& ObA, QObj& ObB ) { 
		// Broad Phase 2 (Rectangles) //
		if ( ObA.Rect == ObB.Rect ) {
			// This is safe, as the Bodies are not used by Squirrel code //
			QBody* BodyA = ObA.GetBody();
			QBody* BodyB = ObB.GetBody();
			
			// Only if Objects have Bodies //
			if ( BodyA && BodyB ) {
				QContactInfo Info;
				// Solve/Resolve Collision //
				if ( Solve_Body(*BodyA,*BodyB,Info) ) {
					// If a collision was solved/resolved, trigger Contact events //
					ObA.Contact( ObB, Info );
					Info.Contact.Normal = -Info.Contact.Normal; // Flip the Normal //
					ObB.Contact( ObA, Info );			
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
			// Broad Phase 2 (Rectangles) //
			if ( SensorA->Rect == SensorB->Rect ) {
				// Compare Sensors //
				if ( Sense_Sensor(ObA,*SensorA, ObB,*SensorB) ) {
					// Sense Squirrel Functions are called in Sense_Sensor //
					
					// Inside Sense_Sensor (QSensorSpineBB.h), we iterate over //
					// all sensors of the object. Then compare, one by one, each //
					// sensor vs eachother. //
					// After that, we populate a QSensorInfo and call the Squirrel //
					// Sense functions (both of them). //
				}
			}
		}
		
	}

public:	
	void Draw( const QRect& View, const Matrix4x4& Mat ) {
		// NOTE: Double Drawing is due to multiple cells having multiple instances of objects. //
		// TODO: Do timestamping here as well!! //
		int CellIndex = Grid.FindCellIndex( View );
		int CellWidth = Grid.FindCellWidth( View );
		int CellHeight = Grid.FindCellHeight( View );

		for ( int y = 0; y < CellHeight; ++y ) {
			for ( int x = 0; x < CellWidth; ++x ) {
				int IndexItr = CellIndex + (y*Grid.Width()) + x;
				// Check against all objects in my cell //
				if ( Grid.Size( IndexItr ) ) {
					QObjList& VsList = Grid[ IndexItr ];

					for ( typename std::list<QObj*>::iterator Itr = VsList.begin(); Itr != VsList.end(); ++Itr ) {
						QObj& Ob = **Itr;
						
						if ( Stamper.Check( Ob.Stamp ) ) {
							// If in the view (Rectangle Test) //
							if ( Ob.Rect == View ) {
								// TODO: Add to Draw Queue, to allow sorting/layering. //
								Ob.Draw( Mat );
							}
	
							if ( Prop.Debug ) {
								gelDrawSquare(Mat,Ob.Rect.Center().ToVector3D(),Ob.Rect.HalfShape(),GEL_RGBA(96,96,0,96));
				
								QSensor* Sensor = Ob.GetSensor();
								if ( Sensor ) {
									gelDrawSquare(Mat,Sensor->Rect.BasePoint().ToVector3D(),Sensor->Rect.HalfShape(),GEL_RGBA(32,96,32,96));
								}
							}
						}
					}
				}
			}
		}

		if ( Stamper.NewStamp() ) {
			Log( "! OMG WE'RE ALL DEAD !" );
			for ( typename std::list<QObj>::iterator Itr = Obj.begin(); Itr != Obj.end(); ++Itr ) {
				Stamper.Clear( Itr->Stamp );
			}
		}

		if ( Prop.Debug ) {			
			QVec CellPos = Grid.FindCornerCellPos( View );
			QVec CellShape(Grid.CellWidth(),Grid.CellHeight());
			for ( int y = 0; y < CellHeight; ++y ) {
				for ( int x = 0; x < CellWidth; ++x ) {
					QVec Pos = CellPos + QVec(x*Grid.CellWidth(),y*Grid.CellHeight());
					gelDrawRect(
						Mat,
						Pos.ToVector3D(),
						CellShape,
						GEL_RGBA(48,0,96,96));
				}
			}
		}


		// Old Brute Force Draw code //
//		for ( typename std::list<QObj>::iterator Itr = Obj.begin(); Itr != Obj.end(); ++Itr ) {
//			QObj& Ob = *Itr;
//
//			// If in the view (Rectangle Test) //
//			if ( Ob.Rect == View ) {
//				// TODO: Add to Draw Queue, to allow sorting/layering. //
//				Ob.Draw( Mat );
//			}
//			
//			if ( Prop.Debug ) {
//				gelDrawSquare(Mat,Ob.Rect.Center().ToVector3D(),Ob.Rect.HalfShape(),GEL_RGBA(96,96,0,96));
//
//				QSensor* Sensor = Ob.GetSensor();
//				if ( Sensor ) {
//					gelDrawSquare(Mat,Sensor->Rect.BasePoint().ToVector3D(),Sensor->Rect.HalfShape(),GEL_RGBA(32,96,32,96));
//				}
//			}
//		}		
	}

	// This is something that needs to happen inside the partitioning, not the natural stepping of objects. //	
//	void Optimize() {
//		// TODO: Reassign Indexes based on new positions. //
//		// TODO: Reassign Indexes in the Named Object Search Table //
//		int Swaps = 0;
//		// Reorganize so that Infinite Mass Objects go last //
////		for ( st idx = 1; idx < Obj.size(); idx++ ) {
//		std::list<QObj>::iterator ItrA = Obj.begin();
//		std::list<QObj>::iterator ItrB = ItrA;
//		for ( ItrB++; ItrB != Obj.end(); ++ItrB ) {
//			if ( ItrB->GetInvMass() == Real::Zero ) {
//				if ( ItrA->GetInvMass() != Real::Zero ) {
////					std::swap(Obj[idx-1],Obj[idx]);
//					std::swap(ItrB,ItrA);
//
//					// Update internal Indexes, now that they've changed position //
//					st32 OldIndex = Obj[idx-1].MyIndex;
//					Obj[idx-1].MyIndex = Obj[idx].MyIndex;
//					Obj[idx].MyIndex = OldIndex;
//
//					Swaps++;
//				}
//			}
//		}
//		if ( Swaps ) {
//			Log("Optimized: %i Object Swaps", Swaps);
//		}
//	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
