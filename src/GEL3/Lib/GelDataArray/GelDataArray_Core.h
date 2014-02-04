// - ------------------------------------------------------------------------------------------ - //
// GelDataArray - A dynamically allocated array.  A C implementation, and a lightweight STL vector. //
//
// IMPORTANT NOTE: Will not correctly copy STL containers! If you want STL, then you must use STL. //
// (or fix the copy constructor/constructor/destuctor model)
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_LIB_GelDataArray_Core_H__
#define __GEL_LIB_GelDataArray_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#pragma warning (disable : 4200) // Zero sized array member //
#endif // _MSC_VER
// - ------------------------------------------------------------------------------------------ - //
#include <new>

#include <Lib/Log/Log.h>
#include <Lib/DataBlock/DataBlock_Core.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Insertion code, Alignment resizing (min, max), searching, sorting  //
// NOTE: Consider making reallocate specific to max size change.
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
struct GelDataArray {
//	st32 MaxSize;
	st32 Size;
	Type Data[0];
	
	inline Type& Back() {
		// TODO: Assert Size //
		return Data[Size-1];
	}
	
	inline const Type& Back() const {
		// TODO: Assert Size //
		return Data[Size-1];
	}
	
	inline Type& Front() {
		// TODO: Assert Size //
		return Data[0];
	}

	inline const Type& Front() const {
		// TODO: Assert Size //
		return Data[0];
	}
	
