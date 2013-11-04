// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger extGetXInputPad( HSQUIRRELVM v ) {
#ifdef USES_WINDOWS
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

	return SQ_RETURN;
#else // USES_WINDOWS //
	return SQ_VOID;
#endif // USES_WINDOWS //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Gets a Simplified GamePad //
// - Left and Right Sticks (D-Pad Merged in to Left Stick)
// - Four face buttons
// - One set of L+R triggers as buttons
// - One extra button (typically Stick Click)
SQInteger qkGetPad( HSQUIRRELVM v ) {
	// Check the Arguments for an Index. If none specified, assume GamePad 0. //
	int Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
	}
	
	// Create a new table to store the data we want to return (will be an empty table on error) //
	sq_newtable(v);

	// TODO: Some smart clever way of assigning Indexes to GamePads //
//	if ( GamePad(Index).Type == GP_XINPUT ) {
#ifdef USES_WINDOWS
	if ( (Index < (int)Gel::Input::XInput::Size()) && (Gel::Input::XInput::IsConnected(Index)) ) {
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
	}
	else
#endif // USES_WINDOWS //
//	else if ( GamePad(Index).Type == GP_SDL ) {
#ifdef USES_SDL2
	if ( Index < (int)Gel::Input::SDLInput::DevicesConnected() ) {
#ifndef USES_WINDOWS
		if ( Gel::Input::SDLInput::Is360(Index) ) {
			
		}
		else
#endif // !USES_WINDOWS //
		if ( Gel::Input::SDLInput::IsPS4(Index) ) {
			sqslot_int(v,"Index", Index);
			sqslot_bool(v,"Connected", true); // Not Optional //
			
			// Buttons //
			u32 ButtonMask = 0; //|= Gel::Input::SDLInput::GamePad[Index].Button;
			
			// Convert to ABXY order (was XABY, or SQ X O TRI) //
			if ( Gel::Input::SDLInput::GamePad[Index].Button & 0x2 ) {
				ButtonMask |= 0x1;
			}
			if ( Gel::Input::SDLInput::GamePad[Index].Button & 0x4 ) {
				ButtonMask |= 0x2;
			}
			if ( Gel::Input::SDLInput::GamePad[Index].Button & 0x1 ) {
				ButtonMask |= 0x4;
			}
			if ( Gel::Input::SDLInput::GamePad[Index].Button & 0x8 ) {
				ButtonMask |= 0x8;
			}
			
			// PS4 Driver has L2+R2 as buttons, in addition to as Analogs //
			if ( Gel::Input::SDLInput::GamePad[Index].Button & (0x10 | 0x40) ) {
				ButtonMask |= 0x10;	// L //
			}
			if ( Gel::Input::SDLInput::GamePad[Index].Button & (0x20 | 0x80) ) {
				ButtonMask |= 0x20;	// R //
			}

			if ( Gel::Input::SDLInput::GamePad[Index].Button & (0x200 | 0x1000) ) {
				ButtonMask |= 0x40;	// Menu //
			}
			if ( Gel::Input::SDLInput::GamePad[Index].Button & (0x800) ) {
				ButtonMask |= 0x80;	// Extra //
			}
			
			sqslot_int(v,"Button", ButtonMask);
	
			// LStick //			
			sq_pushstring(v,"LStick",-1);
			sq_newtable(v);

			Vector2D LStick( Gel::Input::SDLInput::GamePad[Index].Axis[0], -Gel::Input::SDLInput::GamePad[Index].Axis[1] );
			// TODO: Convert to MagnitudeSquared() //
			if ( LStick.Magnitude() < Real(0.1f) ) {
				LStick = Gel::Input::SDLInput::GamePad[Index].DPad;
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

			Vector2D RStick( Gel::Input::SDLInput::GamePad[Index].Axis[2], -Gel::Input::SDLInput::GamePad[Index].Axis[3] );
			// TODO: Fit 0.95<->0.1 range to 1.0<->0.0 //
			// TODO: Convert to MagnitudeSquared() //
			// Clip Ranges above 1.0 //
			if ( RStick.Magnitude() > Real(1.0f) ) {
				RStick.Normalize();
			}

			sqslot_float(v,"x", RStick.x.ToFloat());
			sqslot_float(v,"y", RStick.y.ToFloat());		
			sq_newslot(v,-3,SQFalse);			
		}
		else {
			// a Normal controller //
			sqslot_int(v,"Index", Index);
			sqslot_bool(v,"Connected", true); // Not Optional //
			
			// Buttons //
			sqslot_int(v,"Button", Gel::Input::SDLInput::GamePad[Index].Button);
	
			Vector2D LStick;
			if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 0 )
				LStick.x = Gel::Input::SDLInput::GamePad[Index].Axis[0];
			if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 1 )
				LStick.y = Gel::Input::SDLInput::GamePad[Index].Axis[1];

			Vector2D RStick;
			if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 2 )
				RStick.x = Gel::Input::SDLInput::GamePad[Index].Axis[2];
			if ( Gel::Input::SDLInput::GamePad[Index].NumAxis > 3 )
				RStick.y = Gel::Input::SDLInput::GamePad[Index].Axis[3];
	
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
		}
	}
//	else if ( true ) {
//		// NO GAMEPAD CONNECTED! //
//		// Keyboard Proxy? //	
//	}
	else
#endif // USES_SDL2 //
	{
		// Stub //
		sqslot_int(v,"Index", Index);
		sqslot_bool(v,"Connected", false);
		
		// Buttons //
		sqslot_int(v,"Button", 0);

		// LStick //			
		sq_pushstring(v,"LStick",-1);
		sq_newtable(v);
		sqslot_float(v,"x", 0.0f);
		sqslot_float(v,"y", 0.0f);		
		sq_newslot(v,-3,SQFalse);

		// RStick //			
		sq_pushstring(v,"RStick",-1);
		sq_newtable(v);
		sqslot_float(v,"x", 0.0f);
		sqslot_float(v,"y", 0.0f);		
		sq_newslot(v,-3,SQFalse);
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
	_DECL_FUNC(extGetXInputPad,2,_SC(".i")),
	_DECL_FUNC(qkGetPad,2,_SC(".i")),
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
