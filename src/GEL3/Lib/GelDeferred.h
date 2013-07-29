// - ------------------------------------------------------------------------------------------ - //
// A Deferred/Future implementation by me //
// - ------------------------------------------------------------------------------------------ - //
// Typically used with threads, Deferreds lets you chain together a list of functions to call. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GELDEFERRED_H__
#define __GEL_LIB_GELDEFERRED_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelSignal.h"
// - ------------------------------------------------------------------------------------------ - //
class GelDeferred {
	GelSignal Callbacks;
	GelSignal Errbacks;
	
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
	inline GelDeferred() :
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
	template<class TC2>
	inline void* Callback( TC2* ArgsPtr = 0 ) {
		Flags |= DF_CALLED | DF_MODE_CALLBACK;
		Args = (void*)ArgsPtr;
		void* Ret = Callbacks( ArgsPtr );
		Flags |= DF_FINISHED;
		return Ret;
	}
	inline void* Callback( size_t ArgsData = 0 ) {
		return Callback( (void*)ArgsData );
	}

	template<class TC2>
	inline void* Errback( TC2* ArgsPtr ) {
		Flags |= DF_CALLED | DF_MODE_ERRBACK;
		Args = (void*)ArgsPtr;
		void* Ret = Errbacks( ArgsPtr );
		Flags |= DF_FINISHED;
		return Ret;
	}
	inline void* Errback( size_t ArgsData = 0 ) {
		return Errback( (void*)ArgsData );
	}
	
	#define _TC1 class TC1
	#define _TC2 class TC2
	#define _TC3 class TC3

	#define DEFERRED_FUNC_T( ___name, ___istype, ___usertype, ___func, ... ) \
		template< __VA_ARGS__ > \
		inline void ___name( ___func, ___usertype UserPtr = 0 ) { \
			___istype ## backs.Connect( _Func, UserPtr, GelSignal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() && Is ## ___istype ## back() ) { \
				___istype ## backs( Args ); \
			} \
		}
	#define DEFERRED_FUNC_s( ___name, ___istype, ___usertype, ___func ) \
		inline void ___name( ___func, ___usertype UserPtr = 0 ) { \
			___istype ## backs.Connect( _Func, UserPtr, GelSignal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() && Is ## ___istype ## back() ) { \
				___istype ## backs( Args ); \
			} \
		}

		
	#define DEFERRED_BOTH_FUNC_T( ___name, ___usertype, ___func, ... ) \
		template< __VA_ARGS__ > \
		inline void ___name( ___func, ___usertype UserPtr = 0 ) { \
			Callbacks.Connect( _Func, UserPtr, GelSignal::FF_BLOCKED_AFTER_CALL ); \
			Errbacks.Connect( _Func, UserPtr, GelSignal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() ) { \
				if ( IsCallback() ) { \
					Callbacks( Args ); \
				} \
				else { \
					Errbacks( Args ); \
				} \
			} \
		}
	#define DEFERRED_BOTH_FUNC_s( ___name, ___usertype, ___func ) \
		inline void ___name( ___func, ___usertype UserPtr = 0 ) { \
			Callbacks.Connect( _Func, UserPtr, GelSignal::FF_BLOCKED_AFTER_CALL ); \
			Errbacks.Connect( _Func, UserPtr, GelSignal::FF_BLOCKED_AFTER_CALL ); \
			if ( IsFinished() ) { \
				if ( IsCallback() ) { \
					Callbacks( Args ); \
				} \
				else { \
					Errbacks( Args ); \
				} \
			} \
		}

	DEFERRED_FUNC_T( Then, Call, TC1*,    void   (*_Func)(void), _TC1 )
	DEFERRED_FUNC_T( Then, Call, TC1*,    void   (*_Func)(TC1*), _TC1 )
	DEFERRED_FUNC_T( Then, Call, TC1*,    void   (*_Func)(TC1*,TC2*), _TC1, _TC2 )
	DEFERRED_FUNC_T( Then, Call, TC1*,    TC3*    (*_Func)(TC1*,TC2*,TC3*), _TC1, _TC2, _TC3 )
	DEFERRED_FUNC_T( Then, Call, TC1*,    void   (*_Func)(TC1*,size_t), _TC1 )
	DEFERRED_FUNC_T( Then, Call, TC1*,    TC3*    (*_Func)(TC1*,size_t,TC3*), _TC1, _TC3 )
	DEFERRED_FUNC_T( Then, Call, TC1*,    size_t (*_Func)(TC1*,TC2*,size_t), _TC1, _TC2 )
	DEFERRED_FUNC_s( Then, Call, size_t, void   (*_Func)(void) )
	DEFERRED_FUNC_s( Then, Call, size_t, void   (*_Func)(size_t) )
	DEFERRED_FUNC_T( Then, Call, size_t, void   (*_Func)(size_t,TC2*), _TC2 )
	DEFERRED_FUNC_T( Then, Call, size_t, TC3*    (*_Func)(size_t,TC2*,TC3*), _TC2, _TC3 )
	DEFERRED_FUNC_s( Then, Call, size_t, void   (*_Func)(size_t,size_t) )
	DEFERRED_FUNC_T( Then, Call, size_t, TC3*    (*_Func)(size_t,size_t,TC3*), _TC3 )
	DEFERRED_FUNC_T( Then, Call, size_t, size_t (*_Func)(size_t,TC2*,size_t), _TC2 )

	DEFERRED_FUNC_T( OnError, Err, TC1*,    void   (*_Func)(void), _TC1 )
	DEFERRED_FUNC_T( OnError, Err, TC1*,    void   (*_Func)(TC1*), _TC1 )
	DEFERRED_FUNC_T( OnError, Err, TC1*,    void   (*_Func)(TC1*,TC2*), _TC1, _TC2 )
	DEFERRED_FUNC_T( OnError, Err, TC1*,    TC3*    (*_Func)(TC1*,TC2*,TC3*), _TC1, _TC2, _TC3 )
	DEFERRED_FUNC_T( OnError, Err, TC1*,    void   (*_Func)(TC1*,size_t), _TC1 )
	DEFERRED_FUNC_T( OnError, Err, TC1*,    TC3*    (*_Func)(TC1*,size_t,TC3*), _TC1, _TC3 )
	DEFERRED_FUNC_T( OnError, Err, TC1*,    size_t (*_Func)(TC1*,TC2*,size_t), _TC1, _TC2 )
	DEFERRED_FUNC_s( OnError, Err, size_t, void   (*_Func)(void) )
	DEFERRED_FUNC_s( OnError, Err, size_t, void   (*_Func)(size_t) )
	DEFERRED_FUNC_T( OnError, Err, size_t, void   (*_Func)(size_t,TC2*), _TC2 )
	DEFERRED_FUNC_T( OnError, Err, size_t, TC3*    (*_Func)(size_t,TC2*,TC3*), _TC2, _TC3 )
	DEFERRED_FUNC_s( OnError, Err, size_t, void   (*_Func)(size_t,size_t) )
	DEFERRED_FUNC_T( OnError, Err, size_t, TC3*    (*_Func)(size_t,size_t,TC3*), _TC3 )
	DEFERRED_FUNC_T( OnError, Err, size_t, size_t (*_Func)(size_t,TC2*,size_t), _TC2 )

