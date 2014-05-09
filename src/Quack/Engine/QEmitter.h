// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QEMITTER_H__
#define __QUACK_ENGINE_QEMITTER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Array/GelArray.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
struct QParticle {
	QVec Pos;
	QVec Orientation;		// Basis Vector of the Orientation (2nd vector is Orientation.Tangent())
	QVec Shape;
	GelSColor Color;
	
	QVec Velocity;
	QFloat AngularVelocity;
	QVec ShapeVelocity;
	GelSColor ColorVelocity;
	
	QVec Drift;				// Sort of Acceleration, sort of not. //
	QFloat AngularDrift;
	QVec ShapeDrift;
	GelSColor ColorDrift;
	
	int ArtIndex;
	
	inline QParticle() :
		Shape(4,4),
		Color(GEL_SRGB_DEFAULT),
		ArtIndex(0)
	{
	}
	
	inline void Set( const QVec _Pos, const int _ArtIndex = 0 ) {
		Pos = _Pos;
		Orientation = QVec(0,1);
		Shape = QVec(4,4);
		Color = GEL_SRGB_DEFAULT;
		
		Velocity = QVec::Zero;
		AngularVelocity = QFloat::Zero;
		ShapeVelocity = QVec::Zero;
		ColorVelocity = 0ll;
		
		Drift = QVec::Zero;
		AngularDrift = QFloat::Zero;
		ShapeDrift = QVec::Zero;
		ColorDrift = 0ll;
		
		ArtIndex = _ArtIndex;
	}
	
	inline void Step() {
		Pos += Velocity;
		Velocity += Drift;
		
		Orientation += Orientation.Tangent() * AngularVelocity;
		AngularVelocity += AngularDrift;

		Shape += ShapeVelocity;
		ShapeVelocity += ShapeDrift;
		
		// TODO: Make Less Bad Please Batman! //
		// NOTE: There is no add operator for the Color types that saturate the values, to 8bit and 16bit parts //
		//       I.e. MMX Add and Saturate. //
		Color = AddGelSColor(Color,ColorVelocity);
		ColorVelocity = AddGelSColor(ColorVelocity,ColorDrift);
		
//		Color += ColorVelocity;
//		ColorVelocity += ColorDrift;
	}
};
// - ------------------------------------------------------------------------------------------ - //
//typedef GelArray<QParticle> QEmitter;
class QEmitter: public GelParticle<QParticle> {
public:
//	GelAlloc2UC Vert;
	GelAlloc2C Vert;
	
	inline QEmitter() :
		GelParticle<QParticle>( 4096 ),
		Vert( 4096*6 )
	{
	}
	
	inline void Step() {
		GelParticle<QParticle>::Step();
			
		for ( int idx = 0; idx < Size(); ++idx ) {
			if ( IsAlive( idx ) ) {
				(*this)[idx].Step();
			}
		}
	}
		
	inline void Draw( const QRect& View, const QMat& Mat ) {
		Vert.Clear();
		
		for ( int idx = 0; idx < Size(); ++idx ) {
			QParticle& Me = (*this)[idx];
			
			if ( IsAlive( idx ) ) {
				GelColor Color = ToGelColor(Me.Color);
				
				QVec P1 = Me.Pos + QVec(-Me.Shape.x,-Me.Shape.y);
				QVec P2 = Me.Pos + QVec(+Me.Shape.x,-Me.Shape.y);
				QVec P3 = Me.Pos + QVec(+Me.Shape.x,+Me.Shape.y);
				QVec P4 = Me.Pos + QVec(-Me.Shape.x,+Me.Shape.y);
				
				GelUV UV1(0,0);
				GelUV UV2(0,0);
				GelUV UV3(0,0);
				GelUV UV4(0,0);
				
				Vert.Next()->Pos = P1;
//				Vert->UV = UV1;
				Vert->Color = Color;
				Vert.Next()->Pos = P2;
//				Vert->UV = UV2;
				Vert->Color = Color;
				Vert.Next()->Pos = P3;
//				Vert->UV = UV3;
				Vert->Color = Color;

				Vert.Next()->Pos = P3;
//				Vert->UV = UV3;
				Vert->Color = Color;
				Vert.Next()->Pos = P4;
//				Vert->UV = UV4;
				Vert->Color = Color;
				Vert.Next()->Pos = P1;
//				Vert->UV = UV1;
				Vert->Color = Color;

				
		//		gelDrawSquareFill( Mat, Me.Pos.ToVector3D(), Me.Size, ToGelColor(Me.Color) );
			}
		}
		
		Gel::RenderColor2D_Packed( GEL_TRIANGLES, Mat, GEL_RGBA(255,255,255,0)/*GEL_RGB_WHITE*/, &(Vert.Get()->Pos), &(Vert.Get()->Color), Vert.Size() );
	}
	
	inline QParticle* Add( const GelTime Age, const QVec _Pos, const int _ArtIndex = 0 ) {
		QParticle* Ret = GelParticle<QParticle>::Add( Age );
		Ret->Set( _Pos, _ArtIndex );
		return Ret;
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QEMITTER_H__ //
// - ------------------------------------------------------------------------------------------ - //
