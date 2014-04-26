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

		self->_GetRect = (QSensor::QGetRectFunc)_GetRect;
	}
public:
	GelSkelAnimator*	Skel;
	int					Message;
	const char*			Name;

public:
	inline QSensorSpineBB()
	{
	}
	
	inline void Set( GelSkelAnimator* _Skel ) {
		Skel = _Skel;
	}

public:
	// NOTE: This function would be faster if we had Rect methods to directly add points to a Rect (not Rects) //
	static QRect _GetRect( thistype* self ) { return self->GetRect(); }
	inline QRect GetRect() {
		QRect Rect;

		int SlotIndex = 0;
		spSlot* Slot = 0;
		spBoundingBoxAttachment* Attachment = 0;
		// Find first BB Attachment //
		for ( ; SlotIndex < Skel->GetSlotCount(); SlotIndex++ ) {
			Slot = Skel->_GetSlot(SlotIndex);
			Attachment = Skel->GetBB(Slot);
			if ( Attachment )
				break;
		}
		
		if ( Attachment ) {
			float bbVert[16*2];		// NOTE: Max Verts 16! //
			Skel->_TransformBBVertices(Slot,Attachment,bbVert);

			// Set First Point //
			Rect = QRect(bbVert[(0<<1)+0],bbVert[(0<<1)+1],0,0);
			// Set Remaining Points //
			for ( int idx = 1; idx < (Attachment->verticesCount>>1); idx++ ) {
				Rect += QRect(bbVert[(idx<<1)+0],bbVert[(idx<<1)+1],0,0);
			}
			
			// Iterate through remaining slots, adding all points //
			for ( ++SlotIndex; SlotIndex < Skel->GetSlotCount(); SlotIndex++ ) {
				Slot = Skel->_GetSlot(SlotIndex);
				Attachment = Skel->GetBB(Slot);
				if ( Attachment ) {
					Skel->_TransformBBVertices(Slot,Attachment,bbVert);

					for ( int idx = 0; idx < (Attachment->verticesCount>>1); idx++ ) {
						Rect += QRect(bbVert[(idx<<1)+0],bbVert[(idx<<1)+1],0,0);
					}					
				}
			}
		}
		
		return Rect;
	}
};
// - ------------------------------------------------------------------------------------------ - //
//inline bool Sense_Sensor( const Vector2D& PosA, const GelSkelAnimator& SkelA, QSensorInfo& InfoA, const Vector2D& PosB, const GelSkelAnimator& SkelB, QSensorInfo& InfoB ) {
inline bool Sense_Sensor( QObj& ObA, QSensorSpineBB& SenA, QObj& ObB, QSensorSpineBB& SenB ) {
	bool Sensed = false;
	
	const char _HITBOX[] = {'H','I','T','-',0};
	const char _HURTBOX[] = {'H','U','R','T',0};
	const int& HITBOX = *((int*)_HITBOX);
	const int& HURTBOX = *((int*)_HURTBOX);
	
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
								
				// ** A ** //
				QSensorData DataA;
				DataA.Name = BBA->super.name;
				{
					int* NamePtr = (int*)DataA.Name;
					if ( *NamePtr == HITBOX ) {
						DataA.Message = QSI_HITBOX;
					}
					else if ( *NamePtr == HURTBOX ) {
						DataA.Message = QSI_HURTBOX;
					}
					else {
						// TODO: String to Number
						DataA.Message = 0;
					}
				}

				// ** B ** //
				QSensorData DataB;
				DataB.Name = BBB->super.name;
				{
					int* NamePtr = (int*)DataB.Name;
					if ( *NamePtr == HITBOX ) {
						DataB.Message = QSI_HITBOX;
					}
					else if ( *NamePtr == HURTBOX ) {
						DataB.Message = QSI_HURTBOX;
					}
					else {
						// TODO: String to Number
						DataB.Message = 0;
					}
				}

				QSensorInfo Info;

				Info.A = DataA;
				Info.B = DataB;
				ObA.Sense(ObB,Info);	// DANGER! May break following Call if Object Resized! //

				Info.A = DataB;
				Info.B = DataA;
				ObB.Sense(ObA,Info);
				
//				Log( "** [%x][%i] %s (%.01f,%.01f) vs [%x][%i] %s (%.01f,%.01f)...", 
//					SkelA.GetSkeleton(),IndexA,SkelA.GetName(IndexA),
//					PosA.x.ToFloat(),PosA.y.ToFloat(),
//					SkelB.GetSkeleton(),IndexB,SkelB.GetName(IndexB),
//					PosB.x.ToFloat(),PosB.y.ToFloat()
//					);

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
