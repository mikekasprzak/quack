// -------------------------------------------------------------------------- //
#ifdef USES_STAT
// - ------------------------------------------------------------------------------------------ - //
#include "GelFileInfo.h"
#include "GelFileInfo_Stat_Wrapper.h"
// - ------------------------------------------------------------------------------------------ - //
void GelFileInfo::Load( const char* FileName ) {
	// Have to use the 'stat' wrapper, 'cause Linux didn't like me using stat in C++ //
	GelFileInfo_Stat_Wrapper FileStat;
	stat_GelFileInfo_Stat_Wrapper( &FileStat, FileName );
	
	// Copy the flags (compatible) or set the File Not Found state //
	if ( FileStat.Error == 0 ) {
		Flags = FileStat.Flags;
	}
	else {
		Flags = GFI_NOT_FOUND;
	}
	
	Size = FileStat.Size;
	Time = FileStat.MTime;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_STAT //
// - ------------------------------------------------------------------------------------------ - //
