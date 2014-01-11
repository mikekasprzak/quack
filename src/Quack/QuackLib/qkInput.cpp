// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
//#include <System/System.h>
//#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include "qkInput.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Gets a Simplified GamePad //
// - Left and Right Sticks (D-Pad Merged in to Left Stick)
// - Four face buttons
// - One set of L+R triggers as buttons
// - One Menu button (Start or Option)
// - One Extra button (Select or RStick Click)
SQInteger qkInputPadGet( HSQUIRRELVM v ) {	
#ifdef USES_XINPUT
	if ( qkInputPadXInputGetSimple(v) != SQ_ERROR ) { /* Success */ }
	else
#endif // USES_XINPUT //
#ifdef USES_SDL2
	if ( qkInputPadSDLGetSimple(v) != SQ_ERROR ) { /* Success */ }
	else if ( qkInputPadSDLProxyGetSimple(v) != SQ_ERROR ) { /* Success (Never Fails) - Proxy Gamepad (Keyboard) */ }
	else
#endif // USES_SDL2 //
	{
		// Return a Stub Gamepad if none of the above succeeded //
		qkInputPadStubGetSimple(v);
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkInput_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qkInputPadXInputGet,2,_SC(".i")),
	_DECL_FUNC(qkInputPadXInputGetSimple,2,_SC(".i")),

	_DECL_FUNC(qkInputPadSDLGet,2,_SC(".i")),
	_DECL_FUNC(qkInputPadSDLGetSimple,2,_SC(".i")),
	_DECL_FUNC(qkInputPadSDLProxyGetSimple,2,_SC(".i")),

	_DECL_FUNC(qkInputPadStubGetSimple,2,_SC(".i")),

	_DECL_FUNC(qkInputPadGet,2,_SC(".i")),
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkInput(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* qklib_funcs = qkInput_funcs;
	while(qklib_funcs[i].name!=0) {
		sq_pushstring(v,qklib_funcs[i].name,-1);
		sq_newclosure(v,qklib_funcs[i].f,0);
		sq_setparamscheck(v,qklib_funcs[i].nparamscheck,qklib_funcs[i].typemask);
		sq_setnativeclosurename(v,-1,qklib_funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
