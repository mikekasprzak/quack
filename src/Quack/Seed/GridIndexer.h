// - ------------------------------------------------------------------------------------------ - //
// Seed Engine specific custom indexing function for the GelGrid family of types //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __SEED_GRIDINDEXER_H__
#define __SEED_GRIDINDEXER_H__
// - ------------------------------------------------------------------------------------------ - //
namespace Seed {
// - ------------------------------------------------------------------------------------------ - //
// Planetary Indexer (functor, otherwise I can't inline in non C++11) //
// - Planets wrap about X axis, Sky is infinite (+Y), World Flips at center of planet 
struct PlanetIndexer {
	template<typename T>
	inline st operator() ( const T& MyGrid, int x, int y ) const {
		
		return MyGrid._Index(x,y);
	}
};
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Seed //
// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_GRIDINDEXER_H__ //
// - ------------------------------------------------------------------------------------------ - //
