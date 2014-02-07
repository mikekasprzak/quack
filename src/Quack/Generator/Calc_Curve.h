// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEN_CALC_CURVE_H__
#define __GEN_CALC_CURVE_H__
// - ------------------------------------------------------------------------------------------ - //
// Alphas of 0 and 1 return the first and last point.
// - ------------------------------------------------------------------------------------------ - //
// http://en.wikipedia.org/wiki/Besier_curve
// - ------------------------------------------------------------------------------------------ - //
template<typename T, typename T2>
inline T Calc_Curve( const T2& Alpha, const T& P1, const T& P2 ) {
	T B1 = P1;
	B1 += (P2-P1)*Alpha;
	return B1;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T, typename T2>
inline T Calc_Curve( const T2& Alpha, const T& P1, const T& P2, const T& P3 ) {
	T B1 = P1;
	T Q1 = (P2-P1)*Alpha;
	T Q2 = (P3-P2)*Alpha;
	B1 += (Q2-Q1)*Alpha;
	return B1;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T, typename T2>
inline T Calc_Curve( const T2& Alpha, const T& P1, const T& P2, const T& P3, const T& P4 ) {
	T B1 = P1;
	T Q1 = (P2-P1)*Alpha;
	T Q2 = (P3-P2)*Alpha;
	T Q3 = (P4-P3)*Alpha;
	T R1 = (Q2-Q1)*Alpha;
	T R2 = (Q3-Q2)*Alpha;
	B1 += (R2-R1)*Alpha;
	return B1;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename T, typename T2>
inline T Calc_Curve( const T2& Alpha, const T& P1, const T& P2, const T& P3, const T& P4, const T& P5 ) {
	T B1 = P1;
	T Q1 = (P2-P1)*Alpha;
	T Q2 = (P3-P2)*Alpha;
	T Q3 = (P4-P3)*Alpha;
	T Q4 = (P5-P4)*Alpha;
	T R1 = (Q2-Q1)*Alpha;
	T R2 = (Q3-Q2)*Alpha;
	T R3 = (Q4-Q3)*Alpha;
	T S1 = (R2-R1)*Alpha;
	T S2 = (R3-R2)*Alpha;
	B1 += (S2-S1)*Alpha;
	return B1;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename Type, typename Type2>
inline Type Calc_Curve( const Type2& Alpha, const Type& P1, const Type& P2, const Type& P3, const Type& P4, const Type& P5, const Type& P6 ) {
	Type B1 = P1;
	Type Q1 = (P2-P1)*Alpha;
	Type Q2 = (P3-P2)*Alpha;
	Type Q3 = (P4-P3)*Alpha;
	Type Q4 = (P5-P4)*Alpha;
	Type Q5 = (P6-P5)*Alpha;
	Type R1 = (Q2-Q1)*Alpha;
	Type R2 = (Q3-Q2)*Alpha;
	Type R3 = (Q4-Q3)*Alpha;
	Type R4 = (Q5-Q4)*Alpha;
	Type S1 = (R2-R1)*Alpha;
	Type S2 = (R3-R2)*Alpha;
	Type S3 = (R4-R3)*Alpha;
	Type T1 = (S2-S1)*Alpha;
	Type T2 = (S3-S2)*Alpha;
	B1 += (T2-T1)*Alpha;
	return B1;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEN_CALC_CURVE_H__ //
// - ------------------------------------------------------------------------------------------ - //
