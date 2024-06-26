// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_Squirrel.h>
#include "QuackLib_Internal.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Math/Matrix.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// _tostring //
#define _VEC_TOSTRING(_TYPE_,_NAME_,...) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Vec; \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	char Text[(24*4)+2+3+1]; \
	sprintf(Text, __VA_ARGS__ ); \
	\
	sq_pushstring(v,Text,-1); \
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// _cloned //
#define _VEC_CLONED(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Vec; /* +1 */ \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	*Vec = *Vs; \
	\
	return SQ_VOID; \
}
// - ------------------------------------------------------------------------------------------ - //
// cross //
#define _VEC_VS_RETURNS_VEC(_TYPE_,_NAME_,_OP_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	*Vec = (*Vec)._OP_(*Vs); \
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// mix //
#define _VEC_VS_ALPHA_RETURNS_VEC(_TYPE_,_NAME_,_OP_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	float Alpha; \
	sq_getfloat(v,3,&Alpha); \
	\
	*Vec = (*Vec)._OP_(*Vs,Alpha); \
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// dot //
#define _VEC_VS_RETURNS_FLOAT(_TYPE_,_NAME_,_OP_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Vec; \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	sq_pushfloat( v, (*Vec)._OP_(*Vs).ToFloat() ); \
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// _unm (i.e. negative) //
#define _VEC_UNM(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	*Vec = -(*Vec);\
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// Functions Returning a Vector //
#define _VEC_FUNC_RETURNS_VEC(_TYPE_,_NAME_,_FUNC_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	*Vec = Vec->_FUNC_();\
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
#define _VEC_FUNC_SELF_RETURNS_VEC(_TYPE_,_NAME_,_FUNC_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Vec; \
	sq_getinstanceup(v,-1,(void**)&Vec,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,1,(void**)&Vs,0); \
	\
	*Vec = Vs->_FUNC_();\
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //
// Functions Returning a Float //
#define _VEC_FUNC_RETURNS_FLOAT(_TYPE_,_NAME_,_FUNC_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	_TYPE_* Vec; \
	sq_getinstanceup(v,1,(void**)&Vec,0); \
	\
	sq_pushfloat( v, Vec->_FUNC_().ToFloat() ); /* +1 */ \
	\
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_vec_get( HSQUIRRELVM v, const unsigned int VecWidth ) {
	float* Vec;
	sq_getinstanceup(v,1,(void**)&Vec,0);

	const int Type = sq_gettype(v,2);
	if ( Type == OT_STRING ) {
		const char* Text;
		sq_getstring(v,2,&Text);
	
		// NOTE: MyVec[""] may out-of-bounds this. //
		// Indexing //
		if ( Text[1] == 0 ) {	// One character, zero terminated.
			unsigned int Index = Text[0] - 'x';
			if ( Index < VecWidth ) {
				sq_pushfloat(v,Vec[Index]);
				return SQ_RETURN;
			}
			else if ( Text[0] == 'w' && (VecWidth >= 4) ) {
				sq_pushfloat(v,Vec[3]);
				return SQ_RETURN;
			}
			else if ( Text[0] == '_' ) {
				return sq_throwerror(v,"Vector swizzle operator _ without any swizzle mask.");
			}
		}
		// Swizzle //
		else {
			int Len = strlen( Text );
			const char* Str = Text;
			unsigned int StrSize = Len;
			if ( Text[0] == '_' ) {
				Str = &Text[1];
				StrSize--;
			}
			
			if ( StrSize <= 4 ) {
				sq_pushroottable(v);
				// NOTE: Zero size (_) already handled //
				if ( StrSize == 1 ) {
					sq_pushstring(v,"scalar",6);	// +1 //
					sq_get(v,-2);					// =0 //
					sq_createinstance(v,-1);		// +1 //
				}
				else if ( StrSize == 2 ) {
					sq_pushstring(v,"vec2",4);		// +1 //
					sq_get(v,-2);					// =0 //
					sq_createinstance(v,-1);		// +1 //
				}
				else if ( StrSize == 3 ) {
					sq_pushstring(v,"vec3",4);		// +1 //
					sq_get(v,-2);					// =0 //
					sq_createinstance(v,-1);		// +1 //
				}
				else {
					sq_pushstring(v,"vec4",4);		// +1 //
					sq_get(v,-2);					// =0 //
					sq_createinstance(v,-1);		// +1 //
				}
				
				float* Ret;
				sq_getinstanceup(v,-1,(void**)&Ret,0);
				
				unsigned int Index = 0;
				while ( Index != StrSize ) {
					unsigned int ArgIndex = Str[Index] - 'x';
					if ( ArgIndex < StrSize ) {
						Ret[Index] = Vec[ArgIndex];
					}
					else if ( Str[Index] == 'w' && (StrSize >= 4) ) {
						Ret[Index] = Vec[3];
					}
					else if ( Str[Index] == '0' ) {
						Ret[Index] = 0.0f;
					}
					else if ( Str[Index] == '1' ) {
						Ret[Index] = 1.0f;
					}
					Index++;
				}

				return SQ_RETURN;
			}
//			else {
//				return sq_throwerror(v,"Too many characters used in vector swizzle mask.");
//			}
		}
	}
	// Array Style Indexing. I.e. MyVec[0] for x.
	else if ( Type == OT_INTEGER ) {		
		SQInteger Index;
		sq_getinteger(v,2,&Index);
		
		if ( Index < VecWidth ) {
			sq_pushfloat(v,Vec[Index]);	// +1 //
			return SQ_RETURN;
		}
		else {
			return sq_throwerror(v,"Vector index out of range");
		}
	}
	
	sq_pushnull(v);				/* +1 */
	return sq_throwobject(v);	/* -1 */
}
// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_vec_set( HSQUIRRELVM v, const unsigned int VecWidth ) {
	if ( sq_gettype(v,3) & (OT_FLOAT|OT_INTEGER) ) {
		float Value;
		sq_getfloat(v,3,&Value);

		float* Vec;
		sq_getinstanceup(v,1,(void**)&Vec,0);

		const int Type = sq_gettype(v,2);
		if ( Type == OT_STRING ) {
			const char* Text;
			sq_getstring(v,2,&Text);
		
			// NOTE: MyVec[""] may out-of-bounds this. //
			// Indexing //
			if ( Text[1] == 0 ) {	// One character, zero terminated.
				unsigned int Index = Text[0] - 'x';
				if ( Index < VecWidth ) {
					Vec[Index] = Value;
					sq_pushfloat( v, Value );
					return SQ_RETURN;
				}
				else if ( Text[0] == 'w' && (VecWidth >= 4) ) {
					Vec[3] = Value;
					sq_pushfloat( v, Value );
					return SQ_RETURN;
				}
			}
		}
		else if ( Type == OT_INTEGER ) {
			SQInteger Index;
			sq_getinteger(v,2,&Index);
	
			if ( Index < (unsigned int)VecWidth ) {
				Vec[Index] = Value;
				sq_pushfloat(v,Value);
				return SQ_RETURN;
			}
			else {
				return sq_throwerror(v,"vector element index is out of range");
			}
		}
	}
	else {
		return sq_throwerror(v,"cannot assign specified type to a vector element");
	}

	sq_pushnull(v);				/* +1 */
	return sq_throwobject(v);	/* -1 */
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// scalar --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_constructor( HSQUIRRELVM v ) {
	float* Arr;
	sq_getinstanceup(v,1,(void**)&Arr,0);
	const int ArrSize = sizeof(Real) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Arr,ArrSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_get( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Real) / sizeof(Real);
	return qk_vec_get( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_set( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Real) / sizeof(Real);
	return qk_vec_set( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. All new elements are zero. //
SQInteger qk_scalar_tovec2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling up type, last element becomes 1 //
SQInteger qk_scalar_tohvec2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// i = identity. I.e. When scaling up type, all new elements become 1 //
SQInteger qk_scalar_toivec2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. All new elements are zero. //
SQInteger qk_scalar_tovec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling up type, last element becomes 1 //
SQInteger qk_scalar_tohvec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// i = identity. I.e. When scaling up type, all new elements become 1 //
SQInteger qk_scalar_toivec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 1.0f;
	Ret[2] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. All new elements are zero. //
SQInteger qk_scalar_tovec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling up type, last element becomes 1 //
SQInteger qk_scalar_tohvec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// i = identity. I.e. When scaling up type, all new elements become 1 //
SQInteger qk_scalar_toivec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 1.0f;
	Ret[2] = 1.0f;
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_tofloat( HSQUIRRELVM v ) {
	Real* Vec;
	sq_getinstanceup(v,1,(void**)&Vec,0);

	sq_pushfloat(v,Vec->ToFloat()); // +1 //

	return SQ_RETURN;	
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_scalar_tomat2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 1.0f; // Identity //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_scalar_tomat3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;

	Ret[3] = 0.0f;
	Ret[4] = 1.0f; // Identity //
	Ret[5] = 0.0f;

	Ret[6] = 0.0f;
	Ret[7] = 0.0f;
	Ret[8] = 1.0f; // Identity //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_scalar_tomat4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	Ret[4] = 0.0f;
	Ret[5] = 1.0f; // Identity //
	Ret[6] = 0.0f;
	Ret[7] = 0.0f;

	Ret[8] = 0.0f;
	Ret[9] = 0.0f;
	Ret[10] = 1.0f; // Identity //
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = 1.0f; // Identity //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// scalar.identity() //
SQInteger qk_scalar_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("scalar",6);
	
	Ret[0] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_VEC_TOSTRING(Real,qk_scalar_tostring,"(%0.03f)",Vec->ToFloat());
_FUNC_TYPEOF(Real,qk_scalar_typeof,"scalar",6);
_VEC_CLONED(Real,qk_scalar_cloned);
_MATH_LEN(Real,qk_scalar_len);
_VEC_UNM(Real,qk_scalar_unm);
_VEC_FUNC_RETURNS_VEC(Real,qk_scalar_flipx,FlipX);
_VEC_FUNC_RETURNS_VEC(Real,qk_scalar_xaxis,XAxis);
_VEC_FUNC_RETURNS_VEC(Real,qk_scalar_normal,Normal);
_VEC_FUNC_SELF_RETURNS_VEC(Real,qk_scalar_normalize,Normalize);
_VEC_FUNC_RETURNS_FLOAT(Real,qk_scalar_normalizeret,NormalizeRet);
_VEC_FUNC_RETURNS_FLOAT(Real,qk_scalar_magnitude,Magnitude);
_VEC_FUNC_RETURNS_FLOAT(Real,qk_scalar_magnitudesquared,MagnitudeSquared);
_VEC_FUNC_RETURNS_FLOAT(Real,qk_scalar_manhattan,Manhattan);
//_VEC_FUNC_RETURNS_FLOAT(Real,qk_scalar_minitude,Minitude);
//_VEC_FUNC_RETURNS_FLOAT(Real,qk_scalar_maxitude,Maxitude);
//_VEC_VS_RETURNS_FLOAT(Real,qk_scalar_dot,dot);
_VEC_VS_ALPHA_RETURNS_VEC(Real,qk_scalar_mix,mix);
//_VEC_FUNC_RETURNS_VEC(Real,qk_scalar_tangent,Tangent);
//_VEC_FUNC_RETURNS_VEC(Real,qk_scalar_rotate45,Rotate45);
//_VEC_FUNC_RETURNS_VEC(Real,qk_scalar_rotatenegative45,RotateNegative45);
//_VEC_VS_RETURNS_VEC(Real,qk_scalar_cross,cross);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Real,Real,QK_TAG_SCALAR,+)
		_MATH_OP_TAG2(Real,Vector2D,QK_TAG_VEC2,+)
		_MATH_OP_TAG2(Real,Vector3D,QK_TAG_VEC3,+)
		_MATH_OP_TAG2(Real,Vector4D,QK_TAG_VEC4,+)
//		_MATH_OP_TAG2(Real,Matrix2x2,QK_TAG_MAT2,+)
//		_MATH_OP_TAG2(Real,Matrix3x3,QK_TAG_MAT3,+)
//		_MATH_OP_TAG2(Real,Matrix4x4,QK_TAG_MAT4,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Real,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Real,Real,QK_TAG_SCALAR,-)
		_MATH_OP_TAG2(Real,Vector2D,QK_TAG_VEC2,-)
		_MATH_OP_TAG2(Real,Vector3D,QK_TAG_VEC3,-)
		_MATH_OP_TAG2(Real,Vector4D,QK_TAG_VEC4,-)
//		_MATH_OP_TAG2(Real,Matrix2x2,QK_TAG_MAT2,-)
//		_MATH_OP_TAG2(Real,Matrix3x3,QK_TAG_MAT3,-)
//		_MATH_OP_TAG2(Real,Matrix4x4,QK_TAG_MAT4,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Real,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Real,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG2(Real,Vector2D,QK_TAG_VEC2,*)
		_MATH_OP_TAG2(Real,Vector3D,QK_TAG_VEC3,*)
		_MATH_OP_TAG2(Real,Vector4D,QK_TAG_VEC4,*)
		_MATH_OP_TAG2(Real,Matrix2x2,QK_TAG_MAT2,*)
		_MATH_OP_TAG2(Real,Matrix3x3,QK_TAG_MAT3,*)
		_MATH_OP_TAG2(Real,Matrix4x4,QK_TAG_MAT4,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Real,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_scalar_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Real,Real,QK_TAG_SCALAR,/)
		_MATH_OP_TAG2(Real,Vector2D,QK_TAG_VEC2,/)
		_MATH_OP_TAG2(Real,Vector3D,QK_TAG_VEC3,/)
		_MATH_OP_TAG2(Real,Vector4D,QK_TAG_VEC4,/)
//		_MATH_OP_TAG2(Real,Matrix2x2,QK_TAG_MAT2,/)
//		_MATH_OP_TAG2(Real,Matrix3x3,QK_TAG_MAT3,/)
//		_MATH_OP_TAG2(Real,Matrix4x4,QK_TAG_MAT4,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Real,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// vec2 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_constructor( HSQUIRRELVM v ) {
	float* Arr;
	sq_getinstanceup(v,1,(void**)&Arr,0);
	const int ArrSize = sizeof(Vector2D) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Arr,ArrSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_get( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Vector2D) / sizeof(Real);
	return qk_vec_get( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_set( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Vector2D) / sizeof(Real);
	return qk_vec_set( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. Old elements are disposed of. //
SQInteger qk_vec2_toscalar( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("scalar",6);
	
	Ret[0] = Arr[0];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling down type, divide by last element. //
SQInteger qk_vec2_tohscalar( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0] / Arr[1];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. All new elements are zero. //
SQInteger qk_vec2_tovec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 0.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling up type, last element becomes 1 //
SQInteger qk_vec2_tohvec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// i = identity. I.e. When scaling up type, all new elements become 1 //
SQInteger qk_vec2_toivec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. All new elements are zero. //
SQInteger qk_vec2_tovec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling up type, last element becomes 1 //
SQInteger qk_vec2_tohvec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 0.0f;
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// i = identity. I.e. When scaling up type, all new elements become 1 //
SQInteger qk_vec2_toivec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = 1.0f;
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec2_tomat2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = Arr[1];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec2_tomat3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;

	Ret[3] = 0.0f;
	Ret[4] = Arr[1];
	Ret[5] = 0.0f;

	Ret[6] = 0.0f;
	Ret[7] = 0.0f;
	Ret[8] = 1.0f; // Identity //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec2_tomat4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	Ret[4] = 0.0f;
	Ret[5] = Arr[1];
	Ret[6] = 0.0f;
	Ret[7] = 0.0f;

	Ret[8] = 0.0f;
	Ret[9] = 0.0f;
	Ret[10] = 1.0f; // Identity //
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = 1.0f; // Identity //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// vec2.identity() //
SQInteger qk_vec2_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("vec2",4);
	
	Ret[0] = 1.0f;
	Ret[1] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_VEC_TOSTRING(Vector2D,qk_vec2_tostring,"(%0.03f,%0.03f)",Vec->x.ToFloat(),Vec->y.ToFloat());
_FUNC_TYPEOF(Vector2D,qk_vec2_typeof,"vec2",4);
_VEC_CLONED(Vector2D,qk_vec2_cloned);
_MATH_LEN(Vector2D,qk_vec2_len);
_VEC_UNM(Vector2D,qk_vec2_unm);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_flipx,FlipX);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_flipy,FlipY);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_xaxis,XAxis);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_yaxis,YAxis);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_normal,Normal);
_VEC_FUNC_SELF_RETURNS_VEC(Vector2D,qk_vec2_normalize,Normalize);
_VEC_FUNC_RETURNS_FLOAT(Vector2D,qk_vec2_normalizeret,NormalizeRet);
_VEC_FUNC_RETURNS_FLOAT(Vector2D,qk_vec2_magnitude,Magnitude);
_VEC_FUNC_RETURNS_FLOAT(Vector2D,qk_vec2_magnitudesquared,MagnitudeSquared);
_VEC_FUNC_RETURNS_FLOAT(Vector2D,qk_vec2_manhattan,Manhattan);
_VEC_FUNC_RETURNS_FLOAT(Vector2D,qk_vec2_minitude,Minitude);
_VEC_FUNC_RETURNS_FLOAT(Vector2D,qk_vec2_maxitude,Maxitude);
_VEC_VS_RETURNS_FLOAT(Vector2D,qk_vec2_dot,dot);
_VEC_VS_ALPHA_RETURNS_VEC(Vector2D,qk_vec2_mix,mix);

_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_tangent,Tangent);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_rotate45,Rotate45);
_VEC_FUNC_RETURNS_VEC(Vector2D,qk_vec2_rotatenegative45,RotateNegative45);
//_VEC_VS_RETURNS_VEC(Vector2D,qk_vec2_cross,cross);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector2D,Vector2D,QK_TAG_VEC2,+)
		_MATH_OP_TAG(Vector2D,Real,QK_TAG_SCALAR,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector2D,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector2D,Vector2D,QK_TAG_VEC2,-)
		_MATH_OP_TAG(Vector2D,Real,QK_TAG_SCALAR,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector2D,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector2D,Vector2D,QK_TAG_VEC2,*)
		_MATH_OP_TAG(Vector2D,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG(Matrix2x1,Matrix2x2,QK_TAG_MAT2,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector2D,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec2_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector2D,Vector2D,QK_TAG_VEC2,/)
		_MATH_OP_TAG(Vector2D,Real,QK_TAG_SCALAR,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector2D,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// vec3 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_constructor( HSQUIRRELVM v ) {
	float* Arr;
	sq_getinstanceup(v,1,(void**)&Arr,0);
	const int ArrSize = sizeof(Vector3D) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Arr,ArrSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_get( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Vector3D) / sizeof(Real);
	return qk_vec_get( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_set( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Vector3D) / sizeof(Real);
	return qk_vec_set( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. Old elements are disposed of. //
SQInteger qk_vec3_toscalar( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("scalar",6);
	
	Ret[0] = Arr[0];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. Old elements are disposed of. //
SQInteger qk_vec3_tovec2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling down type, divide by last element. //
SQInteger qk_vec3_tohvec2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0] / Arr[2];
	Ret[1] = Arr[1] / Arr[2];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. All new elements are zero. //
SQInteger qk_vec3_tovec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = Arr[2];
	Ret[3] = 0.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling up type, last element becomes 1 //
SQInteger qk_vec3_tohvec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = Arr[2];
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// i = identity. I.e. When scaling up type, all new elements become 1 //
SQInteger qk_vec3_toivec4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = Arr[2];
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec3_tomat2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = Arr[1];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec3_tomat3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;

	Ret[3] = 0.0f;
	Ret[4] = Arr[1];
	Ret[5] = 0.0f;

	Ret[6] = 0.0f;
	Ret[7] = 0.0f;
	Ret[8] = Arr[2];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec3_tomat4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	Ret[4] = 0.0f;
	Ret[5] = Arr[1];
	Ret[6] = 0.0f;
	Ret[7] = 0.0f;

	Ret[8] = 0.0f;
	Ret[9] = 0.0f;
	Ret[10] = Arr[2];
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = 1.0f; // Identity //

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// vec3.identity() //
SQInteger qk_vec3_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("vec3",4);
	
	Ret[0] = 1.0f;
	Ret[1] = 1.0f;
	Ret[2] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_VEC_TOSTRING(Vector3D,qk_vec3_tostring,"(%0.03f,%0.03f,%0.03f)",Vec->x.ToFloat(),Vec->y.ToFloat(),Vec->z.ToFloat());
_FUNC_TYPEOF(Vector3D,qk_vec3_typeof,"vec3",4);
_VEC_CLONED(Vector3D,qk_vec3_cloned);
_MATH_LEN(Vector3D,qk_vec3_len);
_VEC_UNM(Vector3D,qk_vec3_unm);
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_flipx,FlipX);
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_flipy,FlipY);
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_flipz,FlipZ); // * //
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_xaxis,XAxis);
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_yaxis,YAxis);
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_zaxis,ZAxis); // * //
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_normal,Normal);
_VEC_FUNC_SELF_RETURNS_VEC(Vector3D,qk_vec3_normalize,Normalize);
_VEC_FUNC_RETURNS_FLOAT(Vector3D,qk_vec3_normalizeret,NormalizeRet);
_VEC_FUNC_RETURNS_FLOAT(Vector3D,qk_vec3_magnitude,Magnitude);
_VEC_FUNC_RETURNS_FLOAT(Vector3D,qk_vec3_magnitudesquared,MagnitudeSquared);
_VEC_FUNC_RETURNS_FLOAT(Vector3D,qk_vec3_manhattan,Manhattan);
//_VEC_FUNC_RETURNS_FLOAT(Vector3D,qk_vec3_minitude,Minitude);
//_VEC_FUNC_RETURNS_FLOAT(Vector3D,qk_vec3_maxitude,Maxitude);
_VEC_VS_RETURNS_FLOAT(Vector3D,qk_vec3_dot,dot);
_VEC_VS_ALPHA_RETURNS_VEC(Vector3D,qk_vec3_mix,mix);
_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_tangent,Tangent);
//_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_rotate45,Rotate45);
//_VEC_FUNC_RETURNS_VEC(Vector3D,qk_vec3_rotatenegative45,RotateNegative45);
_VEC_VS_RETURNS_VEC(Vector3D,qk_vec3_cross,cross);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector3D,Vector3D,QK_TAG_VEC3,+)
		_MATH_OP_TAG(Vector3D,Real,QK_TAG_SCALAR,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector3D,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector3D,Vector3D,QK_TAG_VEC3,-)
		_MATH_OP_TAG(Vector3D,Real,QK_TAG_SCALAR,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector3D,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector3D,Vector3D,QK_TAG_VEC3,*)
		_MATH_OP_TAG(Vector3D,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG(Matrix2x1,Matrix2x2,QK_TAG_MAT2,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector3D,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec3_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector3D,Vector3D,QK_TAG_VEC3,/)
		_MATH_OP_TAG(Vector3D,Real,QK_TAG_SCALAR,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector3D,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// vec4 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_constructor( HSQUIRRELVM v ) {
	float* Arr;
	sq_getinstanceup(v,1,(void**)&Arr,0);
	const int ArrSize = sizeof(Vector4D) / sizeof(Real);
	
	return qk_arr_constructor_body(v,Arr,ArrSize);
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_get( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Vector4D) / sizeof(Real);
	return qk_vec_get( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_set( HSQUIRRELVM v ) {
	const int VecSize = sizeof(Vector4D) / sizeof(Real);
	return qk_vec_set( v, VecSize );
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. Old elements are disposed of. //
SQInteger qk_vec4_toscalar( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("scalar",6);
	
	Ret[0] = Arr[0];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. Old elements are disposed of. //
SQInteger qk_vec4_tovec2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to vector conversion. Old elements are disposed of. //
SQInteger qk_vec4_tovec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = Arr[1];
	Ret[2] = Arr[2];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// h = homogeneous. I.e. When scaling down type, divide by last element. //
SQInteger qk_vec4_tohvec3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("vec3",4);
	
	Ret[0] = Arr[0] / Arr[3];
	Ret[1] = Arr[1] / Arr[3];
	Ret[2] = Arr[2] / Arr[3];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec4_tomat2( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat2",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = Arr[1];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec4_tomat3( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat3",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;

	Ret[3] = 0.0f;
	Ret[4] = Arr[1];
	Ret[5] = 0.0f;

	Ret[6] = 0.0f;
	Ret[7] = 0.0f;
	Ret[8] = Arr[2];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// Standard to Matrix conversion //
SQInteger qk_vec4_tomat4( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN("mat4",4);
	
	Ret[0] = Arr[0];
	Ret[1] = 0.0f;
	Ret[2] = 0.0f;
	Ret[3] = 0.0f;

	Ret[4] = 0.0f;
	Ret[5] = Arr[1];
	Ret[6] = 0.0f;
	Ret[7] = 0.0f;

	Ret[8] = 0.0f;
	Ret[9] = 0.0f;
	Ret[10] = Arr[2];
	Ret[11] = 0.0f;

	Ret[12] = 0.0f;
	Ret[13] = 0.0f;
	Ret[14] = 0.0f;
	Ret[15] = Arr[3];

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
// vec3.identity() //
SQInteger qk_vec4_identity( HSQUIRRELVM v ) {
	_ARR_TO_BEGIN_RETONLY("vec4",4);
	
	Ret[0] = 1.0f;
	Ret[1] = 1.0f;
	Ret[2] = 1.0f;
	Ret[3] = 1.0f;

	return SQ_RETURN;
}
// - ------------------------------------------------------------------------------------------ - //
_VEC_TOSTRING(Vector4D,qk_vec4_tostring,"(%0.03f,%0.03f,%0.03f,%0.03f)",Vec->x.ToFloat(),Vec->y.ToFloat(),Vec->z.ToFloat(),Vec->w.ToFloat());
_FUNC_TYPEOF(Vector4D,qk_vec4_typeof,"vec4",4);
_VEC_CLONED(Vector4D,qk_vec4_cloned);
_MATH_LEN(Vector4D,qk_vec4_len);
_VEC_UNM(Vector4D,qk_vec4_unm);
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_flipx,FlipX);
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_flipy,FlipY);
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_flipz,FlipZ); // * //
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_flipw,FlipW); // * //
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_xaxis,XAxis);
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_yaxis,YAxis);
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_zaxis,ZAxis); // * //
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_waxis,WAxis); // * //
_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_normal,Normal);
_VEC_FUNC_SELF_RETURNS_VEC(Vector4D,qk_vec4_normalize,Normalize);
_VEC_FUNC_RETURNS_FLOAT(Vector4D,qk_vec4_normalizeret,NormalizeRet);
_VEC_FUNC_RETURNS_FLOAT(Vector4D,qk_vec4_magnitude,Magnitude);
_VEC_FUNC_RETURNS_FLOAT(Vector4D,qk_vec4_magnitudesquared,MagnitudeSquared);
_VEC_FUNC_RETURNS_FLOAT(Vector4D,qk_vec4_manhattan,Manhattan);
//_VEC_FUNC_RETURNS_FLOAT(Vector4D,qk_vec4_minitude,Minitude);
//_VEC_FUNC_RETURNS_FLOAT(Vector4D,qk_vec4_maxitude,Maxitude);
_VEC_VS_RETURNS_FLOAT(Vector4D,qk_vec4_dot,dot);
_VEC_VS_ALPHA_RETURNS_VEC(Vector4D,qk_vec4_mix,mix);
//_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_tangent,Tangent);
//_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_rotate45,Rotate45);
//_VEC_FUNC_RETURNS_VEC(Vector4D,qk_vec4_rotatenegative45,RotateNegative45);
//_VEC_VS_RETURNS_VEC(Vector4D,qk_vec4_cross,cross);
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_add( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector4D,Vector4D,QK_TAG_VEC4,+)
		_MATH_OP_TAG(Vector4D,Real,QK_TAG_SCALAR,+)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector4D,+)
	_MATH_OP_END(+)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_sub( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector4D,Vector4D,QK_TAG_VEC4,-)
		_MATH_OP_TAG(Vector4D,Real,QK_TAG_SCALAR,-)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector4D,-)
	_MATH_OP_END(-)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_mul( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector4D,Vector4D,QK_TAG_VEC4,*)
		_MATH_OP_TAG(Vector4D,Real,QK_TAG_SCALAR,*)
		_MATH_OP_TAG(Matrix2x1,Matrix2x2,QK_TAG_MAT2,*)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector4D,*)
	_MATH_OP_END(*)
}
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_vec4_div( HSQUIRRELVM v ) {
	_MATH_OP_START()
	_MATH_OP_TYPE_START(OT_INSTANCE)
		_MATH_OP_TAG(Vector4D,Vector4D,QK_TAG_VEC4,/)
		_MATH_OP_TAG(Vector4D,Real,QK_TAG_SCALAR,/)
	_MATH_OP_TYPE_END()
	_MATH_OP_TYPE_FLOAT(Vector4D,/)
	_MATH_OP_END(/)
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkVector_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qk_scalar_constructor,-1,NULL),
	_DECL_FUNC(qk_scalar_identity,0,NULL),
	_DECL_FUNC(qk_scalar_get,2,NULL),
	_DECL_FUNC(qk_scalar_set,3,NULL),
	_DECL_FUNC(qk_scalar_typeof,0,NULL),
	_DECL_FUNC(qk_scalar_tostring,1,NULL),
	_DECL_FUNC(qk_scalar_cloned,2,NULL),
	_DECL_FUNC(qk_scalar_len,0,NULL),
	_DECL_FUNC(qk_scalar_add,2,NULL),
	_DECL_FUNC(qk_scalar_sub,2,NULL),
	_DECL_FUNC(qk_scalar_mul,2,NULL),
	_DECL_FUNC(qk_scalar_div,2,NULL),
	_DECL_FUNC(qk_scalar_unm,1,NULL),
	_DECL_FUNC(qk_scalar_flipx,1,NULL),
	_DECL_FUNC(qk_scalar_xaxis,1,NULL),
	_DECL_FUNC(qk_scalar_normal,1,NULL),
	_DECL_FUNC(qk_scalar_normalize,1,NULL),
	_DECL_FUNC(qk_scalar_normalizeret,1,NULL),
	_DECL_FUNC(qk_scalar_magnitude,1,NULL),
	_DECL_FUNC(qk_scalar_magnitudesquared,1,NULL),
	_DECL_FUNC(qk_scalar_manhattan,1,NULL),
