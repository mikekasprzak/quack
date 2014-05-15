// - ------------------------------------------------------------------------------------------ - //
// My own Signal, inspired by Boost and Loki signals, but not shit //
//
// Does not do: Slot Ordering, Scoped Connections
// Reference: http://www.boost.org/doc/libs/1_52_0/doc/html/signals/tutorial.html
// - ------------------------------------------------------------------------------------------ - //
// Usage:
//   Signal MySignal;
//   MySignal.Connect( MyFunc );
//   MySignal.Connect( MyFunc2, 200 );
//   MySignal.Connect( MyFunc3, 1 );
//   MySignal.Connect( MyFunc3, 2 );
//   void* Ret = MySignal( 25 );
//
// Pass 1 of 4 different function formattings for different usage.
//
// void MyFunc();
// void MyFunc2( void* UserPtr );
// void MyFunc3( void* UserPtr, void* ArgsPtr );
// void* MyFunc4( void* UserPtr, void* ArgsPtr, void* ReturnPtr );
//
// UserPtr - User data you decide to pass along (or not).
// ArgsPtr - Data passed to the Chain function upon execution of the chain.
// ReturnPtr - The returned value from the prior function in the chain.
// NOTE: MyFunc4 also returns a value.
// TIP: If using MyFunc4 syntax, if you don't change it, then you should return ReturnPtr.
//
// In addition to void*'s, you can also use any combination of size_t's instead of void*'s.
// NOTE: integers and floats must be converted to a size_t, an unsigned type.
//   size_t's are architecture dependent. 64bit on 64bit architectures, and 32bit on 32bit.
//
// void MyAltFunc2( size_t UserData );
// void MyAltFunc3( size_t UserData, size_t ArgsData );
// size_t MyAltFunc4( size_t UserData, size_t ArgsData, size_t ReturnData );
// void MyAltFunc3b( void* UserPtr, size_t ArgsData );
//
// Finally, you can actually use any pointer type in the place of void*'s, but only pointers.
//
// void MyAnyFunc2( MyType* UserPtr );
// void MyAnyFunc3( MyType* UserPtr, MyArgType* ArgsPtr );
// MyReturnType* MyAnyFunc4( MyType* UserPtr, MyArgType* ArgsPtr, MyReturnType* ReturnPtr );
//
// ProTip: You can pass class members if you have an appropriate static function in your class.
// Sample goes here;
//
// NEW: Can set additional flags, such as GelSignal::FF_BLOCKED_AFTER_CALL, on Connect().
// NEW: Can specify an intial input return value. MySignal(Arg,Ret);
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GELSIGNAL_H__
#define __GEL_LIB_GELSIGNAL_H__
// - ------------------------------------------------------------------------------------------ - //
//#include <Lib/GelDataArray/GelDataArray_Core.h>
#include <vector>
#include <algorithm>
// - ------------------------------------------------------------------------------------------ - //
class GelSignal {
public:
	// Arguments: User Ptr, Arguments Ptr, Return Ptr (also returns)  //
	typedef void  (*F0VoidPtr)();
	typedef void  (*F1VoidPtr)(void*);
	typedef void  (*F2VoidPtr)(void*,void*);
	typedef void* (*F3VoidPtr)(void*,void*,void*);
	
	enum /*FuncFlags*/ {
		FF_NULL						= 0,
		
		// Mode is number of arguments //
		FF_MODE_0					= 0,
		FF_MODE_1					= 1,
		FF_MODE_2					= 2,
		FF_MODE_3					= 3,
		FF_MODE_MASK				= 0xF,
		
		// Stops functions from being called //
		FF_BLOCKED					= 0x10,
		// Combined mask used for cleverness //
		FF_MODE_OR_BLOCKED_MASK		= FF_MODE_MASK | FF_BLOCKED,
		
		// If set, the function should set the blocked state //
		FF_BLOCKED_AFTER_CALL		= 0x20,
		
		// Stops calling functions attached to the signal if the value of Ret is non-zero/zero //
		FF_RETURN_IF_NON_ZERO		= 0x40,
		FF_RETURN_IF_ZERO			= 0x80,
	};
	
