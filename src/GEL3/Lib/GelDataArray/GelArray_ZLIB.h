// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArray_ZLIB_H__
#define __Library_Data_GelDataArray_ZLIB_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_ZLIB.h"

#include "GelDataArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Decode packed ZLIB data to a new GelDataArray //
template< class Type >
inline GelDataArray<Type>* unpack_ZLIB_GelDataArray( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_ZLIB_DataBlock( _Src );
	GelDataArray<Type>* UncompressedGelDataArray = new_GelDataArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed ZLIB data to a new GelDataArray //
template< class Type >
inline GelDataArray<Type>* unpack_ZLIB_GelDataArray( char* _Src, const st32 _SrcSize ) {
	DataBlock* Uncompressed = unpack_ZLIB_DataBlock( _Src, _SrcSize );
	GelDataArray<Type>* UncompressedGelDataArray = new_GelDataArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode GelDataArray data to a packed ZLIB DataBlock //
template< class Type >
inline DataBlock* pack_ZLIB_DataBlock( GelDataArray<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_ZLIB_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelDataArray<Type>::UnpackZLIB( cDataBlock& _Src ) {
	*this = cGelDataArray<Type>( unpack_ZLIB_GelDataArray<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelDataArray<Type>::UnpackZLIB( DataBlock* _Src ) {
	*this = cGelDataArray<Type>( unpack_ZLIB_GelDataArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cGelDataArray<Type>::PackZLIB() {
	return pack_ZLIB_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArray_ZLIB_H__ //
// - ------------------------------------------------------------------------------------------ - //
