// - ------------------------------------------------------------------------------------------ - //
// Glayout - General Purpose Layout Engine for simple UIs //
// - ------------------------------------------------------------------------------------------ - //
// NOTES: By default a node is at (0,0) and is of size 1x1. Nodes can be size 0x0, meaning they're
//   both unaffected and don't affect Fitting operations. Say, if you needed to chain some data.
// - ------------------------------------------------------------------------------------------ - //
// TODO: Add a way that sizes cascade to children.
// TODO: Make inner filling work (which means deciding what width/height mean to them).
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GLAYOUT_H__
#define __GEL_GLAYOUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <list>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Floating Point Layout //
typedef float GlayNum;			// Number //
#define GLAY_0			0.0f
#define GLAY_1			1.0f
inline GlayNum GlayNumHalf( const GlayNum In ) { return In * 0.5f; }
// - ------------------------------------------------------------------------------------------ - //
// Fixed Point Layout //
//typedef int GlayNum;			// Number //
//#define GLAY_0		0
//#define GLAY_1		1		// Should be bigger than 1 //
//inline GlayNum GlayNumHalf( const GlayNum In ) { return In >> 1; }
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// GlayPoint - Positions in the Layout //
struct GlayPoint {
	GlayNum x,y;
	
	inline GlayPoint( const GlayNum _x = GLAY_0, const GlayNum _y = GLAY_0 ) :
		x(_x),
		y(_y)
	{
	}
	
public:
	inline GlayPoint GetHalf() const {
		return GlayPoint( GlayNumHalf(x), GlayNumHalf(y) );
	}
};
// - ------------------------------------------------------------------------------------------ - //
#define __GLAY_OPERATOR_AB( _SYM ) \
inline GlayPoint operator _SYM ( const GlayPoint& a, const GlayPoint& b ) { \
	return GlayPoint( a.x _SYM b.x, a.y _SYM b.y ); \
}
// - ------------------------------------------------------------------------------------------ - //
__GLAY_OPERATOR_AB(+)
__GLAY_OPERATOR_AB(-)
__GLAY_OPERATOR_AB(*)
__GLAY_OPERATOR_AB(/)
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// GlayRegion - Rectangles //
struct GlayRegion {
	GlayPoint Pos, Shape;
	
	inline GlayRegion( const GlayNum _x = GLAY_0, const GlayNum _y = GLAY_0, const GlayNum _w = GLAY_1, const GlayNum _h = GLAY_1 ) :
		Pos(_x,_y),
		Shape(_w,_h)
	{
	}

public:
	inline GlayPoint GetCenter() const {
		return Pos + Shape.GetHalf();
	}
	
