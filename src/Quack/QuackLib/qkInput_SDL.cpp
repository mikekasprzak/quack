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
	SQInteger Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( Index < (int)Gel::Input::SDLInput::DevicesConnected() ) {
			return SQ_ERROR;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);

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
	SQInteger Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( Index >= (int)Gel::Input::SDLInput::DevicesConnected() ) {
			return SQ_ERROR;
		}
	}
	
#ifndef USES_XINPUT
	if ( Gel::Input::SDLInput::Is360(Index) ) {
		// Do Nothing (MinGW XInput/SDL Compatibility Mode) //
		return SQ_ERROR;
	}
#endif // !USES_WINDOWS //

	// Create a new table to store the data we want to return (will be an empty table on error) //
	sq_newtable(v);
	
	// TODO: Add "Raw" member here, containing the return of qkInputPadSDLGet //

	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", true); // Not Optional //
	
	// Buttons //
	u32 ButtonMask = 0;

	if ( Gel::Input::SDLInput::IsPS4(Index) ) {		
		// Convert to ABXY order (was XABY, or SQ X O TRI) //
		if ( Gel::Input::SDLInput::GamePad[Index].Button & PS4_B1 ) {
			ButtonMask |= 0x1;
		}
		if ( Gel::Input::SDLInput::GamePad[Index].Button & PS4_B2 ) {
			ButtonMask |= 0x2;
		}
		if ( Gel::Input::SDLInput::GamePad[Index].Button & PS4_B3 ) {
			ButtonMask |= 0x4;
		}
		if ( Gel::Input::SDLInput::GamePad[Index].Button & PS4_B4 ) {
			ButtonMask |= 0x8;
		}
		
		// PS4 Driver has L2+R2 as buttons, in addition to as Analogs //
		if ( Gel::Input::SDLInput::GamePad[Index].Button & (PS4_L1 | PS4_L2) ) {
			ButtonMask |= 0x10;	// L1 //
		}
		if ( Gel::Input::SDLInput::GamePad[Index].Button & (PS4_R1 | PS4_R2) ) {
			ButtonMask |= 0x20;	// R1 //
		}

		if ( Gel::Input::SDLInput::GamePad[Index].Button & (PS4_OPTION | PS4_PS) ) {
			ButtonMask |= 0x40;	// Menu //
		}
		if ( Gel::Input::SDLInput::GamePad[Index].Button & (PS4_R3) ) {
			ButtonMask |= 0x80;	// Extra //
		}
	}
//	else if ( Gel::Input::SDLInput::Is360(Index) ) {
//		// TODO: Look at the SDL Axis 2 and 5, and convert to L2/R2 buttons
//	}
	else {
		ButtonMask = Gel::Input::SDLInput::GamePad[Index].Button;
	}
		
	sqslot_int(v,"Button", ButtonMask);

	// Sticks //
	Vector2D LStick;
	if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 0 )
		LStick.x = Gel::Input::SDLInput::GamePad[Index].Axis[0];
	if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 1 )
		LStick.y = -Gel::Input::SDLInput::GamePad[Index].Axis[1];

	// TODO: Convert to MagnitudeSquared() //
	if ( LStick.Magnitude() < Real(0.1f) ) {
		LStick = Gel::Input::SDLInput::GamePad[Index].DPad;
	}

	Vector2D RStick;
	if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 2 )
		RStick.x = Gel::Input::SDLInput::GamePad[Index].Axis[2];
	if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 3 )
		RStick.y = -Gel::Input::SDLInput::GamePad[Index].Axis[3];

	// LStick //
	sq_pushstring(v,"LStick",-1);
	sq_newtable(v);
	sqslot_float(v,"x", LStick.x.ToFloat());
	sqslot_float(v,"y", LStick.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	// RStick //			
	sq_pushstring(v,"RStick",-1);
	sq_newtable(v);
	sqslot_float(v,"x", RStick.x.ToFloat());
	sqslot_float(v,"y", RStick.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLProxyGetSimple( HSQUIRRELVM v ) {
	SQInteger Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		// Always Succeeds //
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);
	
	// No Gamepad Connected? KEYBOARD PROXY! //
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
	
	sq_pushstring(v,"LStick",-1);
	sq_newtable(v);
	sqslot_float(v,"x", LStick.x.ToFloat());
	sqslot_float(v,"y", LStick.y.ToFloat());
	sq_newslot(v,-3,SQFalse);

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

	sq_pushstring(v,"RStick",-1);
	sq_newtable(v);
	sqslot_float(v,"x", RStick.x.ToFloat());
	sqslot_float(v,"y", RStick.y.ToFloat());
	sq_newslot(v,-3,SQFalse);

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSDLGet( HSQUIRRELVM v ) {
	return SQ_VOID;
}
SQInteger qkInputPadSDLGetSimple( HSQUIRRELVM v ) {
	return SQ_VOID;
}
SQInteger qkInputPadSDLProxyGetSimple( HSQUIRRELVM v ) {
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
