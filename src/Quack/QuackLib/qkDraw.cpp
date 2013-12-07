// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Math.h>
#include <Asset/Asset.h>
#include <Graphics/Graphics.h>
#include <Render/Render.h>
#include <Font/Font.h>
#include <Model/Model.h>

#include <Generate/Generate.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDrawCircle(HSQUIRRELVM vm) {
	float Radius = 10.0f;
	Vector3D Pos;
	
	Matrix4x4* uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		// ARG1: Matrix
		sq_getinstanceup(vm,2,(void**)&uMatrix,NULL);

		// ARG2: Position
		if ( NumArgs >= 3 ) {
			void* UserPointer;
			sq_getinstanceup(vm,3,(void**)&UserPointer,NULL);

			// TODO: Check type (vec2, vec3) //

			Vector2D* Vec = (Vector2D*)UserPointer;
			Pos = Vec->ToVector3D();
		}
		
		// ARG3: Radius
		if ( NumArgs >= 4 ) {
			sq_getfloat(vm,4,&Radius);
		}
		
		// ARG4: Color
		if ( NumArgs >= 5 ) {
			// Retrieve Data (Pointer) //
			GelColor* ColorArg;
			sq_getinstanceup(vm,5,(void**)&ColorArg,0);
			Color = *ColorArg;
		}
	
		const st32 VertCount = size_Vertex3D_Circle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Circle( Verts, Pos, Real(Radius) );
	
		Gel::RenderFlat( GEL_LINE_LOOP, *uMatrix, Color, Verts, VertCount );
	}
	else {
		Log("! qkDrawCircle -- Not enough arguments");
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a .Draw member to the QkTexture that does exactly this. //
SQInteger qkDrawTexturedQuad(HSQUIRRELVM vm) {
	float Radius = 10.0f;
	Vector3D Pos;
	
	Matrix4x4* uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		// ARG1: Matrix
		sq_getinstanceup(vm,2,(void**)&uMatrix,NULL);

		// ARG2: Position
		if ( NumArgs >= 3 ) {
			void* UserPointer;
			sq_getinstanceup(vm,3,(void**)&UserPointer,NULL);

			// TODO: Check type (vec2, vec3) //

			Vector2D* Vec = (Vector2D*)UserPointer;
			Pos = Vec->ToVector3D();
		}
		
		// ARG3: Radius
		if ( NumArgs >= 4 ) {
			sq_getfloat(vm,4,&Radius);
		}
		
		// ARG4: Color
		if ( NumArgs >= 5 ) {
			// Retrieve Data (Pointer) //
			GelColor* ColorArg;
			sq_getinstanceup(vm,5,(void**)&ColorArg,0);
			Color = *ColorArg;
		}
	
		const st32 VertCount = 6;
		Vector3D Verts[ VertCount ];
		Verts[0] = Vector3D(-Radius,-Radius,0);
		Verts[1] = Vector3D(+Radius,-Radius,0);
		Verts[2] = Vector3D(+Radius,+Radius,0);
		Verts[3] = Vector3D(+Radius,+Radius,0);
		Verts[4] = Vector3D(-Radius,+Radius,0);
		Verts[5] = Vector3D(-Radius,-Radius,0);
		
		for ( st32 idx = 0; idx < VertCount; idx++ ) {
			Verts[idx] += Pos;
		}
		
		UVSet<Gel::UVType> UVs[ VertCount ];
		UVs[0] = UVSet<Gel::UVType>(UV_ZERO,UV_ZERO);
		UVs[1] = UVSet<Gel::UVType>( UV_ONE,UV_ZERO);
		UVs[2] = UVSet<Gel::UVType>( UV_ONE, UV_ONE);
		UVs[3] = UVSet<Gel::UVType>( UV_ONE, UV_ONE);
		UVs[4] = UVSet<Gel::UVType>(UV_ZERO, UV_ONE);
		UVs[5] = UVSet<Gel::UVType>(UV_ZERO,UV_ZERO);
		
		Gel::RenderTexture( GEL_TRIANGLES, *uMatrix, Color, Verts, UVs, VertCount );
	}
	else {
		Log("! qkDrawTexturedQuad -- Not enough arguments");
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDrawText(HSQUIRRELVM vm) {
	float FontSize = 8.0f;
	Vector3D Pos;
	
	Matrix4x4* uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	
	const char* Text = "";
	
	GelFontPool::UID FontUID = 1; // Default to Font #1 //
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 3 ) {
		// ARG1: Matrix
		sq_getinstanceup(vm,2,(void**)&uMatrix,NULL);
		
		// ARG2: Text
		sq_getstring(vm,3,&Text);

		// ARG3: Position
		if ( NumArgs >= 4 ) {
			void* UserPointer;
			sq_getinstanceup(vm,4,(void**)&UserPointer,NULL);

			// TODO: Check type (vec2, vec3) //

			Vector2D* Vec = (Vector2D*)UserPointer;
			Pos = Vec->ToVector3D();
		}
		
		// ARG4: Font Size
		if ( NumArgs >= 5 ) {
			sq_getfloat(vm,5,&FontSize);
		}
		
		// ARG5: Color
		if ( NumArgs >= 6 ) {
			// Retrieve Data (Pointer) //
			GelColor* ColorArg;
			sq_getinstanceup(vm,6,(void**)&ColorArg,0);
			Color = *ColorArg;
		}

		// ARG6: Font
		if ( NumArgs >= 7 ) {
			// Retrieve Data (Pointer) //
			GelFontPool::UID* UIDPtr;
			sq_getinstanceup(vm,7,(void**)&UIDPtr,0);
			FontUID = *UIDPtr;
		}
		
		// TODO: Align
	
		Gel::FontPool[FontUID].DrawText( *uMatrix, Text, Pos, FontSize, Color, GEL_ALIGN_DEFAULT );
	}
	else {
		Log("! qkDrawText -- Not enough arguments");
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a .Draw member to the QkModel that does exactly this. //
SQInteger qkDrawModel(HSQUIRRELVM vm) {
	Matrix4x4* uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	GelModelPool::UID ModelUID = 1; // Default to Font #1 //
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		// ARG1: Matrix
		sq_getinstanceup(vm,2,(void**)&uMatrix,NULL);

		// ARG2: Font
		if ( NumArgs >= 3 ) {
			// Retrieve Data (Pointer) //
			GelModelPool::UID* UIDPtr;
			sq_getinstanceup(vm,3,(void**)&UIDPtr,0);
			ModelUID = *UIDPtr;
		}

		// ARG3: Color
		if ( NumArgs >= 4 ) {
			// Retrieve Data (Pointer) //
			GelColor* ColorArg;
			sq_getinstanceup(vm,4,(void**)&ColorArg,0);
			Color = *ColorArg;
		}
		
		// Render // 
		{
			CPVRTModelPOD* Model = Gel::ModelPool[ModelUID].Model;
			
			for ( st32 MeshIndex = 0; MeshIndex < Model->nNumMesh; MeshIndex++ ) {
				SPODMesh& Mesh = Model->pMesh[MeshIndex];
				const float* Vert = (const float*)Mesh.pInterleaved;//sVertex.pData;
				const st32 VertCount = Mesh.nNumVertex;
				
				//if ( Mesh.sFaces.eType == EPODDataUnsignedShort ) // Is usually an Unsigned Short! Good! //
				const int* Index = (const int*)Mesh.sFaces.pData;
				const st32 IndexCount = Mesh.nNumFaces;

//					Log( ">> %i -- %x:%i [%x:%i,%i]  %x:%i [%x:%i,%i]", 
//						MeshIndex, 
//						Vert,VertCount,  
//						Mesh.sVertex.eType,Mesh.sVertex.n,Mesh.sVertex.nStride,  
//						Index,IndexCount ,Mesh.sFaces.eType,Mesh.sFaces.n,Mesh.sFaces.nStride 
//						);
							
				if ( Mesh.nNumUVW > 0 ) {
					//Gel::RenderTextureIndexed( GEL_TRIANGLES, *uMatrix, Color, Vert,VertCount, Index,IndexCount*3 );
				}
				else {
					Gel::RenderFlatIndexed( GEL_TRIANGLES, *uMatrix, Color, Vert,VertCount, Index,IndexCount*3 );
				}
			}
		}
	}
	else {
		Log("! qkDrawModel -- Not enough arguments");
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkDraw_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qkDrawCircle,-2,NULL),
	_DECL_FUNC(qkDrawTexturedQuad,-2,NULL),
	_DECL_FUNC(qkDrawText,-3,NULL),
	_DECL_FUNC(qkDrawModel,-3,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkDraw(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkDraw_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
