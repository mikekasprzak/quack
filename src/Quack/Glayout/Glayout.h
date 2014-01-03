// - ------------------------------------------------------------------------------------------ - //
// Glayout - General Purpose Layout Engine for simple UIs //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLAYOUT_H__
#define __GLAYOUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <list>
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
typedef float GlayNum;		// Number //
#define GLAY_0		0.0f
#define GLAY_1		1.0f
inline GlayNum GlayNumHalf( const GlayNum In ) { return In * 0.5f; }
// - ------------------------------------------------------------------------------------------ - //
//typedef int GlayNum;		// Number //
//#define GLAY_0		0
//#define GLAY_1		1
//inline GlayNum GlayNumHalf( const GlayNum In ) { return In >> 1; }
// - ------------------------------------------------------------------------------------------ - //
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
enum GlayNodeFlag {
	GLAY_LEFT =			0x1,
	GLAY_RIGHT = 		0x2,
	GLAY_CENTER =		GLAY_LEFT | GLAY_RIGHT,
			
	GLAY_TOP =			0x4,
	GLAY_BOTTOM	=		0x8,
	GLAY_MIDDLE =		GLAY_TOP | GLAY_BOTTOM,
	
	// ??? //
	GLAY_SCALE = 		0x10,	// Child Positions are scaled to fit the Parent dimensions //
	GLAY_SUM = 			0x20,	// Child Positions are the sum of the Parents //


	GLAY_DEFAULT =		GLAY_CENTER | GLAY_MIDDLE,// | GLAY_SCALE,
};
// - ------------------------------------------------------------------------------------------ - //
struct GlayNode {
	GlayRegion Region;
	unsigned int Flags;
	
	// Tree //
	GlayNode* Parent;
	std::list<GlayNode> Child;
		
	inline GlayNode( GlayNode* _Parent ) :
		Region( GLAY_0,GLAY_0, GLAY_1,GLAY_1 ),
		Flags( GLAY_DEFAULT ),
		Parent( _Parent )
	{
	}

public:
	inline void AddChild() {
		Child.push_back( GlayNode(this) );
	}

public:
	inline void SetPos( const GlayNum _x = GLAY_0, const GlayNum _y = GLAY_0 ) {
		Region.Pos = GlayPoint(_x,_y);
	}
	inline void SetShape( const GlayNum _x = GLAY_1, const GlayNum _y = GLAY_1 ) {
		Region.Shape = GlayPoint(_x,_y);
	}
	
public:	
	// Get the Local position //
	inline const GlayPoint& GetLocalPos() const {
		return Region.Pos;
	}
	// Get the Shape //
	inline const GlayPoint& GetShape() const {
		return Region.Shape;
	}
	
	// Get the True position //
	inline GlayPoint GetPos() const {
		if ( Parent ) {
			return Region.Pos + Parent->GetPos();
		}
		
		return Region.Pos;
	}
	
	// Get the True Center point //
	inline GlayPoint GetCenterPos() const {
		return GetPos() + Region.GetHalfShape();
	}
	
public:
	// Given a node (me), fit my children to my width, using their width as sizes. Also Y align. //
	inline void FitChildrenWide( const GlayNodeFlag Flag = GLAY_MIDDLE ) {
		// Sum one axis, and find the largest value of the other axis //
		GlayNum Width = GLAY_0;
		GlayNum Height = GLAY_0;
		for (std::list<GlayNode>::const_iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			Width += Itr->Region.Shape.x;
			if ( Itr->Region.Shape.y > Height ) {
				Height = Itr->Region.Shape.y;
			}
		}
		
		GlayNum Offset = GLAY_0;
		for (std::list<GlayNode>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			// "Reg", so now to shadow my internal member "Region" //
			GlayRegion& Reg = Itr->Region;
			
			// Distribute about axis //
			Reg.Pos.x = Offset;
			Reg.Shape.x = Reg.Shape.x / Width;
			Offset += Reg.Shape.x;
			
			// Align about other axis //
			Reg.Shape.y /= Height; // Convert to 0-1 range //
			
			if ( Flag == GLAY_MIDDLE )
				Reg.Pos.y = GlayNumHalf(GLAY_1 - Reg.Shape.y);
			else if ( Flag == GLAY_BOTTOM )
				Reg.Pos.y = GLAY_1 - Reg.Shape.y;
			else //if ( Flag == GLAY_TOP )
				Reg.Pos.y = GLAY_0;
			
			// Scale to size of parent //
			Reg.Pos = Reg.Pos * Region.Shape;
			Reg.Shape = Reg.Shape * Region.Shape;			
		}
	}

	// Given a node (me), fit my children to my height, using their heights as sizes. Also X align. //
	inline void FitChildrenTall( const GlayNodeFlag Flag = GLAY_CENTER ) {
		// Sum one axis, and find the largest value of the other axis //
		GlayNum Width = GLAY_0;
		GlayNum Height = GLAY_0;
		for (std::list<GlayNode>::const_iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			if ( Itr->Region.Shape.x > Width ) {
				Width = Itr->Region.Shape.x;
			}
			Height += Itr->Region.Shape.y;
		}
		
		GlayNum Offset = GLAY_0;
		for (std::list<GlayNode>::iterator Itr = Child.begin(), End = Child.end(); Itr != End; ++Itr) {
			// "Reg", so now to shadow my internal member "Region" //
			GlayRegion& Reg = Itr->Region;
						
			// Align about axis //
			Reg.Shape.x /= Width; // Convert to 0-1 range //
			
			if ( Flag == GLAY_CENTER )
				Reg.Pos.x = GlayNumHalf(GLAY_1 - Reg.Shape.x);
			else if ( Flag == GLAY_RIGHT )
				Reg.Pos.x = GLAY_1 - Reg.Shape.x;
			else //if ( Flag == GLAY_LEFT )
				Reg.Pos.x = GLAY_0;
			
			// Distribute about other axis //
			Reg.Pos.y = Offset;
			Reg.Shape.y = Reg.Shape.y / Height;
			Offset += Reg.Shape.y;

			// Scale to size of parent //
			Reg.Pos = Reg.Pos * Region.Shape;
			Reg.Shape = Reg.Shape * Region.Shape;			
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
struct GlayLayout {
	GlayNode Root;
	
	inline GlayLayout() :
		Root( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GLAYOUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