//	_DECL_FUNC(qk_scalar_minitude,1,NULL),
//	_DECL_FUNC(qk_scalar_maxitude,1,NULL),
//	_DECL_FUNC(qk_scalar_dot,2,NULL),
	_DECL_FUNC(qk_scalar_mix,3,NULL),
//	_DECL_FUNC(qk_scalar_tangent,1,NULL),
//	_DECL_FUNC(qk_scalar_rotate45,1,NULL),
//	_DECL_FUNC(qk_scalar_rotatenegative45,1,NULL),
//	_DECL_FUNC(qk_scalar_cross,2,NULL),
	_DECL_FUNC(qk_scalar_tofloat,1,NULL),
	_DECL_FUNC(qk_scalar_tovec2,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_tohvec2,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_toivec2,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_tovec3,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_tohvec3,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_toivec3,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_tovec4,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_tohvec4,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_toivec4,1,NULL),	// + //
	_DECL_FUNC(qk_scalar_tomat2,1,NULL),
	_DECL_FUNC(qk_scalar_tomat3,1,NULL),
	_DECL_FUNC(qk_scalar_tomat4,1,NULL),
	
	_DECL_FUNC(qk_vec2_constructor,-1,NULL),
	_DECL_FUNC(qk_vec2_identity,0,NULL),
	_DECL_FUNC(qk_vec2_get,2,NULL),
	_DECL_FUNC(qk_vec2_set,3,NULL),
	_DECL_FUNC(qk_vec2_typeof,0,NULL),
	_DECL_FUNC(qk_vec2_tostring,1,NULL),
	_DECL_FUNC(qk_vec2_cloned,2,NULL),
	_DECL_FUNC(qk_vec2_len,0,NULL),
	_DECL_FUNC(qk_vec2_add,2,NULL),
	_DECL_FUNC(qk_vec2_sub,2,NULL),
	_DECL_FUNC(qk_vec2_mul,2,NULL),
	_DECL_FUNC(qk_vec2_div,2,NULL),
	_DECL_FUNC(qk_vec2_unm,1,NULL),
	_DECL_FUNC(qk_vec2_flipx,1,NULL),
	_DECL_FUNC(qk_vec2_flipy,1,NULL),
	_DECL_FUNC(qk_vec2_xaxis,1,NULL),
	_DECL_FUNC(qk_vec2_yaxis,1,NULL),
	_DECL_FUNC(qk_vec2_normal,1,NULL),
	_DECL_FUNC(qk_vec2_normalize,1,NULL),
	_DECL_FUNC(qk_vec2_normalizeret,1,NULL),
	_DECL_FUNC(qk_vec2_magnitude,1,NULL),
	_DECL_FUNC(qk_vec2_magnitudesquared,1,NULL),
	_DECL_FUNC(qk_vec2_manhattan,1,NULL),
	_DECL_FUNC(qk_vec2_minitude,1,NULL),
	_DECL_FUNC(qk_vec2_maxitude,1,NULL),
	_DECL_FUNC(qk_vec2_dot,2,NULL),
	_DECL_FUNC(qk_vec2_mix,3,NULL),
	_DECL_FUNC(qk_vec2_tangent,1,NULL),
	_DECL_FUNC(qk_vec2_rotate45,1,NULL),
	_DECL_FUNC(qk_vec2_rotatenegative45,1,NULL),
