// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <System/System.h>
#include <Graphics/Graphics.h>
#include <API/API_Squirrel.h>
#include <App.h>

#include <Graphics/GelColor.h>
#include <Math/Vector.h>
#include <Math/Matrix.h>
#include <Render/Render.h>

#include <Generate/Vertex.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkSetScreenScalar( HSQUIRRELVM v ) {
	float Scale;
	if(SQ_FAILED(sq_getfloat(v,2,&Scale)))
		return sq_throwerror(v,_SC("invalid param"));
	
	gelSetScreenScalar( Scale );
	
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkInitScreens( HSQUIRRELVM v ) {
	gelInitScreens();

	gelLogGraphicsAPIDetails();
	gelGraphicsInit();

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkAspectRatio(HSQUIRRELVM vm) {
	sq_pushfloat( vm, (float)Gel::Native[0].GetWidth() / (float)Gel::Native[0].GetHeight() );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkClear(HSQUIRRELVM vm) {
	//gelClear( true, true );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	return SQ_VOID;
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
			sq_getinteger(vm,5,(SQInteger*)&Color);
		}
	
		const st32 VertCount = size_Vertex3D_Circle();
		Vector3D Verts[ VertCount ];
		generate_Vertex3D_Circle( Verts, Vector3D(x,y,z), Real(Radius) );
	
		Gel::Flat( GEL_LINE_LOOP, *((Matrix4x4*)uMatrix), Color, Verts, VertCount );
	}
	else {
		Log("! qkDrawCircle -- Not enough arguments");
	}
	
	return SQ_VOID;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMatrixIdentity(HSQUIRRELVM vm) {
	// Also pushes the UserPointer on the Stack //
	SQUserPointer Mat = sq_newuserdata( vm, sizeof( Matrix4x4 ) );
	copy_Data( (void*)&Matrix4x4::Identity, (void*)Mat, sizeof( Matrix4x4 ) );

	return SQ_RETURN;
}

// - ------------------------------------------------------------------------------------------ - //
SQInteger qkScalarMatrix(HSQUIRRELVM vm) {
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
	float w = 1.0f;
	
	int NumArgs = sq_gettop(vm);

	if ( NumArgs >= 2 ) {
		sq_getfloat(vm,2,&x);
	}
	if ( NumArgs >= 3 ) {
		sq_getfloat(vm,3,&y);
	}
	if ( NumArgs >= 4 ) {
		sq_getfloat(vm,4,&z);
	}
	if ( NumArgs >= 5 ) {
		sq_getfloat(vm,5,&w);
	}

	Matrix4x4 rMatrix = Matrix4x4::Identity;
	rMatrix(0,0) = x;
	rMatrix(1,1) = y;
	rMatrix(2,2) = z;
	rMatrix(3,3) = w;
	
	// Also pushes the UserPointer on the Stack //
	SQUserPointer Mat = sq_newuserdata( vm, sizeof( Matrix4x4 ) );
	copy_Data( (void*)&rMatrix, (void*)Mat, sizeof( Matrix4x4 ) );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMultMatrix(HSQUIRRELVM vm) {
	SQUserPointer aMatrix = 0;
	SQUserPointer bMatrix = 0;
	
	sq_getuserdata(vm,2,&aMatrix,NULL);	
	sq_getuserdata(vm,3,&bMatrix,NULL);	
	
	Matrix4x4* paMatrix = (Matrix4x4*)aMatrix;
	Matrix4x4* pbMatrix = (Matrix4x4*)bMatrix;
	
	Matrix4x4 rMatrix = (*paMatrix) * (*pbMatrix);
	
	// Also pushes the UserPointer on the Stack //
	SQUserPointer Mat = sq_newuserdata( vm, sizeof( Matrix4x4 ) );
	copy_Data( (void*)&rMatrix, (void*)Mat, sizeof( Matrix4x4 ) );

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkDoMatrix(HSQUIRRELVM vm) {
	SQUserPointer uMatrix = 0;
	
	int NumArgs = sq_gettop(vm);
	if ( NumArgs >= 2 ) {
		sq_getuserdata(vm,2,&uMatrix,NULL);	
	}
	
	Matrix4x4* pMatrix = (Matrix4x4*)uMatrix;
	
	Log( "[%f %f %f %f]", (*pMatrix)(0,0).ToFloat(),(*pMatrix)(1,0).ToFloat(),(*pMatrix)(2,0).ToFloat(),(*pMatrix)(3,0).ToFloat() );
	Log( "[%f %f %f %f]", (*pMatrix)(0,1).ToFloat(),(*pMatrix)(1,1).ToFloat(),(*pMatrix)(2,1).ToFloat(),(*pMatrix)(3,1).ToFloat() );
	Log( "[%f %f %f %f]", (*pMatrix)(0,2).ToFloat(),(*pMatrix)(1,2).ToFloat(),(*pMatrix)(2,2).ToFloat(),(*pMatrix)(3,2).ToFloat() );
	Log( "[%f %f %f %f]", (*pMatrix)(0,3).ToFloat(),(*pMatrix)(1,3).ToFloat(),(*pMatrix)(2,3).ToFloat(),(*pMatrix)(3,3).ToFloat() );
	Log( "" );
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qklib_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qkSetScreenScalar,2,_SC(".n")),
	_DECL_FUNC(qkInitScreens,1,NULL),
	_DECL_FUNC(qkAspectRatio,1,NULL),
	_DECL_FUNC(qkClear,1,NULL),
	_DECL_FUNC(qkDrawCircle,-2,NULL),
	_DECL_FUNC(qkMatrixIdentity,1,NULL),
	_DECL_FUNC(qkScalarMatrix,-2,NULL),
	_DECL_FUNC(qkMultMatrix,3,NULL), // TODO ARG3
	_DECL_FUNC(qkDoMatrix,2,NULL),
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkScreen(HSQUIRRELVM v) {
	SQInteger i=0;
	while(qklib_funcs[i].name!=0) {
		sq_pushstring(v,qklib_funcs[i].name,-1);
		sq_newclosure(v,qklib_funcs[i].f,0);
		sq_setparamscheck(v,qklib_funcs[i].nparamscheck,qklib_funcs[i].typemask);
		sq_setnativeclosurename(v,-1,qklib_funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
