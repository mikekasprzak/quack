// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include "qkInput.h"
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInputPadStubGetSimple( HSQUIRRELVM v ) {
	SQInteger Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(v);

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
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
