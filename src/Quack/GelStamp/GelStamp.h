// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_CORE_GELSTAMP_H__
#define __GEL_CORE_GELSTAMP_H__
// - ------------------------------------------------------------------------------------------ - //
// Default Stamp should be 0.
// Stampers will start always start at 1.
// Whenever we overflow the Stamper, reset all Stamps back to 1.
// - ------------------------------------------------------------------------------------------ - //
typedef unsigned int GelStamp;
// - ------------------------------------------------------------------------------------------ - //
class GelStamper {
	GelStamp Current;
public:
	inline GelStamper( const GelStamp _Current = 1 ) :
		Current(_Current)
	{
	}

	inline bool Check( GelStamp& Target ) const {
		if ( Target < Current ) {
			Target = Current;
			return true;
		}
		return false;
	}
	
	inline bool NewStamp() {
		Current++;
//		Current &= 255;	// Make Stamp Overflows happen more often //
		if ( Current == 0 ) {
			Current = 1;
			return true;
		}
		return false;
	}

	// DANGER! This function is unsafe! It will not handle overflows! //
	inline GelStamp RetNewStamp() {
		return Current++;
	}
	
	inline void Clear( GelStamp& Target ) const {
		Target = 0;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_CORE_GELSTAMP_H__ //
// - ------------------------------------------------------------------------------------------ - //
