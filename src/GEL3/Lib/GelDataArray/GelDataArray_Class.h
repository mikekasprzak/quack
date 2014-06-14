// - ------------------------------------------------------------------------------------------ - //
// GelDataArray Class - Class version of DataBlock. Deletes self as it goes out of scope. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArray_Class_H__
#define __Library_Data_GelDataArray_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>

#include <Lib/DataBlock/DataBlock_Core.h>
#include <Lib/DataBlock/DataBlock_File.h>

#include "GelDataArray_Core.h"
#include "GelDataArray_File.h"
#include "GelDataArray_Hash32.h"
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class cGelDataArray {
protected:
	GelDataArray<Type>* _Data;
public:
	// Constructor //
	inline cGelDataArray() :
		_Data( 0 )
	{
	}
	
	// Since this is a "power use" class, I'm making initializing optional //
	inline cGelDataArray( const size_t _Size ) :
		_Data( new_GelDataArray<Type>( _Size ) )
	{
	}
	
	inline cGelDataArray( const size_t _Size, const Type& _InitValue ) :
		_Data( new_GelDataArray<Type>( _Size, _InitValue ) )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cGelDataArray( const char* _FileName ) :
		_Data( new_read_GelDataArray<Type>( _FileName ) )
	{
	}
	
	// Given an GelDataArray, make our GelDataArray directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cGelDataArray( GelDataArray<Type>* _Src ) :
		_Data( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cGelDataArray( const cGelDataArray<Type>& _Src ) :
		_Data( copy_GelDataArray<Type>( _Src ) )
	{
	}
	
	// Assignment Operator -- for compatibility with new_GelDataArray, use it as is //
	inline GelDataArray<Type>* operator = ( GelDataArray<Type>* Val ) {
		if ( _Data )
			delete_GelDataArray<Type>( _Data );
			
		_Data = Val;
		return _Data;
	}
	
	// Destructor //
	inline ~cGelDataArray() {
		if ( _Data )
			delete_GelDataArray<Type>( _Data );
	}
public:
	inline const size_t FirstIndex() const {
		return 0;
	}
	inline const size_t LastIndex() const {
		if ( _Data == 0 )
			return 0;
		return _Data->Size - 1;
	}
	
	// Size() returns the number of elements used. //
	inline const size_t Size() const {
		if ( _Data == 0 )
			return 0;
		return _Data->Size;
	}
	
	// SizeOf() returns the size in bytes //
	inline const size_t SizeOf() const {
		if ( _Data == 0 )
			return 0;
		return _Data->Size * sizeof( Type );
	}

	
	inline Type& operator [] ( const size_t Index ) {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		//Warning( Index < 0, "Index out of bounds (%i < 0)", Index );
		Warning( Index > Size(), "Index out of bounds (%i >= %i)", Index, Size() );
		return _Data->Data[ Index ];
	}
	inline const Type& operator [] ( const size_t Index ) const {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		//Warning( Index < 0, "Index out of bounds (%i < 0)", Index );
		Warning( Index > Size(), "Index out of bounds (%i >= %i)", Index, Size() );
		return _Data->Data[ Index ];
	}
	
	inline Type& Front() {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return _Data->Data[ FirstIndex() ];
	}
	inline const Type& Front() const {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return _Data->Data[ FirstIndex() ];
	}

	inline Type& Back() {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return _Data->Data[ LastIndex() ];
	}
	inline const Type& Back() const {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return _Data->Data[ LastIndex() ];
	}

	inline Type* FrontPtr() {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return &_Data->Data[ FirstIndex() ];
	}
	inline const Type* FrontPtr() const {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return &_Data->Data[ FirstIndex() ];
	}
	inline Type* BackPtr() {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return &_Data->Data[ LastIndex() ];
	}
	inline const Type* BackPtr() const {
		Warning( _Data == 0, "cGelDataArray w/o Data" );
		return &_Data->Data[ LastIndex() ];
	}

	
	inline GelDataArray<Type>* operator * () {
		return _Data;	
	}
public:
	inline void Load( const char* _FileName ) {
		// Delete the file if there is one loaded //
		if ( _Data )
			delete_GelDataArray<Type>( _Data );
		// Load the file //
		_Data = new_GelDataArray<Type>( _FileName );
	}
	
	inline void Save( const char* _FileName ) {
		return_void_Warning( _Data == 0, "cGelDataArray w/o Data" );
		write_GelDataArray<Type>( _Data, _FileName );
	}

public:
	inline void Resize( const size_t _Size ) {
		resize_GelDataArray<Type>( &_Data, _Size );
	}
	
	inline void Set( const Type& _Value ) {
		return_void_Warning( _Data == 0, "cGelDataArray w/o Data" );
		set_GelDataArray<Type>( _Data, _Value );
	}
	
	inline void Clear( ) {
		Set( Type() );
	}
	
	inline void Reset( ) {
		Resize( 0 );
	}
	
	inline Type* PushBack() {
		const st32 OldSize = Size();
		pushback_GelDataArray<Type>( &_Data );
		return &_Data->Data[ OldSize ];
	}
	inline Type* PushBack( const Type& _Value ) {
		const st32 OldSize = Size();
		pushback_GelDataArray<Type>( &_Data, _Value );
		return &_Data->Data[ OldSize ];
	}
	inline Type* PushBlockBack( const st32 _Count ) {
		const st32 OldSize = Size();
		pushblockback_GelDataArray<Type>( &_Data, _Count );
		return &_Data->Data[ OldSize ];
	}
	inline Type* PushBlockBack( const void* Src, const st32 _Count ) {
		const st32 OldSize = Size();
		pushblockback_GelDataArray<Type>( &_Data, Src, _Count );
		return &_Data->Data[ OldSize ];
	}
	
	inline const Type PopBack() {
		return popback_GelDataArray<Type>( &_Data );
	}
	inline const Type* PopBlockBack( const st32 _Count ) {
		return popblockback_GelDataArray<Type>( &_Data, _Count );
	}

public:
	// Compression //
	inline void UnpackLZMA( const DataBlock* _Src );
	
	inline void UnpackBZIP( DataBlock* _Src );
	inline DataBlock* PackBZIP();
	
	inline void UnpackZLIB( DataBlock* _Src );
	inline DataBlock* PackZLIB();
	
	inline void UnpackLZO( DataBlock* _Src );
	inline DataBlock* PackLZO();
	
	// Hash //
	inline const unsigned int Hash32() const {
		return_value_Warning( 0, _Data == 0, "cGelDataArray w/o Data" );
		return hash32_GelDataArray( _Data );
	}
	//inline static const MD5Hash HashMD5( const cGelDataArray<Type>& _Src  );
	//inline static const SHA1Hash HashSHA1( const cGelDataArray<Type>& _Src  );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArray_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
