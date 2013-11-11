// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Matrix.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
#include "QuackLib.h"
// - ------------------------------------------------------------------------------------------ - //
// TODO: .row0(), .column2() functions might be nice, for getting vectors of the data.
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
#define _MAT_LEN(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_pushinteger(v, sizeof(_TYPE_) / sizeof(Real) ); \
	return SQ_RETURN; \
}
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
// _add, _sub, _mul, _div //
#define _MAT_MATH(_TYPE_,_NAME_,_OP_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_clone(v,1); /* +1 */ \
	\
	_TYPE_* Mat; \
	sq_getinstanceup(v,-1,(void**)&Mat,0); \
	\
	_TYPE_* Vs; \
	sq_getinstanceup(v,2,(void**)&Vs,0); \
	\
	*Mat = (*Mat) _OP_ (*Vs); \
	\
	return SQ_RETURN; \
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

// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_mat_constructor_body( HSQUIRRELVM v, float* Mat, const int MatSize ) {
	int Args = sq_gettop(v);
	if ( Args > 1 ) {
		int MatIndex = 0; // Which Cell of the Matrix we are writing to. //
		
		// Iterate through all arguments //
		for ( int idx = 2; (idx <= Args) && (MatIndex < MatSize); idx++ ) {
			int Type = sq_gettype(v,idx);
			if ( Type & (OT_FLOAT|OT_INTEGER) ) {
				sq_getfloat(v,idx,&(Mat[MatIndex]));
				
				MatIndex++;
			}
			else if ( Type == OT_ARRAY ) {
				int Size = sq_getsize(v,idx);
				if ( Size > MatSize-MatIndex ) {
					//Size = MatSize-MatIndex;
					return sq_throwerror(v,"array assigned to matrix is too large");
				}
				
				for ( int idx2 = 0; idx2 < Size; idx2++ ) {
					sq_pushinteger(v,idx2); 	// +1 //
					sq_get(v,idx); 				// =0 (-1 then +1) //
					sq_getfloat(v,-1,&(Mat[MatIndex]));
					sq_poptop(v);				// -1 //
					MatIndex++;
				}
			}
			else if ( Type == OT_INSTANCE ) {
				int Tag;			
				sq_gettypetag(v,idx,(SQUserPointer*)&Tag);
				if ( Tag == QK_TAG_VEC2 ) {
					if ( MatIndex+1 < MatSize ) {
						Vector2D* Vec;
						sq_getinstanceup(v,idx,(void**)&Vec,0);				
						
						Mat[MatIndex+0] = Vec->x.ToFloat();
						Mat[MatIndex+1] = Vec->y.ToFloat();
	
						MatIndex+=2;
					}
					else {
						return sq_throwerror(v,"vector assigned to matrix is too large");
					}
				}
				else if ( Tag == QK_TAG_VEC3 ) {
					if ( MatIndex+2 < MatSize ) {
						Vector3D* Vec;
						sq_getinstanceup(v,idx,(void**)&Vec,0);				
						
						Mat[MatIndex+0] = Vec->x.ToFloat();
						Mat[MatIndex+1] = Vec->y.ToFloat();
						Mat[MatIndex+2] = Vec->z.ToFloat();
	
						MatIndex+=3;
					}
					else {
						return sq_throwerror(v,"vector assigned to matrix is too large");
					}
				}
				else if ( Tag == QK_TAG_VEC4 ) {
					if ( MatIndex+3 < MatSize ) {
						Vector4D* Vec;
						sq_getinstanceup(v,idx,(void**)&Vec,0);				
						
						Mat[MatIndex+0] = Vec->x.ToFloat();
						Mat[MatIndex+1] = Vec->y.ToFloat();
						Mat[MatIndex+2] = Vec->z.ToFloat();
						Mat[MatIndex+3] = Vec->w.ToFloat();
	
						MatIndex+=4;
					}
					else {
						return sq_throwerror(v,"vector assigned to matrix is too large");
					}
				}
				else if ( Tag == QK_TAG_SCALAR ) {
					Real* Vec;
					sq_getinstanceup(v,idx,(void**)&Vec,0);				
					
					Mat[MatIndex] = Vec->ToFloat();

					MatIndex++;
				}
				else {
					return sq_throwerror(v,"bad type to assignment to matrix");
				}
			}
			else {
				return sq_throwerror(v,"bad type to assignment to matrix");
			}
		}
		
		// If we didn't put enough data in, pad with zeros //
		while ( MatIndex < MatSize ) {
			Mat[MatIndex] = 0.0f;
			MatIndex++;
		}
	}
	else {
		// TODO: No Arguments //
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_mat_get( HSQUIRRELVM v, float* Mat, const int MatSize, const unsigned int MatWidth ) {
	int Type = sq_gettype(v,2);
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
	
		int Type = sq_gettype(v,2);
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
	
	return qk_mat_constructor_body(v,Mat,MatSize);
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
_MAT_TOSTRING(Matrix2x2,qk_mat2_tostring,"[% 10.03f % 10.03f]\n[% 10.03f % 10.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat());
_MAT_LEN(Matrix2x2,qk_mat2_len);
_MAT_CLONED(Matrix2x2,qk_mat2_cloned);
_MAT_UNM(Matrix2x2,qk_mat2_unm);
//_MAT_MATH(Matrix2x2,qk_mat2_add,+);
//_MAT_MATH(Matrix2x2,qk_mat2_sub,-);
_MAT_MATH(Matrix2x2,qk_mat2_mul,*);
//_MAT_MATH(Matrix2x2,qk_mat2_div,/);
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// mat3 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix3x3) / sizeof(Real);
	
	return qk_mat_constructor_body(v,Mat,MatSize);
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
_MAT_TOSTRING(Matrix3x3,qk_mat3_tostring,"[% 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat(),(*Mat)[4].ToFloat(),(*Mat)[5].ToFloat(),(*Mat)[6].ToFloat(),(*Mat)[7].ToFloat(),(*Mat)[8].ToFloat());
_MAT_LEN(Matrix3x3,qk_mat3_len);
_MAT_CLONED(Matrix3x3,qk_mat3_cloned);
_MAT_UNM(Matrix3x3,qk_mat3_unm);
//_MAT_MATH(Matrix3x3,qk_mat3_add,+);
//_MAT_MATH(Matrix3x3,qk_mat3_sub,-);
_MAT_MATH(Matrix3x3,qk_mat3_mul,*);
//_MAT_MATH(Matrix3x3,qk_mat3_div,/);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// mat4 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix4x4) / sizeof(Real);
	
	return qk_mat_constructor_body(v,Mat,MatSize);
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
_MAT_TOSTRING(Matrix4x4,qk_mat4_tostring,"[% 10.03f % 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f % 10.03f]\n[% 10.03f % 10.03f % 10.03f % 10.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat(),(*Mat)[4].ToFloat(),(*Mat)[5].ToFloat(),(*Mat)[6].ToFloat(),(*Mat)[7].ToFloat(),(*Mat)[8].ToFloat(),(*Mat)[9].ToFloat(),(*Mat)[10].ToFloat(),(*Mat)[11].ToFloat(),(*Mat)[12].ToFloat(),(*Mat)[13].ToFloat(),(*Mat)[14].ToFloat(),(*Mat)[15].ToFloat());
_MAT_LEN(Matrix4x4,qk_mat4_len);
_MAT_CLONED(Matrix4x4,qk_mat4_cloned);
_MAT_UNM(Matrix4x4,qk_mat4_unm);
//_MAT_MATH(Matrix4x4,qk_mat4_add,+);
//_MAT_MATH(Matrix4x4,qk_mat4_sub,-);
_MAT_MATH(Matrix4x4,qk_mat4_mul,*);
//_MAT_MATH(Matrix4x4,qk_mat4_div,/);

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
	_DECL_FUNC(qk_mat2_tostring,1,NULL),
	_DECL_FUNC(qk_mat2_len,1,NULL),
	_DECL_FUNC(qk_mat2_cloned,2,NULL),
	_DECL_FUNC(qk_mat2_unm,1,NULL),
//	_DECL_FUNC(qk_mat2_add,2,NULL),
//	_DECL_FUNC(qk_mat2_sub,2,NULL),
	_DECL_FUNC(qk_mat2_mul,2,NULL),
//	_DECL_FUNC(qk_mat2_div,2,NULL),

	_DECL_FUNC(qk_mat3_constructor,-1,NULL),
	_DECL_FUNC(qk_mat3_get,2,NULL),
	_DECL_FUNC(qk_mat3_set,3,NULL),
	_DECL_FUNC(qk_mat3_tostring,1,NULL),
	_DECL_FUNC(qk_mat3_len,1,NULL),
	_DECL_FUNC(qk_mat3_cloned,2,NULL),
	_DECL_FUNC(qk_mat3_unm,1,NULL),
//	_DECL_FUNC(qk_mat3_add,2,NULL),
//	_DECL_FUNC(qk_mat3_sub,2,NULL),
	_DECL_FUNC(qk_mat3_mul,2,NULL),
//	_DECL_FUNC(qk_mat3_div,2,NULL),

	_DECL_FUNC(qk_mat4_constructor,-1,NULL),
	_DECL_FUNC(qk_mat4_get,2,NULL),
	_DECL_FUNC(qk_mat4_set,3,NULL),
	_DECL_FUNC(qk_mat4_tostring,1,NULL),
	_DECL_FUNC(qk_mat4_len,1,NULL),
	_DECL_FUNC(qk_mat4_cloned,2,NULL),
	_DECL_FUNC(qk_mat4_unm,1,NULL),
//	_DECL_FUNC(qk_mat4_add,2,NULL),
//	_DECL_FUNC(qk_mat4_sub,2,NULL),
	_DECL_FUNC(qk_mat4_mul,2,NULL),
//	_DECL_FUNC(qk_mat4_div,2,NULL),
	
	{0,0,0,0}
};
#undef _DECL_FUNC
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define _CLASS_ADDFUNC(_FUNC_,_METHOD_) \
	sq_pushstring(v,#_METHOD_,-1);				/* +1 */ \
	sq_pushstring(v,#_FUNC_,-1);				/* +1 */ \
	sq_get(v,Root); /* lookup function */		/* =0 */ \
	sq_newslot(v,CPos,false);					/* -2 */
// - ------------------------------------------------------------------------------------------ - //
#define _ADD_CLASS_START(_TYPE_,_TYPENAME_,_TYPETAG_) \
	sq_pushstring(v,_TYPENAME_,-1);				/* +1 */ \
	sq_newclass(v,false); 						/* +1 */ \
	int CPos = sq_gettop(v); /* class pos */ \
	sq_setclassudsize(v,CPos,sizeof(_TYPE_)); \
	sq_settypetag(v,CPos,(void*)_TYPETAG_);
// - ------------------------------------------------------------------------------------------ - //
#define _ADD_CLASS_END(_TYPE_) \
	sq_newslot(v,Root,false); /* Add to Root */	/* -2 */
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
		_CLASS_ADDFUNC(qk_mat2_tostring,_tostring);
		_CLASS_ADDFUNC(qk_mat2_len,len);
		_CLASS_ADDFUNC(qk_mat2_cloned,_cloned);
		_CLASS_ADDFUNC(qk_mat2_unm,_unm);
//		_CLASS_ADDFUNC(qk_mat2_add,_add);
//		_CLASS_ADDFUNC(qk_mat2_sub,_sub);
		_CLASS_ADDFUNC(qk_mat2_mul,_mul);
//		_CLASS_ADDFUNC(qk_mat2_div,_div);
		_ADD_CLASS_END(Matrix2x2);
	}
	{
		_ADD_CLASS_START(Matrix3x3,"mat3",QK_TAG_MAT3);
		_CLASS_ADDFUNC(qk_mat3_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat3_get,_get);
		_CLASS_ADDFUNC(qk_mat3_set,_set);
		_CLASS_ADDFUNC(qk_mat3_tostring,_tostring);
		_CLASS_ADDFUNC(qk_mat3_len,len);
		_CLASS_ADDFUNC(qk_mat3_cloned,_cloned);
		_CLASS_ADDFUNC(qk_mat3_unm,_unm);
//		_CLASS_ADDFUNC(qk_mat3_add,_add);
//		_CLASS_ADDFUNC(qk_mat3_sub,_sub);
		_CLASS_ADDFUNC(qk_mat3_mul,_mul);
//		_CLASS_ADDFUNC(qk_mat3_div,_div);
		_ADD_CLASS_END(Matrix3x3);
	}
	{
		_ADD_CLASS_START(Matrix4x4,"mat4",QK_TAG_MAT4);
		_CLASS_ADDFUNC(qk_mat4_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat4_get,_get);
		_CLASS_ADDFUNC(qk_mat4_set,_set);
		_CLASS_ADDFUNC(qk_mat4_tostring,_tostring);
		_CLASS_ADDFUNC(qk_mat4_len,len);
		_CLASS_ADDFUNC(qk_mat4_cloned,_cloned);
		_CLASS_ADDFUNC(qk_mat4_unm,_unm);
//		_CLASS_ADDFUNC(qk_mat4_add,_add);
//		_CLASS_ADDFUNC(qk_mat4_sub,_sub);
		_CLASS_ADDFUNC(qk_mat4_mul,_mul);
//		_CLASS_ADDFUNC(qk_mat4_div,_div);
		_ADD_CLASS_END(Matrix4x4);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
	