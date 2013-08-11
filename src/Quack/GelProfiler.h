// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_WTF_GELPROFILER_H__
#define __GEL_WTF_GELPROFILER_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/GelTime/GelTime.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
class GelProfiler {
protected:
	st CurrentProfile;
	std::vector<GelTime> Profile;
	
	// Results //
	GelTime Average;
	GelTime Min, Max;
public:
	inline GelProfiler( const st ProfileCount = 60 ) :
		CurrentProfile( 0 ),
		Average( 0 ),
		Min( 0 ),
		Max( 0 )
	{
		Profile.resize( ProfileCount );
	}
public:	
	inline void Start() {
		// Begin Timing //
		Profile[CurrentProfile] = get_us_GelTime();
	}
	
	inline void Stop() {
		// Stop Timing //
		GelTime End = get_us_GelTime();
		
		// Record an Entry //
		Profile[CurrentProfile] = End - Profile[CurrentProfile];
		
		// Prepare to record the next profile //
		CurrentProfile++;
		if ( CurrentProfile == Profile.size() ) {
			// If we happen to be on the last profile, it's time to generate results //
			UpdateResults();
		}
		CurrentProfile %= Profile.size();
	}
	
	inline void UpdateResults() {
		Average = Profile[0];
		Min = Profile[0];
		Max = Profile[0];
		
		// Starting at Index 1, because //
		for ( st idx = 1; idx < Profile.size(); idx++ ) {
			Average += Profile[idx];
			
			if ( Profile[idx] > Max ) {
				Max = Profile[idx];
			}
			
			if ( Profile[idx] < Min ) {
				Min = Profile[idx];
			}
		}
		
		Average /= Profile.size();
	}

public:
	inline GelTime GetAverage() {
		return Average;
	}
	inline GelTime GetMin() {
		return Min;
	}
	inline GelTime GetMax() {
		return Max;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_WTF_GELPROFILER_H__ //
// - ------------------------------------------------------------------------------------------ - //