	struct FuncType {
		F3VoidPtr	Function;
		void*		UserPtr;
		int			Flags;
		// TODO: Slot Ordering, either as an order member (int) or in some unused flag space //
		
		inline FuncType() { }
		
		inline FuncType( F3VoidPtr _Function, void* _UserPtr, const int _Flags ) :
			Function( _Function ),
			UserPtr( _UserPtr ),
			Flags( _Flags )
		{
		}
		
		// For the erase function we need an == operator //
		inline bool operator == ( const FuncType& Vs ) const {
			return (Function == Vs.Function) && (UserPtr == Vs.UserPtr);
		}
		
		// Blocked - Function does not call //
		inline bool IsBlocked() const {
			return Flags & FF_BLOCKED;
		}
		inline void SetBlocked() {
			Flags |= FF_BLOCKED;
		}
		inline void ClearBlocked() {
			Flags &= ~FF_BLOCKED;
		}
		
		// Blocked After Call - After being called, set the Blocked state //
		inline bool IsBlockedAfterCall() const {
			return Flags & FF_BLOCKED_AFTER_CALL;
		}
		inline void SetBlockedAfterCall() {
			Flags |= FF_BLOCKED_AFTER_CALL;
		}
		inline void ClearBlockedAfterCall() {
			Flags &= ~FF_BLOCKED_AFTER_CALL;
		}

		// Return If Non Zero - If the return value becomes non-zero, stop calling signals //		
		inline bool IsReturnIfNonZero() const {
			return Flags & FF_RETURN_IF_NON_ZERO;
		}
		inline void SetReturnIfNonZero() {
			Flags |= FF_RETURN_IF_NON_ZERO;
		}
		inline void ClearReturnIfNonZero() {
			Flags &= ~FF_RETURN_IF_NON_ZERO;
		}

		// Return If Zero - If the return value becomes zero, stop calling signals //		
		inline bool IsReturnIfZero() const {
			return Flags & FF_RETURN_IF_ZERO;
		}
		inline void SetReturnIfZero() {
			Flags |= FF_RETURN_IF_ZERO;
		}
		inline void ClearReturnIfZero() {
			Flags &= ~FF_RETURN_IF_ZERO;
		}
	};
protected:
	std::vector<FuncType>	Funcs;
public:
	inline GelSignal() {
	}
	
	inline ~GelSignal() {
	}
	
	inline void Clear() {
		Funcs.clear();
	}
	
public:
	// Call the function chain //
	// NOTE: The Return is only ever changed by 3 argument functions! //
	inline void* operator () ( void* ArgsPtr, void* Ret = 0 ) {
		for ( size_t idx = 0; idx < Funcs.size(); idx++ ) {
//			Log("** Signal: %i (%i)", idx, Funcs->Size );
			FuncType* Func = &(Funcs[idx]);
			
			// Check the value of Ret, and act depending on certain flags //
			if ( Ret ) {
				if ( Func->IsReturnIfNonZero() )
					return Ret;
			}
			else {
				if ( Func->IsReturnIfZero() )
					return Ret;
			}				
			
			// NOTE: Cleverness! If the FF_BLOCKED flag is set, then only default will be //
			//   called, because the bitmask will be incorrect. //
			switch( Func->Flags & FF_MODE_OR_BLOCKED_MASK ) {
				case FF_MODE_0: {
					F0VoidPtr FunctionToCall = (F0VoidPtr)Func->Function;
					FunctionToCall();
					break;
				}
				case FF_MODE_1: {
					// Use only the User Pointer //
					F1VoidPtr FunctionToCall = (F1VoidPtr)Func->Function;
					FunctionToCall( Func->UserPtr );
					break;
				}
				case FF_MODE_2: {
					// Use the Arguments Poiter too //
					F2VoidPtr FunctionToCall = (F2VoidPtr)Func->Function;
					FunctionToCall( Func->UserPtr, ArgsPtr );
					break;
				}
				case FF_MODE_3: {
					// NOTE: The only variation that changes (and uses) Ret //
					F3VoidPtr FunctionToCall = (F3VoidPtr)Func->Function;
					Ret = FunctionToCall( Func->UserPtr, ArgsPtr, Ret );
					break;
				}
				default: {
					return Ret;
					break;
				}
			};
			// If the "Block me after a call" flag is set, set the blocking state //
			if ( Func->IsBlockedAfterCall() ) {
				Func->SetBlocked();
			}
		}
		return Ret;
	}
	// size_t version of calling //
	inline void* operator () ( const size_t Args = 0, void* const Ret = 0 ) {
		return operator()( (void*)Args, Ret );
	}
	
