// - ---------------------------------------------------------------------- - //
#include <stdio.h>
#include <stdlib.h>
// - ---------------------------------------------------------------------- - //
#include <string.h> // for size_t //
#include <External/STB/stb_image.h>
// - ---------------------------------------------------------------------- - //
#include <External/RectangleBinPack/MaxRectsBinPack.h>
using namespace rbp;
// - ---------------------------------------------------------------------- - //
#include <vector>
using namespace std;
// - ---------------------------------------------------------------------- - //
#include <Lib/Lib.h>
// - ---------------------------------------------------------------------- - //
#define _Log(...) {printf(__VA_ARGS__);}
#define Log(...) {printf(__VA_ARGS__);printf("\n");}
// - ---------------------------------------------------------------------- - //
struct Vec2 {
	int x, y;
};
// - ---------------------------------------------------------------------- - //
struct Image {
	u32* Data;
	int BPP;
	int width, height;
};
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
// Globals //
int CellW, CellH;
int PadX, PadY;
int TargetW, TargetH;
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
inline u32 Alpha( const u32 Val ) {
	return Val & 0xFF000000;
}
// - ---------------------------------------------------------------------- - //
void ReduceRect( const Image& Img, Rect& r ) {
	// Top Row //
	for ( size_t y = 0; y < r.height; y++ ) {
		for ( size_t x = 0; x < r.width; x++ ) {
		}
	}
}
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
int main(int argc, char* argv[]) {
	if ( argc <= 2 ) {
		Log("Usage: %s InFile OutFile", argv[0]);
		exit(-1);	
	}
	
	// Set Defalts // 
	CellW = 16;
	CellH = 16;
	
	// You should always use the same padding about both axis, but internally I should support seperate //
	PadX = 2;
	PadY = 2;

	// Target Output //
	TargetW = 64;
	TargetH = 64;
	
	
	// PreStep 1 - Parse Info-File for Instructions //
	
	// PreStep 2 - Parse Filename for Instructions (i.e. Blah.16x16.png) //
	
	// PreStep 3 - Parse Command Line arguments for Instructions //
	
	// Load Image //
	Image Img;
	Img.Data = (u32*)stbi_load(argv[1],&Img.width,&Img.height,&Img.BPP,4); 	// FileName, w*, h*, NumComponents*, RequiredNumComponents //
	// For now, we're forcing the number of components to 4, so I don't have to write more code //

	Log("%s loaded.",argv[1]);
	Log("Size: %i,%i -- %i bytes per pixel",Img.width,Img.height,Img.BPP);

	if ( Img.width % CellW ) {
		Log("** WARNING: Cell Width does not divide evenly in to Image! (%i in to %i)", CellW, Img.width );
	}
	if ( Img.height % CellH ) {
		Log("** WARNING: Cell Height does not divide evenly in to Image! (%i in to %i)", CellH, Img.height );
	}
	
	int CellsX = Img.width / CellW;
	int CellsY = Img.height / CellH;
	
	Log( "Image contains %i (%i*%i) Cells of size %i,%i", CellsX*CellsY, CellsX, CellsY, CellW, CellH );
		
	// Step 1 - Slice the image (i.e. make Rectangles) //
	vector<Vec2> SpriteBase;
	vector<Rect> SpriteRect;
	for ( size_t y = 0; y < CellsY; y++ ) {
		for ( size_t x = 0; x < CellsX; x++ ) {
			// The Full Rectangle (to be modified) //
			SpriteRect.push_back(Rect());
			SpriteRect.back().x = x*CellW;
			SpriteRect.back().y = y*CellH;
			SpriteRect.back().width = CellW;
			SpriteRect.back().height = CellH;
			//Log("%i %i %i %i",SpriteRect.back().x,SpriteRect.back().y,SpriteRect.back().width,SpriteRect.back().height );
			
			// The Base Position (used to determine later how much the rectangle is offset) //
			SpriteBase.push_back(Vec2());
			SpriteBase.back().x = x*CellW;
			SpriteBase.back().y = y*CellH;
		}
	}	

	// Step 2 - For every Rectangle, attempt to reduce it's size //
	for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
		ReduceRect( Img, SpriteRect[idx] );
	}
	

	// Step 3 - Apply Padding to Rectangles //
	for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
		SpriteRect[idx].x -= PadX;
		SpriteRect[idx].y -= PadY;
		SpriteRect[idx].width  += PadX+PadX;
		SpriteRect[idx].height += PadY+PadY;
		// TODO: Add code elsewhere that erases the pixels in the padding region //
	}
	
	// Step 4 - Sort Rectangles //
	
	

	// Free Data //
	stbi_image_free( Img.Data );
	
	return 0;
}
// - ---------------------------------------------------------------------- - //