	inline GlayPoint GetHalfShape() const {
		return Shape.GetHalf();
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
enum GlayNodeAlign {
	GALIGN_LEFT =						0x1,
	GALIGN_RIGHT = 						0x2,
	GALIGN_CENTER =						GALIGN_LEFT | GALIGN_RIGHT,
			
	GALIGN_TOP =						0x1<<4,
	GALIGN_BOTTOM =						0x2<<4,
	GALIGN_MIDDLE =						GALIGN_TOP | GALIGN_BOTTOM,
	GALIGN_BASELINE =					0x4<<4 | GALIGN_MIDDLE,		// Include Middle as a fallback (non fonts) //
	
	GALIGN_HALIGN =						GALIGN_CENTER,
	GALIGN_VALIGN =						GALIGN_MIDDLE,
	GALIGN_ALIGN =						0xFF,

	GALIGN_HBITS =						0xF,
	GALIGN_VBITS =						0xF<<4,
	
	// Properties of Self //
	//GALIGN_FREE =						0x000,	// Free Positioning. Relative the Origin (0,0). //
	GALIGN_SUM = 						0x100,	// Positions are relative the parents. Default. //
	GALIGN_FIT =						0x200,	// Fit myself to my parent (100%). //
	GALIGN_EMPTY = 						0x800,	// Special kind of node (an empty) that disregards position. //

	GALIGN_SELF = 						0xF00,
	
	// Properties of Children (ONLY ONE!) //
	GALIGN_FIT_CHILDREN_TO_ME =			0x1000,	// Nodes are placed inside eachother. For borders, outlines, margins and padding. //
	GALIGN_FIT_CHILDREN_TO_WIDTH = 		0x2000,	// Fit my children inside me, arranging them wide, filling all space //
	GALIGN_FIT_CHILDREN_TO_HEIGHT = 	0x3000,	// Fit my children inside me, arranging them tall, filling all space //

	GALIGN_PACK_CHILDREN_FROM_LEFT =	0x4000, // Pack children! In a box! //
	GALIGN_PACK_CHILDREN_FROM_RIGHT =	0x5000,
	GALIGN_PACK_CHILDREN_FROM_TOP =		0x6000,
	GALIGN_PACK_CHILDREN_FROM_BOTTOM =	0x7000,

	GALIGN_CHILDREN =					0xF000,

	// *** //
	
	GALIGN_DEFAULT =					GALIGN_TOP | GALIGN_LEFT,
//	GALIGN_DEFAULT =					GALIGN_CENTER | GALIGN_MIDDLE,
};
// - ------------------------------------------------------------------------------------------ - //
// GlayNode - A Node is an element of a layout. Nodes have children and parent nodes. //
template<typename T>
class GlayNode {
	typedef GlayNode<T> NodeType;
public:	
	NodeType* Parent;
	std::list<NodeType> Child;
	std::string Name;

	GlayRegion Region;			// The visible Region (BaseRegion modified by Flags/Parent/Children)

	GlayRegion BaseRegion;		// The initial Region (not what's shown) //
	unsigned int Align;			// Alignment Flags //
	
	T Data;

public:
	inline GlayNode( NodeType* _Parent, const unsigned int _Align = GALIGN_DEFAULT, const T& _Data = T() ) :
		Parent( _Parent ),
		Region( GLAY_0,GLAY_0, GLAY_1,GLAY_1 ),
		BaseRegion( GLAY_0,GLAY_0, GLAY_1,GLAY_1 ),
		Align( _Align ),
		Data( _Data )
	{
	}

public:
	// Normal Child //
	inline NodeType& AddChild( const unsigned int _Flag = GALIGN_DEFAULT, const T& _Data = T() ) {
		Child.push_back( NodeType(this, _Flag | GALIGN_SUM, _Data) );
		return Child.back();
	}
	// Child that is relative the origin, not the parent //
	inline NodeType& AddFreeChild( const unsigned int _Flag = GALIGN_DEFAULT, const T& _Data = T() ) {
		Child.push_back( NodeType(this, _Flag, _Data) );
		return Child.back();
	}
	// Doesn't affect layout //
	inline NodeType& AddEmptyChild( const unsigned int _Flag = GALIGN_DEFAULT, const T& _Data = T() ) {
		Child.push_back( NodeType(this, _Flag | GALIGN_SUM | GALIGN_EMPTY, _Data ) );
		Child.back().SetShape(GLAY_0,GLAY_0);
		return Child.back();
	}

public:
	inline void SetPos( const GlayNum _x = GLAY_0, const GlayNum _y = GLAY_0 ) {
		BaseRegion.Pos = GlayPoint(_x,_y);
	}
	inline void SetShape( const GlayNum _x = GLAY_1, const GlayNum _y = GLAY_1 ) {
		BaseRegion.Shape = GlayPoint(_x,_y);
	}
	inline void SetAlign( const unsigned int _Align = GALIGN_DEFAULT ) {
		Align = _Align;
	}
	inline void SetName( const char* _Name = "" ) {
		Name = _Name;
	}
	
public:
	// Get Populated Data //
	inline const GlayPoint& GetShape() const {
		return Region.Shape;
	}
	inline const GlayPoint& GetPos() const {
		return Region.Pos;
	}
	// Get the Center point //
	inline GlayPoint GetCenterPos() const {
		return GetPos() + Region.GetHalfShape();
	}
	
	inline const char* GetName() const {
		return Name.c_str();
	}
	inline bool HasName() const {
		return Name.size();
	}

public:
	// Ocassionally we'll need to retrieve the true coordinates (before fitting, etc) //
	inline void CopyBaseToRegion() {
		Region = BaseRegion;
	}
	inline void CopyBases() {
		CopyBaseToRegion();
		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			Itr->CopyBases();
		}
	}
	
public:
	// Given a node (me), fit my children to my width, using their width as sizes. Also Y align. //
	inline void FitChildrenWide( const unsigned int Flag = GALIGN_MIDDLE ) {
		// Sum one axis, and find the largest value of the other axis //
		GlayNum Width = GLAY_0;
		GlayNum Height = GLAY_0;
		for (typename std::list<NodeType>::const_iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			Width += Itr->Region.Shape.x;
			if ( Itr->Region.Shape.y > Height ) {
				Height = Itr->Region.Shape.y;
			}
		}
		
		GlayNum Offset = GLAY_0;
		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			// "Reg", so now to shadow my internal member "Region" //
			GlayRegion& Reg = Itr->Region;
			
			// Distribute about axis //
			Reg.Pos.x = Offset;
			if ( Width != GLAY_0 )
				Reg.Shape.x = Reg.Shape.x / Width;
			Offset += Reg.Shape.x;
			
			// Align about other axis //
			if ( Height != GLAY_0 )
				Reg.Shape.y /= Height; // Convert to 0-1 range //
			
			if ( Flag == GALIGN_TOP )
				Reg.Pos.y = GLAY_0;
			else if ( Flag == GALIGN_BOTTOM )
				Reg.Pos.y = GLAY_1 - Reg.Shape.y;
			else //if ( Flag == GALIGN_MIDDLE )
				Reg.Pos.y = GlayNumHalf(GLAY_1 - Reg.Shape.y);
			
			// Scale to size of parent //
			Reg.Pos = Reg.Pos * Region.Shape;
			Reg.Shape = Reg.Shape * Region.Shape;			
		}
	}

