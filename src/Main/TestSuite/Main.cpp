// - ------------------------------------------------------------------------------------------ - //
// A special version of main to be run on new platforms BEFORE graphics work, to confirm that //
// logging and low level library features are all working. //
//
// Move all test code written when building new libraries here. //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_TESTSUITE
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
//#include <App.h>
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// The Signal Test Suite //
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
void SignalTest() {
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
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();
	
	gelLogSystemAPIDetails();
	gelLogGraphicsAPIDetails();

	// *** //

	SignalTest();

	// *** //
	
//	return AppMain();
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_TESTSUITE //
// - ------------------------------------------------------------------------------------------ - //
