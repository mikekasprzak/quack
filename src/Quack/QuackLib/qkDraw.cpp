// - ------------------------------------------------------------------------------------------ - //
// TODO: Optionally take a vec2 as a radius input argument, to allow distortions of shape. //
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
#define _PRIMITIVE_DRAW_RADIUS(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ...) \
SQInteger _FUNCNAME_( HSQUIRRELVM v ) { \
	Vector3D Pos(0,0); \
	Vector2D Radius(10,10); \
	\
	Matrix4x4* uMatrix = 0; \
	\
	GelColor Color = GEL_RGB_WHITE; \
	\
	int NumArgs = sq_gettop(v); \
	if ( NumArgs >= 2 ) { \
		/* ARG1: Matrix */ \
		sq_getinstanceup(v,2,(void**)&uMatrix,NULL); \
		\
		/* ARG2: Position */ \
		if ( NumArgs >= 3 ) { \
			void* UserPointer; \
			sq_getinstanceup(v,3,(void**)&UserPointer,NULL); \
			\
			/* TODO: Check type (vec2, vec3) */ \
			\
			Vector2D* Vec = (Vector2D*)UserPointer; \
			Pos = Vec->ToVector3D(); \
		} \
		\
		/* ARG3: Radius */ \
		if ( NumArgs >= 4 ) { \
			int Type = sq_gettype(v,4); \
			if ( Type & (OT_FLOAT|OT_INTEGER) ) { \
				float FRadius; \
				sq_getfloat(v,4,&FRadius); \
				Radius = Vector2D(FRadius,FRadius); \
			} \
			else if ( Type == OT_INSTANCE ) { \
				int Tag; \
				sq_gettypetag(v,4,(SQUserPointer*)&Tag); \
				if ( Tag == QK_TAG_VEC2 ) { \
					Vector2D* Value; \
					sq_getinstanceup(v,4,(void**)&Value,NULL); \
					Radius = *Value; \
				} \
			} \
		} \
		\
		/* ARG4: Color */ \
		if ( NumArgs >= 5 ) { \
			GelColor* ColorArg; \
			sq_getinstanceup(v,5,(void**)&ColorArg,0); \
			Color = *ColorArg; \
		} \
		\
		const st32 VertCount = size_Vertex3D_ ## _PRIMNAME_( __VA_ARGS__ ); \
		Vector3D Verts[ VertCount ]; \
		generate_Vertex3D_ ## _PRIMNAME_( Verts, Pos, Radius, ## __VA_ARGS__ ); \
		\
		Gel::RenderFlat( _DRAWMODE_, *uMatrix, Color, Verts, VertCount ); \
	} \
	else { \
		Log("! " #_FUNCNAME_ " -- Not enough arguments"); \
	} \
	\
	return SQ_VOID; \
}
// - ------------------------------------------------------------------------------------------ - //
_PRIMITIVE_DRAW_RADIUS(qkDrawCircle,Circle,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(qkDrawSquare,RadiusRect,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(qkDrawDiamond,Diamond,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_RADIUS(qkDrawTriangle,Circle,GEL_LINE_LOOP,3);
_PRIMITIVE_DRAW_RADIUS(qkDrawCross,Cross,GEL_LINES);
_PRIMITIVE_DRAW_RADIUS(qkDrawX,X,GEL_LINES);
_PRIMITIVE_DRAW_RADIUS(qkDrawRect,Rect,GEL_LINE_LOOP);

_PRIMITIVE_DRAW_RADIUS(qkDrawCircleFill,Circle,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(qkDrawSquareFill,RadiusRect,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(qkDrawDiamondFill,Diamond,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_RADIUS(qkDrawTriangleFill,Circle,GEL_TRIANGLE_FAN,3);
_PRIMITIVE_DRAW_RADIUS(qkDrawRectFill,Rect,GEL_TRIANGLE_FAN);
// - ------------------------------------------------------------------------------------------ - //
#undef _PRIMITIVE_DRAW_RADIUS
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _PRIMITIVE_DRAW_CAPSULE(_FUNCNAME_,_PRIMNAME_,_DRAWMODE_, ... ) \
SQInteger _FUNCNAME_( HSQUIRRELVM v ) { \
	Vector3D PosA(0,0); \
	float RadiusA = 10.0f; \
	Vector3D PosB(0,0); \
	float RadiusB = 10.0f; \
	\
	Matrix4x4* uMatrix = 0; \
	\
	GelColor Color = GEL_RGB_WHITE; \
	\
	int NumArgs = sq_gettop(v); \
	if ( NumArgs >= 2 ) { \
		/* ARG1: Matrix */ \
		sq_getinstanceup(v,2,(void**)&uMatrix,NULL); \
		\
		/* ARG2: Position */ \
		if ( NumArgs >= 3 ) { \
			void* UserPointer; \
			sq_getinstanceup(v,3,(void**)&UserPointer,NULL); \
			\
			/* TODO: Check type (vec2, vec3) */ \
			\
			Vector2D* Vec = (Vector2D*)UserPointer; \
			PosA = Vec->ToVector3D(); \
		} \
		\
		/* ARG3: Radius */ \
		if ( NumArgs >= 4 ) { \
			sq_getfloat(v,4,&RadiusA); \
		} \
		\
		/* ARG2: Position */ \
		if ( NumArgs >= 5 ) { \
			void* UserPointer; \
			sq_getinstanceup(v,5,(void**)&UserPointer,NULL); \
			\
			/* TODO: Check type (vec2, vec3) */ \
			\
			Vector2D* Vec = (Vector2D*)UserPointer; \
			PosB = Vec->ToVector3D(); \
		} \
		\
		/* ARG3: Radius */ \
		if ( NumArgs >= 6 ) { \
			sq_getfloat(v,6,&RadiusB); \
		} \
		\
		/* ARG4: Color */ \
		if ( NumArgs >= 7 ) { \
			GelColor* ColorArg; \
			sq_getinstanceup(v,7,(void**)&ColorArg,0); \
			Color = *ColorArg; \
		} \
		\
		const st32 VertCount = size_Vertex3D_ ## _PRIMNAME_( __VA_ARGS__ ); \
		Vector3D Verts[ VertCount ]; \
		generate_Vertex3D_ ## _PRIMNAME_( Verts, PosA, Real(RadiusA), PosB, Real(RadiusB), ## __VA_ARGS__ ); \
		\
		Gel::RenderFlat( _DRAWMODE_, *uMatrix, Color, Verts, VertCount ); \
	} \
	else { \
		Log("! " #_FUNCNAME_ " -- Not enough arguments"); \
	} \
	\
	return SQ_VOID; \
}
// - ------------------------------------------------------------------------------------------ - //
_PRIMITIVE_DRAW_CAPSULE(qkDrawCapsule,Capsule,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_CAPSULE(qkDrawDiamondCapsule,DiamondCapsule,GEL_LINE_LOOP);
_PRIMITIVE_DRAW_CAPSULE(qkDrawFlatCapsule,FlatCapsule,GEL_LINE_LOOP);

_PRIMITIVE_DRAW_CAPSULE(qkDrawCapsuleFill,Capsule,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_CAPSULE(qkDrawDiamondCapsuleFill,DiamondCapsule,GEL_TRIANGLE_FAN);
_PRIMITIVE_DRAW_CAPSULE(qkDrawFlatCapsuleFill,FlatCapsule,GEL_TRIANGLE_FAN);
// - ------------------------------------------------------------------------------------------ - //
#undef _PRIMITIVE_DRAW_CAPSULE
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a .Draw member to the QkTexture that does exactly this. //
SQInteger qkDrawTexturedQuad(HSQUIRRELVM vm) {
	float RadiusW = 10.0f;
	float RadiusH = RadiusW;
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
			int Type = sq_gettype(vm,4);
			if ( Type & (OT_FLOAT|OT_INTEGER) ) {
				sq_getfloat(vm,4,&RadiusW);
				RadiusH = RadiusW;
			}
			else if ( Type == OT_INSTANCE ) {
				int Tag;
				sq_gettypetag(vm,4,(SQUserPointer*)&Tag);
				if ( Tag == QK_TAG_VEC2 ) {
					float* Vec;
					sq_getinstanceup(vm,4,(void**)&Vec,0);
					
					RadiusW = Vec[0];
					RadiusH = Vec[1];
				}
			}
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
		Verts[0] = Vector3D(-RadiusW,-RadiusH,0);
		Verts[1] = Vector3D(+RadiusW,-RadiusH,0);
		Verts[2] = Vector3D(+RadiusW,+RadiusH,0);
		Verts[3] = Vector3D(+RadiusW,+RadiusH,0);
		Verts[4] = Vector3D(-RadiusW,+RadiusH,0);
		Verts[5] = Vector3D(-RadiusW,-RadiusH,0);
		
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
			
			// For all Nodes in the Scene //
			for ( st32 NodeIndex = 0; NodeIndex < Model->nNumMeshNode; NodeIndex++ ) {
				if ( Model->nNumTexture ) {
					st32 MaterialIndex = Model->pNode[NodeIndex].nIdxMaterial;
					st32 TextureIndex = Model->pMaterial[MaterialIndex].nIdxTexDiffuse;
					//const char* TextureName = Model->pTexture[TextureIndex].pszName;
					
					Gel::TexturePool[Gel::ModelPool[ModelUID].TexturePage[TextureIndex]].Bind();
				}
				
				// We know the first nNumMeshNode objects are all Objects (meshes) in the node List //
				// Everything else is are other things (cameras, lights, etc) //
				{
					st32 MeshIndex = Model->pNode[NodeIndex].nIdx;
					
					SPODMesh& Mesh = Model->pMesh[MeshIndex];
					const float* Vert = (const float*)(Mesh.pInterleaved + (st)Mesh.sVertex.pData); // Stride //
					const st32 VertCount = Mesh.nNumVertex;
					
					//if ( Mesh.sFaces.eType == EPODDataUnsignedShort ) // Is usually an Unsigned Short! Good! //
					const int* Index = (const int*)Mesh.sFaces.pData;
					const st32 IndexCount = Mesh.nNumFaces;
								
					if ( Mesh.nNumUVW > 0 ) {
	//					Log( ">> %i -- Mesh: %x:%i [%x:%i,%i]  UVW: %i [%x:%i,%i]:%x  Index: %x:%i [%x:%i,%i]", 
	//						MeshIndex, 
	//						Vert,VertCount, Mesh.sVertex.eType,Mesh.sVertex.n,Mesh.sVertex.nStride,  
	//						Mesh.nNumUVW, Mesh.psUVW[0].eType,Mesh.psUVW[0].n,Mesh.psUVW[0].nStride,Mesh.psUVW[0].pData,
	//						Index,IndexCount, Mesh.sFaces.eType,Mesh.sFaces.n,Mesh.sFaces.nStride 
	//						);
	
						const float* UVs = (const float*)(Mesh.pInterleaved + (st)Mesh.psUVW[0].pData); // Stride //
	
						Gel::RenderTexturePackedIndexed( GEL_TRIANGLES, *uMatrix, Color, Vert,UVs,VertCount, Index,IndexCount*3 );
					}
					else {
						Gel::RenderFlatIndexed( GEL_TRIANGLES, *uMatrix, Color, Vert,VertCount, Index,IndexCount*3 );
					}
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
	_DECL_FUNC(qkDrawSquare,-2,NULL),
	_DECL_FUNC(qkDrawDiamond,-2,NULL),
	_DECL_FUNC(qkDrawTriangle,-2,NULL),
	_DECL_FUNC(qkDrawCross,-2,NULL),
	_DECL_FUNC(qkDrawX,-2,NULL),
	_DECL_FUNC(qkDrawRect,-2,NULL),

	_DECL_FUNC(qkDrawCircleFill,-2,NULL),
	_DECL_FUNC(qkDrawSquareFill,-2,NULL),
	_DECL_FUNC(qkDrawDiamondFill,-2,NULL),
	_DECL_FUNC(qkDrawTriangleFill,-2,NULL),
	_DECL_FUNC(qkDrawRectFill,-2,NULL),

	_DECL_FUNC(qkDrawCapsule,-2,NULL),
	_DECL_FUNC(qkDrawDiamondCapsule,-2,NULL),
	_DECL_FUNC(qkDrawFlatCapsule,-2,NULL),

	_DECL_FUNC(qkDrawCapsuleFill,-2,NULL),
	_DECL_FUNC(qkDrawDiamondCapsuleFill,-2,NULL),
	_DECL_FUNC(qkDrawFlatCapsuleFill,-2,NULL),

	// 3D Shapes //
//	_DECL_FUNC(qkDrawCube,-2,NULL),
	
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
