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
#include <SkelMesh/SkelMesh.h>
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
GelSkelMeshPool::UID	SpineUID;
spSkeleton*				SpineSkeleton;
spAnimationState*		SpineAnimState;
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
	gelSkelMeshInit();
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
		App::SpineUID = Gel::SkelMeshPool.Load( "SpineTest/spineboy.json" );
		App::SpineSkeleton = spSkeleton_create( Gel::SkelMeshPool[App::SpineUID].GetSkeletonData() );
		App::SpineAnimState = spAnimationState_create(0);//stateData);
			
		spAnimation* Animation = spSkeletonData_findAnimation( App::SpineSkeleton->data, "walk");
		spAnimationState_setAnimation( App::SpineAnimState, 0, Animation, true );
		Log("**** DONE");
	}
}
// - ------------------------------------------------------------------------------------------ - //
void AppExit() {
	{
		spAnimationState_dispose( App::SpineAnimState );
		spSkeleton_dispose( App::SpineSkeleton );
	}

	/***/

	QuackVMCallExit();
	
	Gel::Input::Exit();
}
// - ------------------------------------------------------------------------------------------ - //

void StepSpine() {
	float deltaTime = 1000.0f/60.0f;
	float timeScale = 0.001f;
	
	spSkeleton_update(App::SpineSkeleton, deltaTime);
	spAnimationState_update(App::SpineAnimState, deltaTime * timeScale);
	spAnimationState_apply(App::SpineAnimState, App::SpineSkeleton);
	spSkeleton_updateWorldTransform(App::SpineSkeleton);	
}

void DrawSpine() {
	Matrix4x4 Matrix = App::InfoMatrix;
	Matrix[0] *= Real::Quarter;
	Matrix[5] *= Real::Quarter;
	//Matrix *= Matrix4x4::ScalarMatrix(0.25f) * Matrix;

	spSkeleton* skeleton = App::SpineSkeleton;
	
	float worldVertices[8];
	for (int i = 0; i < skeleton->slotCount; ++i) {
		spSlot* slot = skeleton->drawOrder[i];
		spAttachment* attachment = slot->attachment;
		if (!attachment || attachment->type != ATTACHMENT_REGION) continue;
		spRegionAttachment* regionAttachment = (spRegionAttachment*)attachment;

//		BlendMode blend = slot->data->additiveBlending ? BlendAdd : BlendAlpha;
//		if (states.blendMode != blend) {
//			target.draw(*vertexArray, states);
//			vertexArray->clear();
//			states.blendMode = blend;
//		}

		spRegionAttachment_computeWorldVertices(regionAttachment, slot->skeleton->x, slot->skeleton->y, slot->bone, worldVertices);

		Uint8 r = skeleton->r * slot->r * 255;
		Uint8 g = skeleton->g * slot->g * 255;
		Uint8 b = skeleton->b * slot->b * 255;
		Uint8 a = skeleton->a * slot->a * 255;
		GelColor Color = GEL_RGBA(r,g,b,a);

//		sf::Vertex vertices[4];
//		vertices[0].color.r = r;
//		vertices[0].color.g = g;
//		vertices[0].color.b = b;
//		vertices[0].color.a = a;
//		vertices[1].color.r = r;
//		vertices[1].color.g = g;
//		vertices[1].color.b = b;
//		vertices[1].color.a = a;
//		vertices[2].color.r = r;
//		vertices[2].color.g = g;
//		vertices[2].color.b = b;
//		vertices[2].color.a = a;
//		vertices[3].color.r = r;
//		vertices[3].color.g = g;
//		vertices[3].color.b = b;
//		vertices[3].color.a = a;

//		vertices[0].position.x = worldVertices[VERTEX_X1];
//		vertices[0].position.y = worldVertices[VERTEX_Y1];
//		vertices[1].position.x = worldVertices[VERTEX_X2];
//		vertices[1].position.y = worldVertices[VERTEX_Y2];
//		vertices[2].position.x = worldVertices[VERTEX_X3];
//		vertices[2].position.y = worldVertices[VERTEX_Y3];
//		vertices[3].position.x = worldVertices[VERTEX_X4];
//		vertices[3].position.y = worldVertices[VERTEX_Y4];

		const st32 VertCount = 6;
		Vector3D Verts[ VertCount ];
		Verts[0] = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
		Verts[1] = Vector3D(worldVertices[VERTEX_X2],worldVertices[VERTEX_Y2],0);
		Verts[2] = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
		
		Verts[3] = Vector3D(worldVertices[VERTEX_X3],worldVertices[VERTEX_Y3],0);
		Verts[4] = Vector3D(worldVertices[VERTEX_X4],worldVertices[VERTEX_Y4],0);
		Verts[5] = Vector3D(worldVertices[VERTEX_X1],worldVertices[VERTEX_Y1],0);
		
//		for ( st32 idx = 0; idx < VertCount; idx++ ) {
//			Verts[idx] += Pos;
//		}
//		
//		UVSet<Gel::UVType> UVs[ VertCount ];
//		UVs[0] = UVSet<Gel::UVType>(UV_ZERO,UV_ZERO);
//		UVs[1] = UVSet<Gel::UVType>( UV_ONE,UV_ZERO);
//		UVs[2] = UVSet<Gel::UVType>( UV_ONE, UV_ONE);
//		UVs[3] = UVSet<Gel::UVType>( UV_ONE, UV_ONE);
//		UVs[4] = UVSet<Gel::UVType>(UV_ZERO, UV_ONE);
//		UVs[5] = UVSet<Gel::UVType>(UV_ZERO,UV_ZERO);
//		
//		Gel::RenderTexture( GEL_TRIANGLES, *uMatrix, Color, Verts, UVs, VertCount );
		Gel::RenderFlat( GEL_TRIANGLES, Matrix, Color, Verts, VertCount );

		// SMFL doesn't handle batching for us, so we'll just force a single texture per skeleton.
//		states.texture = (Texture*)((AtlasRegion*)regionAttachment->rendererObject)->page->rendererObject;

//		Vector2u size = states.texture->getSize();
//		vertices[0].texCoords.x = regionAttachment->uvs[VERTEX_X1] * size.x;
//		vertices[0].texCoords.y = regionAttachment->uvs[VERTEX_Y1] * size.y;
//		vertices[1].texCoords.x = regionAttachment->uvs[VERTEX_X2] * size.x;
//		vertices[1].texCoords.y = regionAttachment->uvs[VERTEX_Y2] * size.y;
//		vertices[2].texCoords.x = regionAttachment->uvs[VERTEX_X3] * size.x;
//		vertices[2].texCoords.y = regionAttachment->uvs[VERTEX_Y3] * size.y;
//		vertices[3].texCoords.x = regionAttachment->uvs[VERTEX_X4] * size.x;
//		vertices[3].texCoords.y = regionAttachment->uvs[VERTEX_Y4] * size.y;

//		vertexArray->append(vertices[0]);
//		vertexArray->append(vertices[1]);
//		vertexArray->append(vertices[2]);
//		vertexArray->append(vertices[3]);
	}
//	target.draw(*vertexArray, states);
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

	QuackVMCallStep();
	
	// *** //
	App::StepProfiler.Stop();

	StepSpine();
}
// - ------------------------------------------------------------------------------------------ - //
void AppDraw() {
	App::DrawProfiler.Start();	
	// *** //
	QuackVMCallDraw();
	// *** //
	App::DrawProfiler.Stop();
		
	DrawSpine();

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
