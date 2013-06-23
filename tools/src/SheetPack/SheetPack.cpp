// - ---------------------------------------------------------------------- - //
#include <stdio.h>
#include <stdlib.h>
// - ---------------------------------------------------------------------- - //
#include <string.h> // for size_t //
#include <External/RectangleBinPack/MaxRectsBinPack.h>
#include <External/STB/stb_image.h>

#include <Lib/Lib.h>
// - ---------------------------------------------------------------------- - //
#include <vector>
using namespace std;
// - ---------------------------------------------------------------------- - //
#define _Log(...) {printf(__VA_ARGS__);}
#define Log(...) {printf(__VA_ARGS__);printf("\n");}
// - ---------------------------------------------------------------------- - //
struct Vec2 {
	int x, y;
};
// - ---------------------------------------------------------------------- - //
struct Rect2 {
	int x, y;
	int w, h;
};
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
int main(int argc, char* argv[]) {
	if ( argc <= 2 ) {
		Log("Usage: Blah");
		exit(-1);	
	}
	
	int CellW = 16;
	int CellH = 16;
	
	int x, y, n;
	u8* Data = stbi_load(argv[1],&x,&y,&n,0); 	// FileName, x*, y*, NumComponents*, RequiredNumComponents //
	
	Log("%s: %i,%i -- %i", argv[1],x,y,n);
	
	// Step 1 - Slice the image (i.e. make Rectangles) //
	
	stbi_image_free( Data );
	
	return 0;
}
// - ---------------------------------------------------------------------- - //
