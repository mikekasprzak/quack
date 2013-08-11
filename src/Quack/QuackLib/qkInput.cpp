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
SQInteger extGetPad( HSQUIRRELVM v ) {
#ifdef USES_WINDOWS
	int Index = 0;
	int NumArgs = sq_gettop(v);
	if ( NumArgs > 0 ) {
		sq_getinteger(v,2,&Index);
		if ( (Index > 3) || (Index < 0) ) {
			sq_newtable(v);	// Error //
			return 1;
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
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkInput_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(extGetPad,2,_SC(".i")),
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
