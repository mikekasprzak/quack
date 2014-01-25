// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_STEAM
// - ------------------------------------------------------------------------------------------ - //
#include <System/System.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include "qkInput.h"
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamGet( HSQUIRRELVM v ) {
	if ( !Gel::IsSteamRunning )
		return SQ_ERROR;

	SQInteger Index = Gel::Input::Steam::IndexBase;
	int TrueIndex = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs >= 2 ) {
		sq_getinteger(v,2,&Index);
		TrueIndex = Index - Gel::Input::Steam::IndexBase;
		if ( TrueIndex < 0 )
			return SQ_ERROR;
		else if ( TrueIndex > (int)Gel::Input::Steam::Size() ) {
			return SQ_ERROR;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);
	int TableIndex = sq_gettop(v);

	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", Gel::Input::Steam::IsConnected(TrueIndex) );
	
	// Buttons //
	u32 ButtonMask = Gel::Input::Steam::Pad[TrueIndex].Button;		
	sqslot_int(v,"Button", ButtonMask);

	// LStick //
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"LStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = Gel::Input::Steam::Pad[TrueIndex].LStick;

		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 (class,roottable) //	
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
		*Vec = Gel::Input::Steam::Pad[TrueIndex].RStick;
		
		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamGetSimple( HSQUIRRELVM v ) {
	if ( !Gel::IsSteamRunning )
		return SQ_ERROR;
	
	SQInteger Index = Gel::Input::Steam::IndexBase;
	int TrueIndex = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs >= 2 ) {
		sq_getinteger(v,2,&Index);
		TrueIndex = Index - Gel::Input::Steam::IndexBase;
		if ( TrueIndex < 0 )
			return SQ_ERROR;
		else if ( TrueIndex > (int)Gel::Input::Steam::Size() ) {
			return SQ_ERROR;
		}
	}

	// Create a new table to store the data we want to return (will be an empty table on error) //
	sq_newtable(v);
	int TableIndex = sq_gettop(v);
	
	// Add "Raw" member //
	{
		sq_pushstring(v,"Raw",-1);			// +1 //
		qkInputPadSteamGet(v);				// +1 //
		sq_newslot(v,TableIndex,SQFalse);	// -2 //
	}

	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", Gel::Input::Steam::IsConnected(TrueIndex) );
	
	// Buttons //
	u32 ButtonMask = 0;
	ButtonMask = Gel::Input::Steam::Pad[TrueIndex].Button;		
	sqslot_int(v,"Button", ButtonMask);

	// LStick //
	{
		sq_pushroottable(v);				// +1 //
		sq_pushstring(v,"vec2",4);			// +1 //
		sq_get(v,-2);						// =0 (-1 then +1) //
		sq_pushstring(v,"LStick",-1);		// +1 //
		sq_createinstance(v,-2);			// +1 //

		Vector2D* Vec;
		sq_getinstanceup(v,-1,(void**)&Vec,0);
		*Vec = Gel::Input::Steam::Pad[TrueIndex].LStick;

		*Vec *= Real(1.4); // Simple Only! //
		if ( Vec->Magnitude() < Real(0.14) )
			*Vec = Vector2D::Zero;

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
		*Vec = Gel::Input::Steam::Pad[TrueIndex].RStick;

		*Vec *= Real(1.4); // Simple Only! //
		if ( Vec->Magnitude() < Real(0.14) )
			*Vec = Vector2D::Zero;
		
		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamPulse( HSQUIRRELVM v ) {
	if ( !Gel::IsSteamRunning )
		return SQ_ERROR;
	
	SQInteger Index = Gel::Input::Steam::IndexBase;
	int TrueIndex = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs >= 2 ) {
		sq_getinteger(v,2,&Index);
		TrueIndex = Index - Gel::Input::Steam::IndexBase;
		if ( TrueIndex < 0 )
			return SQ_ERROR;
		else if ( TrueIndex > (int)Gel::Input::Steam::Size() ) {
			return SQ_ERROR;
		}
	}

	SQInteger Motor = 0;
	if ( NumArgs >= 3 ) {
		sq_getinteger(v,3,&Motor);
		if ( Index > 1 ) {
			return SQ_ERROR;
		}
	}

	SQInteger Amount = 1000;
	if ( NumArgs >= 4 ) {
		sq_getinteger(v,4,&Amount);
	}

	Gel::Input::Steam::Pulse( TrueIndex, Motor, Amount );
	
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamVibrate( HSQUIRRELVM v ) {
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_STEAM //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamGet( HSQUIRRELVM v ) {
	return SQ_ERROR;
}
SQInteger qkInputPadSteamGetSimple( HSQUIRRELVM v ) {
	return SQ_ERROR;
}
SQInteger qkInputPadSteamPulse( HSQUIRRELVM v ) {
	return SQ_ERROR;	
}
SQInteger qkInputPadSteamVibrate( HSQUIRRELVM v ) {
	return SQ_ERROR;	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STEAM //
// - ------------------------------------------------------------------------------------------ - //
