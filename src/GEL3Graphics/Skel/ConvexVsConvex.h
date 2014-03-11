// - ----------------------------------------------------------------------------------------- - //
#ifndef __GEL_CONVEXVSCONVEX_H__
#define __GEL_CONVEXVSCONVEX_H__
// - ----------------------------------------------------------------------------------------- - //
#include <Math/Math.h>
// - ----------------------------------------------------------------------------------------- - //
inline bool ConvexVsConvex( const float* _PolyA, int PolyASize, const float* _PolyB, int PolyBSize ) {
	const Vector2D* PolyA = (const Vector2D*)_PolyA;
	PolyASize <<= 1;
	const Vector2D* PolyB = (const Vector2D*)_PolyB;
	PolyBSize <<= 1;

	// For all Axis of PolyA //	
	for ( int idx = 1; idx < PolyASize; idx++ ) {
		Vector2D Axis = (PolyA[idx] - PolyA[idx-1]).Tangent();
		Axis.Normalize();

		Real AMin = dot( PolyA[0], Axis );
		Real AMax = AMin;
		for ( int a = 1; a < PolyASize; a++ ) {
			Real Val = dot( PolyA[a], Axis );
			if ( Val > AMax )
				AMax = Val;
			else if ( Val < AMin )
				AMin = Val;
		}

		Real BMin = dot( PolyB[0], Axis );
		Real BMax = BMin;
		for ( int b = 1; b < PolyBSize; b++ ) {
			Real Val = dot( PolyB[b], Axis );
			if ( Val > BMax )
				BMax = Val;
			else if ( Val < BMin )
				BMin = Val;
		}
		
		Real ALen = AMax - AMin;
		Real BLen = BMax - BMin;
		
		Real AxMin = AMin < BMin ? AMin : BMin;
		Real AxMax = AMax > BMax ? AMax : BMax;
		Real AxLen = AxMax - AxMin;
		
		if ( AxLen > ALen+BLen )
			return false;
	}

	// For all Axis of PolyB //
	for ( int idx = 1; idx < PolyBSize; idx++ ) {
		Vector2D Axis = (PolyB[idx] - PolyB[idx-1]).Tangent();
		Axis.Normalize();

		Real AMin = dot( PolyA[0], Axis );
		Real AMax = AMin;
		for ( int a = 1; a < PolyASize; a++ ) {
			Real Val = dot( PolyA[a], Axis );
			if ( Val > AMax )
				AMax = Val;
			else if ( Val < AMin )
				AMin = Val;
		}

		Real BMin = dot( PolyB[0], Axis );
		Real BMax = BMin;
		for ( int b = 1; b < PolyBSize; b++ ) {
			Real Val = dot( PolyB[b], Axis );
			if ( Val > BMax )
				BMax = Val;
			else if ( Val < BMin )
				BMin = Val;
		}
		
		Real ALen = AMax - AMin;
		Real BLen = BMax - BMin;
		
		Real AxMin = AMin < BMin ? AMin : BMin;
		Real AxMax = AMax > BMax ? AMax : BMax;
		Real AxLen = AxMax - AxMin;
		
		if ( AxLen > ALen+BLen )
			return false;
	}
	
	// No overlaps are greater than the sum of shapes per axis //
	return true;
}
// - ----------------------------------------------------------------------------------------- - //
#endif // __GEL_CONVEXVSCONVEX_H__ //
// - ----------------------------------------------------------------------------------------- - //
