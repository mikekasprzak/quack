// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_ARRAY_GELTREE_H__
#define __GEL_ARRAY_GELTREE_H__
// - ------------------------------------------------------------------------------------------ - //
#include "GelArray.h"
// - ------------------------------------------------------------------------------------------ - //
template<typename T>
class GelTree {
	typedef GelTree thistype;
	GelArray<T> Data;
public:
	typedef T Type;
	
	inline GelTree( const st _Size = 0 ) :
		Data(_Size)
	{
	}
	
	inline T& operator [] ( const st Index ) {
		return Data[Index];
	}
	inline const T& operator [] ( const st Index ) const {
		return Data[Index];
	}
	
	
	inline st32 Size() const {
		return Data.Size();
	}	
	
public:
	inline void Clear() {
		Data.Clear();
	}
	
	inline void Reserve( st32 _Size ) {
		Data.Reserve(_Size);
	}
	inline void Resize( st32 _Size ) {
		Data.Resize(_Size);
	}

public:
	inline T* Add( T* _Parent ) {
		return &(Data.PushBack( T(_Parent) ));
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
template<typename OUT, typename IN>
inline void Gen_GelVert2C_from_GelTree( OUT& Out, IN& In ) { // GelVert2C, GelTree<IN>
	Out.Clear();
	Out.Reserve( (In.Size()-1) * (6+3) );
	
//	Real Radius = 6;
	
//	GelColor Color1;
//	GelColor Color2;
	
	typedef typename IN::Type::Type InVec;
	typedef typename IN::Type InType;

	// Skip element 0, as it will not have a parent. Draw from Parent to me. //
	for ( st idx = 1; idx < In.Size(); idx++ ) {
		const InType& A = *In[idx].Parent;
		const InType& B = In[idx];
		GelColor Color = GEL_RGB_WHITE;// GEL_RGB_MIX(Color1,Color2,Alpha);
/*		
		InVec Ray = B.Pos - A.Pos;
		Ray.Normalize();
		InVec RayTan = Ray.Tangent();
		
		// Lower Triangle //
		Out.PushBack().Pos = A.Pos + (RayTan*Radius);
		Out.Back().Color = Color;
		Out.PushBack().Pos = A.Pos - (RayTan*Radius);
		Out.Back().Color = Color;
		Out.PushBack().Pos = B.Pos - (RayTan*Radius);
		Out.Back().Color = Color;
		// Upper Triangle //
		Out.PushBack().Pos = B.Pos - (RayTan*Radius);
		Out.Back().Color = Color;
		Out.PushBack().Pos = B.Pos + (RayTan*Radius);
		Out.Back().Color = Color;
		Out.PushBack().Pos = A.Pos + (RayTan*Radius);
		Out.Back().Color = Color;
*/

		// Gapless (Using both A and B Tangents) //
		if ( dot( A.Normal, B.Normal ) > Real(0.75) ) {
			// Lower Triangle //
			Out.PushBack().Pos = A.Pos + (A.Normal.Tangent()*A.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = A.Pos - (A.Normal.Tangent()*A.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = B.Pos - (B.Normal.Tangent()*B.Radius);
			Out.Back().Color = Color;
			// Upper Triangle //
			Out.PushBack().Pos = B.Pos - (B.Normal.Tangent()*B.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = B.Pos + (B.Normal.Tangent()*B.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = A.Pos + (A.Normal.Tangent()*A.Radius);
			Out.Back().Color = Color;
		}
		// B Tangent Weighted //
		else {
			// Lower Triangle //
			Out.PushBack().Pos = A.Pos + (B.Normal.Tangent()*A.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = A.Pos - (B.Normal.Tangent()*A.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = B.Pos - (B.Normal.Tangent()*B.Radius);
			Out.Back().Color = Color;
			// Upper Triangle //
			Out.PushBack().Pos = B.Pos - (B.Normal.Tangent()*B.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = B.Pos + (B.Normal.Tangent()*B.Radius);
			Out.Back().Color = Color;
			Out.PushBack().Pos = A.Pos + (B.Normal.Tangent()*A.Radius);
			Out.Back().Color = Color;
		}

/*
		// Fill Gap //
		Real RaySide = dot(RayTan.Tangent(),OldRayTan);
		if ( RaySide < Real::Zero ) {
			Out.PushBack().Pos = In[idx+0].Pos - (RayTan*Radius);
			Out.PushBack().Pos = In[idx+0].Pos;
			Out.PushBack().Pos = In[idx+0].Pos - (OldRayTan*Radius);
		}
		else if ( RaySide > Real::Zero ) {
			Out.PushBack().Pos = In[idx+0].Pos;
			Out.PushBack().Pos = In[idx+0].Pos + (RayTan*Radius);
			Out.PushBack().Pos = In[idx+0].Pos + (OldRayTan*Radius);
		}
		else {
			// Do nothing in Zero case (i.e. First time, axis aligned) //
		}
*/

//		Radius -= Real::Half;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_ARRAY_GELTREE_H__ //
// - ------------------------------------------------------------------------------------------ - //
