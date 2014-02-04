// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for GelDataArray library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArray_LZO_H__
#define __Library_Data_GelDataArray_LZO_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_LZO.h"

#include "GelDataArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZO data to a new GelDataArray //
template< class Type >
inline GelDataArray<Type>* unpack_LZO_GelDataArray( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_LZO_DataBlock( _Src );
	GelDataArray<Type>* UncompressedArray = new_GelDataArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed LZO data to a new GelDataArray //
template< class Type >
inline GelDataArray<Type>* unpack_LZO_GelDataArray( char* _Src, const st32 _SrcSize ) {
	DataBlock* Uncompressed = unpack_LZO_DataBlock( _Src, _SrcSize );
	GelDataArray<Type>* UncompressedArray = new_GelDataArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode array data to a packed LZO DataBlock //
template< class Type >
inline DataBlock* pack_LZO_DataBlock( GelDataArray<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_LZO_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelDataArray<Type>::UnpackLZO( cDataBlock& _Src ) {
	*this = cGelDataArray<Type>( unpack_LZO_GelDataArray<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelDataArray<Type>::UnpackLZO( DataBlock* _Src ) {
	*this = cGelDataArray<Type>( unpack_LZO_GelDataArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cGelDataArray<Type>::PackLZO() {
	return pack_LZO_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArray_LZO_H__ //
// - ------------------------------------------------------------------------------------------ - //
