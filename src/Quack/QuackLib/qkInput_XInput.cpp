// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_XINPUT
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include "qkInput.h"
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadXInputGet( HSQUIRRELVM v ) {
	int Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( (Index > 3) || (Index < 0) ) {
			sq_newtable(v);	// Error //
			return SQ_RETURN;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);
	
	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", Gel::Input::XInput::IsConnected(Index));
	sqslot_int(v,"Button", Gel::Input::XInput::GamePad[Index].Button);
	sqslot_float(v,"LTrigger", Gel::Input::XInput::GamePad[Index].LTrigger.ToFloat());
	sqslot_float(v,"RTrigger", Gel::Input::XInput::GamePad[Index].RTrigger.ToFloat());

	// LStick //			
	sq_pushstring(v,"LStick",-1);
	sq_newtable(v);
	sqslot_float(v,"x", Gel::Input::XInput::GamePad[Index].LStick.x.ToFloat());
	sqslot_float(v,"y", Gel::Input::XInput::GamePad[Index].LStick.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	// RStick //			
	sq_pushstring(v,"RStick",-1);
	sq_newtable(v);
	sqslot_float(v,"x", Gel::Input::XInput::GamePad[Index].RStick.x.ToFloat());
	sqslot_float(v,"y", Gel::Input::XInput::GamePad[Index].RStick.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	// DPad //			
	sq_pushstring(v,"DPad",-1);
	sq_newtable(v);
	sqslot_float(v,"x", Gel::Input::XInput::GamePad[Index].DPad.x.ToFloat());
	sqslot_float(v,"y", Gel::Input::XInput::GamePad[Index].DPad.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadXInputGetSimple( HSQUIRRELVM v ) {
	int Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( (Index > 3) || (Index < 0) ) {
			// TODO: Push an SQ Error
			return SQ_ERROR;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);

	// TODO: Add information that tells me where to go to get raw data (i.e. which XInput controller) //
	
	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", Gel::Input::XInput::IsConnected(Index));
	// ABXY //
	u32 ButtonMask = (Gel::Input::XInput::GamePad[Index].Button & 0xF000) >> 12;
	// Left Trigger (Merging Both Lefts) //
	if ( (Gel::Input::XInput::GamePad[Index].Button & 0x0100) || (Gel::Input::XInput::GamePad[Index].LTrigger.ToFloat() > 0.5f) ) {
		ButtonMask |= 0x10;
	}
	// Right Trigger (Merging Both Rights) //
	if ( (Gel::Input::XInput::GamePad[Index].Button & 0x0200) || (Gel::Input::XInput::GamePad[Index].RTrigger.ToFloat() > 0.5f) ) {
		ButtonMask |= 0x20;
	}
	// Start/Back //
	if ( Gel::Input::XInput::GamePad[Index].Button & 0x0030 ) {
		ButtonMask |= 0x40;
	}
	// Right Thumbstick Click //
	if ( Gel::Input::XInput::GamePad[Index].Button & 0x0080 ) {
		ButtonMask |= 0x80;
	}
	sqslot_int(v,"Button", ButtonMask);

	// LStick //			
	sq_pushstring(v,"LStick",-1);
	sq_newtable(v);
	
	Vector2D LStick = Gel::Input::XInput::GamePad[Index].LStick;
	// TODO: Convert to MagnitudeSquared() //
	if ( LStick.Magnitude() < Real(0.1f) ) {
		LStick = Gel::Input::XInput::GamePad[Index].DPad;
	}
	// TODO: Fit 0.95<->0.1 range to 1.0<->0.0 //
	// TODO: Convert to MagnitudeSquared() //
	// Clip Ranges above 1.0. I.e. DPad diagonals //
	if ( LStick.Magnitude() > Real(1.0f) ) {
		LStick.Normalize();
	}
	
	sqslot_float(v,"x", LStick.x.ToFloat());
	sqslot_float(v,"y", LStick.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	// RStick //			
	sq_pushstring(v,"RStick",-1);
	sq_newtable(v);
	
	Vector2D RStick = Gel::Input::XInput::GamePad[Index].RStick;
	// TODO: Fit 0.95<->0.1 range to 1.0<->0.0 //
	// TODO: Convert to MagnitudeSquared() //
	// Clip Ranges above 1.0 //
	if ( RStick.Magnitude() > Real(1.0f) ) {
		RStick.Normalize();
	}
		
	sqslot_float(v,"x", RStick.x.ToFloat());
	sqslot_float(v,"y", RStick.y.ToFloat());		
	sq_newslot(v,-3,SQFalse);

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_XINPUT //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadXInputGet( HSQUIRRELVM v ) {
	return SQ_VOID;
}
SQInteger qkInputPadXInputGetSimple( HSQUIRRELVM v ) {
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_XINPUT //
// - ------------------------------------------------------------------------------------------ - //
