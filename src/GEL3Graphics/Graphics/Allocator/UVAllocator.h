// - ------------------------------------------------------------------------------------------ - //
#ifndef __UVAllocator_H__
#define __UVAllocator_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Render/UV.h>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class UVAllocator: public Allocator< UVSet<Gel::UVType> > {
public:
	inline UVAllocator( const int MaxSize, const int Start = 0 ) :
		Allocator< UVSet<Gel::UVType> >( MaxSize, Start )
	{
	}
public:
	inline const int AddMany( const Gel::UVType* Src, const int Count ) {
		int OldSize = Allocator< UVSet<Gel::UVType> >::_Size;
		
		// TODO: Use a better copy function //
		for ( int idx = Count; idx--; ) 
		{
			Allocator< UVSet<Gel::UVType> >::Data->Data[ Allocator< UVSet<Gel::UVType> >::_Size + idx ].u = Src[(idx<<1)+0];
			Allocator< UVSet<Gel::UVType> >::Data->Data[ Allocator< UVSet<Gel::UVType> >::_Size + idx ].v = Src[(idx<<1)+1];
		}

		Allocator< UVSet<Gel::UVType> >::_Size += Count;

		return OldSize;
	}


	inline void AddRect6( Gel::UVType U1, Gel::UVType V1, Gel::UVType U2, Gel::UVType V2 ) {
		UVSet<Gel::UVType>* VP = &Allocator< UVSet<Gel::UVType> >::Data->Data[ Allocator< UVSet<Gel::UVType> >::_Size ];
		
		VP[0] = UVSet<Gel::UVType>( U1, V1 );
		VP[1] = UVSet<Gel::UVType>( U2, V1 );
		VP[2] = UVSet<Gel::UVType>( U1, V2 );
		VP[3] = UVSet<Gel::UVType>( U2, V1 );
		VP[4] = UVSet<Gel::UVType>( U1, V2 );
		VP[5] = UVSet<Gel::UVType>( U2, V2 );		
		
		Allocator< UVSet<Gel::UVType> >::_Size += 6;
	}


	inline void AddQuad6( const Gel::UVType* Src ) {
		AddMany( &Src[0], 3 );
		AddMany( &Src[2], 3 );
	}

	inline void AddQuad6( const UVSet<Gel::UVType>* Src ) {
		AddMany( (Gel::UVType*)&Src[0], 3 );
		AddMany( (Gel::UVType*)&Src[1], 3 );
	}


	inline void AddQuad4( const Gel::UVType* Src ) {
		AddMany( &Src[0], 4 );
	}

	inline void AddQuad4( const UVSet<Gel::UVType>* Src ) {
		AddMany( (Gel::UVType*)&Src[0], 4 );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __UVAllocator_H__ //
// - ------------------------------------------------------------------------------------------ - //
