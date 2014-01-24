// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_UNIX_PATH
// - ------------------------------------------------------------------------------------------ - //
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include "SysPath.h"
// - ------------------------------------------------------------------------------------------ - //
void sysGetContentPath( char* PathString, const size_t PathString_Size ) {
	readlink( "/proc/self/exe", PathString, PathString_Size );
	
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
	sprintf( PathString, "%s/.sykronics/", getenv("HOME") );
	mkdir( PathString, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_UNIX_PATH //
// - ------------------------------------------------------------------------------------------ - //
