// - ------------------------------------------------------------------------------------------ - //
#ifndef __QUACK_QUACKLIB_QUACKLIB_H__
#define __QUACK_QUACKLIB_QUACKLIB_H__
// - ------------------------------------------------------------------------------------------ - //
// Type Enums (for TypeTags) //
enum {
	QK_TAG_NULL = 0,
	QK_TAG_DUMMY = 1,


	QK_TAG_VEC2,
	QK_TAG_VEC3,
	QK_TAG_VEC4,
	QK_TAG_SCALAR,

	QK_TAG_MAT2,
	QK_TAG_MAT3,
	QK_TAG_MAT4,

	QK_TAG_COLOR,
	
	
	QK_TAG_MAX		// Last Symbol //
};
// - ------------------------------------------------------------------------------------------ - //
// Convert a Quack TypeTag to a printable string //
inline const char* qk_gettagname( int Index ) {
	switch( Index ) {
		case QK_TAG_NULL:
			return "null";
			break;
		case QK_TAG_DUMMY:
			return "dummy";
			break;
		case QK_TAG_VEC2:
			return "vec2";
			break;
		case QK_TAG_VEC3:
			return "vec3";
			break;
		case QK_TAG_VEC4:
			return "vec4";
			break;
		case QK_TAG_SCALAR:
			return "scalar";
			break;
		case QK_TAG_MAT2:
			return "mat2";
			break;
		case QK_TAG_MAT3:
			return "mat3";
			break;
		case QK_TAG_MAT4:
			return "mat4";
			break;
		case QK_TAG_COLOR:
			return "color";
			break;
	};

	return "invalid tag";
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_START() \
	int VsType = sq_gettype(v,2);
// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_END(_OP_) \
	{ \
		; \
	} \
	return sq_throwerror(v,"Cannot " #_OP_ " versus type.");
// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_TYPE_START(_TYPE_) \
	if ( VsType == _TYPE_ ) { \
		int VsTag; \
		sq_gettypetag(v,2,(SQUserPointer*)&VsTag); \
// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_TYPE_END() \
		{ \
			; \
		} \
	} \
	else
// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_TYPE_FLOAT(_TYPE_,_OP_) \
	if ( VsType & (OT_FLOAT|OT_INTEGER) ) { \
		sq_clone(v,1); /* +1 */ \
		\
		_TYPE_* Vec; \
		sq_getinstanceup(v,-1,(void**)&Vec,0); \
		\
		float Vs; \
		sq_getfloat(v,2,&Vs); \
		\
		*Vec = (*Vec) _OP_ Real(Vs); \
		\
		return SQ_RETURN; \
	} \
	else
// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_TAG(_TYPE_,_TYPE2_,_TYPECONSTANT_,_OP_) \
		if ( VsTag == _TYPECONSTANT_ ) { \
			sq_clone(v,1); /* +1 */ \
			\
			_TYPE_* Ret; \
			sq_getinstanceup(v,-1,(void**)&Ret,0); \
			\
			_TYPE2_* Vs; \
			sq_getinstanceup(v,2,(void**)&Vs,0); \
			\
			*Ret = (*Ret) _OP_ (*Vs); \
			return SQ_RETURN; \
		} \
		else 
// - ------------------------------------------------------------------------------------------ - //
#define _MATH_OP_TAG2(_TYPE_,_TYPE2_,_TYPECONSTANT_,_OP_) \
		if ( VsTag == _TYPECONSTANT_ ) { \
			sq_clone(v,2); /* +1 */ \
			\
			_TYPE2_* Ret; \
			sq_getinstanceup(v,-1,(void**)&Ret,0); \
			\
			_TYPE_* Vec; \
			sq_getinstanceup(v,1,(void**)&Vec,0); \
			\
			*Ret = (*Vec) _OP_ (*Ret); \
			return SQ_RETURN; \
		} \
		else 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _MATH_LEN(_TYPE_,_NAME_) \
SQInteger _NAME_( HSQUIRRELVM v ) { \
	sq_pushinteger(v, sizeof(_TYPE_) / sizeof(Real) ); \
	return SQ_RETURN; \
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define _CLASS_ADDFUNC(_FUNC_,_METHOD_) \
	sq_pushstring(v,#_METHOD_,-1);				/* +1 */ \
	sq_pushstring(v,#_FUNC_,-1);				/* +1 */ \
	sq_get(v,Root); /* lookup function */		/* =0 */ \
	sq_newslot(v,CPos,false);					/* -2 */
// - ------------------------------------------------------------------------------------------ - //
#define _CLASS_ADDFUNC_STATIC(_FUNC_,_METHOD_) \
	sq_pushstring(v,#_METHOD_,-1);				/* +1 */ \
	sq_pushstring(v,#_FUNC_,-1);				/* +1 */ \
	sq_get(v,Root); /* lookup function */		/* =0 */ \
	sq_newslot(v,CPos,true);					/* -2 */
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
#define _ARR_TO_BEGIN(_TYPENAME_,_TYPENAME_LEN_) \
	sq_pushroottable(v); \
	sq_pushstring(v,_TYPENAME_,_TYPENAME_LEN_);		/* +1 */ \
	sq_get(v,-2);									/* =0 */ \
	sq_createinstance(v,-1);						/* +1 */ \
	/* NOTE: Contructor not called! */ \
	\
	float* Arr; \
	sq_getinstanceup(v,1,(void**)&Arr,0); \
	\
	float* Ret; \
	sq_getinstanceup(v,-1,(void**)&Ret,0);
// - ------------------------------------------------------------------------------------------ - //
#define _ARR_TO_BEGIN_RETONLY(_TYPENAME_,_TYPENAME_LEN_) \
	sq_pushroottable(v); \
	sq_pushstring(v,_TYPENAME_,_TYPENAME_LEN_);		/* +1 */ \
	sq_get(v,-2);									/* =0 */ \
	sq_createinstance(v,-1);						/* +1 */ \
	/* NOTE: Contructor not called! */ \
	\
	float* Ret; \
	sq_getinstanceup(v,-1,(void**)&Ret,0);
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline SQInteger qk_arr_constructor_body( HSQUIRRELVM v, float* Arr, const int ArrSize ) {
	int Args = sq_gettop(v);
	if ( Args > 1 ) {
		int ArrIndex = 0; // Which Index we are writing to. //
		
		// Iterate through all arguments //
		for ( int idx = 2; (idx <= Args) && (ArrIndex < ArrSize); idx++ ) {
			int Type = sq_gettype(v,idx);
			if ( Type & (OT_FLOAT|OT_INTEGER) ) {
				sq_getfloat(v,idx,&Arr[ArrIndex]);
				
				ArrIndex++;
			}
			else if ( Type == OT_ARRAY ) {
				int Size = sq_getsize(v,idx);
				if ( Size > ArrSize-ArrIndex ) {
					//Size = ArrSize-ArrIndex;
					return sq_throwerror(v,"array assigned is too large");
				}
	
				for ( int idx2 = 0; idx2 < Size; idx2++ ) {
					sq_pushinteger(v,idx2); 	// +1 //
					sq_get(v,idx); 				// =0 (-1 then +1) //
					sq_getfloat(v,-1,&(Arr[ArrIndex]));
					sq_poptop(v);				// -1 //
					
					ArrIndex++;
				}
			}
			else if ( Type == OT_INSTANCE ) {
				int Tag;			
				sq_gettypetag(v,idx,(SQUserPointer*)&Tag);
				if ( Tag == QK_TAG_VEC2 ) {
					if ( ArrIndex+1 < ArrSize ) {
						float* Vec;
						sq_getinstanceup(v,idx,(void**)&Vec,0);				
						
						Arr[ArrIndex+0] = Vec[0];
						Arr[ArrIndex+1] = Vec[1];
	
						ArrIndex+=2;
					}
					else {
						return sq_throwerror(v,"assignment is too large!");
					}
				}
				else if ( Tag == QK_TAG_VEC3 ) {
					if ( ArrIndex+2 < ArrSize ) {
						float* Vec;
						sq_getinstanceup(v,idx,(void**)&Vec,0);				
						
						Arr[ArrIndex+0] = Vec[0];
						Arr[ArrIndex+1] = Vec[1];
						Arr[ArrIndex+2] = Vec[2];
	
						ArrIndex+=3;
					}
					else {
						return sq_throwerror(v,"assignment is too large!");
					}
				}
				else if ( Tag == QK_TAG_VEC4 ) {
					if ( ArrIndex+3 < ArrSize ) {
						float* Vec;
						sq_getinstanceup(v,idx,(void**)&Vec,0);				
						
						Arr[ArrIndex+0] = Vec[0];
						Arr[ArrIndex+1] = Vec[1];
						Arr[ArrIndex+2] = Vec[2];
						Arr[ArrIndex+3] = Vec[3];
	
						ArrIndex+=4;
					}
					else {
						return sq_throwerror(v,"assignment is too large!");
					}
				}
				else if ( Tag == QK_TAG_SCALAR ) {
					float* Vec;
					sq_getinstanceup(v,idx,(void**)&Vec,0);				
					
					Arr[ArrIndex+0] = Vec[0];

					ArrIndex++;
				}
				else {
					return sq_throwerror(v,"bad type assigned");
				}
			}
			else {
				return sq_throwerror(v,"bad type assigned");
			}
		}
		
		// If we didn't put enough data in, pad with zeros //
		while ( ArrIndex < ArrSize ) {
			Arr[ArrIndex] = 0.0f;
			ArrIndex++;
		}
	}
	else {
		// No Arguments, so zero the data //
		int ArrIndex = 0;
		while ( ArrIndex < ArrSize ) {
			Arr[ArrIndex] = 0.0f;
			ArrIndex++;
		}
	}
	
	return SQ_VOID;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __QUACK_QUACKLIB_QUACKLIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
