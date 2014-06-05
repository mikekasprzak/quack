// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WINDOWS_PATH
// - ------------------------------------------------------------------------------------------ - //
#include <Windows.h>
#include <shlobj.h>
#include <stdio.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include "SysPath.h"
// - ------------------------------------------------------------------------------------------ - //
void sysGetContentPath( char* PathString, const size_t PathString_Size ) {
	GetModuleFileNameA( NULL, PathString, PathString_Size );
	
	int Len = strlen( PathString );
	for( ; Len--; ) {
		if (PathString[Len] == '\\') {
			PathString[Len+1] = 0;	
			break;
		}
		else if (PathString[Len] == '/') {
			PathString[Len+1] = 0;	
			break;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void sysGetStoragePath( char* PathString, const size_t PathString_Size ) {
	// NOTE: UNSAFE! PathString_Size is ignored!! //
	char Path[_MAX_PATH+1];

	// SHGFP_TYPE_DEFAULT = 1
	SHGetFolderPathA( NULL, CSIDL_APPDATA, NULL, 1, Path );
		
	sprintf( PathString, "%s\\Sykhronics\\", &Path[0] );
	CreateDirectoryA( PathString, NULL );		
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WINDOWS_PATH //
// - ------------------------------------------------------------------------------------------ - //
