// - ---------------------------------------------------------------------- - //
// TODO: Add a way given an input, output the same image, but with trimmed regions //
// TODO: Add a way to process any image file, generate a draw list that omits completely empty parts //
// TODO: If implementing edge algorithms, pad each side as you normally would (x+=Pad;w+=Pad+Pad).
//       Then as a post-process, shift the image back Pad units left and upward, while making the now
//       off screen parts of the data loop through the other side. This will correctly allow you to 
//       wrap images and align them correctly.
//       Algorithms: Cell Tiled (same one again+again), replicate edges, blank (what we have now),
//                   Continue (use information from neighbouring cells)
// - ---------------------------------------------------------------------- - //
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// - ---------------------------------------------------------------------- - //
#include <External/STB/stb_image_write.h>
#define STBI_NO_WRITE		// To stop stb_image from generating write functions //
#include <External/STB/stb_image.h>
// - ---------------------------------------------------------------------- - //
#include <External/RectangleBinPack/ShelfBinPack.h>
#include <External/RectangleBinPack/GuillotineBinPack.h>
#include <External/RectangleBinPack/MaxRectsBinPack.h>
#include <External/RectangleBinPack/SkylineBinPack.h>
using namespace rbp;
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
#include <vector>
#include <algorithm>
using namespace std;
// - ---------------------------------------------------------------------- - //
#include <Lib/Lib.h>
// - ---------------------------------------------------------------------- - //
#define _Log(...) {printf(__VA_ARGS__);}
#define Log(...) {printf(__VA_ARGS__);printf("\n");fflush(0);}
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
int CellW, CellH;	// Size of Cells //
int Pad;			// How Many Pixel to Pad //
int Align;			// What Pixel Boundary to Align to (like padding for POT scaling) //
int TargetW, TargetH; // Desired dimensions of the output file (if Packing) //
bool Flip;			// Optimize space by flipping (rotating) rectangles //
bool Packing;		// Packing Enabled (may only be doing Cell optimizations) //
bool CellOptimize;	// Optimize space by reducing cell sizes //
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
inline u32 Alpha( const u32 Val ) {
	return Val & 0xFF000000;
}
// - ---------------------------------------------------------------------- - //
void ReduceRect( const Image& Img, Rect& r ) {
	Rect NewRect = r;
	bool Found = false;

	// Bottom Row //
	Found = false;
	for ( size_t y = r.height; y--; ) {
		for ( size_t x = 0; x < r.width; x++ ) {
			size_t Index = (r.x+x)+((r.y+y)*Img.width);
			if ( Alpha(Img.Data[Index]) > 0 ) {
				Found = true;
			}
		}
		if ( Found ) {
			break;
		}
		else {
			NewRect.height -= 1;
		}
	}
	r = NewRect;	// Overwrite original //
	
	// Top Row //
	Found = false;
	for ( size_t y = 0; y < r.height; y++ ) {
		for ( size_t x = 0; x < r.width; x++ ) {
			size_t Index = (r.x+x)+((r.y+y)*Img.width);
			if ( Alpha(Img.Data[Index]) > 0 ) {
				Found = true;
			}
		}
		if ( Found ) {
			break;
		}
		else {
			NewRect.y += 1;
			NewRect.height -= 1;
		}
	}
	r = NewRect;	// Overwrite original //
	
	// Right Row //
	Found = false;
	for ( size_t x = r.width; x--; ) {
		for ( size_t y = 0; y < r.height; y++ ) {
			size_t Index = (r.x+x)+((r.y+y)*Img.width);
			if ( Alpha(Img.Data[Index]) > 0 ) {
				Found = true;
			}
		}
		if ( Found ) {
			break;
		}
		else {
			NewRect.width -= 1;
		}
	}
	r = NewRect;	// Overwrite original //
	
	// Left Row //
	Found = false;
	for ( size_t x = 0; x < r.width; x++ ) {
		for ( size_t y = 0; y < r.height; y++ ) {
			size_t Index = (r.x+x)+((r.y+y)*Img.width);
			if ( Alpha(Img.Data[Index]) > 0 ) {
				Found = true;
			}
		}
		if ( Found ) {
			break;
		}
		else {
			NewRect.x += 1;
			NewRect.width -= 1;
		}
	}
	r = NewRect;	// Overwrite original //
}
// - ---------------------------------------------------------------------- - //
void ReduceEmptyRect( const Image& Img, Rect& r ) {
	Rect NewRect = r;
	bool Found = false;

	// Bottom Row //
	Found = false;
	for ( size_t y = r.height; y--; ) {
		for ( size_t x = 0; x < r.width; x++ ) {
			size_t Index = (r.x+x)+((r.y+y)*Img.width);
			if ( Alpha(Img.Data[Index]) > 0 ) {
				Found = true;
			}
		}
		if ( Found ) {
			break;
		}
		else {
			NewRect.height -= 1;
		}
	}
	if ( NewRect.height == 0 ) {
		r = NewRect;	// Overwrite original //
	}
}
// - ---------------------------------------------------------------------- - //
void Blit( Image& Src, Image& Dest, const Rect& SrcRect, const Rect& DestRect ) {
	// TODO: Clip coordinates //
	
	int WidthPadded = SrcRect.width + Pad;
	WidthPadded += (Align - (WidthPadded % Align)) % Align;
	
	// Regular Mode //
	if ( WidthPadded == DestRect.width ) {
		for ( size_t y = 0; y < SrcRect.height; y++ ) {
			for ( size_t x = 0; x < SrcRect.width; x++ ) {
				size_t SX = (SrcRect.x+x);
				size_t SY = (SrcRect.y+y);
				size_t SrcIndex = SX + (SY*Src.width);
	
				if ( SX >= Src.width ) Log( "Invalid Src x: %i", SX );
				if ( SY >= Src.height ) Log( "Invalid Src y: %i", SY );
	
				size_t DX = (DestRect.x+x);
				size_t DY = (DestRect.y+y);
				size_t DestIndex = DX + (DY*Dest.width);
	
				if ( DX >= Dest.width ) Log( "Invalid Dest x: %i", DX );
				if ( DY >= Dest.height ) Log( "Invalid Dest y: %i", DY );
				
				Dest.Data[DestIndex] = Src.Data[SrcIndex];
			}
		}
	}
	// Flipped Mode //
	else {
		for ( size_t y = 0; y < SrcRect.height; y++ ) {
			for ( size_t x = 0; x < SrcRect.width; x++ ) {
				size_t SX = (SrcRect.x+x);
				size_t SY = (SrcRect.y+y);
				size_t SrcIndex = SX + (SY*Src.width);
	
				if ( SX >= Src.width ) Log( "Invalid Src x: %i", SX );
				if ( SY >= Src.height ) Log( "Invalid Src y: %i", SY );
	
				// The only differences are here. x+y, y+x //
				size_t DX = (DestRect.x+y);
				size_t DY = (DestRect.y+x);
				size_t DestIndex = DX + (DY*Dest.width);
	
				if ( DX >= Dest.width ) Log( "Invalid Dest x: %i", DX );
				if ( DY >= Dest.height ) Log( "Invalid Dest y: %i", DY );
				
				Dest.Data[DestIndex] = Src.Data[SrcIndex];
			}
		}		
	}
}
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
struct RectInfo {
	int Index;
	int Area;
	int LongestAxis;
	int Manhattan;	
	float Magnitude;
};
// - ---------------------------------------------------------------------- - //
bool Compare( const RectInfo& a, const RectInfo& b ) {
//	return (a.Area < b.Area);
	return (a.LongestAxis < b.LongestAxis);
}
// - ---------------------------------------------------------------------- - //

