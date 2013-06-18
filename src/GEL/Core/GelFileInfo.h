// - ------------------------------------------------------------------------------------------ - //
// GelFileInfo - Information about a file on disk //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_Core_GelFileInfo_H__
#define __GEL_Core_GelFileInfo_H__
// -------------------------------------------------------------------------- //
#include <Style/Style.h>
#include "GelFileInfo_stat.h"
// -------------------------------------------------------------------------- //
class GelFileInfo {
	_GelFileInfo* Info;
public:
	inline GelFileInfo() :
		Info( new_GelFileInfo(0) )
	{
		//clear_GelFileInfo(Info);
		Log( "+ (Z) 0x%x (%i)", Info, getErr_GelFileInfo(Info) );
	}
	
	inline GelFileInfo( const char* InFile ) :
		Info( new_GelFileInfo( InFile ) )
	{
		Log( "+ (!) 0x%x (%i)", Info, getErr_GelFileInfo(Info) );
	}
	
	inline void _Delete() {
		Log( "- [K] 0x%x (%i)", Info, getErr_GelFileInfo(Info) );
		if ( Info ) {
			delete_GelFileInfo( Info );	
			Info = 0;
		}
	}
	
	inline ~GelFileInfo() {
		_Delete();
	}
	
	inline GelFileInfo( const GelFileInfo& In ) :
		Info( copy_GelFileInfo( In.Info ) )
	{
		Log( "* [c] 0x%x (%i)", Info, getErr_GelFileInfo(Info) );
	}

	inline const GelFileInfo& operator = ( const GelFileInfo& In ) {
		Log( "* [=] 0x%x (%i)", Info, getErr_GelFileInfo(Info) );
		_Delete();
		
		Info = copy_GelFileInfo( In.Info );
		return *this;
	}

public:
	inline const bool Exists() const {
		return exists_GelFileInfo(Info);
	}
	
	inline const bool IsDirectory() const {
		return isDirectory_GelFileInfo(Info) != 0;
	}
	inline const bool IsFile() const {
		return isFile_GelFileInfo(Info) != 0;
	}
	
	inline const bool HasChanged( const GelFileInfo& Vs ) const {
		return hasChanged_GelFileInfo( Info, Vs.Info );
	}
	
//	inline void Clear() {
//		set_Data( 0, this, sizeof( GelFileInfo ) );
//	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_Core_GelFileInfo_H__ //
// - ------------------------------------------------------------------------------------------ - //
