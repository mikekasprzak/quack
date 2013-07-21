// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //

void MyFunc() {
	Log("Triggered");
}
void MyFunc2( st User, st Arg ) {
	Log("Triggered Also. %i %i", (int)User, (int)Arg );
}

st MyFunc3( st User, st Arg, st Ret ) {
	Log("Targ: %i %i %i", (int)User, (int)Arg, (int)Ret );
	return Ret+1;
}

// - ------------------------------------------------------------------------------------------ - //
int AppMain() {
	{
		Log( "" );
		Log( "Signal Test:" );
		
		// Signal Testing Code //
		Signal MySignal;
		MySignal.Connect( MyFunc );
		MySignal.Connect( MyFunc2, 200 );
		MySignal.Connect( MyFunc3, 1 );
		MySignal.Connect( MyFunc3, 2 );
		MySignal.Connect( MyFunc3, 3 );
		st Ret = (st)MySignal( 25 );
		Log( "Final Ret is: %i", (int)Ret );
	}
	
	{
		Log( "" );
		Log( "Deferred Test:" );
		
		// Deferred Testing Code //
		Deferred MyDef;
		MyDef.Then( MyFunc );
		MyDef.OnError( MyFunc2 );
		MyDef.Always( MyFunc2, 64 );
		
		MyDef.Callback( 13 );
//		MyDef.Errback( 10 );

		Log( "Adding a late action. These will automatically trigger Callback or Errback." );
		
		MyDef.Then( MyFunc2 );
		MyDef.OnError( MyFunc );
	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
