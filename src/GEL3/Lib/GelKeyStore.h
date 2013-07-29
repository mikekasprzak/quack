// - ------------------------------------------------------------------------------------------ - //
// GelKeyStore is like a simple database. Store and retrieve a variety of types (flex). //
//
// Usage:
//   GelKeyStore MyDB;
//   MyDB.Add("UltimateAnswer") = 42;
//   Log( "Answer: %i", MyDB("UltimateAnswer").ToInt() );
//   MyDB.Delete("UltimateAnswer");
//   if ( MyDB.Exists("UltimateAnswer") ) { Log("This should have failed"); }
//
// - ------------------------------------------------------------------------------------------ - //
// Originally from PlayMore Engine //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GELKEYSTORE_H__
#define __GEL_LIB_GELKEYSTORE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <string>

#include "Flex.h"
// - ------------------------------------------------------------------------------------------ - //
class GelKeyStore {
public: // - Class Helpers -------------------------------------------------------------------- - //
	typedef GelKeyStore thistype;
	inline void* GetThis() { return this; }
public: // - Members -------------------------------------------------------------------------- - //
	std::map<std::string,flex> Data;						// Key/Value Pairs //
	typedef std::map<std::string,flex>::iterator ItrType; 
public: // - Constructors and Destructors ----------------------------------------------------- - //
	GelKeyStore()
	{
	}

public: // - Methods -------------------------------------------------------------------------- - //
	inline flex& operator() ( const char* Name ) {
		ItrType Itr = Data.find( Name );
		if ( Itr != Data.end() ) {
			return Itr->second;
		}
		else {
			Log( "! ERROR: Invalid Key \"%s\" in KeyStore", Name );
			static flex Dummy;
			return Dummy;
		}
	}
	inline flex& operator() ( const std::string Name ) {
		return operator()( Name.c_str() );
	}
	
	inline flex& Add( const char* Name ) {
		return Data[Name];
	}
	inline flex& Add( const std::string Name ) {
		return Add( Name.c_str() );
	}

	inline bool Exists( const char* Name ) {
		ItrType Itr = Data.find( Name );
		return Itr != Data.end();
	}
	inline bool Exists( const std::string Name ) {
		return Exists( Name.c_str() );
	}

	inline void Delete( const char* Name ) {
		ItrType Itr = Data.find( Name );
		if ( Itr != Data.end() ) {
			Data.erase( Itr );
		}
		else {
			Log( "! ERROR: Can't Delete! Key \"%s\" not found!", Name );
		}		
	}
	inline void Delete( const std::string Name ) {
		Delete( Name.c_str() );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GELKEYSTORE_H__ //
// - ------------------------------------------------------------------------------------------ - //