// - ---------------------------------------------------------------------- - //
int main(int argc, char* argv[]) {
	if ( argc <= 2 ) {
		Log("Usage: %s InFile OutFile", argv[0]);
		exit(-1);	
	}
	
	// Set Defalts // 
	CellW = 40;//64;
	CellH = 40;//64;
	
	Pad = 1;//1;
	Align = 1;//8;
	Flip = false;//true;
	Packing = true;
	CellOptimize = false;//true;

	// Target Output //
	TargetW = 480;//256;
	TargetH = 480;//256;
	
	
	// PreStep 1 - Parse Info-File for Instructions //
	
	// PreStep 2 - Parse Filename for Instructions (i.e. Blah.16x16.png) //
	
	// PreStep 3 - Parse Command Line arguments for Instructions //
	
	// Load Image //
	Image Img;
	Img.Data = (u32*)stbi_load(argv[1],&Img.width,&Img.height,&Img.BPP,4); 	// FileName, w*, h*, NumComponents*, RequiredNumComponents //
	// For now, we're forcing the number of components to 4, so I don't have to write more code //

	if ( Img.Data == 0 ) {
		Log("File \"%s\" not found!",argv[1]);
		exit(-1);
	}

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
	
	Log( "Image contains %i (%ix%i) Cells of size %ix%i", CellsX*CellsY, CellsX, CellsY, CellW, CellH );
		
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

	// Step 1B - Remove Empty Rects //
	if ( true ) {
		for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
			ReduceEmptyRect( Img, SpriteRect[idx] );
		}		
	}

	// Step 1C - Combine Cells //
	if ( true ) {
		// X Axis //
		for ( size_t idx = SpriteRect.size()-1; idx--; ) {
			Rect& S1 = SpriteRect[idx];
			Rect& S2 = SpriteRect[idx+1];
			if ( S1.y == S2.y ) {
				if ( (S1.height != 0) && (S2.height != 0) ) {
					S1.width += S2.width;
					S2.width = 0;
					S2.height = 0;
				}
			}
		}
		
		int CombineError = 4*CellW;
		// NOTE: THIS ISN'T WORKING BECAUSE THE ONLY LEGAL TEST IS VS THE TILE BELOW YOU! //
		
		// Y Axis (Bottom to top) //
		for ( size_t idx = SpriteRect.size()-CellsX; idx--; ) {
			Rect& S1 = SpriteRect[idx];
			Rect& S2 = SpriteRect[idx+CellsX];
			if ( abs(S1.x - S2.x) == 0 )//<= CombineError ) 
			{
				if ( abs(S1.width - S2.width) == 0 )//<= CombineError )
				{
					if ( (S1.height != 0) && (S2.height != 0) ) {
						S1.height += S2.height;
						
						//int XDiff = abs(S1.x-S2.x);
						S1.width = S1.width > S2.width ? S1.width : S2.width;
						//S1.width += XDiff;
						//S1.x = S1.x < S2.x ? S1.x : S2.x;;

						S2.width = 0;
						S2.height = 0;
					}
				}
			}
		}

		// Y Axis (Top to bottom) //
		for ( size_t idx = 0; idx < SpriteRect.size()-CellsX-1; idx++ ) {
			Rect& S1 = SpriteRect[idx];
			Rect& S2 = SpriteRect[idx+CellsX];
			if ( abs(S1.x - S2.x) == 0 )//<= CombineError ) 
			{
				if ( abs(S1.width - S2.width) <= CombineError )
				{
					if ( (S1.height != 0) && (S2.height != 0) ) {
						S1.height += S2.height;
						
						//int XDiff = abs(S1.x-S2.x);
						S1.width = S1.width > S2.width ? S1.width : S2.width;
						//S1.width += XDiff;
						//S1.x = S1.x < S2.x ? S1.x : S2.x;;

						S2.width = 0;
						S2.height = 0;
					}
				}
			}
		}
	}

	// Step 2 - For every Rectangle, attempt to reduce it's size //
	if ( CellOptimize ) {
		for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
			ReduceRect( Img, SpriteRect[idx] );
			//Log("%i: %i,%i %i,%i", idx, SpriteRect[idx].x,SpriteRect[idx].y,SpriteRect[idx].width,SpriteRect[idx].height );
		}
	}
		
	// Step 3 -- Have an Image *shrug* //
	Image Out;
	
	if ( Packing ) {
		
		// Step 4 - Sort Rectangles //
		vector<RectInfo> Info;
		// Populate Info Structure //
		for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
			Rect& r = SpriteRect[idx];
			
			Info.push_back( RectInfo() );
			Info.back().Index = idx;
			Info.back().Area = r.width * r.height;
			Info.back().LongestAxis = r.width > r.height ? r.width : r.height;		
			Info.back().Manhattan = abs(r.width) + abs(r.height); // NOTE: Will always be positive //
			Info.back().Magnitude = sqrt(r.width*r.width+r.height*r.height);
		}
		
		sort(Info.begin(),Info.end(),Compare);	// Ascending Order -- Lowest to Highest //
		reverse(Info.begin(),Info.end());		// Swap that around (Highest to Lowest) //
		
