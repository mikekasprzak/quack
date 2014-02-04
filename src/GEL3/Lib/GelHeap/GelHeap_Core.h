// - ------------------------------------------------------------------------------------------ - //
// GelHeap - A combination block of data + Index Key directory type //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Library_Data_GelHeap_Core_H__
#define __Library_Data_GelHeap_Core_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/DataBlock/DataBlock_Core.h>
#include <Lib/GelDataArray/GelDataArray_Core.h>
// - ------------------------------------------------------------------------------------------ - //
struct GelHeap {
	GelDataArray<size_t>* Index;
	GelDataArray<char>* Data;
	
	// Since this is a complicated struct, I've added this //
	inline char* operator [] ( const size_t _Index ) {
		return &(Data->Data[ Index->Data[ _Index ] ]);
	}

	inline const char* operator [] ( const size_t _Index ) const {
		return &(Data->Data[ Index->Data[ _Index ] ]);
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline GelHeap* new_GelHeap() {
	GelHeap* p = new GelHeap;

	// Allocate an array for our entries //
	p->Index = new_GelDataArray<size_t>(0);
	
	// Allocate a mass of data //
	p->Data = new_GelDataArray<char>(0);

	return p;
}
// - ------------------------------------------------------------------------------------------ - //
//inline GelHeap* new_GelHeap( const size_t _IndexMax, const size_t _DataMax ) {
//	GelHeap* p = new GelHeap;
//
//	// Allocate an array for our entries //
//	p->Index = newmax_GelDataArray<size_t>(_IndexMax);
//	
//	// Allocate a mass of data //
//	p->Data = newmax_GelDataArray<char>(_DataMax);
//
//	return p;
//}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_GelHeap( GelHeap* p ) {
	if ( p->Index )
		delete_GelDataArray<size_t>( p->Index );
	
	if ( p->Data )
		delete_GelDataArray<char>( p->Data );
	
	delete p;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
inline char* index_GelHeap( GelHeap* p, const size_t _Index ) {
	return &(p->Data->Data[ p->Index->Data[ _Index ] ]);
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t size_GelHeap( GelHeap* p ) {
	return p->Index->Size;
}
// - ------------------------------------------------------------------------------------------ - //
inline const size_t heapsize_GelHeap( GelHeap* p ) {
	return p->Data->Size;
}
// - ------------------------------------------------------------------------------------------ - //
inline size_t allocate_GelHeap( GelHeap* p, const size_t _AllocationSize ) {
	// Allocate a key //
	size_t Key = p->Index->Size;
	pushback_GelDataArray<size_t>( &p->Index, p->Data->Size );
	
	// Allocate memory //
	pushblockback_GelDataArray<char>( &p->Data, _AllocationSize );
	
	// Return key //
	return Key;
}
// - ------------------------------------------------------------------------------------------ - //
inline size_t allocate_GelHeap( GelHeap* p, const char* Src, const size_t _AllocationSize ) {
	// Allocate a key //
	size_t Key = p->Index->Size;
	pushback_GelDataArray<size_t>( &p->Index, p->Data->Size );
	
	// Allocate memory //
	pushblockback_GelDataArray<char>( &p->Data, _AllocationSize );
	
	// Copy Data //
	copy_Data( Src, index_GelHeap( p, Key ), _AllocationSize );
	
	// Return key //
	return Key;
}
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#endif // __Library_Data_GelHeap_Core_H__ //
// - ------------------------------------------------------------------------------------------ - //
