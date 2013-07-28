// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo_Stat_Wrapper - C code wrapper for stat (since it doesn't work right on Linux) //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GelFileInfo_Stat_Wrapper_H__
#define __GEL_LIB_GelFileInfo_Stat_Wrapper_H__
// -------------------------------------------------------------------------- //
#ifdef USES_STAT
// -------------------------------------------------------------------------- //
#ifdef __cplusplus
extern "C" {
#endif // __cplusplus //
// -------------------------------------------------------------------------- //
enum {
	GFI_DIR		= 0x1,
	GFI_FILE	= 0x2, // REG //
	GFI_SYMLINK	= 0x4,
	//GFI_? 	= 0x8,

	// User //
	GFI_UEXEC	= 0x10,
	GFI_UREAD	= 0x20,
	GFI_UWRITE	= 0x40,
	// Group //
	GFI_GEXEC	= 0x100,
	GFI_GREAD	= 0x200,
	GFI_GWRITE	= 0x400,
	// Other //
	GFI_OEXEC	= 0x1000,
	GFI_OREAD	= 0x2000,
	GFI_OWRITE	= 0x4000,
	
	// Check for any of these (if (Flags & GFI_READ){}) to see if file has a prop //
	GFI_EXEC	= (GFI_UEXEC|GFI_GEXEC|GFI_OEXEC),
	GFI_READ	= (GFI_UREAD|GFI_GREAD|GFI_OREAD),
	GFI_WRITE	= (GFI_UWRITE|GFI_GWRITE|GFI_OWRITE),
};
// -------------------------------------------------------------------------- //
// NOTE: This structure is free to be populated by other file system functions, so
//   feel free to use it inside Archive wrapping libraries, remote access libs, etc.
struct GelFileInfo_Stat_Wrapper {
	int 					Error;	// Error Code Returned By Stat (0 if exists) //
	unsigned 				Flags;	// File Property Flags //
	unsigned long long int	Size;	// File Size //	
	
	unsigned long long int	ATime;	// Access Time (Linux Only?) //
	unsigned long long int	MTime;	// Modified Time //
	unsigned long long int	CTime;	// Creation Time //
};
// -------------------------------------------------------------------------- //
void stat_GelFileInfo_Stat_Wrapper( struct GelFileInfo_Stat_Wrapper* Out, const char* InFile );
// -------------------------------------------------------------------------- //
#ifdef __cplusplus
}; // extern "C" //
#endif // __cplusplus //
// -------------------------------------------------------------------------- //
#endif // USES_STAT //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Core_GelFileInfo_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
