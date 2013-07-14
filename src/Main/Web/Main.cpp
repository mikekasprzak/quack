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

	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WEB //
// - ------------------------------------------------------------------------------------------ - //