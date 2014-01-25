// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include "qkInput.h"
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLGet( HSQUIRRELVM v ) {
	SQInteger Index = Gel::Input::SDLInput::IndexBase;
	int TrueIndex = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs >= 2 ) {
		sq_getinteger(v,2,&Index);
		TrueIndex = Index - Gel::Input::SDLInput::IndexBase;
		if ( TrueIndex < 0 )
			return SQ_ERROR;
		else if ( TrueIndex >= (int)Gel::Input::SDLInput::DevicesConnected() ) {//(int)Gel::Input::SDLInput::Size() ) {
			return SQ_ERROR;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);
	int TableIndex = sq_gettop(v);
	
	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", true); // Not Optional //
	
	// Buttons //
	u32 ButtonMask = Gel::Input::SDLInput::Pad[TrueIndex].Button;		
	sqslot_int(v,"Button", ButtonMask);

	// Sticks (NOT FLIPPED!) //
	Vector2D LStick;
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 0 )
		LStick.x = Gel::Input::SDLInput::Pad[TrueIndex].Axis[0];
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 1 )
		LStick.y = Gel::Input::SDLInput::Pad[TrueIndex].Axis[1];

	Vector2D DPad = Gel::Input::SDLInput::Pad[TrueIndex].DPad;

	Vector2D RStick;
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 3 )
		RStick.x = Gel::Input::SDLInput::Pad[TrueIndex].Axis[3];
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 4 )
		RStick.y = Gel::Input::SDLInput::Pad[TrueIndex].Axis[4];

	// Analogs //
	Real Analog[2];
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 2 )
		Analog[0] = Gel::Input::SDLInput::Pad[TrueIndex].Axis[2];
	else
		Analog[0] = Real::Zero;

	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 5 )
		Analog[1] = Gel::Input::SDLInput::Pad[TrueIndex].Axis[5];
	else
		Analog[1] = Real::Zero;

	sqslot_float(v,"LAnalog",Analog[0].ToFloat());
	sqslot_float(v,"RAnalog",Analog[1].ToFloat());

	// LStick //
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"LStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = LStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	// RStick //			
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"RStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = RStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	// DPad //
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"DPad",-1);			// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = DPad;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
enum {
	XINPUT_B1 = 0x1,
	XINPUT_B2 = 0x2,
	XINPUT_B3 = 0x4,
	XINPUT_B4 = 0x8,
	
	// Face Buttons //
	PS4_B1 = 0x2,
	PS4_B2 = 0x4,
	PS4_B3 = 0x1,
	PS4_B4 = 0x8,
	// Triggers //
	PS4_L1 = 0x10,
	PS4_R1 = 0x20,
	PS4_L2 = 0x40,
	PS4_R2 = 0x80,
	// Stick Click //
	PS4_L3 = 0x400,
	PS4_R3 = 0x800,
	// More Buttons //
	PS4_OPTION =	0x400,
	PS4_SHARE =		0x800,
	PS4_PS = 		0x1000,
	PS4_MOUSE = 	0x2000,
};
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLGetSimple( HSQUIRRELVM v ) {
	SQInteger Index = Gel::Input::SDLInput::IndexBase;
	int TrueIndex = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs >= 2 ) {
		sq_getinteger(v,2,&Index);
		TrueIndex = Index - Gel::Input::SDLInput::IndexBase;
		if ( TrueIndex < 0 )
			return SQ_ERROR;
		else if ( TrueIndex >= (int)Gel::Input::SDLInput::DevicesConnected() ) {
			return SQ_ERROR;
		}
	}
	
#ifndef USES_XINPUT
	if ( Gel::Input::SDLInput::Is360(TrueIndex) ) {
		// Do Nothing (MinGW XInput/SDL Compatibility Mode) //
		return SQ_ERROR;
	}