//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    void   (*_Func)(void), _TC1 )
//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    void   (*_Func)(TC1*), _TC1 )
//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    void   (*_Func)(TC1*,TC2*), _TC1, _TC2 )
//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    TC3*    (*_Func)(TC1*,TC2*,TC3*), _TC1, _TC2, _TC3 )
//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    void   (*_Func)(TC1*,size_t), _TC1 )
//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    TC3*    (*_Func)(TC1*,size_t,TC3*), _TC1, _TC3 )
//	DEFERRED_BOTH_FUNC_T( Always, TC1*,    size_t (*_Func)(TC1*,TC2*,size_t), _TC1, _TC2 )
//	DEFERRED_BOTH_FUNC_s( Always, size_t, void   (*_Func)(void) )
//	DEFERRED_BOTH_FUNC_s( Always, size_t, void   (*_Func)(size_t) )
//	DEFERRED_BOTH_FUNC_T( Always, size_t, void   (*_Func)(size_t,TC2*), _TC2 )
//	DEFERRED_BOTH_FUNC_T( Always, size_t, TC3*    (*_Func)(size_t,TC2*,TC3*), _TC2, _TC3 )
//	DEFERRED_BOTH_FUNC_s( Always, size_t, void   (*_Func)(size_t,size_t) )
//	DEFERRED_BOTH_FUNC_T( Always, size_t, TC3*    (*_Func)(size_t,size_t,TC3*), _TC3 )
//	DEFERRED_BOTH_FUNC_T( Always, size_t, size_t (*_Func)(size_t,TC2*,size_t), _TC2 )

	#undef _TC1
	#undef _TC2
	#undef _TC3

	#undef DEFERRED_BOTH_FUNC_T
	#undef DEFERRED_BOTH_FUNC_s
	#undef DEFERRED_FUNC_T
	#undef DEFERRED_FUNC_s
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GELDEFERRED_H__ //
// - ------------------------------------------------------------------------------------------ - //
