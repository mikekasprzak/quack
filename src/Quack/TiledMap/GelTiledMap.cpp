// - ------------------------------------------------------------------------------------------ - //
#include "GelTiledMap.h"
#include <cJSON.h>
// - ------------------------------------------------------------------------------------------ - //
// Some safer shorthands for cJSON_GetObjectItem //
#define cJSON_Get(_NODE,_NAME,_VALUE,_FAIL) ( (Elm = cJSON_GetObjectItem(_NODE,_NAME)) ? Elm->_VALUE : _FAIL)
#define cJSON_GetInt(_NODE,_NAME) ( (Elm = cJSON_GetObjectItem(_NODE,_NAME)) ? Elm->valueint : 0)
#define cJSON_GetDouble(_NODE,_NAME) ( (Elm = cJSON_GetObjectItem(_NODE,_NAME)) ? Elm->valuedouble : 0.0)
#define cJSON_GetString(_NODE,_NAME) ( (Elm = cJSON_GetObjectItem(_NODE,_NAME)) ? Elm->valuestring : "")
// - ------------------------------------------------------------------------------------------ - //
void GelTiledMap::Load( const char* const InFile ) {
	// Use Asset Pool //
	GelAssetPool::UID Id = Gel::AssetPool.Load( Gel::Search( InFile ) );
	
	// Load JSON //
	cJSON* Root = cJSON_Parse( Gel::AssetPool[Id].GetStr() );

	if ( Root ) {
		cJSON* Elm; // Dummy Variable for cJSON_Get //
		
		// Process JSON Data //
		Version = cJSON_GetInt(Root,"version");
	
		Width = cJSON_GetInt(Root,"width");
		Height = cJSON_GetInt(Root,"height");
		TileWidth = cJSON_GetInt(Root,"tilewidth");
		TileHeight = cJSON_GetInt(Root,"tileheight");

		// Check String, store value //
		//Orientation = cJSON_GetObjectItem(Root,"orientation")->valuestring;

		cJSON* Node;

		// Properties (Object) //
		Node = cJSON_GetObjectItem(Root,"properties");
		if ( Node ) {
			if ( Node->type == cJSON_Object ) {
				int Size = cJSON_GetArraySize(Node);
				Log( "Properties: %i (Object)", Size );
				
				// Not an array //
			}
		}

		// TileSets (Array) //
		Node = cJSON_GetObjectItem(Root,"tilesets");
		if ( Node ) {
			if ( Node->type == cJSON_Array ) {
				int Size = cJSON_GetArraySize(Node);
				Log( "TileSets: %i", Size );
				
				for ( int idx = 0; idx < Size; idx++ ) {
					cJSON* Element = cJSON_GetArrayItem(Node,idx);
					if ( Element ) {
						GelTiledTileset& TS = Tileset.PushBack();
						
						TS.Name = cJSON_GetString(Element,"name");
						TS.FirstGID = cJSON_GetInt(Element,"firstgid");

						TS.ImageFile = cJSON_GetString(Element,"image");
						TS.ImageWidth = cJSON_GetInt(Element,"imagewidth");
						TS.ImageHeight = cJSON_GetInt(Element,"imageheight");

						TS.TileWidth = cJSON_GetInt(Element,"tilewidth");
						TS.TileHeight = cJSON_GetInt(Element,"tileheight");

						TS.Margin = cJSON_GetInt(Element,"margin");
						TS.Spacing = cJSON_GetInt(Element,"spacing");
						
						// Properties //
						int PropSize = 0;
						{
							cJSON* Prop = cJSON_GetObjectItem(Element,"properties");
							if ( Prop ) {
								PropSize = cJSON_GetArraySize(Prop);
								
								// TODO: ... //
							}
						}

						Log("* %s [%s %i,%i] -- %i,%i [P: %i]", TS.Name.c_str(), TS.ImageFile.c_str(), TS.ImageWidth,TS.ImageHeight, TS.TileWidth,TS.TileHeight, PropSize );
					}
				}
			}
		}

		// Layers (Array) //
		Node = cJSON_GetObjectItem(Root,"layers");
		if ( Node ) {
			if ( Node->type == cJSON_Array ) {
				int Size = cJSON_GetArraySize(Node);
				Log( "Layers: %i", Size );

				for ( int idx = 0; idx < Size; idx++ ) {
					cJSON* Element = cJSON_GetArrayItem(Node,idx);
					if ( Element ) {
						GelTiledLayer& Lyr = Layer.PushBack();
						
						Lyr.Name = cJSON_GetString(Element,"name");
						
						std::string LayerType = cJSON_GetString(Element,"type");
						if ( LayerType == "tilelayer" ) {
							Lyr.Type = GelTiledLayer::LT_TILELAYER;
						}
						else if ( LayerType == "objectgroup" ) {
							Lyr.Type = GelTiledLayer::LT_OBJECTGROUP;
						}
						else if ( LayerType == "imagelayer" ) {
							Lyr.Type = GelTiledLayer::LT_IMAGELAYER;
						}
						else {
							Lyr.Type = 0;
						}
						
						std::string DrawOrderType = cJSON_GetString(Element,"draworder");
						if ( LayerType == "topdown" ) {
							Lyr.DrawOrder =  GelTiledLayer::DO_TOPDOWN;
						}
						else {
							Lyr.DrawOrder = 0;
						}
						
						Lyr.Width = cJSON_GetInt(Element,"width");
						Lyr.Height = cJSON_GetInt(Element,"height");

						Lyr.Pos.x = Real(cJSON_GetDouble(Element,"x"));
						Lyr.Pos.y = Real(cJSON_GetDouble(Element,"y"));
						
						Lyr.Visible = cJSON_GetInt(Element,"visible");
						Lyr.Opacity = cJSON_GetDouble(Element,"opacity");
						
						// Properties //
						int PropSize = 0;
						{
							cJSON* Prop = cJSON_GetObjectItem(Element,"properties");
							if ( Prop ) {
								PropSize = cJSON_GetArraySize(Prop);
								
								// TODO: ... //
							}
						}
						
						Log("* %s [%i,%i] -- (%f,%f) [P: %i]", Lyr.Name.c_str(), Lyr.Width,Lyr.Height, Lyr.Pos.x.ToFloat(),Lyr.Pos.y.ToFloat(), PropSize );

						// Tile Layer //
						if ( Lyr.Type == GelTiledLayer::LT_TILELAYER ) {							
							cJSON* Data = cJSON_GetObjectItem(Element,"data");

							if ( Data ) {
								if ( Data->type == cJSON_Array ) {
									//int DataSize = cJSON_GetArraySize(Data);
	
									Lyr.Data.Resize( Lyr.Width, Lyr.Height );
	
									//Log("WORM: %i [%i]", DataSize, Lyr.Data.Size());

									// NOTE: For loop is too slow //
									cJSON* Item = cJSON_GetArrayItem(Data,0);
									int idx2 = 0;
									do {
										Lyr.Data[idx2++] = Item->valueint;
										Item = Item->next;
									} while ( Item != 0 ); //idx2 < DataSize );

//									for ( int idx2 = 0; idx2 < DataSize; idx2++ ) {
//										cJSON* Item = cJSON_GetArrayItem(Data,idx2);
//										if ( Item ) {
////											Lyr.Data[idx2] = Item->valueint;
//										}
//									}							
								}
							}
						}

						// Object Group Layer //
						
					}
				}

			}
		}
	
		// Cleanup //
		cJSON_Delete(Root);
	}
}
// - ------------------------------------------------------------------------------------------ - //
