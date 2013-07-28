// -------------------------------------------------------------------------- //
#ifdef USES_STAT
// -------------------------------------------------------------------------- //
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
// -------------------------------------------------------------------------- //
#include "GelFileInfo_Stat_Wrapper.h"
// -------------------------------------------------------------------------- //
// Use 'stat' to populate the GelFileInfo_Stat_Wrapper structure //
void stat_GelFileInfo_Stat_Wrapper( struct GelFileInfo_Stat_Wrapper* Out, const char* InFile ) {
	struct stat FileStat;
	Out->Error = stat(InFile, &FileStat);
	memset(Out,sizeof(struct GelFileInfo_Stat_Wrapper),0);
	if ( Out->Error == 0 ) {
		Out->Size = FileStat.st_size;
		
		Out->ATime = (unsigned long long int)FileStat.st_atime;
		Out->MTime = (unsigned long long int)FileStat.st_mtime;
		Out->CTime = (unsigned long long int)FileStat.st_ctime;
		
		Out->Flags = 0;
		if ( S_ISDIR(FileStat.st_mode) )
			Out->Flags |= GFI_DIR;
		if ( S_ISREG(FileStat.st_mode) )
			Out->Flags |= GFI_FILE;
		
		#ifdef WIN32
			// Simple File Info (Windows) //
			if ( FileStat.st_mode & S_IXUSR )
				Out->Flags |= GFI_EXEC;
			if ( FileStat.st_mode & S_IRUSR )
				Out->Flags |= GFI_READ;
			if ( FileStat.st_mode & S_IWUSR )
				Out->Flags |= GFI_WRITE;
		#else // !WIN32 //
			// Complex File Info (Unix) //
			if ( FileStat.st_mode & S_IXUSR )
				Out->Flags |= GFI_UEXEC;
			if ( FileStat.st_mode & S_IRUSR )
				Out->Flags |= GFI_UREAD;
			if ( FileStat.st_mode & S_IWUSR )
				Out->Flags |= GFI_UWRITE;
	
			if ( FileStat.st_mode & S_IXGRP )
				Out->Flags |= GFI_GEXEC;
			if ( FileStat.st_mode & S_IRGRP )
				Out->Flags |= GFI_GREAD;
			if ( FileStat.st_mode & S_IWGRP )
				Out->Flags |= GFI_GWRITE;
	
			if ( FileStat.st_mode & S_IXOTH )
				Out->Flags |= GFI_OEXEC;
			if ( FileStat.st_mode & S_IROTH )
				Out->Flags |= GFI_OREAD;
			if ( FileStat.st_mode & S_IWOTH )
				Out->Flags |= GFI_OWRITE;
	
			if ( S_ISLNK(FileStat.st_mode) )
				Out->Flags |= GFI_SYMLINK;	
		#endif // WIN32 //
	}
}
// -------------------------------------------------------------------------- //
#endif // USES_STAT //
// -------------------------------------------------------------------------- //
