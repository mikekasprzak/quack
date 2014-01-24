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
	SQInteger Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( Index < (int)Gel::Input::Steam::Size() ) {
			return SQ_ERROR;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);

	// TODO: Store Data //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamGetSimple( HSQUIRRELVM v ) {
	SQInteger Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( Index >= (int)Gel::Input::Steam::Size() ) {
			return SQ_ERROR;
		}
	}

	// Create a new table to store the data we want to return (will be an empty table on error) //
	sq_newtable(v);
	
	// TODO: Add "Raw" member here, containing the return of qkInputPadSteamGet //

	sqslot_int(v,"Index", Index);
	sqslot_bool(v,"Connected", Gel::Input::Steam::IsConnected(Index) );
	
	// Buttons //
	u32 ButtonMask = 0;
	ButtonMask = Gel::Input::Steam::SteamPad[Index].Button;		
	sqslot_int(v,"Button", ButtonMask);

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
		*Vec = Gel::Input::Steam::SteamPad[Index].LStick;

		*Vec *= Real(1.4); // Simple Only! //
		if ( Vec->Magnitude() < Real(0.14) )
			*Vec = Vector2D::Zero;

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
		*Vec = Gel::Input::Steam::SteamPad[Index].RStick;

		*Vec *= Real(1.4); // Simple Only! //
		if ( Vec->Magnitude() < Real(0.14) )
			*Vec = Vector2D::Zero;
		
		sq_newslot(v,TableIndex,SQFalse);	// -2 //
		sq_pop(v,2);						// -2 //	
	}

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
#else // USES_STEAM //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadSteamGet( HSQUIRRELVM v ) {
	return SQ_VOID;
}
SQInteger qkInputPadSteamGetSimple( HSQUIRRELVM v ) {
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STEAM //
// - ------------------------------------------------------------------------------------------ - //
