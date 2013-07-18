// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WEB
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Main/Main_HgVersion.h>
#include <Main/Main_Product.h>
// - ------------------------------------------------------------------------------------------ - //

void MyFunc( void* ) {
	Log("Triggered");
}
void MyFunc2( st Arg ) {
	Log("Triggered Also. %i", (int)Arg );
}

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();
		
	// *** //

	Log( "-=======- GEL3 Application Started -- Web Branch -- SKU: %s -=======-", PRODUCT_SKU );
	Log( "GEL (C) Copyright 2008-2014 Mike Kasprzak and Sykhronics Entertainment" );
	Log( "" );
	
	Log( "-=- SKU: %s -=- %s -=-", PRODUCT_SKU, FullProductName );
	Log( "Hg Revision: %i [%s]", HG_VERSION, HG_HASH );
	Log( "Compiled on: %s %s", __DATE__, __TIME__ );

	{
		// Signal Testing Code //
		Signal MySignal;
		MySignal.Connect( MyFunc );
		MySignal.Connect( MyFunc2 );
		MySignal( 13 );
	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WEB //
// - ------------------------------------------------------------------------------------------ - //