//		for ( size_t idx = 0; idx < Info.size(); idx++ ) {
//			Log("%i: %i (%i)",idx,Info[idx].Index,Info[idx].Area);
//		}
		
		// Step 5 - Add Rectangles to BinPack Structure, Recording New Positions //	
		typedef MaxRectsBinPack BinPack;
		BinPack::FreeRectChoiceHeuristic Heuristic = BinPack::RectBestShortSideFit;
		BinPack Pack( TargetW, TargetH );
		if ( !Flip )
			Pack.DisableFlip();
	
		vector<Rect> NewSpriteRect;
		for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
			int Index = Info[idx].Index;
			
			int PW = SpriteRect[Index].width + Pad;
			PW += (Align - (PW % Align)) % Align;
			int PH = SpriteRect[Index].height + Pad;
			PH += (Align - (PH % Align)) % Align;
			
			NewSpriteRect.push_back( Pack.Insert( PW, PH, Heuristic	) );
			
			if ( (SpriteRect[Index].width != 0) && (SpriteRect[Index].height != 0) ) {
				if ( (NewSpriteRect.back().width == 0) || (NewSpriteRect.back().height == 0) ) {
					Log("Error! Unable to fit sprite on sheet!");
				}
			}
			//Log("%i: (%i,%i)-(%i,%i)", Index, NewSpriteRect[Index].x,NewSpriteRect[Index].y,NewSpriteRect[Index].width,NewSpriteRect[Index].height );
		}
		
		// Step 6 - Populate an image to blit our new rectangles of data to //
		Out.width = TargetW;
		Out.height = TargetH;
		Out.BPP = Img.BPP;
		Out.Data = (u32*)new u8[Out.width*Out.height*Out.BPP];
		memset( Out.Data, 255, Out.width*Out.height*Out.BPP );
	
		// Step 7 - Blit data from old image to new image, at positions specified //
		for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
			int Index = Info[idx].Index;
			
			Blit( Img, Out, SpriteRect[Index], NewSpriteRect[idx] );
		}
	} // Packing //
	else {
		// Hack: Output the exact same image to check clip borders//
		Out.width = Img.width;
		Out.height = Img.height;
		Out.BPP = Img.BPP;
		Out.Data = (u32*)new u8[Out.width*Out.height*Out.BPP];
		memset( Out.Data, 255, Out.width*Out.height*Out.BPP );
	
		// Step 7 - Blit data from old image to new image, at positions specified //
		for ( size_t idx = 0; idx < SpriteRect.size(); idx++ ) {
			Blit( Img, Out, SpriteRect[idx], SpriteRect[idx] );
		}
	}
		
	// Step 8 - Save Image File //
	stbi_write_png( argv[2], Out.width, Out.height, Out.BPP, (u8*)Out.Data, 0 );
	
	// Step 9 - Save Offsets File //

	// Free Data //
	delete [] Out.Data;
	stbi_image_free( Img.Data );
	
	return 0;
}
// - ---------------------------------------------------------------------- - //
