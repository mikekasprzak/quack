// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_ENGINE_H__
#define __QUACK_ENGINE_ENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
SQInteger register_qkEngine(HSQUIRRELVM v);
SQInteger register_qkObject(HSQUIRRELVM v);
SQInteger register_qkCamera(HSQUIRRELVM v);
SQInteger register_qkContactInfo(HSQUIRRELVM v);
SQInteger register_qkSensorInfo(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
// Objects have only one body, but can multiple sensors. //
// Bodies must be convex. Bodies determine orientation (Flips are in Rendering). //
#include "QBody.h"
#include "QBodyAABB.h"
#include "QBodySphere.h"
#include "QBodyCapsule.h"
//#include "QBodyOBB.h"
// - ------------------------------------------------------------------------------------------ - //
// Sensors can be fancier shapes than bodies. For information gathering and notification. //
//#include "QSensorAABB.h"
//#include "QSensorSphere.h"
//#include "QSensorCapsule.h"
//#include "QSensorOBB.h"
//#include "QSensorPoly.h"
#include "QSensorSpineBB.h"
// - ------------------------------------------------------------------------------------------ - //
// Will eventually only need a few Object types, but for the sake of dev/debugging we have extras.
#include "QObjDummy.h"
#include "QObjBoxy.h"
#include "QObjBoxyStatic.h"
#include "QObjBally.h"
#include "QObjCappy.h"
#include "QObjCappyStatic.h"

#include "QObjBoxObj.h"
// - ------------------------------------------------------------------------------------------ - //
// Particle Systems //
#include "QEmitter.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_ENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
