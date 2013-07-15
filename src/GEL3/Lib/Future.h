// - ------------------------------------------------------------------------------------------ - //
// My version of Futures/Promises/Defereds. //
// - ------------------------------------------------------------------------------------------ - //
// http://twistedmatrix.com/documents/current/core/howto/defer-intro.html
// http://twistedmatrix.com/documents/current/core/howto/defer.html
// http://twistedmatrix.com/documents/current/core/howto/gendefer.html
// http://en.wikipedia.org/wiki/Future_%28programming%29
// http://bartoszmilewski.com/2009/03/03/broken-promises-c0x-futures/
// http://bartoszmilewski.com/2009/03/10/futures-done-right/
// http://en.cppreference.com/w/cpp/thread/future
// - ------------------------------------------------------------------------------------------ - //
// Question: What actually causes a deferred to go down a certain path?
// Q: If we're going down the success path, does a failure cause us to go down the Errback path?
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_FUTURE_H__
#define __GEL_LIB_FUTURE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <External/TinyThread/tinythread.h>
#include <Lib/GelArray/GelArray_Core.h>
// - ------------------------------------------------------------------------------------------ - //
template< class T >
class Future {
public:
	typedef T (*FuncPtr)(T);		// All functions return and recieve the same arguments, chained ?? //
protected:
	tthread::thread Thread;
	GelArray<FuncPtr>* Callback;
	GelArray<FuncPtr>* Errback;
	
	bool Called;
public:
	// Constructor //
	Future() :
		Called( false )
	{
	}
	// Destructor //
	~Future() {
		if ( Callback ) {
			delete_GelArray( Callback );
		}
		if ( Errback ) {
			delete_GelArray( Errback );
		}
	}
	
public:
	// Add a Callback function (Success) //
	void Then( FuncPtr ) {
		// Add it //
		
		// If we've already finished running, restart the thread here //
	}
	
	// Add an Errback function (Failure) //
	void OnError( FuncPtr ) {
		// Add it //
		
		// If we've already finished running, restart the thread here //
	}
	
	// On Both (Failure or Success, always do these actions) //
	void OnBoth( FuncPtr ) { // Always? //
		// Add it //
		
		// If we've already finished running, restart the thread here //
	}
	
public:
	// Static functions that return a Future already in the Succes/Failure state //
	// TODO: Figure out copy constructor implications of the Thread
	static Future Success( const T Args ) {
		Future ret;
		// Do stuff //	
		return ret;
	}
	static Future Failure( const T Args ) {
		Future ret;
		// Do stuff //	
		return ret;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_FUTURE_H__ //
// - ------------------------------------------------------------------------------------------ - //
