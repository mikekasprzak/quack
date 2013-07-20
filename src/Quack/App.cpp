// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
// - ------------------------------------------------------------------------------------------ - //

void MyFunc( int* ) {
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
		// Signal Testing Code //
		FuncChain MySignal;
		MySignal.Connect( &MyFunc );
		MySignal.Connect( &MyFunc2, 200 );
		MySignal.Connect( &MyFunc3, 1 );
		MySignal.Connect( &MyFunc3, 2 );
		MySignal.Connect( &MyFunc3, 3 );
		st Ret = (st)MySignal( 25 );
		Log( "Final Ret is: %i", (int)Ret );
	}
	
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
