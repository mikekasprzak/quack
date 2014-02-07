// - -------------------------------------------------------------------------------------- - //
#include <Node/GelDisjointSet.h>
#include "GelGrid.h"
// - -------------------------------------------------------------------------------------- - //
// http://en.wikipedia.org/wiki/Blob_extraction
// http://robotix.in/tutorials/category/imageprocessing/blob_detection
// ALT: http://junk.mikekasprzak.com/Research/Blob%20Extraction/
// - -------------------------------------------------------------------------------------- - //
template<typename T1, typename T2, typename F1, typename F2>
inline void BlobExtract_from_GelGrid( GelGrid<u16>& Out, const T1& In, const T2& Value, F1 OpFunc, F2 IndexFunc ) {
	const u16 BGVal = 0xFFFF;
	u16 NextLabel = 0;
	GelDisjointSet Linked(0);
	Out.Clear();
	Out.Resize( In.Width(), In.Height(), BGVal );
	
	// First Pass //
	for ( int y = 0; y < (int)In.Height()+1; y++ ) {
		for ( int x = 0; x < (int)In.Width()+1; x++ ) {
			if ( OpFunc( In[IndexFunc(In,x,y)], Value) ) {
				enum { N_Size = 3 };
				u16 N[N_Size];
				for ( st idx = 0; idx < N_Size; idx++ ) {
					N[idx] = BGVal;
				}
				
				if ( x>0 )
					N[0] = Out[IndexFunc(Out,x-1,y)];
				if ( y>0 )
					N[1] = Out[IndexFunc(Out,x,y-1)];
				N[2] = Out[IndexFunc(Out,x,y)];

				// If Neighbours is Empty //
				if ( AllEq( BGVal, N[0], N[1], N[2] ) ) {
					Linked.Add(NextLabel);
					Out[IndexFunc(Out,x,y)] = NextLabel;
					NextLabel++;
				}
				else {
					Out[IndexFunc(Out,x,y)] = ::Min( N[0], N[1], N[2] );	// Ok, because BGVal is big //
					
					// Perform a union on Neighbours //
					for ( st idx = 0; idx < N_Size; idx++ ) {
						if ( N[idx] != BGVal ) {
							for ( st idx2 = idx+1; idx2 < N_Size; idx2++ ) {
								if ( N[idx2] != BGVal ) {
									if ( N[idx] != N[idx2] ) {
										Linked.Union( N[idx], N[idx2] );
									}
								}
							}
						}
					}
				}
			}
		}
	}
	
	// Second Pass //
	for ( st y = 0; y < In.Height(); y++ ) {
		for ( st x = 0; x < In.Width(); x++ ) {
			if ( OpFunc( In[IndexFunc(In,x,y)], Value ) ) {
				Out[IndexFunc(Out,x,y)] = Linked.Find( Out[IndexFunc(Out,x,y)] );
			}
		}
	}
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
#define __DEF_FUNCTOR_SYMBOL( _NAME, _RET, _SYMBOL ) \
struct _NAME { \
	template<typename T1, typename T2> \
	inline _RET operator() ( const T1& a, const T2& b ) const { \
		return a _SYMBOL b; \
	} \
};
// - -------------------------------------------------------------------------------------- - //
#define __DEF_FUNCTOR_FUNC( _NAME, _RET, _FUNC ) \
struct _NAME { \
	template<typename T1, typename T2> \
	inline _RET operator() ( const T1& a, const T2& b ) const { \
		return _FUNC(a,b); \
	} \
};
// - -------------------------------------------------------------------------------------- - //
__DEF_FUNCTOR_SYMBOL( Functor_EQ,  bool, == )
__DEF_FUNCTOR_SYMBOL( Functor_NEQ, bool, != )
__DEF_FUNCTOR_SYMBOL( Functor_GT,  bool, >  )
__DEF_FUNCTOR_SYMBOL( Functor_GTE, bool, >= )
__DEF_FUNCTOR_SYMBOL( Functor_LT,  bool, <  )
__DEF_FUNCTOR_SYMBOL( Functor_LTE, bool, <= )
// - -------------------------------------------------------------------------------------- - //
#undef __DEF_FUNCTOR_FUNC
#undef __DEF_FUNCTOR_SYMBOL
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
// Default Usage is to find all values not equal to zero //
template<typename T1>
inline void BlobExtract_from_GelGrid( GelGrid<u16>& Out, const T1& In ) {
	BlobExtract_from_GelGrid( Out, In, 0, Functor_NEQ(), GelGrid_Index() );
}
// - -------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------- - //
// Alternative Usage is to, given a Value and an Op, find all that match that Op. //
// - -------------------------------------------------------------------------------------- - //
#define __DEF_BLOBEXTRACT_OP( _NAME, _OPFUNC, _INDEXFUNC ) \
template<typename T1, typename T2> \
inline void _NAME( GelGrid<u16>& Out, const T1& In, const T2& Value ) { \
	BlobExtract_from_GelGrid( Out, In, Value, _OPFUNC, _INDEXFUNC ); \
}
// - -------------------------------------------------------------------------------------- - //
__DEF_BLOBEXTRACT_OP( BlobExtract_EQ_from_GelGrid,  Functor_EQ(),  GelGrid_Index() )
__DEF_BLOBEXTRACT_OP( BlobExtract_NEQ_from_GelGrid, Functor_NEQ(), GelGrid_Index() )
__DEF_BLOBEXTRACT_OP( BlobExtract_GT_from_GelGrid,  Functor_GT(),  GelGrid_Index() )
__DEF_BLOBEXTRACT_OP( BlobExtract_GTE_from_GelGrid, Functor_GTE(), GelGrid_Index() )
__DEF_BLOBEXTRACT_OP( BlobExtract_LT_from_GelGrid,  Functor_LT(),  GelGrid_Index() )
__DEF_BLOBEXTRACT_OP( BlobExtract_LTE_from_GelGrid, Functor_LTE(), GelGrid_Index() )
// - -------------------------------------------------------------------------------------- - //
#undef __DEF_BLOBEXTRACT_OP
// - -------------------------------------------------------------------------------------- - //
