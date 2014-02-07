// - -------------------------------------------------------------------------------------- - //
#include <Node/GelDisjointSet.h>
#include "GelGrid.h"
// - -------------------------------------------------------------------------------------- - //
// http://en.wikipedia.org/wiki/Blob_extraction
// http://robotix.in/tutorials/category/imageprocessing/blob_detection
// - -------------------------------------------------------------------------------------- - //
template<typename T, typename T2, typename F>
inline void BlobExtract_from_GelGrid( GelGrid<u16>& Out, const T& In, const T2 Middle, F IndexFunc ) {
	const u16 BGVal = 0xFFFF;
	u16 NextLabel = 0;
	GelDisjointSet Linked(0);
	Out.Clear();
	Out.Resize( In.Width(), In.Height(), BGVal );
	
	// First Pass //
	for ( st y = 0; y < In.Height(); y++ ) {
		for ( st x = 0; x < In.Width(); x++ ) {
			if ( IndexFunc(In,x,y) >= Middle ) {
				enum { N_Size = 2 };
				u16 N[N_Size];
				for ( st idx = 0; idx < N_Size; idx++ ) {
					N[idx] = BGVal;
				}
				
				if ( (x>0) && (IndexFunc(In,x-1,y) >= Middle) ) {
					N[0] = Out(x-1,y);
				}
				if ( (y>0) && (IndexFunc(In,x,y-1) >= Middle) ) {
					N[1] = Out(x,y-1);
				}
				
				// If Neighbours is Empty //
				if ( AllEq( BGVal, N[0], N[1] ) ) {
					Linked.Add(NextLabel);
					Out(x,y) = NextLabel;
					NextLabel++;
				}
				else {
					Out(x,y) = ::Min( N[0], N[1] );	// Ok, because BGVal is big //
					
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
			if ( IndexFunc(In,x,y) >= Middle ) {
				Out(x,y) = Linked.Find( Out(x,y) );
			}
		}
	}
}
// - -------------------------------------------------------------------------------------- - //
template<typename T, typename T2>
inline void BlobExtract_from_GelGrid( GelGrid<u16>& Out, const T& In, const T2 Middle ) {
	BlobExtract_from_GelGrid( Out, In, Middle, GelGrid_Index() );
}
// - -------------------------------------------------------------------------------------- - //
