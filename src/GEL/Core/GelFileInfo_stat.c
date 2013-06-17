// -------------------------------------------------------------------------- //
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
// -------------------------------------------------------------------------- //
struct _GelFileInfo {
	int Err;				// Error code returned by stat //
	struct stat Status;		// C File Info Structure //
};
#define _GelFileInfo_Size	sizeof(struct _GelFileInfo)
// -------------------------------------------------------------------------- //
extern void* alloc_GelFileInfo( const size_t Size );
extern void free_GelFileInfo( void* Me );
// -------------------------------------------------------------------------- //
struct _GelFileInfo* new_GelFileInfo( const char* InFile ) {
//	struct _GelFileInfo* Ret = malloc( _GelFileInfo_Size );
//	struct _GelFileInfo* Ret = calloc( _GelFileInfo_Size, 1 );
	struct _GelFileInfo* Ret = alloc_GelFileInfo( _GelFileInfo_Size );
	printf("T(%i) 0x%x (%s)\n", _GelFileInfo_Size, Ret, InFile );
	
	if ( InFile != 0 ) {
		Ret->Err = stat( InFile, &(Ret->Status) );
	}
	else {
		Ret->Err = -1;
	}
	
	return Ret;		
}
// -------------------------------------------------------------------------- //
void delete_GelFileInfo( struct _GelFileInfo* Me ) {
	free_GelFileInfo( (void*)Me );
//	free( Me );
}
// -------------------------------------------------------------------------- //

// -------------------------------------------------------------------------- //
const int exists_GelFileInfo( struct _GelFileInfo* Me ) {
	return Me->Err == 0;// Me->Status.st_mode != 0;
}
// -------------------------------------------------------------------------- //
const int isDirectory_GelFileInfo( struct _GelFileInfo* Me ) {
	return S_ISDIR( Me->Status.st_mode );// != 0;
}
// -------------------------------------------------------------------------- //
const int isFile_GelFileInfo( struct _GelFileInfo* Me ) {
	return S_ISREG( Me->Status.st_mode );// != 0;
}
// -------------------------------------------------------------------------- //
const int hasChanged_GelFileInfo( struct _GelFileInfo* Me, struct _GelFileInfo* Vs ) {
	return Me->Status.st_mtime != Vs->Status.st_mtime;	
}
// -------------------------------------------------------------------------- //
const int getErr_GelFileInfo( struct _GelFileInfo* Me ) {
	return Me->Err;
}
// -------------------------------------------------------------------------- //
