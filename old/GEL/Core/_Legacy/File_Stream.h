// - ------------------------------------------------------------------------------------------ - //
// File Stream - File functions adapted to Stream syntax.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_File_Stream_H__
#define __Library_Data_File_Stream_H__
// - ------------------------------------------------------------------------------------------ - //
#include "Stream_Core.h"
#include "File_Core.h"
// - ------------------------------------------------------------------------------------------ - //
//namespace Data {
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Get the size of an open file, in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_Stream( FILE* fp ) {
	return size_File( fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening Stream //
// - ------------------------------------------------------------------------------------------ - //
template<>
inline FILE* open_Stream<FILE>( const char* FileName ) {
	return open_File( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline FILE* open_Stream<FILE>( const char* FileName, const char* OpenMask ) {
	return open_File( FileName, OpenMask );
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline FILE* open_readonly_Stream<FILE>( const char* FileName ) {
	return open_readonly_File( FileName );
}
// - ------------------------------------------------------------------------------------------ - //
template<>
inline FILE* open_writeonly_Stream<FILE>( const char* FileName ) {
	return open_writeonly_File( FileName );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Closing Stream //
// - ------------------------------------------------------------------------------------------ - //
inline void close_Stream( FILE* fp ) {
	close_File( fp );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type read_Stream( FILE* fp ) {
	return read_File<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readswap_Stream( FILE* fp ) {
	return readswap_File<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readbe_Stream( FILE* fp ) {
	return readbe_File<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readle_Stream( FILE* fp ) {
	return readle_File<Type>( fp );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_Stream( FILE* fp, char* Data, const size_t Size ) {
	return read_File( fp, Data, Size );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_Stream( FILE* fp, const Type Data ) {
	return write_File( fp, Data );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writeswap_Stream( FILE* fp, const Type Data ) {
	return writeswap_File( fp, Data );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writebe_Stream( FILE* fp, const Type Data ) {
	return writebe_File( fp, Data );}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writele_Stream( FILE* fp, const Type Data ) {
	return writele_File( fp, Data );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_Stream( FILE* fp, const char* Data, const size_t Size ) {
	return write_File( fp, Data, Size );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//}; // namespace Data //
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_File_Stream_H__ //
// - ------------------------------------------------------------------------------------------ - //
