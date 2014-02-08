// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEN_FILL_H__
#define __GEN_FILL_H__
// - ------------------------------------------------------------------------------------------ - //
// http://en.wikipedia.org/wiki/Flood_fill
// - ------------------------------------------------------------------------------------------ - //
#include <list>
// - ------------------------------------------------------------------------------------------ - //
template<typename INOUT, typename T1, typename T2>
inline void Flood( INOUT& InOut, int Index, const T1 FillColor, const T2 MatchColor ) {
	if ( InOut[Index] == FillColor )
		return;
	
	std::list<int> Queue; // Index Type //

	Queue.push_back( Index );
	while ( Queue.size() ) {
		Index = Queue.front();
		Queue.pop_front();
		if ( InOut[Index] == MatchColor ) {
			int w = InOut.IndexToX( Index );
			int e = w;
			int y = InOut.IndexToY( Index );

			// Find how far East and West a line extends //
			for (;--w >= 0;) {
				if ( InOut[InOut._Index(w,y)] != MatchColor )
					break;
			}
			for (;++e < InOut.Width();) {
				if ( InOut[InOut._Index(e,y)] != MatchColor )
					break;
			}
						
			for (;++w < e;) {
				InOut[InOut._Index(w,y)] = FillColor;

				if ( y > 0 ) {
					int IndexS = InOut._Index(w,y-1);
					if ( InOut[IndexS] == MatchColor )
						Queue.push_back( IndexS );
				}
				if ( y < InOut.Height()-1 ) {
					int IndexN = InOut._Index(w,y+1);
					if ( InOut[IndexN] == MatchColor )
						Queue.push_back( IndexN );
				}
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<typename INOUT, typename T>
inline void Flood( INOUT& InOut, const int Index, const T FillColor ) {
	Flood( InOut, Index, FillColor, InOut[Index] );
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Wrap around version //
template<typename INOUT, typename T1, typename T2>
inline void FloodWrap( INOUT& InOut, int Index, const T1 FillColor, const T2 MatchColor ) {
	if ( InOut[Index] == FillColor )
		return;
	
	std::list<int> Queue; // Index Type //

	Queue.push_back( Index );
	while ( Queue.size() ) {
		Index = Queue.front();
		Queue.pop_front();
		if ( InOut[Index] == MatchColor ) {
			int w = InOut.IndexToX( Index );
			int e = w;
			int y = InOut.IndexToY( Index );

			// Find how far East and West a line extends //
			for (;--w != e-InOut.Width();) {
//			for (;--w >= 0;) {
				if ( InOut[InOut.Index(w,y)] != MatchColor )
					break;
			}
			for (;e++ != w+InOut.Width();) {
//			for (;++e < InOut.Width();) {
				if ( InOut[InOut.Index(e,y)] != MatchColor )
					break;
			}
						
			for (;++w < e;) {
				InOut[InOut.Index(w,y)] = FillColor;

				int IndexS = InOut.Index(w,y-1);
				if ( InOut[IndexS] == MatchColor )
					Queue.push_back( IndexS );

				int IndexN = InOut.Index(w,y+1);
				if ( InOut[IndexN] == MatchColor )
					Queue.push_back( IndexN );
			}
		}
	}
}
// - ------------------------------------------------------------------------------------------ - //
template<typename INOUT, typename T>
inline void FloodWrap( INOUT& InOut, const int Index, const T FillColor ) {
	FloodWrap( InOut, Index, FillColor, InOut[Index] );
}
// - ------------------------------------------------------------------------------------------ - //
//Flood-fill (node, target-color, replacement-color):
// 1. Set Q to the empty queue.
// 2. If the color of node is not equal to target-color, return.
// 3. Add node to Q.
// 4. For each element N of Q:
// 5.     If the color of N is equal to target-color:
// 6.         Set w and e equal to N.
// 7.         Move w to the west until the color of the node to the west of w no longer matches target-color.
// 8.         Move e to the east until the color of the node to the east of e no longer matches target-color.
// 9.         For each node n between w and e:
//10.             Set the color of n to replacement-color.
//11.             If the color of the node to the north of n is target-color, add that node to Q.
//12.             If the color of the node to the south of n is target-color, add that node to Q.
//13. Continue looping until Q is exhausted.
//14. Return.
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEN_FILL_H__ //
// - ------------------------------------------------------------------------------------------ - //
