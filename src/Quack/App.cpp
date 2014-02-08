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

#include "Glayout/Glayout.h"
#include <Array/Array.h>
#include "Generator/Generator.h"
#include "Seed/VtTree.h"

#include "NewGrid/NewGrid.h"
#include <TiledMap/GelTiledMap.h>
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
bool HadVMError;
// - ------------------------------------------------------------------------------------------ - //
//GelSkelPool::UID	SpineUID;
//spSkeleton*				SpineSkeleton;
//spAnimationState*		SpineAnimState;
//GelSkelAnimator MySkel;
//GelAtlasPool::UID MyAtlasID;
	
GlayLayout Layout;

GelVert2 InCurve;
GelVert2C OutCurve;

VtTree InTree;
GelVert2C OutTree;

GelGrid<u8> TestMap;
GelVert2C OutTestMap;
GelGrid<u16> MapBlobs;

GelVert2 OrigBesier;
GelVert2 InBesier;
GelVert2 OutBesier;
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
	App::InfoMatrix[10] = Real::One;
	App::InfoMatrix[15] = Real::One;

	// **** //

//	{	
//		Log("**** LOADING POD");
//		GelModelPool::UID MyUID = Gel::ModelPool.Load( "project/content/Cube.pod" );
//		
//		Log("**** DONE");
//	}

//	{	
//		Log("**** LOADING SPINE");
//		App::MySkel.Load( Gel::SkelPool.Load( "Creature/QuadrupedA.json" ) );//"SpineTest/spineboy.json" ) );
////		App::SpineUID = Gel::SkelPool.Load( "SpineTest/spineboy.json" );
////		App::SpineSkeleton = spSkeleton_create( Gel::SkelPool[App::SpineUID].GetSkeletonData() );
////		App::SpineAnimState = spAnimationState_create(0);//stateData);
////			
////		spAnimation* Animation = spSkeletonData_findAnimation( App::SpineSkeleton->data, "walk");
////		spAnimationState_setAnimation( App::SpineAnimState, 0, Animation, true );
//
//		App::MySkel.Set( "Walk" );//"walk" );
//		Log("**** DONE");
//	}

//	{
//		Log("**** LOADING ATLAS");
//		App::MyAtlasID = Gel::AtlasPool.Load( "ItemIcons.atlas" );
//		//App::MySkel.Set( "Walk" );//"walk" );
//		Log("**** DONE");		
//	}

