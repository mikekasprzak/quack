// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo stat - C code wrapper for stat (since it doesn't work right anymore) //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Core_GelFileInfo_stat_H__
#define __GEL_Core_GelFileInfo_stat_H__
// -------------------------------------------------------------------------- //
extern "C" {
// -------------------------------------------------------------------------- //
struct _GelFileInfo;

_GelFileInfo* new_GelFileInfo( const char* InFile );
void delete_GelFileInfo( _GelFileInfo* Me );
_GelFileInfo* copy_GelFileInfo( _GelFileInfo* Vs );

const int exists_GelFileInfo( _GelFileInfo* Me );
const int isDirectory_GelFileInfo( _GelFileInfo* Me );
const int isFile_GelFileInfo( _GelFileInfo* Me );
const int hasChanged_GelFileInfo( _GelFileInfo* Me, _GelFileInfo* Vs );

const int getErr_GelFileInfo( struct _GelFileInfo* Me );
// -------------------------------------------------------------------------- //
}; // extern "C" //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Core_GelFileInfo_stat_H__ //
// - ------------------------------------------------------------------------------------------ - //
