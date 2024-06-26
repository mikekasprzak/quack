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

#include "Engine/Engine.h"
#include "GelSync/GelSync.h"

#include "GelLayout/GelLayout.h"
// - ------------------------------------------------------------------------------------------ - //
namespace App {
// - ------------------------------------------------------------------------------------------ - //
int Mode = AM_NULL;
bool Debug = false;
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
GelTime FrameTime = 0;	// Time in Frames //
GelTime WorkTime = 0;	// Time is usec //
int FPS = 0;			// How many actual frames were rendered in a second //
// - ------------------------------------------------------------------------------------------ - //
GelProfiler StepProfiler;
GelProfiler DrawProfiler;
GelProfiler SqStepProfiler;
GelProfiler SqDrawProfiler;
// - ------------------------------------------------------------------------------------------ - //
bool AppStarted = false;	// Flag that is set only after Init is called (for the these Focus functions).
GelSignal GainFocus;
GelSignal LoseFocus;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
GelFontPool::UID RuntimeErrorFont = 0;
Real AspectRatio;

Matrix4x4 InfoMatrix;
Rect2D InfoView;

bool HadVMError;
// - ------------------------------------------------------------------------------------------ - //
//QK::QEngine* Engine;
QK::QEmitter* Emitter;
//QK::QSky* Sky;

#ifdef USES_GELNET
GelNet*		Net;
GelSync*	Sync;
#endif //USES_GELNET //

//GelLayout	Layout;
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
	App::WorkTime = 0;

	// **** //

	gelTimeInit();
	gelSystemInit();
	init_GelDirectory();
	gelAssetInit();
	gelTextureInit();
	gelFontInit();
	gelAtlasInit();
	gelSkelInit();
	gelModelInit();
	Gel::Input::Init();
	
	// **** //

#if __NACL__
	Log("* NACL Mount");
	
    SDL_NaClUmount("/");
    SDL_NaClMount(
        "",  /* source */
        "/",  /* target */
        "httpfs",  /* filesystemtype */
        0,  /* mountflags */
        "");  /* data specific to the html5fs type */
#endif    

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

	Real UIScale( 256.0f );

	bool WideRatio = App::AspectRatio < 1.0;
	Vector2D AspectVec(App::AspectRatio,1.0);
	if ( WideRatio )
		AspectVec = Vector2D(1.0,Real(1.0)/App::AspectRatio);

	App::InfoMatrix = Matrix4x4::Identity;
	App::InfoMatrix[0] = Real::One / UIScale / AspectVec.x;
	App::InfoMatrix[5] = Real::One / UIScale / AspectVec.y;
	App::InfoMatrix[10] = Real::One / UIScale;
	App::InfoMatrix[15] = Real::One;

	Vector2D UIViewVec = AspectVec * UIScale;
	App::InfoView = Rect2D(-UIViewVec.x,-UIViewVec.y, UIViewVec.x+UIViewVec.x,UIViewVec.y+UIViewVec.y);

	// **** //

