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
	QVec Size;
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
		Size(4,4),
		Color(GEL_SRGB_DEFAULT),
		ArtIndex(0)
	{
	}
	
	inline void Set( const QVec _Pos, const int _ArtIndex = 0 ) {
		Pos = _Pos;
		Orientation = QVec(0,1);
		Size = QVec(4,4);
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

		Size += ShapeVelocity;
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
	inline QEmitter() :
		GelParticle<QParticle>( 128 )// 4096 )
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
		for ( int idx = 0; idx < Size(); ++idx ) {
			if ( IsAlive( idx ) ) {
				gelDrawSquareFill( Mat, (*this)[idx].Pos.ToVector3D(), (*this)[idx].Size, ToGelColor((*this)[idx].Color) );
			}
		}
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
