// - ------------------------------------------------------------------------------------------ - //
#include "Engine.h"
// - ------------------------------------------------------------------------------------------ - //
// Sense Function Includes //
//#include "blah"
// - ------------------------------------------------------------------------------------------ - //
using namespace QK;
// - ------------------------------------------------------------------------------------------ - //
bool QK::Sense_Sensor( QObj& ObA,QSensor& A, QObj& ObB,QSensor& B ) {	
	// If a collision was resolved, return true //
	if ( A.Type == QS_SPINE_BB ) {
		if ( B.Type == QS_SPINE_BB ) { return Sense_Sensor( ObA,*(QSensorSpineBB*)A.Data, ObB,*(QSensorSpineBB*)B.Data ); }
	}
	
	// QS_NULL type tests will fall through, so no need to check for them //
	return false;
}
// - ------------------------------------------------------------------------------------------ - //
