// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Matrix.h>
#include <API/API_Squirrel.h>
#include "sqext.h"
#include "sqgelext.h"
#include "QuackLib.h"
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
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void qk_mat_constructor_body( HSQUIRRELVM v, float* Mat, const int MatSize ) {
	int Args = sq_gettop(v);
	if ( Args > 1 ) {
		int MatIndex = 0; // Which Cell of the Matrix we are writing to. //
		
		// Iterate through all arguments //
		for ( int idx = 1; (idx <= Args) && (MatIndex < MatSize); idx++ ) {
			int Type = sq_gettype(v,idx);
			if ( Type & (OT_FLOAT|OT_INTEGER) ) {
				sq_getfloat(v,idx,&(Mat[MatIndex]));
				
				MatIndex++;
			}
			else if ( Type == OT_ARRAY ) {
				int Size = sq_getsize(v,idx);
				if ( Size > MatSize-MatIndex ) {
					// TODO: Log an error that array attempting to use is too big //
					Size = MatSize-MatIndex;
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
					// TODO: Assert on out of bounds
					Vector2D* Vec;
					sq_getinstanceup(v,idx,(void**)&Vec,0);				
					
					Mat[MatIndex+0] = Vec->x.ToFloat();
					if ( MatIndex+1 < MatSize )
						Mat[MatIndex+1] = Vec->y.ToFloat();

					MatIndex+=2;
				}
				else if ( Tag == QK_TAG_VEC3 ) {
					// TODO: Assert on out of bounds
					Vector3D* Vec;
					sq_getinstanceup(v,idx,(void**)&Vec,0);				
					
					Mat[MatIndex+0] = Vec->x.ToFloat();
					if ( MatIndex+1 < MatSize )
						Mat[MatIndex+1] = Vec->y.ToFloat();
					if ( MatIndex+2 < MatSize )
						Mat[MatIndex+2] = Vec->z.ToFloat();

					MatIndex+=3;
				}
				else if ( Tag == QK_TAG_VEC4 ) {
					// TODO: Assert on out of bounds
					Vector4D* Vec;
					sq_getinstanceup(v,idx,(void**)&Vec,0);				
					
					Mat[MatIndex+0] = Vec->x.ToFloat();
					if ( MatIndex+1 < MatSize )
						Mat[MatIndex+1] = Vec->y.ToFloat();
					if ( MatIndex+2 < MatSize )
						Mat[MatIndex+2] = Vec->z.ToFloat();
					if ( MatIndex+3 < MatSize )
						Mat[MatIndex+3] = Vec->w.ToFloat();

					MatIndex+=4;
				}
				else if ( Tag == QK_TAG_SCALAR ) {
					Real* Vec;
					sq_getinstanceup(v,idx,(void**)&Vec,0);				
					
					Mat[MatIndex] = Vec->ToFloat();

					MatIndex++;
				}
				else {
					// TODO: Log Bad Matrix Init Type //
				}
			}
			else {
				// TODO: Log Bad Matrix Init Type //
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
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// mat2 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat2_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix2x2) / sizeof(Real);
	
	qk_mat_constructor_body(v,Mat,MatSize);

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
_MAT_TOSTRING(Matrix2x2,qk_mat2_tostring,"[%0.03f %0.03f]\n[%0.03f %0.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat());
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// mat3 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat3_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix3x3) / sizeof(Real);
	
	qk_mat_constructor_body(v,Mat,MatSize);

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
_MAT_TOSTRING(Matrix3x3,qk_mat3_tostring,"[%0.03f %0.03f %0.03f]\n[%0.03f %0.03f %0.03f]\n[%0.03f %0.03f %0.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat(),(*Mat)[4].ToFloat(),(*Mat)[5].ToFloat(),(*Mat)[6].ToFloat(),(*Mat)[7].ToFloat(),(*Mat)[8].ToFloat());
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// mat4 --------------------------------------------------------------------------------------- - //
// - ------------------------------------------------------------------------------------------ - //
SQInteger qk_mat4_constructor( HSQUIRRELVM v ) {
	float* Mat;
	sq_getinstanceup(v,1,(void**)&Mat,0);
	const int MatSize = sizeof(Matrix4x4) / sizeof(Real);
	
	qk_mat_constructor_body(v,Mat,MatSize);

	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //
_MAT_TOSTRING(Matrix4x4,qk_mat4_tostring,"[%0.03f %0.03f %0.03f %0.03f]\n[%0.03f %0.03f %0.03f %0.03f]\n[%0.03f %0.03f %0.03f %0.03f]\n[%0.03f %0.03f %0.03f %0.03f]",(*Mat)[0].ToFloat(),(*Mat)[1].ToFloat(),(*Mat)[2].ToFloat(),(*Mat)[3].ToFloat(),(*Mat)[4].ToFloat(),(*Mat)[5].ToFloat(),(*Mat)[6].ToFloat(),(*Mat)[7].ToFloat(),(*Mat)[8].ToFloat(),(*Mat)[9].ToFloat(),(*Mat)[10].ToFloat(),(*Mat)[11].ToFloat(),(*Mat)[12].ToFloat(),(*Mat)[13].ToFloat(),(*Mat)[14].ToFloat(),(*Mat)[15].ToFloat());
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define _DECL_FUNC(name,nparams,pmask) {_SC(#name),name,nparams,pmask}
SQRegFunction qkMatrix_funcs[] = {
	// 1: Function Name.
	// 2: Number of Args (Positive=Required Arg Count, Negative=Minimum Arg Count, 0=Don't check).
	// 3: Arg type check string (or NULL for no checking). See sq_setparamscheck for options.
	_DECL_FUNC(qk_mat2_constructor,-1,NULL),
	_DECL_FUNC(qk_mat2_tostring,1,NULL),

	_DECL_FUNC(qk_mat3_constructor,-1,NULL),
	_DECL_FUNC(qk_mat3_tostring,1,NULL),

	_DECL_FUNC(qk_mat4_constructor,-1,NULL),
	_DECL_FUNC(qk_mat4_tostring,1,NULL),
	
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
		_CLASS_ADDFUNC(qk_mat2_tostring,_tostring);
		_ADD_CLASS_END(Matrix2x2);
	}
	{
		_ADD_CLASS_START(Matrix3x3,"mat3",QK_TAG_MAT3);
		_CLASS_ADDFUNC(qk_mat3_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat3_tostring,_tostring);
		_ADD_CLASS_END(Matrix3x3);
	}
	{
		_ADD_CLASS_START(Matrix4x4,"mat4",QK_TAG_MAT4);
		_CLASS_ADDFUNC(qk_mat4_constructor,constructor);
		_CLASS_ADDFUNC(qk_mat4_tostring,_tostring);
		_ADD_CLASS_END(Matrix4x4);
	}
	
	return SQ_OK;
}
// - ------------------------------------------------------------------------------------------ - //
	