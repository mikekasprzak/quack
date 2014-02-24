// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_ENGINE_ENGINE_H__
#define __QUACK_ENGINE_ENGINE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
SQInteger register_qkEngine(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
#include "QEngine.h"
// - ------------------------------------------------------------------------------------------ - //
// Objects have only one body, but can multiple sensors. Bodies must be convex. //
#include "QBody.h"
#include "QBodyAABB.h"
#include "QBodySphere.h"
#include "QBodyCapsule.h"
// - ------------------------------------------------------------------------------------------ - //
#include "QObjDummy.h"
#include "QObjBoxy.h"
#include "QObjBoxyStatic.h"
#include "QObjBally.h"
#include "QObjCappy.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_ENGINE_ENGINE_H__ //
// - ------------------------------------------------------------------------------------------ - //
