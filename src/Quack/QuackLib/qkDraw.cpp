// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Math.h>
#include <Graphics/Graphics.h>
#include <Render/Render.h>
#include <Generate/Generate.h>
#include <Asset/Asset.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDrawCircle(HSQUIRRELVM vm) {
	float Radius = 10.0f;
	Vector3D Pos;
	
	Matrix4x4* uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		sq_getinstanceup(vm,2,(void**)&uMatrix,NULL);

		if ( NumArgs >= 3 ) {
			void* UserPointer;
			sq_getinstanceup(vm,3,(void**)&UserPointer,NULL);

			// TODO: Check type (vec2, vec3) //

			Vector2D* Vec = (Vector2D*)UserPointer;
			Pos = Vec->ToVector3D();
		}
		
		if ( NumArgs >= 4 ) {
			sq_getfloat(vm,4,&Radius);
		}
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
SQInteger qkDrawTexturedQuad(HSQUIRRELVM vm) {
	float Radius = 10.0f;
	Vector3D Pos;
	
	Matrix4x4* uMatrix = 0;
	
	GelColor Color = GEL_RGBA(255,255,255,255);
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		sq_getinstanceup(vm,2,(void**)&uMatrix,NULL);

		if ( NumArgs >= 3 ) {
			void* UserPointer;
			sq_getinstanceup(vm,3,(void**)&UserPointer,NULL);

			// TODO: Check type (vec2, vec3) //

			Vector2D* Vec = (Vector2D*)UserPointer;
			Pos = Vec->ToVector3D();
		}
		
		if ( NumArgs >= 4 ) {
			sq_getfloat(vm,4,&Radius);
		}
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

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkDraw_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.

	_DECL_FUNC(qkDrawCircle,-2,NULL),
	_DECL_FUNC(qkDrawTexturedQuad,-2,NULL),
	
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