//	_DECL_FUNC(qk_vec2_cross,2,NULL),
	_DECL_FUNC(qk_vec2_toscalar,1,NULL),	// - //
	_DECL_FUNC(qk_vec2_tohscalar,1,NULL),	// - //
	_DECL_FUNC(qk_vec2_tovec3,1,NULL),		// + //
	_DECL_FUNC(qk_vec2_tohvec3,1,NULL),		// + //
	_DECL_FUNC(qk_vec2_toivec3,1,NULL),		// + //
	_DECL_FUNC(qk_vec2_tovec4,1,NULL),		// + //
	_DECL_FUNC(qk_vec2_tohvec4,1,NULL),		// + //
	_DECL_FUNC(qk_vec2_toivec4,1,NULL),		// + //
	_DECL_FUNC(qk_vec2_tomat2,1,NULL),
	_DECL_FUNC(qk_vec2_tomat3,1,NULL),
	_DECL_FUNC(qk_vec2_tomat4,1,NULL),

	_DECL_FUNC(qk_vec3_constructor,-1,NULL),
	_DECL_FUNC(qk_vec3_identity,0,NULL),
	_DECL_FUNC(qk_vec3_get,2,NULL),
	_DECL_FUNC(qk_vec3_set,3,NULL),
	_DECL_FUNC(qk_vec3_typeof,0,NULL),
	_DECL_FUNC(qk_vec3_tostring,1,NULL),
	_DECL_FUNC(qk_vec3_cloned,2,NULL),
	_DECL_FUNC(qk_vec3_len,1,NULL),
	_DECL_FUNC(qk_vec3_add,2,NULL),
	_DECL_FUNC(qk_vec3_sub,2,NULL),
	_DECL_FUNC(qk_vec3_mul,2,NULL),
	_DECL_FUNC(qk_vec3_div,2,NULL),
	_DECL_FUNC(qk_vec3_unm,1,NULL),
	_DECL_FUNC(qk_vec3_flipx,1,NULL),
	_DECL_FUNC(qk_vec3_flipy,1,NULL),
	_DECL_FUNC(qk_vec3_flipz,1,NULL),
	_DECL_FUNC(qk_vec3_xaxis,1,NULL),
	_DECL_FUNC(qk_vec3_yaxis,1,NULL),
	_DECL_FUNC(qk_vec3_zaxis,1,NULL),
	_DECL_FUNC(qk_vec3_normal,1,NULL),
	_DECL_FUNC(qk_vec3_normalize,1,NULL),
	_DECL_FUNC(qk_vec3_normalizeret,1,NULL),
	_DECL_FUNC(qk_vec3_magnitude,1,NULL),
	_DECL_FUNC(qk_vec3_magnitudesquared,1,NULL),
	_DECL_FUNC(qk_vec3_manhattan,1,NULL),
