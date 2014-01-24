// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_SYSPATH_SYSPATH_H__
#define __GEL_SYSTEM_SYSPATH_SYSPATH_H__
// - ------------------------------------------------------------------------------------------ - //
// Pass a string (char[]) to store the data in //
void sysGetContentPath( char* PathString, const size_t PathString_Size ); // Base //
void sysGetStoragePath( char* PathString, const size_t PathString_Size ); // Save //
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
	extern char BaseDir[];
	extern char SaveDir[];
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_SYSPATH_SYSPATH_H__ //
// - ------------------------------------------------------------------------------------------ - //
