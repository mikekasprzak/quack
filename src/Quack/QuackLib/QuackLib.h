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
	return sq_throwerror(v,"Cannot " #_OP_ " type versus vector. Types must be same vector type, or vector and scalar.");
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
#endif // __QUACK_QUACKLIB_QUACKLIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
