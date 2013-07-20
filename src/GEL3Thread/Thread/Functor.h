// - ------------------------------------------------------------------------------------------ - //
// My implementation of Functors. AKA: Asynchronous functions. Functions run on another thread. //
// The syntax is a compromise because I can't rely on C++11 Lambdas. //
// - ------------------------------------------------------------------------------------------ - //
// Usage:
//
// // Create a struct/class with a () operator //
// struct MyFunctor {
// 	 void operator()( ) {
//     // This will be called in a thread //
//   }
// };
//
// Functor<MyFunctor> Func; 		// Instance the Functor and Call it //
// Func.join();						// Wait for the Thread to finish //
//
// DFunctor<MyFunctor> Delayed;		// Instance the Functor but DO NOT CALL! //
// Delayed();						// Call/Start the Functor //
// Delayed.join();					// Wait for the Thread to finish //
//
// TODO: Make this support standard C functions. void Blah() { }
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_FUNCTOR_H__
#define __GEL_LIB_FUNCTOR_H__
// - ------------------------------------------------------------------------------------------ - //
#include <External/TinyThread/tinythread.h>
// - ------------------------------------------------------------------------------------------ - //
// Internal Functor Type used by Functor and DFunctor //
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
class _Functor: public Type {
protected:
	static void StaticFunction( _Functor* th ) {
		th->operator()( );
	}
public:
	typedef void (*FVoidPtr)(void*);
	
	inline _Functor* GetThis() {
		return this;
	}
	
	inline static FVoidPtr GetFunc() {
		return (FVoidPtr)&StaticFunction;
	}

public: // Threading Extensions. Need to manage the thread pointers yourself. //
	// These exist because the Move operator is not available. //
	inline tthread::thread* new_thread() {
		return new tthread::thread( GetFunc(), this );
	}
	
	inline void delete_thread( tthread::thread* Me ) const {
		delete Me;
	}
};
// - ------------------------------------------------------------------------------------------ - //
// A variation that has an internal Thread and starts automatically //
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
class Functor: public _Functor<Type> {
protected:
	tthread::thread Thread;
public:
	inline Functor() :
		Thread( _Functor<Type>::GetFunc(), this )
	{
	}
	
	inline tthread::thread& GetThread() {
		return Thread;
	}
	
	// Wait for Thread to finish //
	inline void join() {
		Thread.join();
	}
};
// - ------------------------------------------------------------------------------------------ - //
// A variation that doesn't start automatically //
// - ------------------------------------------------------------------------------------------ - //
template<class Type>
class DFunctor: public _Functor<Type> {
protected:
	tthread::thread* Thread;
public:
	inline DFunctor() :
		Thread( 0 )
	{
	}
	
	inline ~DFunctor() {
		if ( Thread ) {
			delete Thread;
			//delete_thread( Thread );	// TODO: Try this //
		}
	}

	inline void operator()( ) {
		// NOTE: Only the first call will work //
		if ( !Thread ) {
			Thread = new tthread::thread( _Functor<Type>::GetFunc(), this );
			//Thread = new_thread();	// TODO: Try this //
		}
	}
	
	inline tthread::thread* GetThread() {
		return Thread;
	}
	
	// Wait for Thread to finish //
	inline void join() {
		if ( Thread ) {
			Thread->join();
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_FUNCTOR_H__ //
// - ------------------------------------------------------------------------------------------ - //