//	_DECL_FUNC(qk_vec3_minitude,1,NULL),
//	_DECL_FUNC(qk_vec3_maxitude,1,NULL),
	_DECL_FUNC(qk_vec3_dot,2,NULL),
	_DECL_FUNC(qk_vec3_mix,3,NULL),
	_DECL_FUNC(qk_vec3_tangent,1,NULL),
//	_DECL_FUNC(qk_vec3_rotate45,1,NULL),
//	_DECL_FUNC(qk_vec3_rotatenegative45,1,NULL),
	_DECL_FUNC(qk_vec3_cross,2,NULL),
	_DECL_FUNC(qk_vec3_toscalar,1,NULL),	// - //
	_DECL_FUNC(qk_vec3_tovec2,1,NULL),		// - //
	_DECL_FUNC(qk_vec3_tohvec2,1,NULL),		// - //
	_DECL_FUNC(qk_vec3_tovec4,1,NULL),		// + //
	_DECL_FUNC(qk_vec3_tohvec4,1,NULL),		// + //
	_DECL_FUNC(qk_vec3_toivec4,1,NULL),		// + //
	_DECL_FUNC(qk_vec3_tomat2,1,NULL),
	_DECL_FUNC(qk_vec3_tomat3,1,NULL),
	_DECL_FUNC(qk_vec3_tomat4,1,NULL),

	_DECL_FUNC(qk_vec4_constructor,-1,NULL),
	_DECL_FUNC(qk_vec4_identity,0,NULL),
	_DECL_FUNC(qk_vec4_get,2,NULL),
	_DECL_FUNC(qk_vec4_set,3,NULL),
	_DECL_FUNC(qk_vec4_typeof,0,NULL),
	_DECL_FUNC(qk_vec4_tostring,1,NULL),
	_DECL_FUNC(qk_vec4_cloned,2,NULL),
	_DECL_FUNC(qk_vec4_len,0,NULL),
	_DECL_FUNC(qk_vec4_add,2,NULL),
	_DECL_FUNC(qk_vec4_sub,2,NULL),
	_DECL_FUNC(qk_vec4_mul,2,NULL),
	_DECL_FUNC(qk_vec4_div,2,NULL),
	_DECL_FUNC(qk_vec4_unm,1,NULL),
	_DECL_FUNC(qk_vec4_flipx,1,NULL),
	_DECL_FUNC(qk_vec4_flipy,1,NULL),
	_DECL_FUNC(qk_vec4_flipz,1,NULL),
	_DECL_FUNC(qk_vec4_flipw,1,NULL),
	_DECL_FUNC(qk_vec4_xaxis,1,NULL),
	_DECL_FUNC(qk_vec4_yaxis,1,NULL),
	_DECL_FUNC(qk_vec4_zaxis,1,NULL),
	_DECL_FUNC(qk_vec4_waxis,1,NULL),
	_DECL_FUNC(qk_vec4_normal,1,NULL),
	_DECL_FUNC(qk_vec4_normalize,1,NULL),
	_DECL_FUNC(qk_vec4_normalizeret,1,NULL),
	_DECL_FUNC(qk_vec4_magnitude,1,NULL),
	_DECL_FUNC(qk_vec4_magnitudesquared,1,NULL),
	_DECL_FUNC(qk_vec4_manhattan,1,NULL),
