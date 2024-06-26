// - ------------------------------------------------------------------------------------------ - //
// USAGE:
//   GelArray<Type> for an array 
//   GelVert2 for an array of 2D elements containing just a Position
//   GelVert3NC for an array of 3D elements containing Position, a Normal, and a Color
// - ------------------------------------------------------------------------------------------ - //
// GUIDE:
// 1 -- 1D Position (Real)
// 2 -- 2D Position (Vector2D)
// 3 -- 3D Position (Vector3D)
// 4 -- 4D Position (Vector4D)
// N -- Normal (same as Position)
// U -- UV Coordinate (GelUV)
// C -- Color (GelColor)
// R -- Radius (Real)
// D -- Data (int)
// NN UU CC RR -- Include 2 sets of the primary types (Normal and Normal2, etc)
// - ------------------------------------------------------------------------------------------ - //
// TODO: //
// MultiPairs -- Currently only a single NN UU CC RR can be used.
// Finish Data -- Currently only non-multipairs can use Data. Also no DD multipair.
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ARRAY_GELARRAY_H__
#define __GEL_ARRAY_GELARRAY_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Math.h>
#include <Graphics/Graphics.h>
#include <vector>
// - ------------------------------------------------------------------------------------------ - //
// GelVertX    - Array of elements. I.e. GelVert2 (Pos), GelVert3NC (Pos,Normal,Color)
// GelAllocX   - Like GelVertX, but for allocting from a pool of a fixed capacity.
// GelVertexX  - Single element (same naming scheme)
// GelVert     - Base Template of all GelVertX types
// GelAlloc    - Base Template of all GelAllocX types
// GelParticle - Adds 'Life Time' to GelAlloc, making it suiatble for particle simulations. No GelParticleX!
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelArray {
	typedef GelArray thistype;
	std::vector<T> Data;
//	static T Dummy;
public:
	typedef T Type;
	
	inline GelArray( const st _Size = 0 ) :
		Data(_Size)
	{
	}
	
	inline T& operator [] ( const st Index ) {
		return Data[Index];
	}
	inline const T& operator [] ( const st Index ) const {
		return Data[Index];
	}

	inline T* Get() {
		return &(Data[0]);
	}
	inline const T* Get() const {
		return &(Data[0]);
	}

	inline T& Front() {
		return Data.front();
	}	
	inline const T& Front() const {
		return Data.front();
	}	
	inline T& Back() {
		return Data.back();
	}
	inline const T& Back() const {
		return Data.back();
	}

public:
	inline st Size() const {
		return Data.size();
	}
	inline st MaxSize() const {
		return Data.capacity();
	}

public:
	inline void Clear() {
		Data.clear();
	}
	inline void Resize( const st _Size ) {
		Data.resize(_Size);
	}
	// Make sure there's enough room //
	inline void Reserve( const st _Size ) {
		Data.reserve(_Size);
	}
	// Dispose-of and reallocate a new Data structure //
	inline void Realloc( const st _Size = 0 ) {
		std::vector<T>(_Size).swap(Data);
	}
	
	inline T& PushFront( const T& Val = T() ) {
		Data.insert( Data.begin(), Val );
		return Front();
	}
	inline T& PushBack( const T& Val = T() ) {
		Data.push_back( Val );
		return Back();
	}

	inline T PopFront() {
		T Ret = Data.front();
		Data.erase( Data.begin() );
		return Ret;
	}
	inline T PopBack() {
		return Data.pop_back();
	}
	
	inline void Insert( const st Index, const T& Val = T() ) {
		Data.insert( Data.at(Index), Val );
	}
	inline void Delete( const st Index ) {
		Data.erase( Data.at(Index) );
	}
	
	inline void Append( const T* const _Data, const st _Count ) {
		st Pos = Size();
		Resize( Pos + _Count );
		memcpy( &Data[Pos], _Data, _Count * sizeof(T) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
//template <typename T> T GelArray<T>::Dummy;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// GelAlloc is a wrapper that provides different methods of automatically indexing a GelArray //
// - ------------------------------------------------------------------------------------------ - //
template <typename T>
class GelAlloc {
	typedef GelAlloc thistype;
	st Capacity;
	st Used;
	int Index;
	GelArray<T> Data;
public:
	typedef T Type;

	inline GelAlloc( const st _Capacity ) :
		Capacity( _Capacity ),
		Used( 0 ),
		Index( -1 ),
		Data( _Capacity )
	{
	}
	
	inline T* Get() {
		return &(Data[0]);
	}
	inline const T* Get() const {
		return &(Data[0]);
	}

	inline int GetIndex() const {
		return Index;
	}
	inline st GetUsed() const {
		return Used;
	}
	inline st Size() const {
		if ( Used > Capacity )
			return Capacity;
		return Used;
	}
	inline st MaxSize() const {
		return Capacity;
	}
	
	// Use -> operator to set the current element //
	inline T* operator -> () {
		return &(Data[Index]);
	}
	inline const T* operator -> () const {
		return &(Data[Index]);
	}

	// Retrieve individual elements (as if it was a GelArrayX type) //
	inline T& operator [] ( const st _Index ) {
		return Data[_Index];
	}
	inline const T& operator [] ( const st _Index ) const {
		return Data[_Index];
	}

public:
	inline void Clear() {
		Index = -1;
		Used = 0;
	}

	inline void Resize( const st _Size ) {
		Capacity = _Size;
		Data.Resize(_Size);
	}

public:
	// ** USE ONE AND ONLY ONE OF THE FOLLOWING FUNCTIONS ** //
	
	// Normal Add Mode (Increases capacity as needed) //
	inline T* Add() {
		Index++;
		Used++;
		
		// TODO: Assert Index > Capacity
		if ( Capacity == Index ) {
			Capacity++;
			Data.PushBack();
		}

		return operator->();
	}
//	inline T* Add( const int Count ) {
//		Index += Count;
//		Used += Count;
//		
//		// TODO: Assert Index > Capacity
//		if ( Capacity >= Index ) {
//			Capacity += Count;
//			Data.PushBack();
//		}
//
//		return operator->();
//	}

	// Wrapping Add Mode (Allocator) -- For ease of understanding, no optional initializer. //
	inline T* Next() {
		Index++;
		Used++;

		// TODO: Assert Capacity == 0
		// TODO: Assert Index < 0
		while ( Index >= Capacity ) {
			Index -= Capacity;
		}
		
		return operator->();
	}
	inline T* Next( const int Count ) {
		T* Ret = &(Data[Index+1]);
		
		Index += Count;
		Used += Count;
		
		// NOTE: THIS CODE IS WEIRD! //

		// TODO: Assert Capacity == 0
		// TODO: Assert Index < 0
		while ( Index >= Capacity ) {
			Index -= Capacity;
		}
		
		return Ret;//operator->();
	}


};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// GelParticle - Particle System, based on GelAlloc. Particles are allocated things with a lifetime. //
// - ------------------------------------------------------------------------------------------ - //
template <typename T>
class GelParticle {
	typedef GelParticle thistype;

	GelTime Time;
	
	GelAlloc<T> Data;
	std::vector<GelTime> DeathTime;
public:
	typedef T Type;

	inline GelParticle( const st _Capacity ) :
		Time( 0 ),
		Data( _Capacity ),
		DeathTime( _Capacity, 0 )
	{
	}

	// Get the GelArray //
	inline T* Get() {
		return Data.Get();
	}
	inline const T* Get() const {
		return Data.Get();
	}

	// You should iterate over all elements //
	inline st Size() const {
		return Data.MaxSize();
	}
	inline st GetTime() const {
		return Time;
	}

	// Use -> operator to set the current element //
	inline T* operator -> () {
		return Data.operator->();
	}
	inline const T* operator -> () const {
		return Data.operator->();
	}

	// Retrieve individual elements (as if it was a GelArrayX type) //
	inline T& operator [] ( const st Index ) {
		return Data[Index];
	}
	inline const T& operator [] ( const st Index ) const {
		return Data[Index];
	}

public:
	inline void Clear() {
		Time = 0;
		Data.Clear();
		DeathTime.assign(DeathTime.size(),0);
	}

	inline void Resize( const st _Size ) {
		Data.Resize(_Size);
		DeathTime.resize(_Size,0);
	}
		
public:
	// Advance the clock //
	inline void Step() {
		Time++;
	}
	
	// Check if an element is alive //
	inline bool IsAlive( const st _Index ) const {
		return Time < DeathTime[_Index];
	}
	// Check how long the particle has left until it dies //
	inline GelTime Life( const st _Index ) const {
		if ( IsAlive(_Index) )
			return DeathTime[_Index] - Time;
		return 0;
	}
	// Kill a particle //
	inline void Kill( const st _Index ) {
		DeathTime[_Index] = 0;
	}

	// Synonyms //
	inline bool IsAlive() const {
		return IsAlive( Data.GetIndex() );
	}
	inline GelTime Life() const {
		return Life( Data.GetIndex() );
	}
	inline void Kill() {
		Kill( Data.GetIndex() );
	}

	// Return how many objects are alive in the system //
	inline st Living() const {
		st Count = 0;
		for ( st idx = 0; idx < Size(); idx++ ) {
			if ( IsAlive(idx) ) {
				Count++;
			}
		}
		return Count;
	}
	// Return how much life the oldest object has //
	inline st Oldest() const {
		st Age = 0;
		
		for ( st idx = 0; idx < Size(); idx++ ) {
			if ( Life(idx) > Age ) {
				Age = Life(idx);
			}
		}
		return Age;
	}


	// Add! Loops until the free element is found. //
	inline T* Add( const GelTime Age ) {
		st Count = 0;
		// TODO: Assert Capacity == 0 (will cause age setting to fail)
		do {
			Data.Next();
			Count++;
			
			// Bail if we've tried all elements (and failed) //
			if ( Count >= Size() ) {
				// Advance to the next element and overwrite //
				Data.Next();
				#ifndef NDEBUG
				Log("WARNING: GelParticle [%x] of capacity %i has no room left to Add(). Overwriting...", this, Data.MaxSize() );
				#endif // NDEBUG //
				// Bail from loop //
				break;
			}
		} while( IsAlive() );
		
		// Set the Age //
		DeathTime[Data.GetIndex()] = Time + Age;
		
		return Data.operator->();
	}
};
// - ------------------------------------------------------------------------------------------ - //


// - ------------------------------------------------------------------------------------------ - //
#define __CAT(a, ...) __PRIMITIVE_CAT(a, __VA_ARGS__)
#define __PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_START(_num,_sym) \
struct __CAT(GelVertex,__CAT(_num,_sym)) { \
	typedef __GelVertex_TYPE Type;
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_END(_num,_sym) \
}; \
typedef GelArray<__CAT(GelVertex,__CAT(_num,_sym))> __CAT(GelVert,__CAT(_num,_sym)); \
typedef GelAlloc<__CAT(GelVertex,__CAT(_num,_sym))> __CAT(GelAlloc,__CAT(_num,_sym));
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Real
#define __GelVertex_NUMBER 1
#include "GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Vector2D
#define __GelVertex_NUMBER 2
#include "GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Vector3D
#define __GelVertex_NUMBER 3
#include "GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //
#define __GelVertex_TYPE Vector4D
#define __GelVertex_NUMBER 4
#include "GelVertex.def.h"
#undef __GelVertex_NUMBER
#undef __GelVertex_TYPE
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#undef __GelVertex_START
#undef __GelVertex_END
// - ------------------------------------------------------------------------------------------ - //
#undef __CAT
#undef __PRIMITIVE_CAT
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ARRAY_GELARRAY_H__ //
// - ------------------------------------------------------------------------------------------ - //
