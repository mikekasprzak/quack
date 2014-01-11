// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_QUACKLIB_QKINPUT_H__
#define __QUACK_QUACKLIB_QKINPUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadXInputGet( HSQUIRRELVM v );
SQInteger qkInputPadXInputGetSimple( HSQUIRRELVM v );
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLGet( HSQUIRRELVM v );
SQInteger qkInputPadSDLGetSimple( HSQUIRRELVM v );
SQInteger qkInputPadSDLProxyGetSimple( HSQUIRRELVM v );	// Keyboard (Simulated Pad) //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadStubGetSimple( HSQUIRRELVM v );
// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_QUACKLIB_QKINPUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
