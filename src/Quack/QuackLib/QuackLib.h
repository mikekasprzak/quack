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
#endif // __QUACK_QUACKLIB_QUACKLIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
