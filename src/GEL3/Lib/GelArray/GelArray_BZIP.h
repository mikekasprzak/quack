// - ------------------------------------------------------------------------------------------ - //
// ArrayCompression - Compression code for Array library //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArray_BZIP_H__
#define __Library_Data_GelDataArray_BZIP_H__
// - ------------------------------------------------------------------------------------------ - //
#include "DataBlock_Core.h"
#include "DataBlock_BZIP.h"

#include "GelDataArray_Core.h"
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new GelDataArray //
template< class Type >
inline GelDataArray<Type>* unpack_BZIP_GelDataArray( DataBlock* _Src ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src );
	GelDataArray<Type>* UncompressedGelDataArray = new_GelDataArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Decode packed BZIP data to a new GelDataArray //
template< class Type >
inline GelDataArray<Type>* unpack_BZIP_GelDataArray( char* _Src, const st32 _SrcSize ) {
	DataBlock* Uncompressed = unpack_BZIP_DataBlock( _Src, _SrcSize );
	GelDataArray<Type>* UncompressedGelDataArray = new_GelDataArray<Type>( Uncompressed );
	
	// Delet our intermediary //
	delete_DataBlock( Uncompressed );
	
	return UncompressedGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Encode GelDataArray data to a packed BZIP DataBlock //
template< class Type >
inline DataBlock* pack_BZIP_DataBlock( GelDataArray<Type>* _Src ) {
	DataBlock* Source = copy_DataBlock( (char*)_Src->Data, _Src->Size * sizeof( Type ) );
	DataBlock* Compressed = pack_BZIP_DataBlock( Source );
	
	// Delete our Intermediary //
	delete_DataBlock( Source );
	
	return Compressed;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelDataArray<Type>::UnpackBZIP( cDataBlock& _Src ) {
	*this = cGelDataArray<Type>( unpack_BZIP_GelDataArray<Type>( _Src._Data ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void cGelDataArray<Type>::UnpackBZIP( DataBlock* _Src ) {
	*this = cGelDataArray<Type>( unpack_BZIP_GelDataArray<Type>( _Src ) );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* cGelDataArray<Type>::PackBZIP() {
	return pack_BZIP_DataBlock( _Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArray_BZIP_H__ //
// - ------------------------------------------------------------------------------------------ - //
