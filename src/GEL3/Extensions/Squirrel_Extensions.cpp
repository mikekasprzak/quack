// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SQUIRREL
// - ------------------------------------------------------------------------------------------ - //
#include <stdarg.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
void sq_PrintFunc( HSQUIRRELVM v, const SQChar *s, ... ) {
	va_list arglist; 
	va_start(arglist, s); 
	vLogAlways(s,arglist);
	va_end(arglist); 
} 
// - ------------------------------------------------------------------------------------------ - //
void sq_ErrorFunc( HSQUIRRELVM v, const SQChar *s, ... ) {
	va_list arglist; 
	va_start(arglist, s); 
	vLogAlways(s,arglist);
	va_end(arglist); 
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void sq_setprintfunc_Log( HSQUIRRELVM vm ) {
	// Set the Functions for Printed output and Errors //
	sq_setprintfunc( vm, sq_PrintFunc, sq_ErrorFunc );
	// Use the above functions for Squirrel Error Printing //
	sqstd_seterrorhandlers(vm);
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SQUIRREL //
// - ------------------------------------------------------------------------------------------ - //