//	_DECL_FUNC(qk_vec4_minitude,1,NULL),
//	_DECL_FUNC(qk_vec4_maxitude,1,NULL),
	_DECL_FUNC(qk_vec4_dot,2,NULL),
	_DECL_FUNC(qk_vec4_mix,3,NULL),
//	_DECL_FUNC(qk_vec4_tangent,1,NULL),
//	_DECL_FUNC(qk_vec4_rotate45,1,NULL),
//	_DECL_FUNC(qk_vec4_rotatenegative45,1,NULL),
//	_DECL_FUNC(qk_vec4_cross,2,NULL),
	_DECL_FUNC(qk_vec4_toscalar,1,NULL),	// - //
	_DECL_FUNC(qk_vec4_tovec2,1,NULL),		// - //
	_DECL_FUNC(qk_vec4_tovec3,1,NULL),		// - //
	_DECL_FUNC(qk_vec4_tohvec3,1,NULL),		// - //
	_DECL_FUNC(qk_vec4_tomat2,1,NULL),
	_DECL_FUNC(qk_vec4_tomat3,1,NULL),
	_DECL_FUNC(qk_vec4_tomat4,1,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
SQInteger register_qkVector(HSQUIRRELVM v) {
	SQInteger i=0;
	SQRegFunction* funcs = qkVector_funcs;
	while(funcs[i].name!=0) {
		sq_pushstring(v,funcs[i].name,-1);
		sq_newclosure(v,funcs[i].f,0);
		sq_setparamscheck(v,funcs[i].nparamscheck,funcs[i].typemask);
		sq_setnativeclosurename(v,-1,funcs[i].name);
		sq_newslot(v,-3,SQFalse);
		i++;
	}
	
	int Root = sq_gettop(v); // root table pos //
	{
		_ADD_CLASS_START(Real,"scalar",QK_TAG_SCALAR);
		_CLASS_ADDFUNC(qk_scalar_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_scalar_identity,identity);
		_CLASS_ADDFUNC(qk_scalar_get,_get);
		_CLASS_ADDFUNC(qk_scalar_set,_set);
		_CLASS_ADDFUNC(qk_scalar_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_scalar_typeof,_typeof);
		_CLASS_ADDFUNC(qk_scalar_cloned,_cloned);
		_CLASS_ADDFUNC_STATIC(qk_scalar_len,len);
		_CLASS_ADDFUNC(qk_scalar_add,_add);
		_CLASS_ADDFUNC(qk_scalar_sub,_sub);
		_CLASS_ADDFUNC(qk_scalar_mul,_mul);
		_CLASS_ADDFUNC(qk_scalar_div,_div);
		_CLASS_ADDFUNC(qk_scalar_unm,_unm);
		_CLASS_ADDFUNC(qk_scalar_flipx,flipx);
		_CLASS_ADDFUNC(qk_scalar_xaxis,xaxis);
		_CLASS_ADDFUNC(qk_scalar_normal,normal);
		_CLASS_ADDFUNC(qk_scalar_normalize,normalize);
		_CLASS_ADDFUNC(qk_scalar_normalizeret,normalizeret);
		_CLASS_ADDFUNC(qk_scalar_magnitude,magnitude);
		_CLASS_ADDFUNC(qk_scalar_magnitudesquared,magnitudesquared);
		_CLASS_ADDFUNC(qk_scalar_manhattan,manhattan);
//		_CLASS_ADDFUNC(qk_scalar_minitude,minitude);
//		_CLASS_ADDFUNC(qk_scalar_maxitude,maxitude);
//		_CLASS_ADDFUNC(qk_scalar_dot,dot);
		_CLASS_ADDFUNC(qk_scalar_mix,mix);
//		_CLASS_ADDFUNC(qk_scalar_tangent,tangent);
//		_CLASS_ADDFUNC(qk_scalar_rotate45,rotate45);
//		_CLASS_ADDFUNC(qk_scalar_rotatenegative45,rotatenegative45);
//		_CLASS_ADDFUNC(qk_scalar_cross,cross);
		_CLASS_ADDFUNC(qk_scalar_tofloat,tofloat);
		_CLASS_ADDFUNC(qk_scalar_tovec2,tovec2);
		_CLASS_ADDFUNC(qk_scalar_tovec3,tovec3);
		_CLASS_ADDFUNC(qk_scalar_tovec4,tovec4);
		_CLASS_ADDFUNC(qk_scalar_tohvec2,tohvec2);
		_CLASS_ADDFUNC(qk_scalar_tohvec3,tohvec3);
		_CLASS_ADDFUNC(qk_scalar_tohvec4,tohvec4);
		_CLASS_ADDFUNC(qk_scalar_toivec2,toivec2);
		_CLASS_ADDFUNC(qk_scalar_toivec3,toivec3);
		_CLASS_ADDFUNC(qk_scalar_toivec4,toivec4);
		_CLASS_ADDFUNC(qk_scalar_tomat2,tomat2);
		_CLASS_ADDFUNC(qk_scalar_tomat3,tomat3);
		_CLASS_ADDFUNC(qk_scalar_tomat4,tomat4);
		_ADD_CLASS_END(Real);
	}

	{
		_ADD_CLASS_START(Vector2D,"vec2",QK_TAG_VEC2);
		_CLASS_ADDFUNC(qk_vec2_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_vec2_identity,identity);
		_CLASS_ADDFUNC(qk_vec2_get,_get);
		_CLASS_ADDFUNC(qk_vec2_set,_set);
		_CLASS_ADDFUNC(qk_vec2_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_vec2_typeof,_typeof);
		_CLASS_ADDFUNC(qk_vec2_cloned,_cloned);
		_CLASS_ADDFUNC_STATIC(qk_vec2_len,len);
		_CLASS_ADDFUNC(qk_vec2_add,_add);
		_CLASS_ADDFUNC(qk_vec2_sub,_sub);
		_CLASS_ADDFUNC(qk_vec2_mul,_mul);
		_CLASS_ADDFUNC(qk_vec2_div,_div);
		_CLASS_ADDFUNC(qk_vec2_unm,_unm);
		_CLASS_ADDFUNC(qk_vec2_flipx,flipx);
		_CLASS_ADDFUNC(qk_vec2_flipy,flipy);
		_CLASS_ADDFUNC(qk_vec2_xaxis,xaxis);
		_CLASS_ADDFUNC(qk_vec2_yaxis,yaxis);
		_CLASS_ADDFUNC(qk_vec2_normal,normal);
		_CLASS_ADDFUNC(qk_vec2_normalize,normalize);
		_CLASS_ADDFUNC(qk_vec2_normalizeret,normalizeret);
		_CLASS_ADDFUNC(qk_vec2_magnitude,magnitude);
		_CLASS_ADDFUNC(qk_vec2_magnitudesquared,magnitudesquared);
		_CLASS_ADDFUNC(qk_vec2_manhattan,manhattan);
		_CLASS_ADDFUNC(qk_vec2_minitude,minitude);
		_CLASS_ADDFUNC(qk_vec2_maxitude,maxitude);
		_CLASS_ADDFUNC(qk_vec2_dot,dot);
		_CLASS_ADDFUNC(qk_vec2_mix,mix);
		_CLASS_ADDFUNC(qk_vec2_tangent,tangent);
		_CLASS_ADDFUNC(qk_vec2_rotate45,rotate45);
		_CLASS_ADDFUNC(qk_vec2_rotatenegative45,rotatenegative45);
//		_CLASS_ADDFUNC(qk_vec2_cross,cross);
		_CLASS_ADDFUNC(qk_vec2_toscalar,toscalar);
		_CLASS_ADDFUNC(qk_vec2_tohscalar,tohscalar);
		_CLASS_ADDFUNC(qk_vec2_tovec3,tovec3);
		_CLASS_ADDFUNC(qk_vec2_tohvec3,tohvec3);
		_CLASS_ADDFUNC(qk_vec2_toivec3,toivec3);
		_CLASS_ADDFUNC(qk_vec2_tovec4,tovec4);
		_CLASS_ADDFUNC(qk_vec2_tohvec4,tohvec4);
		_CLASS_ADDFUNC(qk_vec2_toivec4,toivec4);
		_CLASS_ADDFUNC(qk_vec2_tomat2,tomat2);
		_CLASS_ADDFUNC(qk_vec2_tomat3,tomat3);
		_CLASS_ADDFUNC(qk_vec2_tomat4,tomat4);
		_ADD_CLASS_END(Vector2D);
	}

	{
		_ADD_CLASS_START(Vector3D,"vec3",QK_TAG_VEC3);
		_CLASS_ADDFUNC(qk_vec3_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_vec3_identity,identity);
		_CLASS_ADDFUNC(qk_vec3_get,_get);
		_CLASS_ADDFUNC(qk_vec3_set,_set);
		_CLASS_ADDFUNC(qk_vec3_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_vec3_typeof,_typeof);
		_CLASS_ADDFUNC(qk_vec3_cloned,_cloned);
		_CLASS_ADDFUNC_STATIC(qk_vec3_len,len);
		_CLASS_ADDFUNC(qk_vec3_add,_add);
		_CLASS_ADDFUNC(qk_vec3_sub,_sub);
		_CLASS_ADDFUNC(qk_vec3_mul,_mul);
		_CLASS_ADDFUNC(qk_vec3_div,_div);
		_CLASS_ADDFUNC(qk_vec3_unm,_unm);
		_CLASS_ADDFUNC(qk_vec3_flipx,flipx);
		_CLASS_ADDFUNC(qk_vec3_flipy,flipy);
		_CLASS_ADDFUNC(qk_vec3_flipz,flipz);
		_CLASS_ADDFUNC(qk_vec3_xaxis,xaxis);
		_CLASS_ADDFUNC(qk_vec3_yaxis,yaxis);
		_CLASS_ADDFUNC(qk_vec3_zaxis,zaxis);
		_CLASS_ADDFUNC(qk_vec3_normal,normal);
		_CLASS_ADDFUNC(qk_vec3_normalize,normalize);
		_CLASS_ADDFUNC(qk_vec3_normalizeret,normalizeret);
		_CLASS_ADDFUNC(qk_vec3_magnitude,magnitude);
		_CLASS_ADDFUNC(qk_vec3_magnitudesquared,magnitudesquared);
		_CLASS_ADDFUNC(qk_vec3_manhattan,manhattan);
//		_CLASS_ADDFUNC(qk_vec3_minitude,minitude);
//		_CLASS_ADDFUNC(qk_vec3_maxitude,maxitude);
		_CLASS_ADDFUNC(qk_vec3_dot,dot);
		_CLASS_ADDFUNC(qk_vec3_mix,mix);
		_CLASS_ADDFUNC(qk_vec3_tangent,tangent);
//		_CLASS_ADDFUNC(qk_vec3_rotate45,rotate45);
//		_CLASS_ADDFUNC(qk_vec3_rotatenegative45,rotatenegative45);
		_CLASS_ADDFUNC(qk_vec3_cross,cross);
		_CLASS_ADDFUNC(qk_vec3_toscalar,toscalar);
		_CLASS_ADDFUNC(qk_vec3_tovec2,tovec2);
		_CLASS_ADDFUNC(qk_vec3_tohvec2,tohvec2);
		_CLASS_ADDFUNC(qk_vec3_tovec4,tovec4);
		_CLASS_ADDFUNC(qk_vec3_tohvec4,tohvec4);
		_CLASS_ADDFUNC(qk_vec3_toivec4,toivec4);
		_CLASS_ADDFUNC(qk_vec3_tomat2,tomat2);
		_CLASS_ADDFUNC(qk_vec3_tomat3,tomat3);
		_CLASS_ADDFUNC(qk_vec3_tomat4,tomat4);		
		_ADD_CLASS_END(Vector3D);
	}

	{
		_ADD_CLASS_START(Vector4D,"vec4",QK_TAG_VEC4);
		_CLASS_ADDFUNC(qk_vec4_constructor,constructor);
		_CLASS_ADDFUNC_STATIC(qk_vec4_identity,identity);
		_CLASS_ADDFUNC(qk_vec4_get,_get);
		_CLASS_ADDFUNC(qk_vec4_set,_set);
		_CLASS_ADDFUNC(qk_vec4_tostring,_tostring);
		_CLASS_ADDFUNC_STATIC(qk_vec4_typeof,_typeof);
		_CLASS_ADDFUNC(qk_vec4_cloned,_cloned);
		_CLASS_ADDFUNC_STATIC(qk_vec4_len,len);
		_CLASS_ADDFUNC(qk_vec4_add,_add);
		_CLASS_ADDFUNC(qk_vec4_sub,_sub);
		_CLASS_ADDFUNC(qk_vec4_mul,_mul);
		_CLASS_ADDFUNC(qk_vec4_div,_div);
		_CLASS_ADDFUNC(qk_vec4_unm,_unm);
		_CLASS_ADDFUNC(qk_vec4_flipx,flipx);
		_CLASS_ADDFUNC(qk_vec4_flipy,flipy);
		_CLASS_ADDFUNC(qk_vec4_flipz,flipz);
		_CLASS_ADDFUNC(qk_vec4_flipw,flipw);
		_CLASS_ADDFUNC(qk_vec4_xaxis,xaxis);
		_CLASS_ADDFUNC(qk_vec4_yaxis,yaxis);
		_CLASS_ADDFUNC(qk_vec4_zaxis,zaxis);
		_CLASS_ADDFUNC(qk_vec4_waxis,waxis);
		_CLASS_ADDFUNC(qk_vec4_normal,normal);
		_CLASS_ADDFUNC(qk_vec4_normalize,normalize);
		_CLASS_ADDFUNC(qk_vec4_normalizeret,normalizeret);
		_CLASS_ADDFUNC(qk_vec4_magnitude,magnitude);
		_CLASS_ADDFUNC(qk_vec4_magnitudesquared,magnitudesquared);
		_CLASS_ADDFUNC(qk_vec4_manhattan,manhattan);
//		_CLASS_ADDFUNC(qk_vec4_minitude,minitude);
//		_CLASS_ADDFUNC(qk_vec4_maxitude,maxitude);
		_CLASS_ADDFUNC(qk_vec4_dot,dot);
		_CLASS_ADDFUNC(qk_vec4_mix,mix);
//		_CLASS_ADDFUNC(qk_vec4_tangent,tangent);
//		_CLASS_ADDFUNC(qk_vec4_rotate45,rotate45);
//		_CLASS_ADDFUNC(qk_vec4_rotatenegative45,rotatenegative45);
//		_CLASS_ADDFUNC(qk_vec4_cross,cross);
		_CLASS_ADDFUNC(qk_vec4_toscalar,toscalar);
		_CLASS_ADDFUNC(qk_vec4_tovec2,tovec2);
		_CLASS_ADDFUNC(qk_vec4_tovec3,tovec3);
		_CLASS_ADDFUNC(qk_vec4_tohvec3,tohvec3);
		_CLASS_ADDFUNC(qk_vec4_tomat2,tomat2);
		_CLASS_ADDFUNC(qk_vec4_tomat3,tomat3);
		_CLASS_ADDFUNC(qk_vec4_tomat4,tomat4);
		_ADD_CLASS_END(Vector4D);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
