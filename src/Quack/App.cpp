// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/Asset.h>
#include <rde/rdestl.h>
// - ------------------------------------------------------------------------------------------ - //
void AppInit() {
	Log( "-=- AppInit -=-" );
	
	LogLevel = 3;

	gelTimeInit();
	gelSystemInit();
	gelAssetInit();
	
	Gel::Search.Add( "project" );

	// **** //

	Log( "" );
	
	// **** //
	
	QuackVMInit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
int AppMain() {
	Log( "-=- AppMain -=-" );
	Log( "Screens: %i", (int)Gel::Screen.Count() );		
	
	{
		Log( "" );
		Log( "** Search Test:" );
		
		const char* Text = Gel::Search("main");
		if ( Text ) Log( "> %s", Text );
		Text = Gel::Search("play"); // Will Fail because it's Play not play //
		if ( Text ) Log( "> %s", Text );
		Text = Gel::Search("Nerf");
		if ( Text ) Log( "> %s", Text );
	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