	// Given a node (me), fit my children to my height, using their heights as sizes. Also X align. //
	inline void FitChildrenTall( const unsigned int Flag = GALIGN_CENTER ) {
		// Sum one axis, and find the largest value of the other axis //
		GlayNum Width = GLAY_0;
		GlayNum Height = GLAY_0;
		for (typename std::list<NodeType>::const_iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			if ( Itr->Region.Shape.x > Width ) {
				Width = Itr->Region.Shape.x;
			}
			Height += Itr->Region.Shape.y;
		}
		
		GlayNum Offset = GLAY_0;
		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			// "Reg", so now to shadow my internal member "Region" //
			GlayRegion& Reg = Itr->Region;
						
			// Align about axis //
			if ( Width != GLAY_0 )
				Reg.Shape.x /= Width; // Convert to 0-1 range //
			
			if ( Flag == GALIGN_LEFT )
				Reg.Pos.x = GLAY_0;
			else if ( Flag == GALIGN_RIGHT )
				Reg.Pos.x = GLAY_1 - Reg.Shape.x;
			else //if ( Flag == GALIGN_CENTER )
				Reg.Pos.x = GlayNumHalf(GLAY_1 - Reg.Shape.x);
			
			// Distribute about other axis //
			Reg.Pos.y = Offset;
			if ( Height != GLAY_0 )
				Reg.Shape.y = Reg.Shape.y / Height;
			Offset += Reg.Shape.y;

			// Scale to size of parent //
			Reg.Pos = Reg.Pos * Region.Shape;
			Reg.Shape = Reg.Shape * Region.Shape;
		}
	}

	// Given a node (me), fit my children inside eachother. //
	// NOTE: Empty Children don't affect layout (unless you change their shape). //
	// NOTE: Shape usage may not be obvious. With 2 children, the bigger child takes up more space. //
	//   With more than 2, layouts don't exactly make sense anymore. //
	// NOTE: Can provide an Offset in Pos, but coordinates are in fractions of parent, so it's weird. //
	inline void FitChildren() {
		// Sum of both axis, so we know how to distribute //
		GlayNum Width = GLAY_0;
		GlayNum Height = GLAY_0;
		for (typename std::list<NodeType>::const_iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			Width += Itr->Region.Shape.x;
			Height += Itr->Region.Shape.y;
		}

		GlayNum OffsetX = GLAY_0;
		GlayNum OffsetY = GLAY_0;
		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			// "Reg", so now to shadow my internal member "Region" //
			GlayRegion& Reg = Itr->Region;

			GlayNum StepX = Reg.Shape.x;
			Reg.Shape.x = GLAY_1 - OffsetX;
			Reg.Pos.x = GlayNumHalf(OffsetX) - Reg.Pos.x;
			if ( Width != GLAY_0 )
				OffsetX += StepX / Width;

			GlayNum StepY = Reg.Shape.y;
			Reg.Shape.y = GLAY_1 - OffsetY;
			Reg.Pos.y = GlayNumHalf(OffsetY) - Reg.Pos.y;
			if ( Height != GLAY_0 )
				OffsetY += StepY / Height;

			// Scale to size of parent //
			Reg.Pos = Reg.Pos * Region.Shape;
			Reg.Shape = Reg.Shape * Region.Shape;
		}
	}
	
	inline void PackChildrenLeft() {
		GlayNum Offset = GLAY_0;
		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			// "Reg", so now to shadow my internal member "Region" //
			GlayRegion& Reg = Itr->Region;
			
			// Distribute about axis //
			Reg.Pos.x = Offset;
//			if ( Width != GLAY_0 )
//				Reg.Shape.x = Reg.Shape.x / Width;
			Offset += Reg.Shape.x;
			
			// Align about other axis //
//			if ( Height != GLAY_0 )
//				Reg.Shape.y /= Height; // Convert to 0-1 range //
			
//			if ( Flag == GALIGN_TOP )
//				Reg.Pos.y = GLAY_0;
//			else if ( Flag == GALIGN_BOTTOM )
//				Reg.Pos.y = GLAY_1 - Reg.Shape.y;
//			else //if ( Flag == GALIGN_MIDDLE )
//				Reg.Pos.y = GlayNumHalf(GLAY_1 - Reg.Shape.y);
			
			// Scale to size of parent //
//			Reg.Pos = Reg.Pos * Region.Shape;
//			Reg.Shape = Reg.Shape * Region.Shape;			
		}		
	}
		
