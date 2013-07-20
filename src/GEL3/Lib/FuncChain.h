// - ------------------------------------------------------------------------------------------ - //
// Get Funky with the FuncChain //
// - ------------------------------------------------------------------------------------------ - //
// Usage:
// ??
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
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_FUNCCHAIN_H__
#define __GEL_LIB_FUNCCHAIN_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelArray/GelArray_Core.h>
// - ------------------------------------------------------------------------------------------ - //
class FuncChain {
public:
	// Arguments: User Ptr, Arguments Ptr, Return Ptr (also returns)  //
	typedef void  (*F0VoidPtr)();
	typedef void  (*F1VoidPtr)(void*);
	typedef void  (*F2VoidPtr)(void*,void*);
	typedef void* (*F3VoidPtr)(void*,void*,void*);
	
	enum FuncFlags {
		FF_MODE_0		= 0,
		FF_MODE_1		= 1,
		FF_MODE_2		= 2,
		FF_MODE_3		= 3,
		
		FF_MODE_MASK	= 0xF,
	};
	
	struct FuncType {
		F3VoidPtr	Function;
		void*		UserPtr;
		FuncFlags	Flags;
		
		inline FuncType() { }
		
		inline FuncType( F3VoidPtr _Function, void* _UserPtr, FuncFlags _Flags ) :
			Function( _Function ),
			UserPtr( _UserPtr ),
			Flags( _Flags )
		{
		}
		
		// For the erase function we need an == operator //
		inline const bool operator == ( const FuncType& Vs ) const {
			return (Function == Vs.Function) && (UserPtr == Vs.UserPtr);
		}
	};
protected:
	GelArray<FuncType>*	Funcs;
public:
	inline FuncChain() :
		Funcs( 0 )
	{
	}
	
	inline ~FuncChain() {
		if ( Funcs ) {
			delete_GelArray<FuncType>( Funcs );
		}
	}
public:
	// Call the function chain //
	// NOTE: The Return is only ever changed by 3 argument functions! //
	inline void* operator () ( void* ArgsPtr ) const {
		void* Ret = 0;
		if ( Funcs ) {
			for ( size_t idx = 0; idx < Funcs->Size; idx++ ) {
				FuncType& Func = Funcs->Data[idx];
				switch( Func.Flags & FF_MODE_MASK ) {
					case FF_MODE_0: {
						F0VoidPtr FunctionToCall = (F0VoidPtr)Func.Function;
						FunctionToCall();
						break;
					}
					case FF_MODE_1: {
						// Use only the User Pointer //
						F1VoidPtr FunctionToCall = (F1VoidPtr)Func.Function;
						FunctionToCall( Func.UserPtr );
						break;
					}
					case FF_MODE_2: {
						// Use the Arguments Poiter too //
						F2VoidPtr FunctionToCall = (F2VoidPtr)Func.Function;
						FunctionToCall( Func.UserPtr, ArgsPtr );
						break;
					}
					case FF_MODE_3: {
						// NOTE: The only variation that changes (and uses) Ret //
						F3VoidPtr FunctionToCall = (F3VoidPtr)Func.Function;
						Ret = FunctionToCall( Func.UserPtr, ArgsPtr, Ret );
						break;
					}
				};
			}
		}
		return Ret;
	}
	// size_t version of calling //
	inline void* operator () ( const size_t Args ) const {
		return operator()( (void*)Args );
	}
	
	// Zero Argument Functions //
//	inline void Connect( void (*_Func)(void) ) {
//		FuncType MyFunc( (F3VoidPtr)_Func, 0, FF_MODE_0 );
//		pushback_GelArray<FuncType>( &Funcs, MyFunc );
//	}
	template<class T1>
	inline void Connect( void (*_Func)(void), T1* = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, 0, FF_MODE_0 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	inline void Connect( void (*_Func)(void), size_t = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, 0, FF_MODE_0 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	
	// One Argument Version (Pointer) //
	template<class T1>
	inline void Connect( void (*_Func)(T1*), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_1 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	// One Argument Version (size_t) //
	inline void Connect( void (*_Func)(size_t), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_1 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}

	// Two Argument Version (Pointer,Pointer) //
	template<class T1, class T2>
	inline void Connect( void (*_Func)(T1*,T2*), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	// Two Argument Version (size_t,size_t) //
	inline void Connect( void (*_Func)(size_t,size_t), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	// Two Argument Version (size_t,Pointer) //
	template<class T2>
	inline void Connect( void (*_Func)(size_t,T2*), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	// Two Argument Version (Pointer,size_t) //
	template<class T1>
	inline void Connect( void (*_Func)(T1*,size_t), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_2 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}

	// Three Argument Version (Pointer,Pointer,Pointer) //
	template<class T1, class T2, class T3>
	inline void Connect( T3* (*_Func)(T1*,T2*,T3*), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	template<class T1, class T2>
	inline void Connect( size_t (*_Func)(T1*,T2*,size_t), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	template<class T1, class T3>
	inline void Connect( T3* (*_Func)(T1*,size_t,T3*), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	template<class T1>
	inline void Connect( size_t (*_Func)(T1*,size_t,size_t), T1* UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	// Three Argument Version (size_t,size_t,size_t) //
	inline void Connect( size_t (*_Func)(size_t,size_t,size_t), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	template<class T2>
	inline void Connect( size_t (*_Func)(size_t,T2*,size_t), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	template<class T3>
	inline void Connect( T3* (*_Func)(size_t,size_t,T3*), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}
	template<class T2, class T3>
	inline void Connect( T3* (*_Func)(size_t,T2*,T3*), size_t UserData = 0 ) {
		FuncType MyFunc( (F3VoidPtr)_Func, (void*)UserData, FF_MODE_3 );
		pushback_GelArray<FuncType>( &Funcs, MyFunc );
	}


	// Remove Functions //
	inline void Disconnect( FuncType _Func ) {
		// findlast, to allow us to correctly nest a scoped connection //
		int Index = findlast_GelArray<FuncType>( &Funcs, _Func );
		if ( Index > 0 ) {
			erase_GelArray<FuncType>( &Funcs, Index );
		}
	}
	// TODO: all variations of the above //
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_FUNCCHAIN_H__
// - ------------------------------------------------------------------------------------------ - //