#endif // !USES_WINDOWS //

	// Create a new table to store the data we want to return (will be an empty table on error) //
	sq_newtable(v);
	int TableIndex = sq_gettop(v);
	
	// Add "Raw" member //
	{
		sq_pushstring(v,"Raw",-1);			// +1 //
		qkInputPadSDLGet(v);				// +1 //
		sq_newslot(v,TableIndex,SQFalse);	// -2 //
	}

	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", true); // Not Optional //
	
	// Buttons //
	u32 ButtonMask = 0;

	if ( Gel::Input::SDLInput::IsPS4(TrueIndex) ) {		
		// Convert to ABXY order (was XABY, or SQ X O TRI) //
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & PS4_B1 ) {
			ButtonMask |= 0x1;
		}
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & PS4_B2 ) {
			ButtonMask |= 0x2;
		}
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & PS4_B3 ) {
			ButtonMask |= 0x4;
		}
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & PS4_B4 ) {
			ButtonMask |= 0x8;
		}
		
		// PS4 Driver has L2+R2 as buttons, in addition to as Analogs //
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & (PS4_L1 | PS4_L2) ) {
			ButtonMask |= 0x10;	// L1 //
		}
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & (PS4_R1 | PS4_R2) ) {
			ButtonMask |= 0x20;	// R1 //
		}

		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & (PS4_OPTION | PS4_PS) ) {
			ButtonMask |= 0x40;	// Menu //
		}
		if ( Gel::Input::SDLInput::Pad[TrueIndex].Button & (PS4_R3) ) {
			ButtonMask |= 0x80;	// Extra //
		}
	}
//	else if ( Gel::Input::SDLInput::Is360(TrueIndex) ) {
//		// TODO: Look at the SDL Axis 2 and 5, and convert to L2/R2 buttons
//	}
	else {
		ButtonMask = Gel::Input::SDLInput::Pad[TrueIndex].Button;
	}
		
	sqslot_int(v,"Button", ButtonMask);

	// Sticks //
	Vector2D LStick;
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 0 )
		LStick.x = Gel::Input::SDLInput::Pad[TrueIndex].Axis[0];
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 1 )
		LStick.y = -Gel::Input::SDLInput::Pad[TrueIndex].Axis[1];

	// TODO: Convert to MagnitudeSquared() //
	if ( LStick.Magnitude() < Real(0.1f) ) {
		LStick = Gel::Input::SDLInput::Pad[TrueIndex].DPad;
	}

	Vector2D RStick;
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 3 )
		RStick.x = Gel::Input::SDLInput::Pad[TrueIndex].Axis[3];
	if ( Gel::Input::SDLInput::Pad[TrueIndex].NumAxis > 4 )
		RStick.y = -Gel::Input::SDLInput::Pad[TrueIndex].Axis[4];

	// LStick //
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"LStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = LStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	// RStick //			
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"RStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = RStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLProxyGetSimple( HSQUIRRELVM v ) {
	SQInteger Index = Gel::Input::SDLInput::ProxyIndexBase;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( Index != Gel::Input::SDLInput::ProxyIndexBase )
			return SQ_ERROR;
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);
	
	// No Pad Connected? KEYBOARD PROXY! //
	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", true);
	
	// Buttons //
	sqslot_int(v,"Button", Gel::KeyFakeButtons);

	// LStick //
	Vector2D LStick;
	if ( Gel::KeyFakeLStick & Gel::KEY_UP )
		LStick.y = Real::One;
	else if ( Gel::KeyFakeLStick & Gel::KEY_DOWN )
		LStick.y = -Real::One;
			
	if ( Gel::KeyFakeLStick & Gel::KEY_LEFT )
		LStick.x = -Real::One;
	else if ( Gel::KeyFakeLStick & Gel::KEY_RIGHT )
		LStick.x = Real::One;
	
	// RStick //			
	Vector2D RStick;
	if ( Gel::KeyFakeRStick & Gel::KEY_UP )
		RStick.y = Real::One;
	else if ( Gel::KeyFakeRStick & Gel::KEY_DOWN )
		RStick.y = -Real::One;
			
	if ( Gel::KeyFakeRStick & Gel::KEY_LEFT )
		RStick.x = -Real::One;
	else if ( Gel::KeyFakeRStick & Gel::KEY_RIGHT )
		RStick.x = Real::One;

	// LStick //
	{
		int TableIndex = sq_gettop(v);

		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"LStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = LStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	// RStick //			
	{
		int TableIndex = sq_gettop(v);

		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"RStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = RStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLPulse( HSQUIRRELVM v ) {
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLVibrate( HSQUIRRELVM v ) {
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLGet( HSQUIRRELVM v ) {
	return SQ_ERROR;
}
SQInteger qkInputPadSDLGetSimple( HSQUIRRELVM v ) {
	return SQ_ERROR;
}
SQInteger qkInputPadSDLProxyGetSimple( HSQUIRRELVM v ) {
	return SQ_ERROR;
}
SQInteger qkInputPadSDLPulse( HSQUIRRELVM v ) {
	return SQ_ERROR;	
}
SQInteger qkInputPadSDLVibrate( HSQUIRRELVM v ) {
	return SQ_ERROR;	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
