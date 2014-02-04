// - ------------------------------------------------------------------------------------------ - //
// GelVFile - "FILE*" like implementation that's to a virtual file in RAM //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_GELCore_GelVFile_Core_H__
#define __Library_GELCore_GelVFile_Core_H__
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add functions for reading/adapting floating point numbers from IEEE to other needed types
// TODO: Add functions for converting/writing floats to fixed point numbers (a cheat)
// - ------------------------------------------------------------------------------------------ - //
#include "../Data/Data_Core.h"
#include "../GelDataArray/GelDataArray_Core.h"

#include "../GelFile/Endian.h"
// - ------------------------------------------------------------------------------------------ - //
struct GelVFile {
	size_t Position;
	GelDataArray<char>* Data;
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Get the size of an open file, in bytes //
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_GelVFile( GelVFile* fp ) {
	return fp->Data->Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Opening files //
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* open_GelVFile( const char* = "rb" ) {
	GelVFile* MyFile = new GelVFile;
	MyFile->Position = 0;
	MyFile->Data = new GelDataArray<char>();
	return MyFile;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* open_readonly_GelVFile( ) {
	return open_GelVFile();
}
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* open_writeonly_GelVFile( ) {
	return open_GelVFile();
}
// - ------------------------------------------------------------------------------------------ - //

// NOTE: C library has 2 interesting functions.  tmpfile() and tmpname( .. ).  tmpfile creates //
//   a temorary file instance, that erases itself when closed.  tmpname returns a legit temporary //
//   filename, that does not conflict (with what, I don't know).  If you choose to open the file, //
//   don't forget to delete it with "remove( "File.blah" );". //


// - ------------------------------------------------------------------------------------------ - //
// Closing Files //
// - ------------------------------------------------------------------------------------------ - //
inline void close_GelVFile( GelVFile* fp ) {
	delete_GelDataArray<char>( fp->Data );
	
	delete fp;
}
// - ------------------------------------------------------------------------------------------ - //
// Special Function -- Destroyes the shell. Returns the important data part. // 
inline GelDataArray<char>* close_skeleton_GelVFile( GelVFile* fp ) {
	GelDataArray<char>* Ret = fp->Data;
	
	delete fp;
	
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Converting between other Gel Types //
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* copy_GelVFile( const char* In, const size_t Size ) {
	GelVFile* MyFile = new GelVFile;
	MyFile->Position = 0;
	MyFile->Data = new_GelDataArray<char>( Size );
	copy_Data( In, MyFile->Data->Data, Size );
	return MyFile;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* copy_GelVFile( const DataBlock* In ) {
	GelVFile* MyFile = new GelVFile;
	MyFile->Position = 0;
	MyFile->Data = new_GelDataArray<char>( In->Size );
	copy_Data( In->Data, MyFile->Data->Data, In->Size );
	return MyFile;
}
// - ------------------------------------------------------------------------------------------ - //
inline GelVFile* copy_GelVFile( GelDataArray<char>* In ) {
	GelVFile* MyFile = new GelVFile;
	MyFile->Position = 0;
	MyFile->Data = new_copy_GelDataArray<char>( In );
	return MyFile;
}
// - ------------------------------------------------------------------------------------------ - //


// NOTE: fread( TargetPointer, DataSize, Count, FilePointer ); //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type read_GelVFile( GelVFile* fp ) {
	Type Target;
	copy_Data( &(fp->Data->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	return Target;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readswap_GelVFile( GelVFile* fp ) {
	Type Target;
	copy_Data( &(fp->Data->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	return byteswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readbe_GelVFile( GelVFile* fp ) {
	Type Target;
	copy_Data( &(fp->Data->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	return beswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const Type readle_GelVFile( GelVFile* fp ) {
	Type Target;
	copy_Data( &(fp->Data->Data[fp->Position]), (char*)&Target, sizeof( Target ) );
	fp->Position += sizeof( Target );
	return leswap(Target);
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t read_GelVFile( GelVFile* fp, char* Data, const size_t Size ) {
	copy_Data( &(fp->Data->Data[fp->Position]), Data, Size );
	fp->Position += Size;
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Templated read functions (read_File<int>( fp );) //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t write_GelVFile( GelVFile* fp, const Type Data ) {
	pushblockback_GelDataArray( &(fp->Data), sizeof(Data) );

	copy_Data( (char*)&Data, &(fp->Data->Data[fp->Position]), sizeof( Data ) );
	fp->Position += sizeof( Data );
	
	return sizeof( Data );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writeswap_GelVFile( GelVFile* fp, const Type Data ) {
	Type Copy = byteswap(Data);
	
	pushblockback_GelDataArray( &(fp->Data), sizeof(Copy) );
	
	copy_Data( (char*)&Copy, &(fp->Data->Data[fp->Position]), sizeof( Copy ) );
	fp->Position += sizeof( Copy );
	
	return sizeof( Copy );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writebe_GelVFile( GelVFile* fp, const Type Data ) {
	Type Copy = beswap(Data);
	
	pushblockback_GelDataArray( &(fp->Data), sizeof(Copy) );
	
	copy_Data( (char*)&Copy, &(fp->Data->Data[fp->Position]), sizeof( Copy ) );
	fp->Position += sizeof( Copy );
	
	return sizeof( Copy );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline const size_t writele_GelVFile( GelVFile* fp, const Type Data ) {
	Type Copy = leswap(Data);
	
	pushblockback_GelDataArray( &(fp->Data), sizeof(Copy) );
	
	copy_Data( (char*)&Copy, &(fp->Data->Data[fp->Position]), sizeof( Copy ) );
	fp->Position += sizeof( Copy );
	
	return sizeof( Copy );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline const size_t write_GelVFile( GelVFile* fp, const char* Data, const size_t Size ) {
	pushblockback_GelDataArray( &(fp->Data), Size );
	
	copy_Data( Data, &(fp->Data->Data[fp->Position]), Size );
	fp->Position += Size;
	return Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelVFile_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
