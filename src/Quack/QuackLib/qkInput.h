// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_QUACKLIB_QKINPUT_H__
#define __QUACK_QUACKLIB_QKINPUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadXInputGet( HSQUIRRELVM v );
SQInteger qkInputPadXInputGetSimple( HSQUIRRELVM v );
SQInteger qkInputPadXInputPulse( HSQUIRRELVM v );
SQInteger qkInputPadXInputVibrate( HSQUIRRELVM v );
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLGet( HSQUIRRELVM v );
SQInteger qkInputPadSDLGetSimple( HSQUIRRELVM v );
SQInteger qkInputPadSDLProxyGetSimple( HSQUIRRELVM v );	// Keyboard (Simulated Pad) //
SQInteger qkInputPadSDLPulse( HSQUIRRELVM v );
SQInteger qkInputPadSDLVibrate( HSQUIRRELVM v );
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamGet( HSQUIRRELVM v );
SQInteger qkInputPadSteamGetSimple( HSQUIRRELVM v );
SQInteger qkInputPadSteamPulse( HSQUIRRELVM v );
SQInteger qkInputPadSteamVibrate( HSQUIRRELVM v );
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadStubGetSimple( HSQUIRRELVM v );
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_QUACKLIB_QKINPUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
