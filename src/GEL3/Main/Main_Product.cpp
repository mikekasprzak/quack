// - ------------------------------------------------------------------------------------------ - //
#include "Main_Product.h"
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_NAME
	const char* const ProductName = PRODUCT_NAME;
#else // PRODUCT_NAME //
	const char* const ProductName = "Unknown";
#endif // PRODUCT_NAME //
// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_VERSION
	const char* const ProductVersion = PRODUCT_VERSION;
#else // PRODUCT_NAME //
	const char* const ProductVersion = "v0.0";
#endif // PRODUCT_NAME //
// - ------------------------------------------------------------------------------------------ - //
#if defined( PRODUCT_NAME )
	const char* const FullProductName = PRODUCT_NAME " " PRODUCT_VERSION;
#else // PRODUCT_NAME //
	const char* const FullProductName = "Unknown v0.0";
#endif // PRODUCT_SKU //
// - ------------------------------------------------------------------------------------------ - //
