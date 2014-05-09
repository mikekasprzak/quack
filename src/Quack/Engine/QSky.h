// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QSKY_H__
#define __QUACK_ENGINE_QSKY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QSkyGradient {
	typedef QSkyGradient thistype;
public:	
	int Bands;
	GelColor Color;
	
	inline QSkyGradient( const int _Bands, const GelColor _Color ) :
		Bands(_Bands),
		Color(_Color)
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class QSky {
	typedef QSky thistype;
public:
	GelAlloc2C Vert;
	std::vector<QSkyGradient> Gradient;	// Elements of the Gradient //
	std::vector<GelColor> Band;
		
	QFloat BaseYPos;
		
	QFloat BandSize;
	bool Changed;
	
	inline QSky() :
		Vert( 128 * 6 ),
		BaseYPos(-8*12),
		BandSize( 8 ),
		Changed( false )
	{
	}
	
	inline void Add( const int BandSize, const GelColor Color ) {
		Gradient.push_back( QSkyGradient(BandSize, Color) );
		Changed = true;
	}
	
	inline void SetBandPos( const Real Pos ) {
		BaseYPos = Pos;
	}
	inline void SetBandSize( const Real Size ) {
		BandSize = Size;
	}
	
	inline void Step() {
		if ( Changed ) {
			for ( st idx = 1; idx < Gradient.size(); ++idx ) {
				QSkyGradient& G1 = Gradient[idx-1];
				QSkyGradient& G2 = Gradient[idx]; 
	
				GelColor C1 = G1.Color;
				GelColor C2 = G2.Color;
				
				for ( st idx2 = 0; idx2 < G1.Bands; ++idx2 ) {
					float StepScalar = (float)idx2 / (float)G1.Bands;
					// TODO: Smoothing Modes Between Gradients //
//					if ( SmoothStep ) {
//						StepScalar = Real(StepScalar).SmoothStep().ToFloat();
//					}
//					if ( EaseIn ) {
//						StepScalar = Real(StepScalar).EaseIn().ToFloat();
//					}
//					if ( EaseOut ) {
//						StepScalar = Real(StepScalar).EaseOut().ToFloat();
//					}
//					//else {
//					//	// Default is LERP //
//					//}
					
					GelSColor ColorDiff = GEL_SRGBA( 
						GEL_GET_R(C2)-GEL_GET_R(C1), 
						GEL_GET_G(C2)-GEL_GET_G(C1), 
						GEL_GET_B(C2)-GEL_GET_B(C1),
						GEL_GET_A(C2)-GEL_GET_A(C1)
						);
					GelColor BandColor = GEL_RGBA(
						GEL_GET_R(C1) + (int)((float)GEL_SGET_R(ColorDiff) * StepScalar),
						GEL_GET_G(C1) + (int)((float)GEL_SGET_G(ColorDiff) * StepScalar),
						GEL_GET_B(C1) + (int)((float)GEL_SGET_B(ColorDiff) * StepScalar),
						GEL_GET_A(C1) + (int)((float)GEL_SGET_A(ColorDiff) * StepScalar)
						);
					
					Band.push_back( BandColor );
				}
			}
			Band.push_back( Gradient.back().Color );
			Changed = false;
		}
	}
	
	inline void Draw( const QRect& View, const QMat& Mat ) {
		Vert.Clear();
		
		QFloat InvBandSize = Real::One / BandSize;
		
		int Start = (int)((View.P1().y - BaseYPos) * InvBandSize).Floor().ToFloat();
		int End = (int)((View.P2().y - BaseYPos) * InvBandSize).Ceil().ToFloat();

		if ( Start < 0 )
			Start = 0;
		if ( End < 0 )
			End = 0;

		if ( Start >= Band.size() )
			Start = Band.size()-1;
		if ( End >= Band.size() )
			End = Band.size()-1;
		
		for ( int idx = Start; idx < End; ++idx ) {
			GelColor C1 = Band[idx];
			//GelColor C2 = Band[idx+1];

			QFloat YPos = BaseYPos + (BandSize*QFloat(idx));

			QVec P1 = QVec(View.P1().x,YPos);
			QVec P2 = QVec(View.P2().x,YPos);
			QVec P3 = QVec(View.P2().x,YPos+BandSize);
			QVec P4 = QVec(View.P1().x,YPos+BandSize);
			
			Vert.Next()->Pos = P1;
			Vert->Color = C1;
			Vert.Next()->Pos = P2;
			Vert->Color = C1;
			Vert.Next()->Pos = P3;
			Vert->Color = C1;
	
			Vert.Next()->Pos = P3;
			Vert->Color = C1;
			Vert.Next()->Pos = P4;
			Vert->Color = C1;
			Vert.Next()->Pos = P1;
			Vert->Color = C1;
		}
		
		Gel::RenderColor2D_Packed( GEL_TRIANGLES, Mat, GEL_RGB_WHITE, &(Vert.Get()->Pos), &(Vert.Get()->Color), Vert.Size() );
	}
};	
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QSKY_H__ //
// - ------------------------------------------------------------------------------------------ - //

