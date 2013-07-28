// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo - Information about a file //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GelFileInfo_H__
#define __GEL_LIB_GelFileInfo_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Log/Log.h>
// - ------------------------------------------------------------------------------------------ - //
class GelFileInfo {
public:
	int		Flags;	// File Property Flags //
	st		Size;	// File Size //	
	
	st		ATime;	// Access Time (Linux Only?) //
	st		MTime;	// Modified Time //
	st		CTime;	// Creation Time //

public:
	enum /* GelFileInfo Flags */ {
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
		
		GFI_NOT_FOUND	= 0x10000,
	};

public:
	
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GelFileInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
