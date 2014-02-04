// - ------------------------------------------------------------------------------------------ - //
// GelDataArray MD5 Hash - MD5 Hashing code for GelDataArray library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArray_MD5_H__
#define __Library_Data_GelDataArray_MD5_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelDataArray_Core.h"
#include "Data_MD5.h"
// - ------------------------------------------------------------------------------------------ - //
// Hash a block of data with an MD5 sum //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const MD5Hash hash_MD5_GelDataArray( const GelDataArray<Type>* _Src ) {
	return hash_MD5_Data( _Src->Data, _Src->Size * sizeof(Type) );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArray_MD5_H__ //
// - ------------------------------------------------------------------------------------------ - //