	// No Operator [] because GelDataArray's are always pointers //
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Set GelDataArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void set_GelDataArray( GelDataArray<Type>* _Dest, const Type& _InitValue ) {
	// Set value in all entries //
	for( st idx = _Dest->Size; idx--; ) {
		_Dest->Data[idx] = _InitValue;
	}
	VVVLog("* SET 0x%x", _Dest );
}
// - ------------------------------------------------------------------------------------------ - //
// Copy one GelDataArray to another, no larger than Destination GelDataArray Size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_GelDataArray( GelDataArray<Type>* _Src, GelDataArray<Type>* _Dest ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy only Source number of entries //
		for( st idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
//			new(_Dest->Data[idx]) Type(_Src->Data[idx]);
		}
	}
	else {
		// Copy Destination number of entries //
		for( st idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
//			new(_Dest->Data[idx]) Type(_Src->Data[idx]);
		}
	}
	
	VVVLog("* COPY= 0x%x -> 0x%x", _Src, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelDataArray<Type>* _new_GelDataArray( const st32 _Size ) {
	GelDataArray<Type>* p = reinterpret_cast<GelDataArray<Type>*>(new char[ (_Size * sizeof(Type)) + sizeof(GelDataArray<Type>) ]);

	p->Size = _Size;
//	p->MaxSize = _Size;

	VVVLog("+ NEW %x",p);
	return p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void placement_new_GelDataArray( GelDataArray<Type>* p ) {
	// Placement New //
	for ( st32 idx = 0; idx < p->Size; idx++ ) {
		new(&(p->Data[idx])) Type;
	}
	
	VVVLog("* pNEW %x",p);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelDataArray<Type>* new_GelDataArray( const st32 _Size ) {
	GelDataArray<Type>* p = _new_GelDataArray<Type>( _Size );
	
	placement_new_GelDataArray( p );

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
// Use this alternative "new" function when you want to initialize the GelDataArray to a value //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelDataArray<Type>* new_GelDataArray( const st32 _Size, const Type& _InitValue ) {
	// Allocate it //
	GelDataArray<Type>* NewGelDataArray = _new_GelDataArray<Type>( _Size );
	
	// Initialize it //
	set_GelDataArray<Type>( NewGelDataArray, _InitValue );
	
	// Return it //
	return NewGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void _delete_GelDataArray( GelDataArray<Type>* p ) {
	VVVLog("- DELETE %x", p);
	delete [] p;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void placement_delete_GelDataArray( GelDataArray<Type>* p ) {
	// Placement Delete //
	for ( st32 idx = 0; idx < p->Size; idx++ ) {
		p->Data[idx].~Type();
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void delete_GelDataArray( GelDataArray<Type>* p ) {
	placement_delete_GelDataArray( p );
	
	_delete_GelDataArray<Type>( p );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Now returns a pointer. All functions will return pointers. Never References. //
template< class Type >
inline Type* index_GelDataArray( GelDataArray<Type>* p, const size_t _Index ) {
	return &(p->Data[ _Index ]);
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline st32 size_GelDataArray( GelDataArray<Type>* p ) {
	return p->Size;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// New that set the maximum size //
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelDataArray<Type>* newmax_GelDataArray( const st32 _MaxSize ) {
//	GelDataArray<Type>* p = reinterpret_cast<GelDataArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelDataArray<Type>) ]);
//
//	p->Size = 0;
//	p->MaxSize = _MaxSize;
//
//	return p;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelDataArray<Type>* newmax_GelDataArray( const st32 _MaxSize, const st32 _Size ) {
//	GelDataArray<Type>* p = reinterpret_cast<GelDataArray<Type>*>(new char[ (_MaxSize * sizeof(Type)) + sizeof(GelDataArray<Type>) ]);
//
//	p->Size = _Size;
//	p->MaxSize = _MaxSize;
//
//	return p;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelDataArray<Type>* newmax_GelDataArray( const st32 _MaxSize, const st32 _Size, const Type& _InitValue ) {
//	// Allocate it //
//	GelDataArray<Type>* NewGelDataArray = newmax_GelDataArray<Type>( _MaxSize, _Size );
//	
//	// Initialize it //
//	set_GelDataArray<Type>( NewGelDataArray, _InitValue );
//	
//	// Return it //
//	return NewGelDataArray;
//}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Copy, but if the destination is larger, fill in rest of space with _InitValue //
template< class Type >
inline void copy_GelDataArray( GelDataArray<Type>* _Src, GelDataArray<Type>* _Dest, const Type& _InitValue ) {
	// If source is smaller than the destination //
	if ( _Dest->Size > _Src->Size ) {
		// Copy Source number of entries //
		for( st idx = _Src->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
//			new(_Dest->Data[idx]) Type(_Src->Data[idx]);
		}
		
		// Fill the rest of the data with initializer //
		Type* NewDest = &_Dest->Data[_Src->Size];
		for( st idx = (_Dest->Size - _Src->Size); idx--; ) {
			NewDest[idx] = _InitValue;
		}
	}
	else {
		// Copy Destination number of entries //
		for( st idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = _Src->Data[idx];
//			new(_Dest->Data[idx]) Type(_Src->Data[idx]);
		}
	}

	VVVLog("* COPY+ 0x%x -> 0x%x", _Src, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //
// Return a duplicate of an GelDataArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelDataArray<Type>* new_copy_GelDataArray( GelDataArray<Type>* _Src ) {
	// Allocate our new block //
	GelDataArray<Type>* NewBlock = _new_GelDataArray<Type>( _Src->Size );
	
	// Copy the data to our new block //
	copy_GelDataArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelDataArray<Type>* new_GelDataArray( GelDataArray<Type>* _Src ) {
//	return copy_GelDataArray<Type>( _Src );
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
// Convert from DataBlock to GelDataArray, and vice versa //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline GelDataArray<Type>* copy_GelDataArray( DataBlock* _Src ) {
	// Allocate our new block //
	GelDataArray<Type>* NewBlock = _new_GelDataArray<Type>( _Src->Size / sizeof(Type) );
	
	// Copy the data to our new block //
	copy_GelDataArray<Type>( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline GelDataArray<Type>* new_GelDataArray( DataBlock* _Src ) {
//	return copy_GelDataArray<Type>( _Src );
//}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* copy_DataBlock( GelDataArray<Type>* _Src ) {
	// Allocate our new block //
	DataBlock* NewBlock = _new_DataBlock( _Src->Size * sizeof( Type ) );
	
	// Copy the data to our new block //
	copy_DataBlock( _Src, NewBlock );
	
	// Return the block //
	return NewBlock;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline DataBlock* new_DataBlock( GelDataArray<Type>* _Src ) {
	return copy_DataBlock( _Src );
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_GelDataArray( DataBlock* _Src, GelDataArray<Type>* _Dest ) {
	Type* SrcPtr = (Type*)_Src->Data;
	st32 SrcSize = _Src->Size / sizeof( Type );
	
	// If source is smaller than the destination //
	if ( _Dest->Size > SrcSize ) {
		// Copy only Source number of entries //
		for( st idx = SrcSize; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
	else {
		// Copy Destination number of entries //
		for( st idx = _Dest->Size; idx--; ) {
			_Dest->Data[idx] = SrcPtr[idx];
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void copy_DataBlock( GelDataArray<Type>* _Src, DataBlock* _Dest  ) {
	char* SrcPtr = (char*)_Src->Data;
	st32 SrcSize = _Src->Size * sizeof( Type );
	
	copy_DataBlock( SrcPtr, SrcSize, _Dest );
}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelDataArray( GelDataArray<Type>** p, const st32 _NewSize ) {
	// Allocate our new block //
	GelDataArray<Type>* NewGelDataArray = _new_GelDataArray<Type>( _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelDataArray<Type>( *p, NewGelDataArray );
		
		// Delete the old block ponted to //
		delete_GelDataArray<Type>( *p );
	}
	else {
		// Do Constructors, as this data is brand new //
		placement_new_GelDataArray( *p );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation that, in the case it doesn't exist copies the _InitValue (instead of placement new) //
template< class Type >
inline void reallocate_GelDataArray( GelDataArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	// Allocate our new block //
	GelDataArray<Type>* NewGelDataArray = _new_GelDataArray<Type>( _NewSize );
	
	if ( *p ) {
		// Copy the data to our new block //
		copy_GelDataArray<Type>( *p, NewGelDataArray, _InitValue );
		
		// Delete the old block ponted to //
		delete_GelDataArray<Type>( *p );
	}
	else {
		// No copy made, so fill in with the data //
		set_GelDataArray<Type>( NewGelDataArray, _InitValue );
	}
	
	// Make the pointer point to the new block //
	(*p) = NewGelDataArray;
}
// - ------------------------------------------------------------------------------------------ - //
// Variation of reallocate that looks at the internal size //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void reallocate_GelDataArray( GelDataArray<Type>** p ) {
	reallocate_GelDataArray<Type>( p, (*p)->Size );
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void reallocatemax_GelDataArray( GelDataArray<Type>** p, const st32 _NewMaxSize ) {
//	// Allocate our new block //
//	GelDataArray<Type>* NewGelDataArray = newmax_GelDataArray<Type>( _NewMaxSize, (*p)->Size );
//	
//	if ( *p ) {
//		// Copy the data to our new block //
//		copy_GelDataArray<Type>( *p, NewGelDataArray );
//		
//		// Delete the old block ponted to //
//		delete_GelDataArray<Type>( *p );
//	}
//		
//	// Make the pointer point to the new block //
//	(*p) = NewGelDataArray;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void reallocatemax_GelDataArray( GelDataArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize ) {
//	// Allocate our new block //
//	GelDataArray<Type>* NewGelDataArray = newmax_GelDataArray<Type>( _NewMaxSize, _NewSize );
//	
//	if ( *p ) {
//		// Copy the data to our new block //
//		copy_GelDataArray<Type>( *p, NewGelDataArray );
//		
//		// Delete the old block ponted to //
//		delete_GelDataArray<Type>( *p );
//	}
//	
//	// Make the pointer point to the new block //
//	(*p) = NewGelDataArray;
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void reallocatemax_GelDataArray( GelDataArray<Type>** p, const st32 _NewMaxSize, const st32 _NewSize, const Type& _InitValue ) {
//	// Allocate our new block //
//	GelDataArray<Type>* NewGelDataArray = newmax_GelDataArray<Type>( _NewMaxSize, _NewSize );
//	
//	if ( *p ) {
//		// Copy the data to our new block //
//		copy_GelDataArray<Type>( *p, NewGelDataArray, _InitValue );
//		
//		// Delete the old block ponted to //
//		delete_GelDataArray<Type>( *p );
//	}
//	else {
//		// No copy made, so fill in with the data //
//		set_GelDataArray<Type>( NewGelDataArray, _InitValue );		
//	}
//	
//	// Make the pointer point to the new block //
//	(*p) = NewGelDataArray;
//}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelDataArray( GelDataArray<Type>** p, const st32 _NewSize ) {
	VVVLog( "* %s", __PRETTY_FUNCTION__ );
	if ( *p == 0 ) {
		*p = new_GelDataArray<Type>( _NewSize );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->Size ) {
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_GelDataArray<Type>( p, _NewSize );
	}
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void resize_GelDataArray( GelDataArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
	VVVLog( "* %s", __PRETTY_FUNCTION__ );
	if ( *p == 0 ) {
		*p = new_GelDataArray<Type>( _NewSize, _InitValue );
	}
	// A cheat.  We can resize the block without reallocating
	else if ( _NewSize <= (*p)->Size ) {
		st32 OldSize = (*p)->Size;
		
		// Set the size to the new size, and we're done //
		(*p)->Size = _NewSize;
		
		// If this grows us //
		if ( OldSize < _NewSize ) {
			// Fill in new values with passed value //
			for( st idx = (_NewSize - OldSize); idx--; ) {
				(*p)->Data[OldSize + idx] = _InitValue;
			}
		}
	}
	else {
		// Well, we tried.  We need to reallocate and copy the data. //
		reallocate_GelDataArray<Type>( p, _NewSize, _InitValue );
	}
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void resize2_GelDataArray( GelDataArray<Type>** p, const st32 _NewSize ) {
//	if ( *p == 0 ) {
//		*p = new_GelDataArray<Type>( _NewSize );		
//	}
//	// A cheat.  We can resize the block without reallocating
//	else if ( _NewSize <= (*p)->MaxSize ) {
//		// Set the size to the new size, and we're done //
//		(*p)->Size = _NewSize;
//	}
//	else {
//		// Well, we tried.  We need to reallocate and copy the data. //
//		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
//		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
//		
//		reallocatemax_GelDataArray<Type>( p, NewMaxSize, _NewSize );
//	}
//}
// - ------------------------------------------------------------------------------------------ - //
//template< class Type >
//inline void resize2_GelDataArray( GelDataArray<Type>** p, const st32 _NewSize, const Type& _InitValue ) {
//	if ( *p == 0 ) {
//		*p = new_GelDataArray<Type>( _NewSize, _InitValue );
//	}
//	// A cheat.  We can resize the block without reallocating
//	else if ( _NewSize <= (*p)->MaxSize ) {
//		st32 OldSize = (*p)->Size;
//		
//		// Set the size to the new size, and we're done //
//		(*p)->Size = _NewSize;
//		
//		// If this grows us //
//		if ( OldSize < _NewSize ) {
//			// Fill in new values with passed value //
//			for( st32 idx = (_NewSize - OldSize); idx--; ) {
//				(*p)->Data[OldSize + idx] = _InitValue;
//			}
//		}
//	}
//	else {
//		// Well, we tried.  We need to reallocate and copy the data. //
//		st32 DoubleSize = (*p)->MaxSize + (*p)->MaxSize;
//		st32 NewMaxSize = DoubleSize > _NewSize ? DoubleSize : _NewSize;
//		
//		reallocatemax_GelDataArray<Type>( p, NewMaxSize, _NewSize, _InitValue );
//	}
//}
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelDataArray( GelDataArray<Type>** p ) {
	VVVLog( "* %s", __PRETTY_FUNCTION__ );
	Warning( p == 0, "Zero Pointer Pointer" );

	if ( (*p) == 0 ) {
//		resize2_GelDataArray<Type>( p, 1 );
		resize_GelDataArray<Type>( p, 1 );
	}
	else {
//		resize2_GelDataArray<Type>( p, (*p)->Size + 1 );
		resize_GelDataArray<Type>( p, (*p)->Size + 1 );
	}
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushback_GelDataArray( GelDataArray<Type>** p, const Type& _Value ) {
	VVVLog( "* %s", __PRETTY_FUNCTION__ );
	Warning( p == 0, "Zero Pointer Pointer" );

	if ( (*p) == 0 )
//		resize2_GelDataArray<Type>( p, 1, _Value );
		resize_GelDataArray<Type>( p, 1, _Value );
	else
//		resize2_GelDataArray<Type>( p, (*p)->Size + 1, _Value );
		resize_GelDataArray<Type>( p, (*p)->Size + 1, _Value );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type& popback_GelDataArray( GelDataArray<Type>** p ) {
	VVVLog( "* %s", __PRETTY_FUNCTION__ );
	Warning( p == 0, "Zero Pointer Pointer" );
	
	return_value_Warning ( Type(), (*p)->Size == 0, "Zero Size" );

	// TODO: Assert if Size == 0 //
	(*p)->Size--;
	
	return (*p)->Data[ (*p)->Size ];
} 
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void insert_GelDataArray( GelDataArray<Type>** p, const size_t Index, const Type& _Value ) {
	VVVLog( "* %s", __PRETTY_FUNCTION__ );
	Warning( p == 0, "Zero Pointer Pointer" );

	pushback_GelDataArray( p );

	Warning( Index >= (*p)->Size, "Invalid Index %i (Size: %i)", (int)Index, (int)(*p)->Size );

	if ( (*p)->Size > 1 ) {
		for( st idx = (*p)->Size-1; idx-- != Index; ) {
			(*p)->Data[idx+1] = (*p)->Data[idx];
		}
	}

	(*p)->Data[ Index ] = _Value;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void erase_GelDataArray( GelDataArray<Type>** p, const size_t Index ) {
	Warning( p == 0, "Zero Pointer Pointer" );
	//Warning( (*p) == 0, "Zero Pointer" );
	Warning( Index >= (*p)->Size, "Invalid Index %i (Size: %i)", Index, (*p)->Size );

	// This is okay //
	if ( (*p) == 0 )
		return;
	
	// TODO: Assert this? 
	if ( (*p)->Size == 0 )
		return;
	
	st Size = (*p)->Size-1;
	for( st idx = Index; idx < Size; idx++ ) {
		(*p)->Data[idx] = (*p)->Data[idx+1];
	}

	(*p)->Size--;
	
	// NOTE: popback doesn't work here, since popback gets the last element //
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline int findfirst_GelDataArray( GelDataArray<Type>** p, const Type& _Value ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	// This is okay //
	if ( (*p) == 0 )
		return -1;
		
	for( st idx = 0; idx < (*p)->Size; idx++ ) {
		if ( (*p)->Data[idx] == _Value ) {
			return idx;
		}
	}

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline int findlast_GelDataArray( GelDataArray<Type>** p, const Type& _Value ) {
	Warning( p == 0, "Zero Pointer Pointer" );

	// This is okay //
	if ( (*p) == 0 )
		return -1;
		
	for( st idx = (*p)->Size; idx--; ) {
		if ( (*p)->Data[idx] == _Value ) {
			return idx;
		}
	}

	return -1;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* back_GelDataArray( GelDataArray<Type>* p ) {
	if ( p == 0 )
		return 0;
	else
		return &(p->Data[ p->Size - 1 ]);
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* front_GelDataArray( GelDataArray<Type>* p ) {
	if ( p == 0 )
		return 0;
	else
		return &(p->Data[ 0 ]);
} 
// - ------------------------------------------------------------------------------------------ - //



// - ------------------------------------------------------------------------------------------ - //
// Push and pop large groups of objects on to the GelDataArray //
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelDataArray( GelDataArray<Type>** p, const st32 _Count ) {
	if ( (*p) == 0 )
		resize_GelDataArray( p, _Count );
	else
		resize_GelDataArray( p, (*p)->Size + _Count );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline void pushblockback_GelDataArray( GelDataArray<Type>** p, const void* Src, const st32 _Count ) {
	st32 OldSize = (*p)->Size;
	
	if ( (*p) == 0 )
		resize_GelDataArray( p, _Count );
	else
		resize_GelDataArray( p, (*p)->Size + _Count );
	
	copy_Data( Src, &((*p)->Data[ OldSize ]), sizeof( Type ) * _Count );
} 
// - ------------------------------------------------------------------------------------------ - //
template< class Type >
inline Type* popblockback_GelDataArray( GelDataArray<Type>** p, const st32 _Count ) {
	// TODO: Assert if Size == 0 //
	(*p)->Size -= _Count;
	
	return &((*p)->Data[ (*p)->Size ]);
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_LIB_GelDataArray_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
