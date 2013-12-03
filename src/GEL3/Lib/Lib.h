// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_LIB_H__
#define __GEL_LIB_LIB_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelTypes.h"			// u8, s16, f32 family of types. Constants like U32_MAX.
// - ------------------------------------------------------------------------------------------ - //
// Usage: GelTime MyTime = get_time_GelTime();
#include "GelTime/GelTime.h"	// get_s_GelTime(), get_ms_GelTime(), get_us_GelTime(), get_time_GelTime() //
// - ------------------------------------------------------------------------------------------ - //
#include "Log/Log.h"
// - ------------------------------------------------------------------------------------------ - //
#include "GelConstants.h"		// GEL_ALIGN_CENTER and other bits and masks //
#include "GelError.h"			// GelError type (size_t), with GEL_OK and GEL_ERROR constants //
// - ------------------------------------------------------------------------------------------ - //
// Usage: return_if( Error ); 	// Returns only if Error is true, else continues //
#include "return_if.h"			// return_if family of functions (return_if_void, return_if_value) //
// - ------------------------------------------------------------------------------------------ - //
// Usage: if ( Gt(10, 1,2,10) ) { ... } // Result will be false, since 1,2 and 10 are not greater than 10)
#include "EqLtGt.h"				// Eq, NEq, Lt, Lte, Gt, Gte. ARG1 must meet condition versus ONE argument
#include "AllEqLtGt.h"			// AllEq, AllNEq, AllLt, etc. ARG1 must meet condition veruss ALL arguments
// - ------------------------------------------------------------------------------------------ - //
// Usage: int Lowest = Min(2,15,-6,85); // Returns -6, which is the lowest number //
#include "MinMax.h"				// Min and Max functions that take up to 7 arguments (returning lowest/higest) //
// - ------------------------------------------------------------------------------------------ - //
// Usage: NSet2<int,float> MyType; // MyType.a is an int, MyType.b is a float. MyType[1] returns a void* (a float*)
#include "NSet.h"				// NSet1 to NSet5. Sets of N values, each with their own type //
// NOTE: Supports indexing operator [], which returns a void* to the specific elements. Cast it to your desired type.
// - ------------------------------------------------------------------------------------------ - //
// Usage: ABSet<int> MyType; 	// MyType.a and MyType.b are both int's //
#include "Set.h"				// ASet->ABCDESet, XSet->XYWHSet, RSet->RGBASet, BSet->BGRASet, USet->UVWSet, WSet->WHLSet //
// - ------------------------------------------------------------------------------------------ - //
#include "safe_sprintf.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "GelSignal.h"			// Type that stores and calls many functions //
#include "GelDeferred.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "GelPool/GelPool.h"	// For creating Asset, Texture, etc Pools. Load/Unload model. //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "GelUID.h"
#include "Flex.h"
#include "GelKeyStore.h"
// - ------------------------------------------------------------------------------------------ - //

#include "StreamReader/StreamReader.h"

// - ------------------------------------------------------------------------------------------ - //
#include "GelFileInfo/GelFileInfo.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_LIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
