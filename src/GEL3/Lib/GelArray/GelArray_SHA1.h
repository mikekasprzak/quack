// - ------------------------------------------------------------------------------------------ - //
// GelDataArray SHA1 Hash - SHA1 Hashing code for GelDataArray library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArray_SHA1_H__
#define __Library_Data_GelDataArray_SHA1_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelDataArray_Core.h"
#include "Data_SHA1.h"
// - ------------------------------------------------------------------------------------------ - //
// Hash a block of data with an SHA1 sum //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const SHA1Hash hash_SHA1_GelDataArray( const GelDataArray<Type>* _Src ) {
	return hash_SHA1_Data( _Src->Data, _Src->Size * sizeof(Type) );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArray_SHA1_H__ //
// - ------------------------------------------------------------------------------------------ - //
