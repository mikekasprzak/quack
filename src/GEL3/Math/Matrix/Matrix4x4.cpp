// - ------------------------------------------------------------------------------------------ - //
#include "Matrix4x4.h"
// - ------------------------------------------------------------------------------------------ - //
#define R1 Real(1)
#define R0 Real(0)
// - ------------------------------------------------------------------------------------------ - //
const Matrix4x4 Matrix4x4::Identity(
	R1, R0, R0, R0,
	R0, R1, R0, R0,
	R0, R0, R1, R0,
	R0, R0, R0, R1
	);
// - ------------------------------------------------------------------------------------------ - //
const Matrix4x4 Matrix4x4::Zero(
	R0, R0, R0, R0,
	R0, R0, R0, R0,
	R0, R0, R0, R0,
	R0, R0, R0, R0
	);
// - ------------------------------------------------------------------------------------------ - //