	App::Emitter = new QK::QEmitter( "ItemIcons.atlas" );
//	App::Sky = new QK::QSky();

#ifdef USES_GELNET
	App::Net = new GelNet();
	App::Sync = new GelSync();
	App::Sync->Bind(App::Net);
#endif //USES_GELNET //

//	{
//		Log("**** GLAYOUT");
//		App::Layout.Root.SetFlags();
//		//App::Layout.Root.Data.SetType( Gel::UI_BOX );		
//		App::Layout.Root.SetPos(-64,-64);
//		App::Layout.Root.SetShape(128,128);
//
//		App::Layout.Root.AddChild( GLAY_MIDDLE | GLAY_RIGHT );
//		App::Layout.Root.Child.back().SetShape(32,32);
//
//		App::Layout.Root.Child.back().AddChild( GLAY_DEFAULT, GelLayoutNodeData( Gel::GLO_IMAGE, "ItemIcons.atlas:IconFish" ) );
//		App::Layout.Root.Child.back().Child.back().SetShape(2,2);
//
//		App::Layout.Root.AddChild( GLAY_TOP | GLAY_CENTER, GelLayoutNodeData( Gel::GLO_TEXT, "Chicken Tonight!" ) );
//		App::Layout.Root.Child.back().SetShape(96,32);
//		App::Layout.Root.Child.back().Data.SetFont( "Fontin.fnt" );
//		App::Layout.Root.Child.back().Data.SetFontSize(16);
//
////		App::Layout.Root.AddChild( GLAY_BOTTOM | GLAY_CENTER, GelLayoutNode( Gel::GLO_TEXT, "Hockey Tomorrow!" ) );
////		App::Layout.Root.Child.back().SetShape(64,32);
////		App::Layout.Root.Child.back().Data.SetFont( "Arial.fnt" );
//
////		App::Layout.Root.Child.back().AddChild();
////		App::Layout.Root.Child.back().AddChild();
////		App::Layout.Root.Child.back().Child.back().SetShape(4,2);
////		App::Layout.Root.Child.back().AddChild();
//
////		App::Layout.Root.AddChild( GLAY_FILL );
////		App::Layout.Root.Child.back().SetPos(10,10);
////		App::Layout.Root.Child.back().SetShape(60,30);
////		App::Layout.Root.Child.back().AddEmptyChild();
////		App::Layout.Root.Child.back().AddEmptyChild();
////		App::Layout.Root.Child.back().AddChild();
////		App::Layout.Root.Child.back().AddEmptyChild();
////		App::Layout.Root.Child.back().AddChild().SetShape(8,4);
////		App::Layout.Root.Child.back().Child.back().SetPos(1,0);
////		App::Layout.Root.Child.back().AddEmptyChild();		
//		App::Layout.Update();
//
////		GlayPoint Pos = App::Layout.Root.Child.back().Child.back().GetPos();
////		GlayPoint Shape = App::Layout.Root.Child.back().Child.back().GetShape();
////		Log("Pos: (%f, %f) (%f, %f)", Pos.x, Pos.y, Shape.x, Shape.y);
//		
//		Log("**** DONE");
//	}
}
// - ------------------------------------------------------------------------------------------ - //
void AppExit() {
//	delete App::Engine;

#ifdef USES_GELNET
	delete App::Net;
	delete App::Sync;
#endif //USES_GELNET //

	delete App::Emitter;

	/***/

	QuackVMCallExit();
	
	Gel::Input::Exit();
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
	extern bool KeyF5;
	extern bool KeyF6;
	extern bool KeyF7;
	extern bool KeyF8;
};
// - ------------------------------------------------------------------------------------------ - //
void AppStep() {
	App::StepProfiler.Start();
	// *** //

	static bool OldKeyF5 = false;
	static bool OldKeyF6 = false;
	static bool OldKeyF7 = false;
	static bool OldKeyF8 = false;
	static bool KeyF5 = false;
	static bool KeyF6 = false;
	static bool KeyF7 = false;
	static bool KeyF8 = false;
	OldKeyF5 = KeyF5;
	OldKeyF6 = KeyF6;
	OldKeyF7 = KeyF7;
	OldKeyF8 = KeyF8;
	KeyF5 = Gel::KeyF5;
	KeyF6 = Gel::KeyF6;
	KeyF7 = Gel::KeyF7;
	KeyF8 = Gel::KeyF8;
	
	Gel::Input::Poll();
	
	// If the Refresh key is pressed (NOTE: this should be 'just pressed' state) //
	if ( Gel::KeyRefresh ) {
		QuackVMCallInit();
	}
	
#ifdef USES_GELNET
	if ( KeyF5 && !OldKeyF5 ) {
		App::Net->Start( true );
	}
	if ( KeyF6 && !OldKeyF6 ) {
		App::Net->Start( false );
//		App::Net->ConnectLocal();
		App::Net->Connect("localhost");
	}
	if ( KeyF7 && !OldKeyF7 ) {
		Log("+ Enet Peer List");
		App::Net->LogPeers();
		Log("- End of Peer List");
	}
	if ( KeyF8 && !OldKeyF8 ) {
		// Can't do this after Net.Connect(). Connection isn't open yet. //
		//App::Sync->SendSync();
	}
	
	App::Sync->Step();
	App::Net->Step();
#endif //USES_GELNET //

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

	App::SqStepProfiler.Start();
	QuackVMCallStep();
	App::SqStepProfiler.Stop();

//	App::Engine->Step();

	App::Emitter->Step();
//	App::Sky->Step();
	
	static float boof = 0.0f;
	boof += 0.2f;
	
	QK::QParticle* Me = App::Emitter->Add( 128, Vector2D::Zero, ((int)(boof*(1.0/0.2)))%6 );
	Me->Shape = Vector2D(2,2);
		
	Me->Velocity = Vector2D(cos(boof),sin(boof)) * Real(4 + (sin(boof*3.2f)*2.0f));
	Me->ColorVelocity = GEL_SRGBA(-256*1,-256*1,-256*1,-256*1);
	Me->Orientation = Vector2D(sin(boof*3412.0f),-cos(boof*3412.0f));
	
	Me->AngularVelocity = Real(sin(boof)*0.125f);
	Me->ShapeVelocity = Vector2D(sin(boof*411.0f)*0.02f,sin(boof*411.0f)*0.02f);
	
	// *** //
	App::StepProfiler.Stop();
}
// - ------------------------------------------------------------------------------------------ - //
void AppDraw() {
	App::DrawProfiler.Start();
	App::SqDrawProfiler.Start();	
	// *** //
	QuackVMCallDraw();
	// *** //
	App::SqDrawProfiler.Stop();

//	App::Engine->Draw( Rect2D(-128,-128,256,256), App::InfoMatrix );

//	App::Sky->Draw( Rect2D(-128,-128,256,256), App::InfoMatrix );
//	App::Emitter->Draw( Rect2D(-128,-128,256,256), App::InfoMatrix );

//	App::Layout.Draw( App::InfoMatrix );

	// Show Runtime Error Notices //
	if ( QuackVMGetError() ) {
		App::HadVMError = true;
		Vector3D MessagePos = Vector3D(-256+4,+256-4,0);
//		MessagePos.y /= App::AspectRatio;
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, Real(1), GEL_RGB(255,64,64), GEL_ALIGN_TOP_LEFT,
			"Runtime Error Detected (see log). Execution Stopped.");
	}
	else if ( App::HadVMError ) {
		Vector3D MessagePos = Vector3D(-256+4,+256-4,0);
//		MessagePos.y /= App::AspectRatio;
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, Real(1), GEL_RGB(255,64,64), GEL_ALIGN_TOP_LEFT,
			"*");			
	}

	// Draw FPS Counter //
	if ( App::Debug ) {		
//		Vector3D MessagePos = Vector3D(+256-4,+256-4,0);
//		MessagePos.y /= App::AspectRatio;

		Vector3D MessagePos = (App::InfoView.P2() - Vector2D(4,4)).ToVector3D();
			
		GelColor Color = GEL_RGB(255,255,255);
		GelAlign Align = GEL_ALIGN_TOP_RIGHT;
		Real YStep(24);
		Real FontSize(24);
		float PercentConstant = (float)(1000000.0f/60.0f) / 100.0f;

		gelDrawRect( 
			App::InfoMatrix,
			Vector2D(-256,-256).ToVector3D(),
			Vector2D(512,512), 
			GEL_RGBA(128,0,0,128)
		);
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, FontSize, Color, Align,
			"FPS: %i (%02i:%02i:%02i [%02i] - %llu)", App::FPS, App::FrameTime/60/60/60, App::FrameTime/60/60%60, App::FrameTime/60%60, App::FrameTime%60, App::FrameTime);
				
		MessagePos.y -= YStep;
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, FontSize, Color, Align,
			"Step [Sq]: %.2f%% - %ius [%ius,%ius]", 
			App::SqStepProfiler.GetAverage() / PercentConstant,
			App::SqStepProfiler.GetAverage(),App::SqStepProfiler.GetMin(),App::SqStepProfiler.GetMax());
		MessagePos.y -= YStep;
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, FontSize, Color, Align,
			"Step: %.2f%% - %ius [%ius,%ius]", 
			App::StepProfiler.GetAverage() / PercentConstant,
			App::StepProfiler.GetAverage(),App::StepProfiler.GetMin(),App::StepProfiler.GetMax());
		MessagePos.y -= YStep;		
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, FontSize, Color, Align,
			"Draw [Sq]: %.2f%% - %ius [%ius,%ius]", 
			App::SqDrawProfiler.GetAverage() / PercentConstant,
			App::SqDrawProfiler.GetAverage(),App::SqDrawProfiler.GetMin(),App::SqDrawProfiler.GetMax());
		MessagePos.y -= YStep;		
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, FontSize, Color, Align,
			"Draw: %.2f%% - %ius [%ius,%ius]", 
			App::DrawProfiler.GetAverage() / PercentConstant,
			App::DrawProfiler.GetAverage(),App::DrawProfiler.GetMin(),App::DrawProfiler.GetMax());
	}
	App::DrawProfiler.Stop();
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
