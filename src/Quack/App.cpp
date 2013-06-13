// - ------------------------------------------------------------------------------------------ - //
#include <Style/Style.h>

#include <Search/Search.h>
#include <Render/Render.h>
#include <Input/Input.h>
#include <Generate/Vertex.h>
#include <Graphics/Graphics_Buffer.h>	// gelClear

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

// - ------------------------------------------------------------------------------------------ - //
void sqslot_bool(HSQUIRRELVM vm, const char* name, SQBool value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushbool(vm,value);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
void sqslot_int(HSQUIRRELVM vm, const char* name, SQInteger value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushinteger(vm,value);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
void sqslot_float(HSQUIRRELVM vm, const char* name, SQFloat value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushfloat(vm,value);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //
void sqslot_string(HSQUIRRELVM vm, const char* name, const char* value ) {
	sq_pushstring(vm,name,-1); // VM, Text, Length (-1 for auto) //
	sq_pushstring(vm,value,-1);
	sq_newslot(vm,-3,SQFalse);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkGetPad(HSQUIRRELVM vm) {
	int Index = 0;
	int NumArgs = sq_gettop(vm);
	if ( NumArgs > 0 ) {
		sq_getinteger(vm,2,&Index);
		if ( (Index > 3) || (Index < 0) ) {
			sq_newtable(vm);	// Error //
			return 1;
		}
	}
	
	// Create a new table to store the data we want to return //
	sq_newtable(vm);
	
	sqslot_int(vm,"Index", Index);
	sqslot_bool(vm,"Connected", Input::XInput::IsConnected(Index));
	sqslot_int(vm,"Button", Input::XInput::GamePad[Index].Button);
	sqslot_float(vm,"LTrigger", Input::XInput::GamePad[Index].LTrigger);
	sqslot_float(vm,"RTrigger", Input::XInput::GamePad[Index].RTrigger);

	// LStick //			
	sq_pushstring(vm,"LStick",-1);
	sq_newtable(vm);
	sqslot_float(vm,"x", Input::XInput::GamePad[Index].LStick.x.ToFloat());
	sqslot_float(vm,"y", Input::XInput::GamePad[Index].LStick.y.ToFloat());		
	sq_newslot(vm,-3,SQFalse);

	// RStick //			
	sq_pushstring(vm,"RStick",-1);
	sq_newtable(vm);
	sqslot_float(vm,"x", Input::XInput::GamePad[Index].RStick.x.ToFloat());
	sqslot_float(vm,"y", Input::XInput::GamePad[Index].RStick.y.ToFloat());		
	sq_newslot(vm,-3,SQFalse);

	return 1;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkClear(HSQUIRRELVM vm) {
	gelClear( true, true );
	return 0;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDrawCircle(HSQUIRRELVM vm) {
	float Radius = 10.0f;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	
	SQUserPointer uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		sq_getuserdata(vm,2,&uMatrix,NULL);

		int Elements = sq_getsize(vm,3);
		if ( Elements >= 1 ) {
			sq_pushinteger(vm,0);	// Push the desired array Index //
			sq_get(vm,3);			// Get the value from an array found at stack pos //
			sq_getfloat(vm,-1,&x);
			sq_pop(vm,1);
		}
		if ( Elements >= 2 ) {
			sq_pushinteger(vm,1);	// Push the desired array Index //
			sq_get(vm,3);			// Get the value from an array found at stack pos //
			sq_getfloat(vm,-1,&y);
			sq_pop(vm,1);
		}
		if ( Elements >= 3 ) {
			sq_pushinteger(vm,2);	// Push the desired array Index //
			sq_get(vm,3);			// Get the value from an array found at stack pos //
			sq_getfloat(vm,-1,&z);
			sq_pop(vm,1);
		}
		
		if ( NumArgs >= 4 ) {
			sq_getfloat(vm,4,&Radius);
		}
		if ( NumArgs >= 5 ) {
			sq_getinteger(vm,5,&Color);
		}
	
		const st32 VertCount = size_Vertex3D_Circle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Circle( Verts, Vector3D(x,y,z), Real(Radius) );
	
		Render::Flat( GEL_LINE_LOOP, *((Matrix4x4*)uMatrix), Color, Verts, VertCount );
	}
	else {
		Log("! qkDrawCircle -- Not enough arguments");
	}
	
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
void CallSqMatrixFunction( HSQUIRRELVM vm, const char* fname, const Matrix4x4& Matrix ) {
	sq_pushroottable(vm);
	
	sq_pushstring(vm,fname,-1);
	sq_get(vm,-2);
	sq_pushroottable(vm);			// this //
	// Push Other Arguments Here //
	SQUserPointer uPtr = sq_newuserdata(vm,sizeof(Matrix));
	Matrix4x4* mPtr = (Matrix4x4*)uPtr;
	(*mPtr) = Matrix;
	
	sq_call(vm,2,SQFalse,SQFalse);	// VM, Arg Count (including this), Push RetVal on Stack, On Error Call Handlers //
	
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
	
	RegisterSqFunction( vm, qkGetPad, "qkGetPad" );
	RegisterSqFunction( vm, qkClear, "qkClear" );
	RegisterSqFunction( vm, qkDrawCircle, "qkDrawCircle" );
	
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
	
	CallSqFunction( vm, "Init" );
}
// - ------------------------------------------------------------------------------------------ - //
cApp::~cApp() {
	CallSqFunction( vm, "Exit" );

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

	CallSqMatrixFunction( vm, "Draw", ViewMatrix );
}
// - ------------------------------------------------------------------------------------------ - //
