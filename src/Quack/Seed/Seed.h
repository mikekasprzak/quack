// - ------------------------------------------------------------------------------------------ - //
// Seed Engine -- Physics, Dynamics, and Rendering //
// NOTE: Try to avoid making calls to scripting inside the engine. Instead, use a general data //
//       type to store function names, or function pointers (if native). //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __SEED_SEED_H__
#define __SEED_SEED_H__
// - ------------------------------------------------------------------------------------------ - //
// In the Seed Engine, a World contains Cells, and Cells contain Things. //
#include "Thing.h"
#include "Cell.h"
//#include "World.h"
// - ------------------------------------------------------------------------------------------ - //
// Objects are the Active Things in the game world. 
//#include "Object.h"
//#include "Prefab.h" // ?
// - ------------------------------------------------------------------------------------------ - //
// TileMap's are a type of thing. Often useful for collision and artwork placement. //
#include "Tile.h"
#include "TileMap.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_SEED_H__ //
// - ------------------------------------------------------------------------------------------ - //
