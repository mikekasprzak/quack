// - ------------------------------------------------------------------------------------------ - //
#include <curl/curl.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void gelNetInit( const bool DoWindowsInit ) {
	curl_global_init( DoWindowsInit ? CURL_GLOBAL_WIN32 : CURL_GLOBAL_NOTHING );
}
// - ------------------------------------------------------------------------------------------ - //
