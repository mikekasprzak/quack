// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_GCC
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_DR_MINGW
#include <DrMinGW/DrMinGW.h>
#endif // USES_DR_MINGW //
// - ------------------------------------------------------------------------------------------ - //
void gelLogCompilerDetails() {
	Log( "-=- Compiler Information -=-" );

	#ifdef USES_MINGW
	Log( "Using MinGW." );
	#endif // USES_MINGW //

	#ifdef USES_DR_MINGW
	Log( "Using DrMinGW: %s", (InitDrMinGW() ? "No" : "Yes") );
	#endif // USES_DR_MINGW //

	#ifdef _MSC_VER
	Log( "With MSVC Version: %i.%i (%i -- %i)", _MSC_VER / 100, _MSC_VER % 100, _MSC_VER, _MSC_FULL_VER );
	#else // _MSC_VER //
	#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
	// _STR -- The name of the macro as a string
	// _XSTR -- The value of a macro as a string
	#define _XSTR(s) _STR(s)
	#define _STR(s) #s
	#define GCC_VERSION_STRING (_XSTR(__GNUC__) "." _XSTR(__GNUC_MINOR__) "." _XSTR(__GNUC_PATCHLEVEL__))
	Log( "With GCC Version: %s (%i -- %s)", GCC_VERSION_STRING, GCC_VERSION, __VERSION__ );
	_Log( "With Settings: " );
	#ifdef __OPTIMIZE__
		_Log( _STR(__OPTIMIZE__) " " );
	#endif
	#ifdef __OPTIMIZE_SIZE__
		_Log( _STR(__OPTIMIZE_SIZE__) " " );
	#endif
	#ifdef __NO_INLINE__
		_Log( _STR(__NO_INLINE__) " " );
	#endif
	#ifdef __STDC__
		_Log( _STR(__STDC__) " " );
	#endif
	#ifdef __STDC_HOSTED__
		_Log( _STR(__STDC_HOSTED__) " " );
	#endif
	#ifdef __STDC_VERSION__
		_Log( _STR(__STDC_VERSION__) "=\"" _XSTR(__STDC_VERSION__) "\" " );
	#endif
	#ifdef __GNUG__
		_Log( _STR(__GNUG__) " " );
	#endif
	#ifdef __STRICT_ANSI__
		_Log( _STR(__STRICT_ANSI__) " " );
	#endif
	#ifdef __ELF__
		_Log( _STR(__ELF__) " " );
	#endif
	#ifdef __GNUC_GNU_INLINE__
		_Log( _STR(__GNUC_GNU_INLINE__) " " );
	#endif
	#ifdef __GNUC_STDC_INLINE__
		_Log( _STR(__GNUC_STDC_INLINE__) " " );
	#endif
	#ifdef __CHAR_UNSIGNED__
		_Log( _STR(__CHAR_UNSIGNED__) " " );
	#endif
	#ifdef __WCHAR_UNSIGNED__
		_Log( _STR(__WCHAR_UNSIGNED__) " " );
	#endif
	#ifdef __REGISTER_PREFIX__
		_Log( _STR(__REGISTER_PREFIX__) "=\"" __REGISTER_PREFIX__ "\" " );
	#endif
	#ifdef __USER_LABEL_PREFIX__
		_Log( _STR(__USER_LABEL_PREFIX__) "=\"" _XSTR(__USER_LABEL_PREFIX__) "\" " );
	#endif
	#ifdef __BYTE_ORDER__
		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) " " );
		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) " " );
		#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_PDP_ENDIAN__) " " );
		#endif
//		#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
//			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) "=\"" _XSTR(__BYTE_ORDER__) "\" " );
//		#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
//			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) "=\"" _XSTR(__BYTE_ORDER__) "\" " );
//		#elif __BYTE_ORDER__ == __ORDER_PDP_ENDIAN__
//			_Log( _STR(__BYTE_ORDER__) "=" _STR(__ORDER_PDP_ENDIAN__) "=\"" _XSTR(__BYTE_ORDER__) "\" " );
//		#endif
	#endif
	#ifdef __FLOAT_WORD_ORDER__
		#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) " " );
		#elif __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) " " );
		#endif
//		#if __FLOAT_WORD_ORDER__ == __ORDER_LITTLE_ENDIAN__
//			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_LITTLE_ENDIAN__) "=\"" _XSTR(__FLOAT_WORD_ORDER__) "\" " );
//		#elif __FLOAT_WORD_ORDER__ == __ORDER_BIG_ENDIAN__
//			_Log( _STR(__FLOAT_WORD_ORDER__) "=" _STR(__ORDER_BIG_ENDIAN__) "=\"" _XSTR(__FLOAT_WORD_ORDER__) "\" " );
//		#endif
	#endif
	#ifdef __DEPRECATED
		_Log( _STR(__DEPRECATED) " " );
	#endif
	#ifdef __EXCEPTIONS
		_Log( _STR(__EXCEPTIONS) " " );
	#endif
	#ifdef __GXX_RTTI
		_Log( _STR(__GXX_RTTI) " " );
	#endif
	#ifdef __USING_SJLJ_EXCEPTIONS__
		_Log( _STR(__USING_SJLJ_EXCEPTIONS__) " " );
	#endif
	#ifdef __GXX_EXPERIMENTAL_CXX0X__
		_Log( _STR(__GXX_EXPERIMENTAL_CXX0X__) " " );
	#endif
	#ifdef __GXX_WEAK__
		_Log( _STR(__GXX_WEAK__) " " );
	#endif
	#ifdef __NEXT_RUNTIME__
		_Log( _STR(__NEXT_RUNTIME__) " " );
	#endif
	#ifdef __LP64__
		_Log( _STR(__LP64__) " " );
	#endif
	#ifdef __SSP__
		_Log( _STR(__SSP__) " " );
	#endif
	#ifdef __SSP_ALL__
		_Log( _STR(__SSP_ALL__) " " );
	#endif
	#ifdef __SANITIZE_ADDRESS__
		_Log( _STR(__SANITIZE_ADDRESS__) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_1
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_1) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_2
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_2) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_4
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_4) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_8
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_8) " " );
	#endif
	#ifdef __GCC_HAVE_SYNC_COMPARE_AND_SWAP_16
		_Log( _STR(__GCC_HAVE_SYNC_COMPARE_AND_SWAP_16) " " );
	#endif
	#ifdef __GCC_HAVE_DWARF2_CFI_ASM
		_Log( _STR(__GCC_HAVE_DWARF2_CFI_ASM) " " );
	#endif
	#ifdef __FP_FAST_FMA
		_Log( _STR(__FP_FAST_FMA) " " );
	#endif
	#ifdef __FP_FAST_FMAF
		_Log( _STR(__FP_FAST_FMAF) " " );
	#endif
	#ifdef __FP_FAST_FMAL
		_Log( _STR(__FP_FAST_FMAL) " " );
	#endif

	Log( "" );
	#endif // _MSC_VER //
	
	Log( "" );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_GCC //
// - ------------------------------------------------------------------------------------------ - //
