// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <Search/Search.h>
#include <Render/Render.h>

#include "App.h"
// - ------------------------------------------------------------------------------------------ - //
#include <squirrel.h> 
#include <sqstdio.h> 
#include <sqstdaux.h> 
// - ------------------------------------------------------------------------------------------ - //
using namespace Texture;
using namespace Render;
// - ------------------------------------------------------------------------------------------ - //
//TextureHandle Texas;
extern cFont* Font;
cFont* Font;

DataBlock* NutFile;
//cRenderTarget* RT_Main;
//cUberShader* BlurShader;
// - ------------------------------------------------------------------------------------------ - //
void PrintFunc(HSQUIRRELVM v, const SQChar *s, ...) {
	char Dummy[4096];
	va_list arglist; 
	va_start(arglist, s); 
	vsprintf(Dummy, s, arglist);
	Log(Dummy);
	va_end(arglist); 
} 
// - ------------------------------------------------------------------------------------------ - //
void ErrorFunc(HSQUIRRELVM v, const SQChar *s, ...) {
	char Dummy[4096];
	va_list arglist; 
	va_start(arglist, s); 
	vsprintf(Dummy, s, arglist);
	Log(Dummy);
	va_end(arglist); 
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger SeaFunction(HSQUIRRELVM vm) {
	Log("I was called. I am C code.");
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
void RegisterSqFunction( HSQUIRRELVM vm, SQFUNCTION fn, const char* fname ) {
	sq_pushroottable(vm);
	
	sq_pushstring(vm,fname,-1);
	sq_newclosure(vm,fn,0);		// create a new function
	sq_newslot(vm,-3,SQFalse);	// VM, Stack Pos, RetVal //
	
	sq_pop(vm,1);				// pops the root table
}
// - ------------------------------------------------------------------------------------------ - //
void CallSqFunction( HSQUIRRELVM vm, const char* fname ) {
	sq_pushroottable(vm);
	
	sq_pushstring(vm,fname,-1);
	sq_get(vm,-2);
	sq_pushroottable(vm);			// this //
	// Push Other Arguments Here //
	
	sq_call(vm,1,SQFalse,SQFalse);	// VM, Arg Count (including this), Push RetVal on Stack, On Error Call Handlers //
	
	sq_pop(vm,2);					// Root Table and Function //
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
cApp::cApp() {
	Search::AddDirectory( "project/" );
	
	Font = new cFont( Search::Search( "C64Pro.fnt" ) );

	// TODO: On some sort of resize event, trigger a delete and recreation of the RenderTargets.		
	int Width = Screen::Native[0].GetWidth();
	int Height = Screen::Native[0].GetHeight();
//	int Width = Screen::Native[0].GetActualWidth();
//	int Height = Screen::Native[0].GetActualHeight();
/*
	RT_Main = new cRenderTarget( Width, Height, 1,0,0 );
	RT_Blur[0] = new cRenderTarget( Width>>2, Height>>2, 1,0,0 );
	RT_Blur[1] = new cRenderTarget( Width>>2, Height>>2, 1,0,0 );
		
	PPShader = new cUberShader( Search::Search("PPEdgeBlend.json") );
	BlurShader = new cUberShader( Search::Search("PostProcess.json") );

	animationTime = 0;
//	try 
	{
		//ifstream atlasFile("../data/spineboy.atlas");
		DataBlock* Data = new_read_DataBlock( Search::Search("spineboy.atlas") );		
		atlas = new spine::Atlas( (const char*)Data->Data, (const char*)(Data->Data+Data->Size) );
		delete_DataBlock( Data );

		spine::SkeletonJson skeletonJson(atlas);

//		ifstream skeletonFile("../data/spineboy-skeleton.json");
		Data = new_read_DataBlock( Search::Search("spineboy-skeleton.json") );		
		skeletonData = skeletonJson.readSkeletonData( (const char*)Data->Data, (const char*)(Data->Data+Data->Size) );
		delete_DataBlock( Data );

//		ifstream animationFile("../data/spineboy-walk.json");
		Data = new_read_DataBlock( Search::Search("spineboy-walk.json") );		
		animation = skeletonJson.readAnimation( (const char*)Data->Data, (const char*)(Data->Data+Data->Size), skeletonData);
		delete_DataBlock( Data );

		skeleton = new spine::Skeleton(skeletonData);
		skeleton->flipX = false;
		skeleton->flipY = true;
		skeleton->setToBindPose();
		skeleton->getRootBone()->x = -180;
		skeleton->getRootBone()->y = -70;
		skeleton->updateWorldTransform();
	}

	Project = new cProjectPuck();*/
	
	vm = sq_open(1024);	// Stack Size //
	sq_setprintfunc( vm, PrintFunc, ErrorFunc ); //sets the print function
	sqstd_seterrorhandlers(vm);	

	sq_pushroottable(vm); //push the root table(were the globals of the script will be stored)
	
	RegisterSqFunction( vm, SeaFunction, "SeaFunction" );
	
	NutFile = new_read_DataBlock( Search::Search("main.nut") );
		
	if( SQ_SUCCEEDED(sq_compilebuffer(vm, NutFile->Data, NutFile->Size, "main.nut", true)) ) {
		sq_push(vm,-2);
		if ( SQ_SUCCEEDED(sq_call(vm,1,false,SQTrue)) ) {
			// Success, and closure removed //
		}
		else {
			sq_pop(vm,1); // removes the closure
		}
	}

	//Log("* Nut: %s", Search::Search("main.nut") );
}
// - ------------------------------------------------------------------------------------------ - //
cApp::~cApp() {
	delete_DataBlock( NutFile );
	
	// Cleanup //
	sq_pop(vm,1); //pops the root table

	sq_close(vm);
	
	
//	delete BlurShader;
//	delete RT_Main;
	
	delete Font;
	
//	delete_TextureHandle( Texas );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
void cApp::Step( ) {
//	Project->Step();
	CallSqFunction( vm, "Step" );
}
// - ------------------------------------------------------------------------------------------ - //
void cApp::Draw( Screen::cNative& Native ) {	
	Matrix4x4 Matrix = Matrix4x4::Identity;
	Matrix(0,0) = 1.0f / (float)Native.GetWidth();//1.0f/(2.0f);
	Matrix(1,1) = 1.0f / (float)Native.GetHeight();//1.0f/(2.0f * Native.GetAspectRatio());

	// Draw Text //
	{
		ViewMatrix = Matrix;

		Matrix4x4 LocalMatrix = Matrix4x4::Identity;
		LocalMatrix(0,0) = (4)*2;
		LocalMatrix(1,1) = (4)*2;

		ViewMatrix *= LocalMatrix;
	}


	Render::EnableAlphaBlending();

	extern cFont* Font;
	Font->printf( Vector3D(0,0,0), 32.0f, GEL_ALIGN_MIDDLE_CENTER, "I want bacon" );

	CallSqFunction( vm, "Draw" );
}
// - ------------------------------------------------------------------------------------------ - //
