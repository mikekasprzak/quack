// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
// Solve Function Includes //
//#include "blah"
// - ------------------------------------------------------------------------------------------ - //
using namespace QK;
// - ------------------------------------------------------------------------------------------ - //
bool QBody::Solve( QBody& Vs ) {
	QBody& A = *this;
	QBody& B = Vs;
	
	// If a collision was resolved, return true //
	if ( A.Type == QB_AABB ) {
		if ( B.Type == QB_AABB ) { return Solve_Body( *(QBodyAABB*)A.Data, *(QBodyAABB*)B.Data ); }
		else if ( B.Type == QB_SPHERE ) { return Solve_Body( *(QBodyAABB*)A.Data, *(QBodySphere*)B.Data ); }
		else if ( B.Type == QB_CAPSULE ) { return Solve_Body( *(QBodyAABB*)A.Data, *(QBodyCapsule*)B.Data ); }
	}
	else if ( A.Type == QB_SPHERE ) {
		if ( B.Type == QB_AABB ) { return Solve_Body( *(QBodyAABB*)B.Data, *(QBodySphere*)A.Data ); }
		else if ( B.Type == QB_SPHERE ) { return Solve_Body( *(QBodySphere*)A.Data, *(QBodySphere*)B.Data ); }
		else if ( B.Type == QB_CAPSULE ) { return Solve_Body( *(QBodySphere*)A.Data, *(QBodyCapsule*)B.Data ); }
	}
	else if ( A.Type == QB_CAPSULE ) {
		if ( B.Type == QB_AABB ) { return Solve_Body( *(QBodyAABB*)B.Data, *(QBodyCapsule*)A.Data );; }
		else if ( B.Type == QB_SPHERE ) { return Solve_Body( *(QBodySphere*)B.Data, *(QBodyCapsule*)A.Data ); }
		else if ( B.Type == QB_CAPSULE ) { return Solve_Body( *(QBodyCapsule*)A.Data, *(QBodyCapsule*)B.Data ); }
	}
	
	// QB_NULL type tests will fall through, so no need to check for them //
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
