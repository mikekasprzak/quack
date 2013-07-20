// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_WEB
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
#include <App.h>
#include <emscripten/emscripten.h>
// - ------------------------------------------------------------------------------------------ - //

void onLoad(void* InputArg, void* Data, int DataSize) {
	// NOTE: there is something wrong here. Only 1 command ever gets run. //
	Log( (char*)Data );
	Log("Musical Furut");
}
void onError( void* FileName ) {
	Log("ERROR: %s failed to load", (char*)FileName);
}

// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv[] ) {
	LogInit();

	gelLogSystemAPIDetails();
	gelLogGraphicsAPIDetails();
		
	// *** //
		
//	const char* FileName = "startup.nut.txt";
//	emscripten_async_wget_data(FileName,(void*)FileName,onLoad,onError);

	return AppMain();
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_WEB //
// - ------------------------------------------------------------------------------------------ - //
