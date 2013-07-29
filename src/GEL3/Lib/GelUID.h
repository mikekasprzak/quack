// - ------------------------------------------------------------------------------------------ - //
// GelUID's are a way to get a (mostly) unique value. 
// By mostly, I mean the UID will eventually loop around after you request 4 billion of them.
// You can assume a UID of "0" will never be used (except if it loops).
//
// Usage 1: Just create one and you
//   GelUID MyId;
//
// Usage 2: Explicitly call generate to also get one.
//   return GelUID::Generate();
//
// Usage 3: Get the value of the UID
//   Log( "UID: %x", (int)MyId.Get() );
//
// Usage 4: Reset the UIDs to the beginning (in your init code)
//   GelUID::Init();
//
// - ------------------------------------------------------------------------------------------ - //
// Originally from PlayMore Engine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_UID_H__
#define __GEL_LIB_UID_H__
// - ------------------------------------------------------------------------------------------ - //
class GelUID {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef GelUID thistype;
	inline void* GetThis() { return this; }
private: // - Members ------------------------------------------------------------------------- - //
	typedef unsigned int UIDType;
	static UIDType CurrentUID;

	UIDType Data;
public: // - Constructors and Destructors ----------------------------------------------------- - //
	GelUID() :
		Data( Generate().Get() )
	{
	}

	GelUID( const UIDType _Data ) :
		Data( _Data )
	{
	}

public: // - Static Methods ------------------------------------------------------------------- - //
	static void Init( const UIDType InitValue = 1 ) {
		CurrentUID = InitValue;
	}
	static const GelUID Generate() {
		return GelUID(CurrentUID++);
	}

public: // - Methods -------------------------------------------------------------------------- - //
	unsigned int Get() const {
		return Data;
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_UID_H__ //
// - ------------------------------------------------------------------------------------------ - //
