// - ------------------------------------------------------------------------------------------ - //
// My own barebones version of Signal, inspired by Boost and Loki signals, but not shit //
//
// Does not do: Slot Ordering, Arguments, Chaining Arguments/Returns, Blocking, Scoped Connections
// Reference: http://www.boost.org/doc/libs/1_52_0/doc/html/signals/tutorial.html
// - ------------------------------------------------------------------------------------------ - //
// Usage: 
//   Signal MySignal;					// Create a Signal //
//   MySignal.Connect( MyFunc );		// Attach a function //
//   MySignal.Connect( MyOtherFunc );	// Attach another function //
//   MySignal();						// Call all of the functions (in Linear/FIFO order) //
//   MySignal( (void*)256 );			// A void* is passed to all functions //
//
// void MyFunc( void* UserDataPtr ) {
//   // This is what a function typically looks like //
// }
//
// TODO: Investigate how to make this syntax work:
// void MyOtherFunc( size_t UserData ) {
//   // The point of this version is to use another type of the same width as a void*. //
//   // Another useful case would be to pass an int* or OtherType* instead of a void*. //
// }
//
// It may simply be a matter of doing (or not casting at all):
//   MySignal.Connect( (FVoidPtr)MyFunc );
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_SIGNAL_H__
#define __GEL_LIB_SIGNAL_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelArray_Core.h>
// - ------------------------------------------------------------------------------------------ - //
class Signal {
public:
	typedef void (*FVoidPtr)(void*);
	
	GelArray<FVoidPtr>* Funcs;

public:
	inline Signal() :
		Funcs( 0 ) 
	{
	}
	
	inline ~Signal() {
		if ( Funcs ) {
			delete_GelArray<FVoidPtr>( Funcs );
		}
	}
	
	inline void operator () ( void* UserDataPtr = 0 ) const {
		if ( Funcs ) {
			for ( size_t idx = 0; idx < Funcs->Size; idx++ ) {
				Funcs->Data[idx]( UserDataPtr );
			}
		}
	}
	
	inline void Connect( FVoidPtr _Func ) {
		pushback_GelArray<FVoidPtr>( &Funcs, _Func );
	}

	inline void Disconnect( FVoidPtr _Func ) {
		// findlast, to allow us to correctly nest a scoped connection //
		int Index = findlast_GelArray<FVoidPtr>( &Funcs, _Func );
		if ( Index > 0 ) {
			erase_GelArray<FVoidPtr>( &Funcs, Index );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_SIGNAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
