// - ------------------------------------------------------------------------------------------ - //
// A Deferred/Future implementation by me //
// - ------------------------------------------------------------------------------------------ - //
// Typically used with threads, Deferreds lets you chain together a list of functions to call. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_DEFERRED_H__
#define __GEL_LIB_DEFERRED_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Signal.h"
// - ------------------------------------------------------------------------------------------ - //
class Deferred {
	Signal Callbacks;
	Signal Errbacks;
	
	void* Args;
	
	enum /* DeferredFlags */ {
		DF_NULL					= 0,
		
		// Which Path we called (Callback or Errback) //
		DF_MODE_CALLBACK 		= 1,
		DF_MODE_ERRBACK			= 2,
		DF_MODE_MASK			= 0xF,
		
		DF_CALLED				= 0x10,		// Has the callback been called? //       
		DF_FINISHED				= 0x20,     // Have we finished calling everything? //
	};
	
	int Flags;
public:
	inline Deferred() :
		Flags( DF_NULL )
	{
	}
	
	inline bool IsCalled() const {
		return Flags & DF_CALLED;
	}
	inline bool IsFinished() const {
		return Flags & DF_FINISHED;
	}
	inline bool IsCallback() const {
		return Flags & DF_MODE_CALLBACK;
	}
	inline bool IsErrback() const {
		return Flags & DF_MODE_ERRBACK;
	}
	
public:
	template<class T2>
	inline void* Callback( T2* ArgsPtr = 0 ) {
		Flags |= DF_CALLED | DF_MODE_CALLBACK;
		Args = (void*)ArgsPtr;
		void* Ret = Callbacks( ArgsPtr );
		Flags |= DF_FINISHED;
		return Ret;
	}
	inline void* Callback( size_t ArgsData = 0 ) {
		return Callback( (void*)ArgsData );
	}

	template<class T2>
	inline void* Errback( T2* ArgsPtr ) {
		Flags |= DF_CALLED | DF_MODE_ERRBACK;
		Args = (void*)ArgsPtr;
		void* Ret = Errbacks( ArgsPtr );
		Flags |= DF_FINISHED;
		return Ret;
	}
	inline void* Errback( size_t ArgsData = 0 ) {
		return Errback( (void*)ArgsData );
	}
	
	#define _T1 class T1
	#define _T2 class T2
	#define _T3 class T3

