// - ------------------------------------------------------------------------------------------ - //
#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Input/Input.h>
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_Squirrel.h>
// - ------------------------------------------------------------------------------------------ - //
#include "QuackVM.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/Asset.h>
//#include <rde/rdestl.h>
#include <PVRTModelPOD.h>
// - ------------------------------------------------------------------------------------------ - //
namespace App {
// - ------------------------------------------------------------------------------------------ - //
int Mode = AM_NULL;
// - ------------------------------------------------------------------------------------------ - //
void SetMode( const int _Mode ) {
	Log( "App::Mode set to %s (%i)", GetModeName(_Mode), _Mode );
	Mode = _Mode;
}
// - ------------------------------------------------------------------------------------------ - //
const char* const ModeName[] = {
	"AM_NULL/AM_ERROR",
	"AM_MAIN",
	"AM_GAMELOOP",
	"AM_ENGINE",
};
// - ------------------------------------------------------------------------------------------ - //
const char* GetModeName( const int _Mode ) {
	return ModeName[_Mode];
}
// - ------------------------------------------------------------------------------------------ - //
const char* GetModeName() {
	return GetModeName( Mode );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
bool Exit = false;
GelTime FrameTime = 0;
// - ------------------------------------------------------------------------------------------ - //
GelProfiler StepProfiler;
GelProfiler DrawProfiler;
// - ------------------------------------------------------------------------------------------ - //
GelSignal GainFocus;
GelSignal LoseFocus;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace App //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AppInit() {
	Log( "-=- AppInit -=-" );
	
	// **** //

	LogLevel = 3;
	App::Mode = App::AM_NULL;
	App::Exit = false;
	App::FrameTime = 0;

	// **** //

	gelTimeInit();
	gelSystemInit();
	gelAssetInit();
	Gel::Input::Init();
	
	Gel::Search.Add( "src/Quack/QuackLib" );
	Gel::Search.Add( "project" );

	// **** //
//	Log( "Screens: %i", (int)Gel::Screen.Count() );
	Log( "" );
	
	// **** //
	
	QuackVMInit();
	QuackVMCallSetup();
	QuackVMCallInit();
	
	{	
		Log("**** LOADING MONKEY POD");
		CPVRTModelPOD Scene;
		EPVRTError Error = Scene.ReadFromFile("project/content/Cube.pod");
		//ReadFromMemory(pData,Size);
		
		if ( Error == PVR_SUCCESS ) {
			Log("Success!");
			
			Log("Nodes: %i  MeshNodes: %i  Meshes: %i  AnimationFrames: %i (Lights: %i  Cameras: %i  Materials: %i  Textures: %i)", 
				Scene.nNumNode, Scene.nNumMeshNode, Scene.nNumMesh, Scene.nNumFrame,
				Scene.nNumLight, Scene.nNumCamera, Scene.nNumMaterial, Scene.nNumTexture );
				
			Log("Verts: %i  Faces: %i  UVW: %i",
				Scene.pMesh[0].nNumVertex, Scene.pMesh[0].nNumFaces, Scene.pMesh[0].nNumUVW );
				
			for ( int idx = 0; idx < Scene.nNumTexture; idx++ ) {
				Log("%i T: %s", idx, Scene.pTexture[idx].pszName );
			}
		}
		
		Log("**** DONE");
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AppExit() {
	QuackVMCallExit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AppStep() {
	App::StepProfiler.Start();
	// *** //
	
	Gel::Input::Poll();
	
	// If the Refresh key is pressed (NOTE: this should be 'just pressed' state) //
	extern bool ___keyRefresh;
	if ( ___keyRefresh ) {
		QuackVMCallInit();
	}

	// START: Update FrameTime //
	sq_pushroottable(vm);
	sq_pushstring(vm,_SC("Qk"),-1);
	sq_get(vm,-2);
	sq_pushstring(vm,_SC("FrameTime"),-1);
	sq_pushinteger(vm,App::FrameTime);
	sq_newslot(vm,-3,SQFalse);
	sq_pop(vm,1);
	// END: Update FrameTime //

	QuackVMCallStep();
	
	// *** //
	App::StepProfiler.Stop();
}
// - ------------------------------------------------------------------------------------------ - //
void AppDraw() {
	App::DrawProfiler.Start();	
	// *** //

	QuackVMCallDraw();

	// *** //
	App::DrawProfiler.Stop();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AppGainFocus() {
	App::GainFocus();
	Gel::AssetPool.ScanForChanges();
	QuackVMCallGainFocus();
}
// - ------------------------------------------------------------------------------------------ - //
void AppLoseFocus() {
	QuackVMCallLoseFocus();
	App::LoseFocus();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AppRequestExit() {
	// In case of multiple exit events triggered by something (SDL_QUIT && SDL_WINDOWEVENT_CLOSE) //
	if ( !App::Exit ) {
		if ( !QuackVMCallRequestExit() ) {
			// Automatically set Exit to true here if the App has no RequestExit function hook //
			App::Exit = true;
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
