// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_QSENSORSPINEBB_H__
#define __QUACK_ENGINE_QSENSORSPINEBB_H__
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
namespace QK {
// - ------------------------------------------------------------------------------------------ - //
class QSensorSpineBB {
	typedef QSensorSpineBB thistype;
public:
	static void InitSensor( QSensor* self ) {
		self->Type = QS_SPINE_BB;
	}
public:
	GelSkelAnimator*	Skel;

public:
	inline QSensorSpineBB()
	{
	}
	
	inline void Set( GelSkelAnimator* _Skel ) {
		Skel = _Skel;
	}
};
// - ------------------------------------------------------------------------------------------ - //
//inline bool Sense_Sensor( const Vector2D& PosA, const GelSkelAnimator& SkelA, QSensorInfo& InfoA, const Vector2D& PosB, const GelSkelAnimator& SkelB, QSensorInfo& InfoB ) {
inline bool Sense_Sensor( QObj& ObA, QSensorSpineBB& SenA, QObj& ObB, QSensorSpineBB& SenB ) {
	bool Sensed = false;
	
	const Vector2D& PosA = ObA.GetPos();
	GelSkelAnimator& SkelA = *(SenA.Skel);

	const Vector2D& PosB = ObB.GetPos();
	GelSkelAnimator& SkelB = *(SenB.Skel);

//	_Log("(%.02f,%.02f) ", PosA.x.ToFloat(), PosA.y.ToFloat() );
//	Log("(%.02f,%.02f) ", PosB.x.ToFloat(), PosB.y.ToFloat() );

	for ( int IndexB = 0; IndexB < SkelB.GetSlotCount(); IndexB++ ) {
		spSlot* SlotB = SkelB._GetSlot(IndexB);
		//if ( !SlotB ) continue;
		spBoundingBoxAttachment* BBB = SkelB._GetBB(IndexB);
		if ( !BBB ) continue;
		for ( int IndexA = 0; IndexA < SkelA.GetSlotCount(); IndexA++ ) {
			spSlot* SlotA = SkelA._GetSlot(IndexA);
			//if ( !SlotA ) continue;
			spBoundingBoxAttachment* BBA = SkelA._GetBB(IndexA);
			if ( !BBA ) continue;

			// NOTE: Max Verts 16! //
			float bbVertA[16*2];
			float bbVertB[16*2];
			
			SkelA._TransformBBVertices(SlotA,BBA,bbVertA);
			SkelB._TransformBBVertices(SlotB,BBB,bbVertB);

			int bbVertASize = BBA->verticesCount;
			int bbVertBSize = BBB->verticesCount;
			
			for ( int idx = 0; idx < bbVertASize>>1; idx++ ) {
				bbVertA[(idx<<1)+0] *= 0.5f;
				bbVertA[(idx<<1)+0] += PosA.x.ToFloat();
				bbVertA[(idx<<1)+1] *= 0.5f;
				bbVertA[(idx<<1)+1] += PosA.y.ToFloat();
			}

			for ( int idx = 0; idx < bbVertBSize>>1; idx++ ) {
				bbVertB[(idx<<1)+0] *= 0.5f;
				bbVertB[(idx<<1)+0] += PosB.x.ToFloat();
				bbVertB[(idx<<1)+1] *= 0.5f;
				bbVertB[(idx<<1)+1] += PosB.y.ToFloat();
			}
			
			if ( ConvexVsConvex(bbVertA,bbVertASize, bbVertB,bbVertBSize ) ) {
				Sensed = true;
				
				Log( "** [%x][%i] %s (%.01f,%.01f) vs [%x][%i] %s (%.01f,%.01f)...", 
					SkelA.GetSkeleton(),IndexA,SkelA.GetName(IndexA),
					PosA.x.ToFloat(),PosA.y.ToFloat(),
					SkelB.GetSkeleton(),IndexB,SkelB.GetName(IndexB),
					PosB.x.ToFloat(),PosB.y.ToFloat()
					);
//				for ( int idx = 0; idx < bbVertASize>>1; idx++ ) {
//					_Log("(%.02f,%.02f) ", bbVertA[(idx<<1)+0],bbVertA[(idx<<1)+1]);
//				}
//				Log("");
//				for ( int idx = 0; idx < bbVertBSize>>1; idx++ ) {
//					_Log("(%.02f,%.02f) ", bbVertB[(idx<<1)+0],bbVertB[(idx<<1)+1]);
//				}
//				Log("");
//				LogFlush();
			}
		}
	}
	return Sensed;
}
// - ------------------------------------------------------------------------------------------ - //
}; // namespace QK //
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_QSENSORSPINEBB_H__ //
// - ------------------------------------------------------------------------------------------ - //
