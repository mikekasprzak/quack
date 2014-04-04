// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_QUACKLIB_QUACKLIB_H__
#define __QUACK_QUACKLIB_QUACKLIB_H__
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkSystem(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkFloat(HSQUIRRELVM v);
SQInteger register_qkVector(HSQUIRRELVM v);
SQInteger register_qkMatrix(HSQUIRRELVM v);
SQInteger register_qkRect2(HSQUIRRELVM v);
SQInteger register_qkRect3(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkScreen(HSQUIRRELVM v);
SQInteger register_qkTarget(HSQUIRRELVM v);
SQInteger register_qkBlending(HSQUIRRELVM v);
SQInteger register_qkDepth(HSQUIRRELVM v);
SQInteger register_qkShader(HSQUIRRELVM v);
SQInteger register_qkDraw(HSQUIRRELVM v);
SQInteger register_qkTexture(HSQUIRRELVM v);
SQInteger register_qkFont(HSQUIRRELVM v);
SQInteger register_qkAtlas(HSQUIRRELVM v);
SQInteger register_qkSkel(HSQUIRRELVM v);
SQInteger register_qkSkelAnimator(HSQUIRRELVM v);
SQInteger register_qkModel(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkInput(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkColor(HSQUIRRELVM v);
SQInteger register_qkGrid(HSQUIRRELVM v);
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_QUACKLIB_QUACKLIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
