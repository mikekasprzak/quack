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
//#include <rde/rdestl.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Asset/Asset.h>
#include <Texture/Texture.h>
#include <Font/Font.h>
#include <Atlas/Atlas.h>
#include <Skel/Skel.h>
#include <Model/Model.h>
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
bool AppStarted = false;	// Flag that is set only after Init is called (for the these Focus functions).
GelSignal GainFocus;
GelSignal LoseFocus;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GelFontPool::UID RuntimeErrorFont = 0;
Real AspectRatio;
Matrix4x4 InfoMatrix;
bool HadVMError;
// - ------------------------------------------------------------------------------------------ - //
//GelSkelPool::UID	SpineUID;
//spSkeleton*				SpineSkeleton;
//spAnimationState*		SpineAnimState;
GelSkelAnimator MySkel;
// - ------------------------------------------------------------------------------------------ - //
}; // namespace App //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AppInit() {
	Log( "-=- AppInit -=-" );
	
	// **** //

#ifdef USES_MOBILE 
	{
	    typedef khronos_int64_t EGLint64NV;
	    typedef khronos_uint64_t EGLuint64NV;
	    typedef void (GL_APIENTRYP PFNGLCOVERAGEMASKNVPROC) (GLboolean mask);
	    typedef void (GL_APIENTRYP PFNGLCOVERAGEOPERATIONNVPROC) (GLenum operation);
	    typedef EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC)(void);
	    typedef EGLuint64NV (EGLAPIENTRYP PFNEGLGETSYSTEMTIMENVPROC)(void);
	    PFNGLCOVERAGEMASKNVPROC glCoverageMaskNV;
	    PFNGLCOVERAGEOPERATIONNVPROC glCoverageOperationNV;
	    PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC eglGetSystemTimeFrequencyNV;
	    PFNEGLGETSYSTEMTIMENVPROC eglGetSystemTimeNV;

	    eglGetSystemTimeFrequencyNV = (PFNEGLGETSYSTEMTIMEFREQUENCYNVPROC)eglGetProcAddress("eglGetSystemTimeFrequencyNV");
		eglGetSystemTimeNV = (PFNEGLGETSYSTEMTIMENVPROC)eglGetProcAddress("eglGetSystemTimeNV");
		//if available use the extension. This enables the frame profiler in PerfHUD ES
		if (eglGetSystemTimeFrequencyNV && eglGetSystemTimeNV) {
			eglGetSystemTimeFrequencyNV();
			eglGetSystemTimeNV();
		}
	}
#endif // USES_MOBILE //
	
//	LogLevel = 3;
	App::Mode = App::AM_NULL;
	App::Exit = false;
	App::FrameTime = 0;

	// **** //

	gelTimeInit();
	gelSystemInit();
	gelAssetInit();
	gelTextureInit();
	gelFontInit();
	gelAtlasInit();
	gelSkelInit();
	gelModelInit();
	Gel::Input::Init();
	
	// **** //

	Gel::Search.Add( "src/Quack/QuackLib" );
	Gel::Search.Add( "project" );
	Log( "" );	
	
	App::HadVMError = false;
	App::AppStarted = false;
	QuackVMInit();
	QuackVMCallInit();
	App::AppStarted = true;

	// **** //

	// AutoLoad a font so 
	App::RuntimeErrorFont = Gel::FontPool.Load( "Arial.fnt" );

	App::AspectRatio = ((float)Gel::Native[0].GetWidth() / (float)Gel::Native[0].GetHeight());
	Log( "%i %i -- %f", Gel::Native[0].GetWidth(), Gel::Native[0].GetHeight(), App::AspectRatio.ToFloat() );
	// NOTE: WHOA! Using Native Screen 0 to calculate this Matrix! This is uncool!
	// Code was borrowed from the Aspect ratio detection code in qkScreen.cpp

	App::InfoMatrix = Matrix4x4::Identity;
	App::InfoMatrix[0] = Real(1.0f/256.0f);
	App::InfoMatrix[5] = Real(1.0f/256.0f) * App::AspectRatio;

	// **** //

//	{	
//		Log("**** LOADING POD");
//		GelModelPool::UID MyUID = Gel::ModelPool.Load( "project/content/Cube.pod" );
//		
//		Log("**** DONE");
//	}

	{	
		Log("**** LOADING SPINE");
		App::MySkel.Load( Gel::SkelPool.Load( "SpineTest/spineboy.json" ) );
//		App::SpineUID = Gel::SkelPool.Load( "SpineTest/spineboy.json" );
//		App::SpineSkeleton = spSkeleton_create( Gel::SkelPool[App::SpineUID].GetSkeletonData() );
//		App::SpineAnimState = spAnimationState_create(0);//stateData);
//			
//		spAnimation* Animation = spSkeletonData_findAnimation( App::SpineSkeleton->data, "walk");
//		spAnimationState_setAnimation( App::SpineAnimState, 0, Animation, true );

		App::MySkel.Set( "jump" );
		Log("**** DONE");
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AppExit() {

	/***/

	QuackVMCallExit();
	
	Gel::Input::Exit();
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
void AppStep() {
	App::StepProfiler.Start();
	// *** //
	
	Gel::Input::Poll();
	
	// If the Refresh key is pressed (NOTE: this should be 'just pressed' state) //
	if ( Gel::KeyRefresh ) {
		QuackVMCallInit();
	}

	// START: Update FrameTime //
	sq_pushroottable(vm);
	sq_pushstring(vm,_SC("Qk"),-1);
	sq_get(vm,-2);
	sq_pushstring(vm,_SC("FrameTime"),-1);
	sq_pushinteger(vm,App::FrameTime);
	sq_newslot(vm,-3,SQFalse);
	sq_pop(vm,1+1); // Slot and Root Table //
	// END: Update FrameTime //
	
	GelAsset::SetTimeStamp( App::FrameTime );

	QuackVMCallStep();
	
	// *** //
	App::StepProfiler.Stop();

	App::MySkel.Step();
}
// - ------------------------------------------------------------------------------------------ - //
void AppDraw() {
	App::DrawProfiler.Start();	
	// *** //
	QuackVMCallDraw();
	// *** //
	App::DrawProfiler.Stop();
		
	App::MySkel.Draw( App::InfoMatrix );

	// Show Runtime Error Notices //
	if ( QuackVMGetError() ) {
		App::HadVMError = true;
		Vector3D MessagePos = Vector3D(-256,+256,0);
		MessagePos.y /= App::AspectRatio;
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, Real(1), GEL_RGB(255,128,128), GEL_ALIGN_TOP_LEFT,
			"Runtime Error Detected (see log). Execution Stopped.");
	}
	else if ( App::HadVMError ) {
		Vector3D MessagePos = Vector3D(-256,+256,0);
		MessagePos.y /= App::AspectRatio;
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, Real(1), GEL_RGB(255,128,128), GEL_ALIGN_TOP_LEFT,
			"*");			
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void AppGainFocus() {
	App::GainFocus();
	// Only Call this code if we have actually finished running VMInit() //
	if ( App::AppStarted ) {
		QuackVMClearError();
		Gel::AssetPool.ScanForChanges();
		QuackVMCallGainFocus();
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AppLoseFocus() {
	// Only Call this code if we have actually finished running VMInit() //
	if ( App::AppStarted ) {
		QuackVMCallLoseFocus();
	}
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