/*
	{
		Log("**** GelVert, GelAlloc, GelParticle");
//		GelVert2 Scrot(4);
//		Scrot[0].Pos = Vector2D(10,10);
//		Scrot.PushBack();
//		Scrot.Back().Pos.x = Real(14);
//		
//		GelVert2::Type Verr = Scrot[4];
//		Log("Verr [%i]: %f", Scrot.Size(), Verr.Pos.x.ToFloat() );
		
		GelAlloc2 Norb(4);	
		Log("Norb: %i (%i) [%i]", Norb.MaxSize(), Norb.Size(), Norb.GetUsed());
		
		Norb.Next();
		Norb->Pos = Vector2D(1,-1);
		Norb.Next();
		Norb->Pos = Vector2D(2,-2);
		Norb.Next();
		Norb->Pos = Vector2D(3,-3);
		Norb.Next();
		Norb->Pos = Vector2D(4,-4);
		Norb.Next();
		Norb->Pos = Vector2D(5,-5);
		Norb.Next();
		Norb->Pos = Vector2D(6,-6);
		
		for ( int idx = 0; idx < Norb.Size(); idx++ ) {
			Log("%i -- %f,%f", idx, Norb[idx].Pos.x.ToFloat(), Norb[idx].Pos.y.ToFloat() );
		}

		Log("Norb: %i (%i) [%i]", Norb.MaxSize(), Norb.Size(), Norb.GetUsed());
		
		GelParticle<GelVertex2> Pork(4);
		Log("Pork: %i -- %i [%i]", Pork.Size(), Pork.Living(), Pork.Oldest());
		
		Pork.Add(4);
		Pork->Pos = Vector2D(1,-1);
		Pork.Add(5);
		Pork->Pos = Vector2D(2,-2);
		Pork.Add(2);
		Pork->Pos = Vector2D(3,-3);

		while ( Pork.Living() ) {
			Log("Pork: %i -- %i [%i]", Pork.Size(), Pork.Living(), Pork.Oldest());
			for ( int idx = 0; idx < Pork.Size(); idx++ ) {
				if ( Pork.IsAlive(idx) ) {
					Log("%i [%i] -- %f,%f", idx, Pork.Life(idx), Pork[idx].Pos.x.ToFloat(), Pork[idx].Pos.y.ToFloat() );
				}
			}
			
			if ( Pork.GetTime() == 3 ) {
				Log("** NEW **");
				Pork.Add(4);
				Pork->Pos = Vector2D(4,-4);
			}
			if ( Pork.GetTime() == 4 ) {
				Log("** NEW **");
				Pork.Add(4);
				Pork->Pos = Vector2D(5,-5);
			}
			if ( Pork.GetTime() == 5 ) {
				Log("** NEW MANY **");
				Pork.Add(2);
				Pork->Pos = Vector2D(6,-6);
				Pork.Add(1);
				Pork->Pos = Vector2D(7,-7);
				Pork.Add(2);
				Pork->Pos = Vector2D(8,-8);
			}
			if ( Pork.GetTime() == 6 ) {
				Log("** NEW **");
				Pork.Add(4);
				Pork->Pos = Vector2D(9,-9);
			}
			
			Pork.Step();
		};
		Log("Pork: %i -- %i [%i]", Pork.Size(), Pork.Living(), Pork.Oldest());
		
		
		Log("**** DONE");
	}
*/

	{
		Log("**** Curve Generator");
		for ( int idx = -4; idx < 8; idx++ ) {
			int Scale = idx;
			if ( Scale < 0 )
				Scale *= -Scale;
			App::InCurve.PushBack().Pos = Vector2D(0,idx*(20-Scale));
		}
		
		Gen_SpecialCurve( App::InCurve, App::OutCurve );

//		for ( st idx = 0; idx < App::OutCurve.Size(); idx++ ) {
//			Log("%i -- %f,%f", idx, App::OutCurve[idx].Pos.x.ToFloat(),App::OutCurve[idx].Pos.y.ToFloat());
//			if ( (idx % 6) == 5 )
//				Log("");
//		}
	
		Log("**** DONE");
	}
	
	{
		Log("**** Besier Generator");
		GelVert2& OB = App::OrigBesier;
		OB.Resize(4);
		OB[0].Pos = Vector2D(0,0);
		OB[1].Pos = Vector2D(50,50);
		OB[2].Pos = Vector2D(-120,100);
		OB[3].Pos = Vector2D(0,120);
		
		const int Count = 6;	
		for ( int idx = 0; idx <= Count; idx++ ) {
			App::InBesier.PushBack().Pos = Calc_Curve( Real(idx/(float)Count), OB[0].Pos, OB[1].Pos, OB[2].Pos, OB[3].Pos );
//			App::InBesier.PushBack().Pos = OB[0].Pos + (Real(idx/(float)Count) * (OB[3].Pos - OB[0].Pos) );
		}
		
		Gen_Curve( App::OutBesier, App::InBesier, Real(14), Real(1) );
		Log("**** DONE");
	}


	{
		Log("**** Tree Generator");
		
		Gen_VtTree( App::InTree );
		Gen_GelVert2C_from_GelTree( App::OutTree, App::InTree );
		// Gen_Curve_GelVert2C_from_GelTree
	
		Log("**** DONE");
	}


	{
		Log("**** Grid Generator");

		//GelTileMap MyMap("Blah.map"); // Use Search and Asset, but no Pool //
		//Gen_TileMap_GelVert2U_from_GelGrid( App::OutMap, MyMap.Layer[0], TileWidth, TileHeight );
		
		GelGrid<st8> MyMap;
		GelImage Mimage( "TestFileNoAlpha.png" );
		
		Log("MIMA: %i, %i (%i)", Mimage.Width(), Mimage.Height(), Mimage.BPP() );
		Log("GRID: %i, %i", MyMap.Width(), MyMap.Height() );
		
		Gen_GelGrid_from_GelImage( MyMap, Mimage ); 

		Log("GRID: %i, %i", MyMap.Width(), MyMap.Height() );

//		for( int y = 0; y < MyMap.Height(); y++ ) {
//			for( int x = 0; x < MyMap.Width(); x++ ) {
//				_Log("%02X", (int)MyMap(x,y) );
//			}		
//			Log("");
//		}
		
		GelSubGrid<st8> SubMap = MyMap.GetSubGrid( 60,60, 12,12 );

		Log("SUBGRID: %i, %i", SubMap.Width(), SubMap.Height() );
		
		for( int y = 0; y < SubMap.Height(); y++ ) {
			for( int x = 0; x < SubMap.Width(); x++ ) {
				_Log("%02X", (int)SubMap(x,y) );
			}		
			Log("");
		}
		
		Log("**** DONE");
	}

	{
		Log("**** TILED MAP");

		GelTiledMap MyTiledMap;
		MyTiledMap.Load("WorldMap.json");

		Log("**** DONE");
	}
	
	{
		Log("**** GLAYOUT");
		App::Layout.Root.SetPos(128+16,-128);
		App::Layout.Root.SetShape(100,100);
		App::Layout.Root.AddChild( GLAY_FILL_WIDTH );
		App::Layout.Root.Child.back().SetPos(40,60);
		App::Layout.Root.Child.back().SetShape(20,20);
		App::Layout.Root.Child.back().AddChild();
		App::Layout.Root.Child.back().AddChild();
		App::Layout.Root.Child.back().Child.back().SetShape(4,2);
		App::Layout.Root.Child.back().AddChild();

		App::Layout.Root.AddChild( GLAY_FILL );
		App::Layout.Root.Child.back().SetPos(10,10);
		App::Layout.Root.Child.back().SetShape(60,30);
		App::Layout.Root.Child.back().AddEmptyChild();
		App::Layout.Root.Child.back().AddEmptyChild();
		App::Layout.Root.Child.back().AddChild();
		App::Layout.Root.Child.back().AddEmptyChild();
		App::Layout.Root.Child.back().AddChild().SetShape(8,4);
		App::Layout.Root.Child.back().Child.back().SetPos(1,0);
		App::Layout.Root.Child.back().AddEmptyChild();		
		App::Layout.Update();

		GlayPoint Pos = App::Layout.Root.Child.back().Child.back().GetPos();
		GlayPoint Shape = App::Layout.Root.Child.back().Child.back().GetShape();
		Log("Pos: (%f, %f) (%f, %f)", Pos.x, Pos.y, Shape.x, Shape.y);
		
		Log("**** DONE");
	}
	
	{
		GelGrid<GelColor> DummyMap;
		GelImage ImageMap( "MapTest.png" );
		
		Gen_GelGrid_from_GelImage( DummyMap, ImageMap ); 
		App::TestMap.Resize( DummyMap.Width(), DummyMap.Height() );
		
		// Convert Map //
		for ( st idx = 0; idx < DummyMap.Size(); idx++ ) {
			if ( GEL_GET_R(DummyMap[idx]) > 192 ) {
				// DIRT //
				App::TestMap[idx] = 1;
			}
			else if ( GEL_GET_G(DummyMap[idx]) > 192 ) {
				// GRASS //
				App::TestMap[idx] = 2;
			}
			else {
				App::TestMap[idx] = 0;
			}
		}
		
//		GelSubGrid<u8> SubMap = App::TestMap.GetSubGrid(400,550,160,90);
		GelSubGrid<u8> SubMap = App::TestMap.GetSubGrid(400,580,80,50);
		
		BlobExtract_EQ_from_GelGrid( App::MapBlobs, SubMap, 2 );
		for( int y = 0; y < App::MapBlobs.Height(); y++ ) {
			for( int x = 0; x < App::MapBlobs.Width(); x++ ) {
				_Log("%01X", App::MapBlobs(x,y)&0xf );
			}		
			Log("");
		}		
		
		// Generate Geometry //
		App::OutTestMap.Clear();
		Real StepX(2);
		Real StepY(2);
		Vector2D Offset(SubMap.HalfWidth(),SubMap.HalfHeight());
		for ( st y = 0; y < SubMap.Height(); y++ ) {
			for ( st x = 0; x < SubMap.Width(); x++ ) {
				int Value = SubMap(x,(SubMap.Height()-1)-y);
				if ( Value > 0 ) {
					GelColor Color = GEL_RGB_MAGENTA;
					if ( Value == 1 )
						Color = GEL_RGB(100,50,40);
					else if ( Value == 2 )
						Color = GEL_RGB_PUKE;
					
					App::OutTestMap.PushBack().Pos = (Vector2D(x+0,y+0) - Offset) * Vector2D(StepX,StepY);
					App::OutTestMap.Back().Color = Color;
					App::OutTestMap.PushBack().Pos = (Vector2D(x+1,y+0) - Offset) * Vector2D(StepX,StepY);
					App::OutTestMap.Back().Color = Color;
					App::OutTestMap.PushBack().Pos = (Vector2D(x+1,y+1) - Offset) * Vector2D(StepX,StepY);
					App::OutTestMap.Back().Color = Color;

					App::OutTestMap.PushBack().Pos = (Vector2D(x+1,y+1) - Offset) * Vector2D(StepX,StepY);
					App::OutTestMap.Back().Color = Color;
					App::OutTestMap.PushBack().Pos = (Vector2D(x+0,y+1) - Offset) * Vector2D(StepX,StepY);
					App::OutTestMap.Back().Color = Color;
					App::OutTestMap.PushBack().Pos = (Vector2D(x+0,y+0) - Offset) * Vector2D(StepX,StepY);
					App::OutTestMap.Back().Color = Color;
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AppExit() {

	/***/

	QuackVMCallExit();
	
	Gel::Input::Exit();
}
// - ------------------------------------------------------------------------------------------ - //

void DrawLayout( const GlayNode& Node ) {
	const st32 VertCount = 4;
	Vector3D Verts[ VertCount ];
	Verts[0].x = Node.GetPos().x;
	Verts[0].y = Node.GetPos().y;
	Verts[1].x = Node.GetPos().x + Node.GetShape().x;
	Verts[1].y = Node.GetPos().y;
	Verts[2].x = Node.GetPos().x + Node.GetShape().x;
	Verts[2].y = Node.GetPos().y + Node.GetShape().y;
	Verts[3].x = Node.GetPos().x;
	Verts[3].y = Node.GetPos().y + Node.GetShape().y;

	Gel::RenderFlat( GEL_LINE_LOOP, App::InfoMatrix, GEL_RGB_PURPLE, Verts, VertCount );
	
	
	for (std::list<GlayNode>::const_iterator Itr = Node.Child.begin(), End = Node.Child.end(); Itr != End; ++Itr) {
		DrawLayout( *Itr );
	}
}

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

	App::SqStepProfiler.Start();
	QuackVMCallStep();
	App::SqStepProfiler.Stop();

	{
		static Real Flow(0);
		Flow += Real(0.01f);
		for ( int idx = 0; idx < App::InCurve.Size(); idx++ ) {
			App::InCurve[idx].Pos.x = Real(200)+(Flow+(Real(idx)*Real(0.1))).Sin() * Real(20-idx);
		}
		App::InCurve[0].Pos.x = App::InCurve[1].Pos.x;
		
		App::OutCurve.Clear();
		Gen_SpecialCurve( App::InCurve, App::OutCurve );
	}
	
//	static int bort = 0;
//	bort++;
//	if ( (bort % 6) == 0 )
	{
//		static Real Nerf(0);
//		Nerf+=Real(0.005);
//		for ( int idx = 1; idx < App::InTree.Size(); idx++ ) {
//			App::InTree[idx].Angle = Vector2D((Nerf+Real(idx)*Real(0.01)).Cos(),1).Normal();
//		}		
		// Step //	
		Step_VtTree( App::InTree );
		Gen_GelVert2C_from_GelTree( App::OutTree, App::InTree );
	}

//#ifdef USES_STEAM
//	if ( Gel::IsSteamRunning ) {
//		static int Boof = 0;
//		Boof++;
//		if ( (Boof & 63) == 0 ) {
//			for (st idx = 0; idx < Gel::Input::Steam::Size(); idx++ ) {
//				if ( Gel::Input::Steam::IsConnected( idx ) ) {
//					Log("%i -- L: %f,%f  R: %f,%f  B:%x",
//						idx, 
//						Gel::Input::Steam::Pad[idx].LStick.x.ToFloat(),
//						Gel::Input::Steam::Pad[idx].LStick.y.ToFloat(),
//						Gel::Input::Steam::Pad[idx].RStick.x.ToFloat(),
//						Gel::Input::Steam::Pad[idx].RStick.y.ToFloat(),
//						Gel::Input::Steam::Pad[idx].Button
//						);
//				}
//			}
//		}
//	}
//#endif // USES_STEAM //

//	App::MySkel.Step();
	
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
	
//	Gel::AtlasPool[App::MyAtlasID].Draw( App::InfoMatrix, 4 );
	
	DrawLayout( App::Layout.Root );
		
//	Gel::RenderColor2D_Packed(GEL_TRIANGLES,App::InfoMatrix,GEL_RGB_WHITE,&(App::OutCurve.Get()->Pos),&(App::OutCurve.Get()->Color),App::OutCurve.Size());
	Gel::RenderColor2D_Packed(GEL_TRIANGLES,App::InfoMatrix,GEL_RGB_WHITE,&(App::OutCurve[6].Pos),&(App::OutCurve[6].Color),App::OutCurve.Size()-6);

	Gel::RenderColor2D_Packed(GEL_TRIANGLES,App::InfoMatrix,GEL_RGB_BLUE,&(App::OutTree[0].Pos),&(App::OutTree[0].Color),App::OutTree.Size());
//	Gel::RenderColor2D_Packed(GEL_LINES,App::InfoMatrix,GEL_RGB_WHITE,&(App::OutTree[0].Pos),&(App::OutTree[0].Color),App::OutTree.Size());

	Gel::RenderColor2D_Packed(GEL_TRIANGLES,App::InfoMatrix,GEL_RGB_WHITE,&(App::OutTestMap[0].Pos),&(App::OutTestMap[0].Color),App::OutTestMap.Size());

	{
		Matrix4x4 Mat = Matrix4x4::Identity;
		Mat *= Matrix4x4::TranslationMatrix( Vector3D(-120,0) );
		Mat *= App::InfoMatrix;
	//	Gel::RenderColor2D_Packed(GEL_TRIANGLES,App::InfoMatrix,GEL_RGB_WHITE,&(App::OutBesier.Get()->Pos),&(App::OutBesier.Get()->Color),App::OutBesier.Size());
		Gel::RenderFlat2D(GEL_TRIANGLES,Mat,GEL_RGB(180,170,255),&(App::OutBesier.Get()->Pos),App::OutBesier.Size());
	}
	
	// Show Runtime Error Notices //
	if ( QuackVMGetError() ) {
		App::HadVMError = true;
		Vector3D MessagePos = Vector3D(-254,+254,0);
		MessagePos.y /= App::AspectRatio;
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, Real(1), GEL_RGB(255,64,64), GEL_ALIGN_TOP_LEFT,
			"Runtime Error Detected (see log). Execution Stopped.");
	}
	else if ( App::HadVMError ) {
		Vector3D MessagePos = Vector3D(-254,+254,0);
		MessagePos.y /= App::AspectRatio;
			
		Gel::FontPool[App::RuntimeErrorFont].printf( 
			App::InfoMatrix, MessagePos, Real(1), GEL_RGB(255,64,64), GEL_ALIGN_TOP_LEFT,
			"*");			
	}

	// Draw FPS Counter //
	{
		Vector3D MessagePos = Vector3D(+254,+254,0);
		MessagePos.y /= App::AspectRatio;
			
		GelColor Color = GEL_RGB(255,255,255);
		GelAlign Align = GEL_ALIGN_TOP_RIGHT;
		Real YStep(12);
		Real FontSize(1);
		float PercentConstant = (float)(1000000/60) / 100.0f;
			
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
