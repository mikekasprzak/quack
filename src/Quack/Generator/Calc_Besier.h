// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEN_CALC_BESIER_H__
#define __GEN_CALC_BESIER_H__
// - ------------------------------------------------------------------------------------------ - //
// Besier Curves -- Alphas of 0 and 1 return the first and last point.
// - ------------------------------------------------------------------------------------------ - //
// http://en.wikipedia.org/wiki/Besier_curve
// - ------------------------------------------------------------------------------------------ - //
template<typename VT, typename FT> // VectorType (VT), FloatType (FT) //
inline VT Calc_Besier( const FT&, const VT& P1 ) {
	return P1;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename VT, typename FT> // VectorType (VT), FloatType (FT) //
inline VT Calc_Besier( const FT& Alpha, const VT& P1, const VT& P2 ) {
	return P1 + (P2-P1) * Alpha;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename VT, typename FT> // VectorType (VT), FloatType (FT) //
inline VT Calc_Besier( const FT& Alpha, const VT& P1, const VT& P2, const VT& P3 ) {
	VT Q1 = P1 + (P2-P1) * Alpha;
	VT Q2 = P2 + (P3-P2) * Alpha;
	return Q1 + (Q2-Q1) * Alpha;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename VT, typename FT> // VectorType (VT), FloatType (FT) //
inline VT Calc_Besier( const FT& Alpha, const VT& P1, const VT& P2, const VT& P3, const VT& P4 ) {
	VT Q1 = P1 + (P2-P1) * Alpha;
	VT Q2 = P2 + (P3-P2) * Alpha;
	VT Q3 = P3 + (P4-P3) * Alpha;
	VT R1 = Q1 + (Q2-Q1) * Alpha;
	VT R2 = Q2 + (Q3-Q2) * Alpha;
	return R1 + (R2-R1) * Alpha;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename VT, typename FT> // VectorType (VT), FloatType (FT) //
inline VT Calc_Besier( const FT& Alpha, const VT& P1, const VT& P2, const VT& P3, const VT& P4, const VT& P5 ) {
	VT Q1 = P1 + (P2-P1) * Alpha;
	VT Q2 = P2 + (P3-P2) * Alpha;
	VT Q3 = P3 + (P4-P3) * Alpha;
	VT Q4 = P4 + (P5-P4) * Alpha;
	VT R1 = Q1 + (Q2-Q1) * Alpha;
	VT R2 = Q2 + (Q3-Q2) * Alpha;
	VT R3 = Q3 + (Q4-Q3) * Alpha;
	VT S1 = R1 + (R2-R1) * Alpha;
	VT S2 = R2 + (R3-R2) * Alpha;
	return S1 + (S2-S1) * Alpha;;
}
// - ------------------------------------------------------------------------------------------ - //
template<typename VT, typename FT> // VectorType (VT), FloatType (FT) //
inline VT Calc_Besier( const FT& Alpha, const VT& P1, const VT& P2, const VT& P3, const VT& P4, const VT& P5, const VT& P6 ) {
	VT Q1 = P1 + (P2-P1) * Alpha;
	VT Q2 = P2 + (P3-P2) * Alpha;
	VT Q3 = P3 + (P4-P3) * Alpha;
	VT Q4 = P4 + (P5-P4) * Alpha;
	VT Q5 = P5 + (P6-P5) * Alpha;
	VT R1 = Q1 + (Q2-Q1) * Alpha;
	VT R2 = Q2 + (Q3-Q2) * Alpha;
	VT R3 = Q3 + (Q4-Q3) * Alpha;
	VT R4 = Q4 + (Q5-Q4) * Alpha;
	VT S1 = R1 + (R2-R1) * Alpha;
	VT S2 = R2 + (R3-R2) * Alpha;
	VT S3 = R3 + (R4-R3) * Alpha;
	VT T1 = S1 + (S2-S1) * Alpha;
	VT T2 = S2 + (S3-S2) * Alpha;
	return T1 + (T2-T1) * Alpha;;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEN_CALC_BESIER_H__ //
// - ------------------------------------------------------------------------------------------ - //
