// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: .row0(), .column2() functions might be nice, for getting vectors of the data.
// TODO: .get00mat2() to get the 2x2 matrix at position 0,0. These sort of functions.
//       Consider adding wrapping functions, like a way to get the matrix of an edge. .get33mat2()
//       Consider making this how we handle skewing a matrix. .get20mat4() to shift everything left 2.
//       Consider using _get for this. That way, we can programatically figure out the position. .get33mat4
// - ------------------------------------------------------------------------------------------ - //
// NOTE: It's okay to have a matrix that supports scalar addition, but no other forms of adding. //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// _tostring //
#define _MAT_TOSTRING(_TYPE_,_NAME_,...) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Mat; \
	sq_getinstanceup(v,1,(void**)&Mat,0); \
	\
	char Text[(24*16)+24+8+1]; \
	sprintf(Text, __VA_ARGS__ ); \
	\
	sq_pushstring(v,Text,-1); \
	\
	return SQ_RETURN; \
}
// TODO: safe_sprintf. need a consistent version that either always prints, or notes a size error //
//       that I can in-turn write a "ERROR: not enough room to sprintf" to it (if it fits). //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// _cloned //
#define _MAT_CLONED(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Mat; /* +1 */ \
	sq_getinstanceup(v,1,(void**)&Mat,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	*Mat = *Vs; \
	\
	return SQ_VOID; \
}
// - ------------------------------------------------------------------------------------------ - //
// _unm (i.e. negative) //
#define _MAT_UNM(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Mat; \
	sq_getinstanceup(v,-1,(void**)&Mat,0); \
	\
	*Mat = -(*Mat);\
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// Functions Returning a Vector //
#define _MAT_FUNC(_TYPE_,_NAME_,_FUNC_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Mat; \
	sq_getinstanceup(v,-1,(void**)&Mat,0); \
	\
	*Mat = Mat->_FUNC_();\
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_mat_get( HSQUIRRELVM v, float* Mat, const int MatSize, const unsigned int MatWidth ) {
	const int Type = sq_gettype(v,2);
	if ( Type == OT_INTEGER ) {
		int Index;
		sq_getinteger(v,2,&Index);

		if ( Index < MatSize ) {
			sq_pushfloat(v,Mat[Index]);
			return SQ_RETURN;
		}
		else {
			return sq_throwerror(v,"matrix element index is out of range");
		}
	}
	else if ( Type == OT_STRING ) {
		const char* Text;
		sq_getstring(v,2,&Text);
		
		if ( Text[0] == 'e' ) {
			if ( Text[1] != 0 ) { // if true, it means Text[2] is safe to read (trailing zero) //
				unsigned int x = Text[1] - '0';
				unsigned int y = Text[2] - '0';
				
				if ( x >= MatWidth )
					return sq_throwerror(v,"x is out of range in matrix eXY expression");
				if ( y >= MatWidth )
					return sq_throwerror(v,"y is out of range in matrix eXY expression");
				
				sq_pushfloat(v,Mat[x+(y*MatWidth)]);
				return SQ_RETURN;
			}
			else {
				return sq_throwerror(v,"incomplete matrix eXY expression");
			}
		}
	}
	
	sq_pushnull(v);				/* +1 */
	return sq_throwobject(v);	/* -1 */
}
// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_mat_set( HSQUIRRELVM v, float* Mat, const int MatSize, const unsigned int MatWidth ) {
	if ( sq_gettype(v,3) & (OT_FLOAT|OT_INTEGER) ) {
		float Value;
		sq_getfloat(v,3,&Value);
	
		const int Type = sq_gettype(v,2);
		if ( Type == OT_INTEGER ) {
			unsigned int Index;
			sq_getinteger(v,2,(int*)&Index);
	
			if ( Index < (unsigned int)MatSize ) {
				Mat[Index] = Value;
				sq_pushfloat(v,Value);
				return SQ_RETURN;
			}
			else {
				return sq_throwerror(v,"matrix element index is out of range");
			}
		}
		else if ( Type == OT_STRING ) {
			const char* Text;
			sq_getstring(v,2,&Text);
			
			if ( Text[0] == 'e' ) {
				if ( Text[1] != 0 ) { // if true, it means Text[2] is safe to read (trailing zero) //
					unsigned int x = Text[1] - '0';
					unsigned int y = Text[2] - '0';
					
					if ( x >= MatWidth )
						return sq_throwerror(v,"x is out of range in matrix eXY expression");
					if ( y >= MatWidth )
						return sq_throwerror(v,"y is out of range in matrix eXY expression");
					
					Mat[x+(y*MatWidth)] = Value;
					sq_pushfloat(v,Value);
					
					return SQ_RETURN;
				}
				else {
					return sq_throwerror(v,"incomplete matrix eXY expression");
				}
			}
		}
	}
	else {
		return sq_throwerror(v,"cannot assign specified type to a matrix element");
	}

	sq_pushnull(v);				/* +1 */
	return sq_throwobject(v);	/* -1 */
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// mat2 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix2x2) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Mat,MatSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_get( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix2x2) / sizeof(Real);
	
	return qk_mat_get(v,Mat,MatSize,2);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_set( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix2x2) / sizeof(Real);
		
	return qk_mat_set(v,Mat,MatSize,2);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_tomat3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 0.0f;

	Ret[3] = Arr[2];
	Ret[4] = Arr[3];
	Ret[5] = 0.0f;

	Ret[6] = 0.0f;
	Ret[7] = 0.0f;
	Ret[8] = 1.0f;

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_tomat4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	Ret[4] = Arr[2];
	Ret[5] = Arr[3];
	Ret[6] = 0.0f;
	Ret[7] = 0.0f;

	Ret[8] = 0.0f;
	Ret[9] = 0.0f;
	Ret[10] = 1.0f;
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = 1.0f;

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("mat2",4);
	
	Ret[0] = 1.0f;
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 1.0f;
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_MAT_TOSTRING(Matrix2x2,qk_mat2_tostring,"[% 10.03f % 10.03f]\n[% 10.03f % 10.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat());
_FUNC_TYPEOF(Matrix2x2,qk_mat2_typeof,"mat2",4);
_MATH_LEN(Matrix2x2,qk_mat2_len);
_MAT_CLONED(Matrix2x2,qk_mat2_cloned);
_MAT_UNM(Matrix2x2,qk_mat2_unm);
_MAT_FUNC(Matrix2x2,qk_mat2_transpose,Transpose);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix2x2,Matrix2x2,QK_TAG_MAT2,+)
		_MATH_OP_TAG(Matrix2x2,Real,QK_TAG_SCALAR,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix2x2,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix2x2,Matrix2x2,QK_TAG_MAT2,-)
		_MATH_OP_TAG(Matrix2x2,Real,QK_TAG_SCALAR,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix2x2,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Matrix2x2,Matrix2x2,QK_TAG_MAT2,*)
		_MATH_OP_TAG(Matrix2x2,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG2(Matrix2x2,Matrix1x2,QK_TAG_VEC2,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix2x2,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix2x2,Matrix2x2,QK_TAG_MAT2,/)
		_MATH_OP_TAG(Matrix2x2,Real,QK_TAG_SCALAR,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix2x2,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// mat3 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix3x3) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Mat,MatSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_get( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix3x3) / sizeof(Real);
	
	return qk_mat_get(v,Mat,MatSize,3);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_set( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix3x3) / sizeof(Real);
		
	return qk_mat_set(v,Mat,MatSize,3);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_tomat4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = Arr[2];
	Ret[3] = 0.0f;

	Ret[4] = Arr[3];
	Ret[5] = Arr[4];
	Ret[6] = Arr[5];
	Ret[7] = 0.0f;

	Ret[8] = Arr[6];
	Ret[9] = Arr[7];
	Ret[10] = Arr[8];
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = 1.0f;

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("mat3",4);
	
	Ret[0] = 1.0f;
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;

	Ret[3] = 0.0f;
	Ret[4] = 1.0f;
	Ret[5] = 0.0f;

	Ret[6] = 0.0f;
	Ret[7] = 0.0f;
	Ret[8] = 1.0f;
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_MAT_TOSTRING(Matrix3x3,qk_mat3_tostring,"[% 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat(),(*Mat)[4].ToFloat(),(*Mat)[5].ToFloat(),(*Mat)[6].ToFloat(),(*Mat)[7].ToFloat(),(*Mat)[8].ToFloat());
_FUNC_TYPEOF(Matrix3x3,qk_mat3_typeof,"mat3",4);
_MATH_LEN(Matrix3x3,qk_mat3_len);
_MAT_CLONED(Matrix3x3,qk_mat3_cloned);
_MAT_UNM(Matrix3x3,qk_mat3_unm);
_MAT_FUNC(Matrix3x3,qk_mat3_transpose,Transpose);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix3x3,Matrix3x3,QK_TAG_MAT3,+)
		_MATH_OP_TAG(Matrix3x3,Real,QK_TAG_SCALAR,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix3x3,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix3x3,Matrix3x3,QK_TAG_MAT3,-)
		_MATH_OP_TAG(Matrix3x3,Real,QK_TAG_SCALAR,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix3x3,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Matrix3x3,Matrix3x3,QK_TAG_MAT3,*)
		_MATH_OP_TAG(Matrix3x3,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG2(Matrix3x3,Matrix1x3,QK_TAG_VEC2,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix3x3,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix3x3,Matrix3x3,QK_TAG_MAT3,/)
		_MATH_OP_TAG(Matrix3x3,Real,QK_TAG_SCALAR,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix3x3,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// mat4 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix4x4) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Mat,MatSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_get( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix4x4) / sizeof(Real);
	
	return qk_mat_get(v,Mat,MatSize,4);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_set( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix4x4) / sizeof(Real);
		
	return qk_mat_set(v,Mat,MatSize,4);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("mat4",4);
	
	Ret[0] = 1.0f;
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	Ret[4] = 0.0f;
	Ret[5] = 1.0f;
	Ret[6] = 0.0f;
	Ret[7] = 0.0f;

	Ret[8] = 0.0f;
	Ret[9] = 0.0f;
	Ret[10] = 1.0f;
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = 1.0f;
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_MAT_TOSTRING(Matrix4x4,qk_mat4_tostring,"[% 10.03f % 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f % 10.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat(),(*Mat)[4].ToFloat(),(*Mat)[5].ToFloat(),(*Mat)[6].ToFloat(),(*Mat)[7].ToFloat(),(*Mat)[8].ToFloat(),(*Mat)[9].ToFloat(),(*Mat)[10].ToFloat(),(*Mat)[11].ToFloat(),(*Mat)[12].ToFloat(),(*Mat)[13].ToFloat(),(*Mat)[14].ToFloat(),(*Mat)[15].ToFloat());
_FUNC_TYPEOF(Matrix4x4,qk_mat4_typeof,"mat4",4);
_MATH_LEN(Matrix4x4,qk_mat4_len);
_MAT_CLONED(Matrix4x4,qk_mat4_cloned);
_MAT_UNM(Matrix4x4,qk_mat4_unm);
_MAT_FUNC(Matrix4x4,qk_mat4_transpose,Transpose);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix4x4,Matrix4x4,QK_TAG_MAT4,+)
		_MATH_OP_TAG(Matrix4x4,Real,QK_TAG_SCALAR,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix4x4,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix4x4,Matrix4x4,QK_TAG_MAT4,-)
		_MATH_OP_TAG(Matrix4x4,Real,QK_TAG_SCALAR,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix4x4,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Matrix4x4,Matrix4x4,QK_TAG_MAT4,*)
		_MATH_OP_TAG(Matrix4x4,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG2(Matrix4x4,Matrix1x4,QK_TAG_VEC2,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix4x4,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
//		_MATH_OP_TAG(Matrix4x4,Matrix4x4,QK_TAG_MAT4,/)
		_MATH_OP_TAG(Matrix4x4,Real,QK_TAG_SCALAR,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Matrix4x4,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMatrixIdentity( HSQUIRRELVM v ) {
	// Check the number of arguments //
	//int Top = sq_gettop(v);

	// Create an instance of the QkColor Class //
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"mat4",4);			// +1 //
	sq_get(v,-2);						// =0 //
	sq_createinstance(v,-1);			// +1 //

	// Retrieve Data (Pointer) //
	Matrix4x4* Mat;
	sq_getinstanceup(v,-1,(void**)&Mat,0);

	(*Mat) = Matrix4x4::Identity;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMatrixRotationXY( HSQUIRRELVM v ) {
	// Check the number of arguments //
	//int Top = sq_gettop(v);

	// Create an instance of the QkColor Class //
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"mat4",4);			// +1 //
	sq_get(v,-2);						// =0 //
	sq_createinstance(v,-1);			// +1 //

	// Retrieve Data (Pointer) //
	Matrix4x4* Mat;
	sq_getinstanceup(v,-1,(void**)&Mat,0);

	// Get Angle //
	float Angle = 0.0f;
	sq_getfloat(v,2,&Angle);

	Real SinA = Real(Angle).Sin();
	Real CosA = Real(Angle).Cos();

	(*Mat) = Matrix4x4::Identity;
	(*Mat)[0] = CosA;
	(*Mat)[1] = SinA;
	(*Mat)[4] = -SinA;
	(*Mat)[5] = CosA;
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMatrixRotationXZ( HSQUIRRELVM v ) {
	// Check the number of arguments //
	//int Top = sq_gettop(v);

	// Create an instance of the QkColor Class //
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"mat4",4);			// +1 //
	sq_get(v,-2);						// =0 //
	sq_createinstance(v,-1);			// +1 //

	// Retrieve Data (Pointer) //
	Matrix4x4* Mat;
	sq_getinstanceup(v,-1,(void**)&Mat,0);

	// Get Angle //
	float Angle = 0.0f;
	sq_getfloat(v,2,&Angle);

	Real SinA = Real(Angle).Sin();
	Real CosA = Real(Angle).Cos();

	(*Mat) = Matrix4x4::Identity;
	(*Mat)[0] = CosA;
	(*Mat)[2] = SinA;
	(*Mat)[8] = -SinA;
	(*Mat)[10] = CosA;
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMatrixRotationYZ( HSQUIRRELVM v ) {
	// Check the number of arguments //
	//int Top = sq_gettop(v);

	// Create an instance of the QkColor Class //
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"mat4",4);			// +1 //
	sq_get(v,-2);						// =0 //
	sq_createinstance(v,-1);			// +1 //

	// Retrieve Data (Pointer) //
	Matrix4x4* Mat;
	sq_getinstanceup(v,-1,(void**)&Mat,0);

	// Get Angle //
	float Angle = 0.0f;
	sq_getfloat(v,2,&Angle);

	Real SinA = Real(Angle).Sin();
	Real CosA = Real(Angle).Cos();

	(*Mat) = Matrix4x4::Identity;
	(*Mat)[5] = CosA;
	(*Mat)[6] = SinA;
	(*Mat)[9] = -SinA;
	(*Mat)[10] = CosA;
	
	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qkMatrixScalar( HSQUIRRELVM v ) {
	// Check the number of arguments //
	int NumArgs = sq_gettop(v);

	// Create an instance of the QkColor Class //
	sq_pushroottable(v);				// +1 //
	sq_pushstring(v,"mat4",4);			// +1 //
	sq_get(v,-2);						// =0 //
	sq_createinstance(v,-1);			// +1 //

	// Retrieve Data (Pointer) //
	Matrix4x4* Mat;
	sq_getinstanceup(v,-1,(void**)&Mat,0);	
	
	float x = 1.0f;
	float y = 1.0f;
	float z = 1.0f;
	float w = 1.0f;

	if ( NumArgs >= 2 ) {
		sq_getfloat(v,2,&x);
	}
	if ( NumArgs >= 3 ) {
		sq_getfloat(v,3,&y);
	}
	if ( NumArgs >= 4 ) {
		sq_getfloat(v,4,&z);
	}
	if ( NumArgs >= 5 ) {
		sq_getfloat(v,5,&w);
	}

	(*Mat) = Matrix4x4::Identity;
	(*Mat)(0,0) = x;
	(*Mat)(1,1) = y;
	(*Mat)(2,2) = z;
	(*Mat)(3,3) = w;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkMatrix_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qk_mat2_constructor,-1,NULL),
	_DECL_FUNC(qk_mat2_get,2,NULL),
	_DECL_FUNC(qk_mat2_set,3,NULL),
	_DECL_FUNC(qk_mat2_identity,0,NULL),
	_DECL_FUNC(qk_mat2_tostring,1,NULL),
	_DECL_FUNC(qk_mat2_typeof,0,NULL),
	_DECL_FUNC(qk_mat2_len,0,NULL),
	_DECL_FUNC(qk_mat2_cloned,2,NULL),
	_DECL_FUNC(qk_mat2_unm,1,NULL),
	_DECL_FUNC(qk_mat2_add,2,NULL),
	_DECL_FUNC(qk_mat2_sub,2,NULL),
	_DECL_FUNC(qk_mat2_mul,2,NULL),
	_DECL_FUNC(qk_mat2_div,2,NULL),
	_DECL_FUNC(qk_mat2_transpose,1,NULL),
	_DECL_FUNC(qk_mat2_tomat3,1,NULL),
	_DECL_FUNC(qk_mat2_tomat4,1,NULL),	

	_DECL_FUNC(qk_mat3_constructor,-1,NULL),
	_DECL_FUNC(qk_mat3_get,2,NULL),
	_DECL_FUNC(qk_mat3_set,3,NULL),
	_DECL_FUNC(qk_mat3_identity,0,NULL),
	_DECL_FUNC(qk_mat3_tostring,1,NULL),
	_DECL_FUNC(qk_mat3_len,0,NULL),
	_DECL_FUNC(qk_mat3_typeof,0,NULL),
	_DECL_FUNC(qk_mat3_cloned,2,NULL),
	_DECL_FUNC(qk_mat3_unm,1,NULL),
	_DECL_FUNC(qk_mat3_add,2,NULL),
	_DECL_FUNC(qk_mat3_sub,2,NULL),
	_DECL_FUNC(qk_mat3_mul,2,NULL),
	_DECL_FUNC(qk_mat3_div,2,NULL),
	_DECL_FUNC(qk_mat3_transpose,1,NULL),
	_DECL_FUNC(qk_mat3_tomat4,1,NULL),

	_DECL_FUNC(qk_mat4_constructor,-1,NULL),
	_DECL_FUNC(qk_mat4_get,2,NULL),
	_DECL_FUNC(qk_mat4_set,3,NULL),
	_DECL_FUNC(qk_mat4_identity,0,NULL),
	_DECL_FUNC(qk_mat4_tostring,1,NULL),
	_DECL_FUNC(qk_mat4_typeof,0,NULL),
	_DECL_FUNC(qk_mat4_len,0,NULL),
	_DECL_FUNC(qk_mat4_cloned,2,NULL),
	_DECL_FUNC(qk_mat4_unm,1,NULL),
	_DECL_FUNC(qk_mat4_add,2,NULL),
	_DECL_FUNC(qk_mat4_sub,2,NULL),
	_DECL_FUNC(qk_mat4_mul,2,NULL),
	_DECL_FUNC(qk_mat4_div,2,NULL),
	_DECL_FUNC(qk_mat4_transpose,1,NULL),

	// Standalone Functions //
	_DECL_FUNC(qkMatrixIdentity,1,NULL),
	_DECL_FUNC(qkMatrixRotationXY,2,NULL),
	_DECL_FUNC(qkMatrixRotationXZ,2,NULL),
	_DECL_FUNC(qkMatrixRotationYZ,2,NULL),
	_DECL_FUNC(qkMatrixScalar,-2,NULL),

	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkMatrix(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkMatrix_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	int Root = sq_gettop(v); 		// root table pos //
	{
		_ADD_CLASS_START(Matrix2x2,"mat2",QK_TAG_MAT2);
		_CLASS_ADDFUNC(qk_mat2_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat2_get,_get);
		_CLASS_ADDFUNC(qk_mat2_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_mat2_identity,identity);
		_CLASS_ADDFUNC(qk_mat2_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_mat2_typeof,_typeof);
		_CLASS_ADDFUNC_STATIC(qk_mat2_len,len);
		_CLASS_ADDFUNC(qk_mat2_cloned,_cloned);
		_CLASS_ADDFUNC(qk_mat2_unm,_unm);
		_CLASS_ADDFUNC(qk_mat2_add,_add);
		_CLASS_ADDFUNC(qk_mat2_sub,_sub);
		_CLASS_ADDFUNC(qk_mat2_mul,_mul);
		_CLASS_ADDFUNC(qk_mat2_div,_div);
		_CLASS_ADDFUNC(qk_mat2_transpose,transpose);
		_CLASS_ADDFUNC(qk_mat2_tomat3,tomat3);
		_CLASS_ADDFUNC(qk_mat2_tomat4,tomat4);
		_ADD_CLASS_END(Matrix2x2);
	}
	{
		_ADD_CLASS_START(Matrix3x3,"mat3",QK_TAG_MAT3);
		_CLASS_ADDFUNC(qk_mat3_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat3_get,_get);
		_CLASS_ADDFUNC(qk_mat3_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_mat3_identity,identity);
		_CLASS_ADDFUNC(qk_mat3_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_mat3_typeof,_typeof);
		_CLASS_ADDFUNC_STATIC(qk_mat3_len,len);
		_CLASS_ADDFUNC(qk_mat3_cloned,_cloned);
		_CLASS_ADDFUNC(qk_mat3_unm,_unm);
		_CLASS_ADDFUNC(qk_mat3_add,_add);
		_CLASS_ADDFUNC(qk_mat3_sub,_sub);
		_CLASS_ADDFUNC(qk_mat3_mul,_mul);
		_CLASS_ADDFUNC(qk_mat3_div,_div);
		_CLASS_ADDFUNC(qk_mat3_transpose,transpose);
		_CLASS_ADDFUNC(qk_mat3_tomat4,tomat4);
		_ADD_CLASS_END(Matrix3x3);
	}
	{
		_ADD_CLASS_START(Matrix4x4,"mat4",QK_TAG_MAT4);
		_CLASS_ADDFUNC(qk_mat4_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat4_get,_get);
		_CLASS_ADDFUNC(qk_mat4_set,_set);
		_CLASS_ADDFUNC_STATIC(qk_mat4_identity,identity);
		_CLASS_ADDFUNC(qk_mat4_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_mat4_typeof,_typeof);
		_CLASS_ADDFUNC_STATIC(qk_mat4_len,len);
		_CLASS_ADDFUNC(qk_mat4_cloned,_cloned);
		_CLASS_ADDFUNC(qk_mat4_unm,_unm);
		_CLASS_ADDFUNC(qk_mat4_add,_add);
		_CLASS_ADDFUNC(qk_mat4_sub,_sub);
		_CLASS_ADDFUNC(qk_mat4_mul,_mul);
		_CLASS_ADDFUNC(qk_mat4_div,_div);
		_CLASS_ADDFUNC(qk_mat4_transpose,transpose);
		_ADD_CLASS_END(Matrix4x4);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
	