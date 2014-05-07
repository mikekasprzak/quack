// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELINPUTQUEUE_H__
#define __GEL_GELINPUTQUEUE_H__
// - ------------------------------------------------------------------------------------------ - //
// The Input Queue is a smart system that tracks controller inputs from multiple players over
// many frames. It can be used to intentionally lag local inputs, to better synchronize remotely.
// It can also be used to track change, such as whether a button is newly pressed this frame.
// - ------------------------------------------------------------------------------------------ - //
// The Input Queue will live on top of local controller inputs, and networking. //
// - ------------------------------------------------------------------------------------------ - //
//#include <vector>
#include <list>
// - ------------------------------------------------------------------------------------------ - //
// Input States are individual snapshots of controller data //
class GelInputState {
	typedef GelInput thistype;
public:
//	unsigned short Id;		// Unique Identifier used to reject a slot (needed?)

	unsigned short Button;	// We always have button data, no matter the device.
	short Data[15];			// Everything else (Analog Axis, Mouse/Touch Coordinates, Triggers, etc)
};
// - ------------------------------------------------------------------------------------------ - //
class GelInput {
	typedef GelInput thistype;
public:
	bool Active;
	bool Remote;		// The input is Remote //
	int LastUsed;
	
	GelInputState State[256];
	
	inline GelInput() :
		Active( false ),
		LastUsed( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //
class GelInputQueue {
	typedef GelInputQueue thistype;
public:
//	std::vector<GelInput> Input;
	std::list<GelInput> Input;
		
	//AddInput
};
// - ------------------------------------------------------------------------------------------ - //
// Application Start:
// - Add Attached Controllers
// Connect to a Server:
// - Clear All Inputs (?)
// - Add all remotes
// - Re-Add All Inputs
// Alternatively, use a mapping table. //
// - Check table. 
//   - If positive, then it's a local player. Index the attached table.
//   - If negative, then it's a remote player. Negate, then Index the attached table.
// Tables should be synchronized.
// Every player is free to pause their own screen.
// Every player should be able to disconnect from the pause menu.
// Should be a way to disconnect all players.
// "master input" ... not sure how to handle.
// There's no reason to send master input across the wire.
// ??
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELINPUTQUEUE_H__ //
// - ------------------------------------------------------------------------------------------ - //