public:
	inline void Update() {
		GlayRegion Dummy(0,0,0,0);

		GlayRegion* ParentRegion;
		if ( Parent == 0 ) {
			ParentRegion = &Dummy;
		}
		else {
			ParentRegion = &Parent->Region;
		}
		
		// **** Properties of Self **** //
		// Fancy Alignment Modes (May Affect Shape) //
		if ( Align & GALIGN_FIT ) {
			Region.Pos = ParentRegion->Pos + Region.Pos;
			Region.Shape = ParentRegion->Shape;
		}
		else if ( Align & GALIGN_SUM ) {
			Region.Pos = ParentRegion->Pos + Region.Pos;
		}
		else {
			// Relative Origin... is automatic, by doing nothing //
			//Region.Pos = Region.Pos;
		}

		// Standard Alignment (X Axis) //
		if ( (Align & GALIGN_CENTER) == GALIGN_CENTER ) {
			Region.Pos.x += /*ParentRegion->Pos.x +*/ GlayNumHalf(ParentRegion->Shape.x-Region.Shape.x);
		}
		else if ( Align & GALIGN_LEFT ) {
			//Region.Pos.x = ParentRegion->Pos.x;
		}
		else if ( Align & GALIGN_RIGHT ) {
			Region.Pos.x += /*ParentRegion->Pos.x +*/ ParentRegion->Shape.x - Region.Shape.x;
		}
		else {
			Region.Pos.x -= GlayNumHalf(Region.Shape.x);
		}

		// Standard Alignment (Y Axis) //
		if ( (Align & GALIGN_MIDDLE) == GALIGN_MIDDLE ) {
			Region.Pos.y += /*ParentRegion->Pos.y +*/ GlayNumHalf(ParentRegion->Shape.y-Region.Shape.y);
		}
		else if ( Align & GALIGN_BOTTOM ) {
			//Region.Pos.y = ParentRegion->Pos.y;
		}
		else if ( Align & GALIGN_TOP ) {
			Region.Pos.y += /*ParentRegion->Pos.y +*/ ParentRegion->Shape.y - Region.Shape.y;
		}
		else {
			Region.Pos.y -= GlayNumHalf(Region.Shape.y);
		}

		// **** Properties of Children **** //
		if ( (Align & GALIGN_CHILDREN) == GALIGN_FIT_CHILDREN_TO_WIDTH ) {
			FitChildrenWide( Align & GALIGN_HALIGN );
		}
		else if ( (Align & GALIGN_CHILDREN) == GALIGN_FIT_CHILDREN_TO_HEIGHT ) {
			FitChildrenTall( Align & GALIGN_VALIGN );
		}
		else if ( (Align & GALIGN_CHILDREN) == GALIGN_FIT_CHILDREN_TO_ME ) {
			FitChildren();
		}
		else if ( (Align & GALIGN_CHILDREN) == GALIGN_PACK_CHILDREN_FROM_LEFT ) {
			PackChildrenLeft();// Align & GALIGN_HALIGN );
		}

		// Update Children //
		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			Itr->Update();
		}
	}
	
public:
	inline NodeType* Find( const char* _Name ) {
		if ( Name == _Name ) {
			return this;
		}

		NodeType* Ret = 0;

		for (typename std::list<NodeType>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			Ret = Itr->Find( _Name );
			return_if( Ret );
		}
		
		return Ret;
	}

};
// - ------------------------------------------------------------------------------------------ - //
// GlayLayout - Contains a heiarchy of Nodes //
template<typename T>
struct GlayLayout {
	typedef GlayNode<T> NodeType;
	
	NodeType Root;
	
	inline GlayLayout() :
		Root( 0 )
	{
	}
	
public: 
	inline void Update() {
		Root.CopyBases();
		Root.Update();
	}
	
	inline void Draw( const Matrix4x4& Mat ) { 
		DrawLayout( Mat, Root );
	}
	
	inline void DrawLayout( const Matrix4x4& Mat, const NodeType& Node ) {
		Node.Data.Draw( Mat, Node );
		
		for (typename std::list<NodeType>::const_iterator Itr = Node.Child.begin(), End = Node.Child.end(); Itr != End; ++Itr) {
			DrawLayout( Mat, *Itr );
		}
	}
	
public:
	inline NodeType* Find( const char* _Name ) {
		return Root.Find( _Name );
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GLAYOUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
