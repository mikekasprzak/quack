// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo - Information about a file //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GELFILEINFO_H__
#define __GEL_LIB_GELFILEINFO_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelTypes.h>
#include <Lib/GelTime/GelTime.h>
#include <Lib/Log/Log.h>
// - ------------------------------------------------------------------------------------------ - //
class GelFileInfo {
public:
	int		Flags;	// File Property Flags //
	u32		Size;	// File Size //	
	GelTime	Time;	// Modified Time //

public:
	enum /* GelFileInfo Flags */ {
		GFI_DIR		= 0x1,
		GFI_FILE	= 0x2, // REG //
		GFI_SYMLINK	= 0x4,
	
		// Simplified File Flags (Since truthfully I don't actually care about them) //
		GFI_EXEC	= 0x1110,
		GFI_READ	= 0x2220,
		GFI_WRITE	= 0x4440,
		
		// Flag that says the file was not found //
		GFI_NOT_FOUND	= 0x10000,
	};

public:
	void Load( const char* FileName );
	
	inline GelFileInfo( const char* FileName ) {
		Load( FileName );
	}
	inline GelFileInfo() :
		Flags( 0 ),
		Size( 0 ),
		Time( 0 )
	{
	}
	
	// To check for changes, use the == operator //
	inline bool operator==( const GelFileInfo& Vs ) const {
		return ( Size == Vs.Size ) && ( Time == Vs.Time );
	}
	inline bool operator!=( const GelFileInfo& Vs ) const {
		return !(operator==( Vs ));
	}

public:	
	inline bool Exists() {
		return !(Flags & GFI_NOT_FOUND);
	}

	inline bool IsFile() {
		return Flags & GFI_FILE;
	}
	inline bool IsDir() {
		return Flags & GFI_DIR;
	}
	inline bool IsSymlink() {
		return Flags & GFI_SYMLINK;
	}
	
	inline bool IsExecutable() {
		return Flags & GFI_EXEC;
	}
	inline bool IsReadable() {
		return Flags & GFI_READ;
	}
	inline bool IsWritable() {
		return Flags & GFI_WRITE;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GELFILEINFO_H__ //
// - ------------------------------------------------------------------------------------------ - //