	#define DEFERRED_FUNC_T( __name, __istype, __usertype, __func, ... ) \
		template< __VA_ARGS__ > \
		inline void __name( __func, __usertype UserPtr = 0 ) { \
			__istype ## backs.Connect( _Func, UserPtr, Signal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() && Is ## __istype ## back() ) { \
				__istype ## backs( Args ); \
			} \
		}
	#define DEFERRED_FUNC_s( __name, __istype, __usertype, __func ) \
		inline void __name( __func, __usertype UserPtr = 0 ) { \
			__istype ## backs.Connect( _Func, UserPtr, Signal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() && Is ## __istype ## back() ) { \
				__istype ## backs( Args ); \
			} \
		}

		
	#define DEFERRED_BOTH_FUNC_T( __name, __usertype, __func, ... ) \
		template< __VA_ARGS__ > \
		inline void __name( __func, __usertype UserPtr = 0 ) { \
			Callbacks.Connect( _Func, UserPtr, Signal::FF_BLOCKED_AFTER_CALL ); \
			Errbacks.Connect( _Func, UserPtr, Signal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() ) { \
				if ( IsCallback() ) { \
					Callbacks( Args ); \
				} \
				else { \
					Errbacks( Args ); \
				} \
			} \
		}
	#define DEFERRED_BOTH_FUNC_s( __name, __usertype, __func ) \
		inline void __name( __func, __usertype UserPtr = 0 ) { \
			Callbacks.Connect( _Func, UserPtr, Signal::FF_BLOCKED_AFTER_CALL ); \
			Errbacks.Connect( _Func, UserPtr, Signal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() ) { \
				if ( IsCallback() ) { \
					Callbacks( Args ); \
				} \
				else { \
					Errbacks( Args ); \
				} \
			} \
		}

	DEFERRED_FUNC_T( Then, Call, T1*,    void   (*_Func)(void), _T1 );
	DEFERRED_FUNC_T( Then, Call, T1*,    void   (*_Func)(T1*), _T1 );
	DEFERRED_FUNC_T( Then, Call, T1*,    void   (*_Func)(T1*,T2*), _T1, _T2 );
	DEFERRED_FUNC_T( Then, Call, T1*,    T3*    (*_Func)(T1*,T2*,T3*), _T1, _T2, _T3 );
	DEFERRED_FUNC_T( Then, Call, T1*,    void   (*_Func)(T1*,size_t), _T1 );
	DEFERRED_FUNC_T( Then, Call, T1*,    T3*    (*_Func)(T1*,size_t,T3*), _T1, _T3 );
	DEFERRED_FUNC_T( Then, Call, T1*,    size_t (*_Func)(T1*,T2*,size_t), _T1, _T2 );
	DEFERRED_FUNC_s( Then, Call, size_t, void   (*_Func)(void) );
	DEFERRED_FUNC_s( Then, Call, size_t, void   (*_Func)(size_t) );
	DEFERRED_FUNC_T( Then, Call, size_t, void   (*_Func)(size_t,T2*), _T2 );
	DEFERRED_FUNC_T( Then, Call, size_t, T3*    (*_Func)(size_t,T2*,T3*), _T2, _T3 );
	DEFERRED_FUNC_s( Then, Call, size_t, void   (*_Func)(size_t,size_t) );
	DEFERRED_FUNC_T( Then, Call, size_t, T3*    (*_Func)(size_t,size_t,T3*), _T3 );
	DEFERRED_FUNC_T( Then, Call, size_t, size_t (*_Func)(size_t,T2*,size_t), _T2 );

	DEFERRED_FUNC_T( OnError, Err, T1*,    void   (*_Func)(void), _T1 );
	DEFERRED_FUNC_T( OnError, Err, T1*,    void   (*_Func)(T1*), _T1 );
	DEFERRED_FUNC_T( OnError, Err, T1*,    void   (*_Func)(T1*,T2*), _T1, _T2 );
	DEFERRED_FUNC_T( OnError, Err, T1*,    T3*    (*_Func)(T1*,T2*,T3*), _T1, _T2, _T3 );
	DEFERRED_FUNC_T( OnError, Err, T1*,    void   (*_Func)(T1*,size_t), _T1 );
	DEFERRED_FUNC_T( OnError, Err, T1*,    T3*    (*_Func)(T1*,size_t,T3*), _T1, _T3 );
	DEFERRED_FUNC_T( OnError, Err, T1*,    size_t (*_Func)(T1*,T2*,size_t), _T1, _T2 );
	DEFERRED_FUNC_s( OnError, Err, size_t, void   (*_Func)(void) );
	DEFERRED_FUNC_s( OnError, Err, size_t, void   (*_Func)(size_t) );
	DEFERRED_FUNC_T( OnError, Err, size_t, void   (*_Func)(size_t,T2*), _T2 );
	DEFERRED_FUNC_T( OnError, Err, size_t, T3*    (*_Func)(size_t,T2*,T3*), _T2, _T3 );
	DEFERRED_FUNC_s( OnError, Err, size_t, void   (*_Func)(size_t,size_t) );
	DEFERRED_FUNC_T( OnError, Err, size_t, T3*    (*_Func)(size_t,size_t,T3*), _T3 );
	DEFERRED_FUNC_T( OnError, Err, size_t, size_t (*_Func)(size_t,T2*,size_t), _T2 );

	DEFERRED_BOTH_FUNC_T( Always, T1*,    void   (*_Func)(void), _T1 );
	DEFERRED_BOTH_FUNC_T( Always, T1*,    void   (*_Func)(T1*), _T1 );
	DEFERRED_BOTH_FUNC_T( Always, T1*,    void   (*_Func)(T1*,T2*), _T1, _T2 );
	DEFERRED_BOTH_FUNC_T( Always, T1*,    T3*    (*_Func)(T1*,T2*,T3*), _T1, _T2, _T3 );
	DEFERRED_BOTH_FUNC_T( Always, T1*,    void   (*_Func)(T1*,size_t), _T1 );
	DEFERRED_BOTH_FUNC_T( Always, T1*,    T3*    (*_Func)(T1*,size_t,T3*), _T1, _T3 );
	DEFERRED_BOTH_FUNC_T( Always, T1*,    size_t (*_Func)(T1*,T2*,size_t), _T1, _T2 );
	DEFERRED_BOTH_FUNC_s( Always, size_t, void   (*_Func)(void) );
	DEFERRED_BOTH_FUNC_s( Always, size_t, void   (*_Func)(size_t) );
	DEFERRED_BOTH_FUNC_T( Always, size_t, void   (*_Func)(size_t,T2*), _T2 );
	DEFERRED_BOTH_FUNC_T( Always, size_t, T3*    (*_Func)(size_t,T2*,T3*), _T2, _T3 );
	DEFERRED_BOTH_FUNC_s( Always, size_t, void   (*_Func)(size_t,size_t) );
	DEFERRED_BOTH_FUNC_T( Always, size_t, T3*    (*_Func)(size_t,size_t,T3*), _T3 );
	DEFERRED_BOTH_FUNC_T( Always, size_t, size_t (*_Func)(size_t,T2*,size_t), _T2 );

	#undef _T1
	#undef _T2
	#undef _T3

	#undef DEFERRED_BOTH_FUNC_T
	#undef DEFERRED_BOTH_FUNC_s
	#undef DEFERRED_FUNC_T
	#undef DEFERRED_FUNC_s
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_DEFERRED_H__ //
// - ------------------------------------------------------------------------------------------ - //
