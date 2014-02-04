// - ------------------------------------------------------------------------------------------ - //
// GelDataArrayPtr Class - Variation of cGelDataArray. Includes pointer specific calls. //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelDataArrayPtr_Class_H__
#define __Library_Data_GelDataArrayPtr_Class_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelDataArray_Class.h"
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
class cGelDataArrayPtr: public cGelDataArray<Type> {
public:
	enum {
		null = 0
	};
public:
	// Constructor //
	inline cGelDataArrayPtr() :
		cGelDataArray<Type>()
	{
	}
	
	// Contrast to cGelDataArray, this will always initialize to null, due to uses //
	inline cGelDataArrayPtr( const size_t _Size ) :
		cGelDataArray<Type>( _Size, (Type)null )
	{
	}
	
	inline cGelDataArrayPtr( const size_t _Size, const Type& _InitValue ) :
		cGelDataArray<Type>( _Size, _InitValue )
	{
	}
	
	// Given a filename as an argument, load it //
	inline cGelDataArrayPtr( const char* _FileName ) :
		cGelDataArray<Type>( _FileName )
	{
	}
	
	// Given an GelDataArray, make our GelDataArray directly what we were given //
	// Note: I'm now in charge of freeing, so don't try sharing this data //
	inline cGelDataArrayPtr( GelDataArray<Type>* _Src ) :
		cGelDataArray<Type>( _Src )
	{
	}
	
	// Copy Constructor - replicates the contents of a DataBlock//
	inline cGelDataArrayPtr( const cGelDataArray<Type>& _Src ) :
		cGelDataArray<Type>( _Src )
	{
	}
	
	// Destructor //
	inline virtual ~cGelDataArrayPtr() {
		// Will not automatically delete! You must explicitly call delete! //
	}
public:	
	// Removing is nulling the pointer //
	inline void Remove( const size_t Index ) {
		cGelDataArray<Type>::_Data->Data[ Index ] = (Type)null;
	}
	inline void RemoveAll() {
		for ( size_t idx = cGelDataArray<Type>::Size(); idx--; ) {
			Remove( idx );
		}
	}
	inline void RemoveAll( const size_t Start, const size_t Count ) {
		// NOTE: size_t handles < 0
		Assert( Start >= cGelDataArray<Type>::Size(), "Start (%i) is out of range (>= %i)", Start, cGelDataArray<Type>::Size() );
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > cGelDataArray<Type>::Size() )
			idx = cGelDataArray<Type>::Size();
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Remove(idx);
		}
	}

	
	// Deleting is explicitly C++ style delete, followed by nulling //
	inline void Delete( const size_t Index ) {
		if ( cGelDataArray<Type>::_Data->Data[ Index ] != (Type)null ) {
			delete cGelDataArray<Type>::_Data->Data[ Index ];
			Remove( Index ); // Null the Pointer //
		}
	}
	inline void DeleteAll() {
		for ( size_t idx = cGelDataArray<Type>::Size(); idx--; ) {
			Delete( idx );
		}
	}
	inline void DeleteAll( const size_t Start, const size_t Count ) {
		// NOTE: size_t handles < 0
		Assert( Start >= cGelDataArray<Type>::Size(), "Start (%i) is out of range (>= %i)", Start, cGelDataArray<Type>::Size() );
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > cGelDataArray<Type>::Size() )
			idx = cGelDataArray<Type>::Size();
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			Delete(idx);
		}
	}
	
	// Variation of delete that does not null. Exists only really to save a cycle. //
	inline void _Delete( const size_t Index ) {
		if ( cGelDataArray<Type>::_Data->Data[ Index ] != (Type)null ) {
			delete cGelDataArray<Type>::_Data->Data[ Index ];
		}
	}
	inline void _DeleteAll() {
		for ( size_t idx = cGelDataArray<Type>::Size(); idx--; ) {
			_Delete( idx );
		}
	}
	inline void _DeleteAll( const size_t Start, const size_t Count ) {
		// NOTE: size_t handles < 0
		Assert( Start >= cGelDataArray<Type>::Size(), "Start (%i) is out of range (>= %i)", Start, cGelDataArray<Type>::Size() );
		// NOTE: This is written funny to encourage the optimizer to eliminate this check //
		size_t idx;
		if ( Start+Count > cGelDataArray<Type>::Size() )
			idx = cGelDataArray<Type>::Size();
		else
			idx = Start+Count;

		// Index in Reverse Order //
		for ( ; idx-- > Start; ) {
			_Delete(idx);
		}
	}
		
	// Erasing is physically removing the data while resizing //
	// TODO: Do this inside cGelDataArray. //

	// DeleteErase doing a delete, followed by physically removing the data while resizing //
	// TODO: this. //
	
	// More word choices: Eradicate, Eliminate, Destroy, Kill, Expunge
	// DeleteErase, while phonetically strange, is more specific RE what is being done.
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelDataArrayPtr_Class_H__ //
// - ------------------------------------------------------------------------------------------ - //