	// Zero Argument Functions //
	template<class T1>
	inline void Connect( void (*_Func)(void), T1* = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, 0, FF_MODE_0 | _Flags );
		Funcs.push_back( MyFunc );
	}
	inline void Connect( void (*_Func)(void), size_t = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, 0, FF_MODE_0 | _Flags );
		Funcs.push_back( MyFunc );
	}
	
	// One Argument Version (Pointer) //
	template<class T1>
	inline void Connect( void (*_Func)(T1*), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_1 | _Flags );
		Funcs.push_back( MyFunc );
	}
	// One Argument Version (size_t) //
	inline void Connect( void (*_Func)(size_t), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_1 | _Flags );
		Funcs.push_back( MyFunc );
	}

	// Two Argument Version (Pointer,Pointer) //
	template<class T1, class T2>
	inline void Connect( void (*_Func)(T1*,T2*), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 | _Flags );
		Funcs.push_back( MyFunc );
	}
	// Two Argument Version (size_t,size_t) //
	inline void Connect( void (*_Func)(size_t,size_t), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 | _Flags );
		Funcs.push_back( MyFunc );
	}
	// Two Argument Version (size_t,Pointer) //
	template<class T2>
	inline void Connect( void (*_Func)(size_t,T2*), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 | _Flags );
		Funcs.push_back( MyFunc );
	}
	// Two Argument Version (Pointer,size_t) //
	template<class T1>
	inline void Connect( void (*_Func)(T1*,size_t), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 | _Flags );
		Funcs.push_back( MyFunc );
	}

	// Three Argument Version (Pointer,Pointer,Pointer) //
	template<class T1, class T2, class T3>
	inline void Connect( T3* (*_Func)(T1*,T2*,T3*), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	template<class T1, class T2>
	inline void Connect( size_t (*_Func)(T1*,T2*,size_t), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	template<class T1, class T3>
	inline void Connect( T3* (*_Func)(T1*,size_t,T3*), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	template<class T1>
	inline void Connect( size_t (*_Func)(T1*,size_t,size_t), T1* UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	// Three Argument Version (size_t,size_t,size_t) //
	inline void Connect( size_t (*_Func)(size_t,size_t,size_t), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	template<class T2>
	inline void Connect( size_t (*_Func)(size_t,T2*,size_t), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	template<class T3>
	inline void Connect( T3* (*_Func)(size_t,size_t,T3*), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}
	template<class T2, class T3>
	inline void Connect( T3* (*_Func)(size_t,T2*,T3*), size_t UserData = 0, const int _Flags = FF_NULL ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 | _Flags );
		Funcs.push_back( MyFunc );
	}


	// Remove Functions //
	// TODO: this //
	inline void Disconnect( FuncType _Func ) {
		std::vector<FuncType>::reverse_iterator itr = std::find( Funcs.rbegin(), Funcs.rend(), _Func );
		if ( itr != Funcs.rend() ) {
			Funcs.erase( itr.base() );
		}
//		// findlast, to allow us to correctly nest a scoped connection //
//		int Index = findlast_GelDataArray<FuncType>( &Funcs, _Func );
//		if ( Index > 0 ) {
//			erase_GelDataArray<FuncType>( &Funcs, Index );
//		}
	}
	// TODO: all variations of the above //
	
	// TODO: Blocking //
	
	// TODO: Connections. i.e. a type returned by the Connect function that can be used to disconnect //
	// TODO: Scoped Connections. A variant of the connection type that knows to auto-disconnect in destructor. //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GELSIGNAL_H__ //
// - ------------------------------------------------------------------------------------------ - //
