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
#include <Lib/GelDataArray/GelDataArray_Core.h>
// - ------------------------------------------------------------------------------------------ - //
class Signal {
public:
	typedef void (*FVoidPtr)(void*);
protected:
	GelDataArray<FVoidPtr>* Funcs;
public:
	inline Signal() :
		Funcs( 0 ) 
	{
	}
	
	inline ~Signal() {
		if ( Funcs ) {
			delete_GelDataArray<FVoidPtr>( Funcs );
		}
	}
	
	// Pointer version of calling //
	inline void operator () ( void* UserDataPtr ) const {
		if ( Funcs ) {
			for ( size_t idx = 0; idx < Funcs->Size; idx++ ) {
				Funcs->Data[idx]( UserDataPtr );
			}
		}
	}
	// size_t version of calling //
	inline void operator () ( const size_t UserData = 0 ) const {
		operator()( (void*)UserData );
	}
		
	// Now supports any pointer type as the argument //
	template<class T>
	inline void Connect( void (*_Func)(T*) ) {
		pushback_GelDataArray<FVoidPtr>( &Funcs, (FVoidPtr)_Func );
	}
	// Alternatively, the size_t type is supported too since it's the same width as a pointer //
	inline void Connect( void (*_Func)(size_t) ) {
		pushback_GelDataArray<FVoidPtr>( &Funcs, (FVoidPtr)_Func );
	}

	// Detach //
	inline void Disconnect( FVoidPtr _Func ) {
		// findlast, to allow us to correctly nest a scoped connection //
		int Index = findlast_GelDataArray<FVoidPtr>( &Funcs, _Func );
		if ( Index > 0 ) {
			erase_GelDataArray<FVoidPtr>( &Funcs, Index );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_SIGNAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
