// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_GELSCREENS_H__
#define __GEL_SYSTEM_GELSCREENS_H__
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <Lib/Lib.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelScreen.h"
// - ------------------------------------------------------------------------------------------ - //
class GelScreens {
	std::vector<GelScreen> Screens;
public:
	inline GelScreens() {
	}
	
	inline void Add( const GelScreen& _Screen ) {
		Screens.push_back( _Screen );
	}
	
	inline const GelScreen& operator[]( const st Index ) const {
		return Screens[Index];
	}
	
	inline st Count() const {
		return Screens.size();
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
extern GelScreens Screen;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSCREENS_H__ //
// - ------------------------------------------------------------------------------------------ - //
