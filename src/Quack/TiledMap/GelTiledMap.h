// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_TILEDMAP_GELTILEDMAP_H__
#define __GEL_TILEDMAP_GELTILEDMAP_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Math/Vector.h>
#include <Array/Array.h>
#include <NewGrid/NewGrid.h>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
class GelTiledProperty {
	typedef GelTiledProperty thistype;
public:
	std::string Name;
	int Type; // Which Type //
	
	// To be helpful, a place to store all of the data posibilities. //
	std::string String;
	union {
		int Integer;
		float Float;
		bool Boolean;
	};
};
// - ------------------------------------------------------------------------------------------ - //
class GelTiledTileset {
	typedef GelTiledTileset thistype;
public:
	// NOTE: Texture Paging is handled by ID's used. So texture 1 may use tiles 1-1025, and //
	//       texture 2 may use tiles 1026-2050. And so on. Remember this! Rendere will need //
	//       multiple passes to render correctly! //
	st32 FirstGID; // 1 - First set. Higher number on later sets. //
	std::string Name;
	
	std::string ImageFile;
	st32 ImageWidth;
	st32 ImageHeight;
		
	st32 TileHeight;
	st32 TileWidth;

	st32 Margin;
	st32 Spacing;
	
	GelArray<GelTiledProperty> Property;	// Can be empty //
};
// - ------------------------------------------------------------------------------------------ - //
class GelTiledObject {
	typedef GelTiledObject thistype;
public:
	std::string Name;
	std::string TypeName; // "type" in JSON //
	int Type;
	enum {
		OT_RECTANGLE = 1,
		OT_ELLIPSE,
		OT_POLYLINE,
		OT_POLYGON,
	};

	Vector2D Pos;
	st32 Width;
	st32 Height;
	
	float Rotation;

	bool Visible;	// TODO: Flags.
	st32 GID;		// Only need 16 bits //
	
	GelArray<Vector2D> Point;			// Can be empty. "polyline" and "polygon" //
	GelArray<GelTiledProperty> Property;	// Can be empty //
};
// - ------------------------------------------------------------------------------------------ - //
class GelTiledLayer {
	typedef GelTiledLayer thistype;
public:
	std::string Name;
	int Type;
	enum {
		LT_TILELAYER = 1,	// "tilelayer"
		LT_OBJECTGROUP,		// "objectgroup"
		LT_IMAGELAYER,		// "imagelayer" (may not use)
		
		DO_TOPDOWN = 1,		// "topdown"
	};
	
	Vector2D Pos;
	st32 Width;
	st32 Height;
	
	float Opacity;	// 0->1 //

	bool Visible;	// TODO: Flags.
	int DrawOrder;	// TODO: Flags. "topdown" (objectgroup only) 

	GelArray<GelTiledObject> Object;	 	// Can be empty //
	GelGrid<st16> Data;						// Can be empty //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GelTiledMap {
	typedef GelTiledMap thistype;
public:
	st32 Width;
	st32 Height;
	st32 TileWidth;
	st32 TileHeight;

	int Version; 		// 1 //
	int Orientation;	// orthogonal // TODO: Flags

	GelArray<GelTiledLayer> Layer;
	GelArray<GelTiledTileset> Tileset;	
	GelArray<GelTiledProperty> Property; // Can be empty //

public:
	inline GelTiledMap() :
		Width(0),
		Height(0),
		TileHeight(0),
		TileWidth(0),
		Version(0),
		Orientation(0)
	{
	}
	
	inline GelTiledMap( const char* const InFile ) {
		Load( InFile );
	}
	
	void Load( const char* const InFile );
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_TILEDMAP_GELTILEDMAP_H__ //
// - ------------------------------------------------------------------------------------------ - //
