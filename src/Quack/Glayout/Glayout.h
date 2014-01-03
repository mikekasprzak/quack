// - ------------------------------------------------------------------------------------------ - //
// Glayout - General Purpose Layout Engine for simple UIs //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GLAYOUT_H__
#define __GLAYOUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
#include <list>
// - ------------------------------------------------------------------------------------------ - //
	//GlayNode* Child;

// - ------------------------------------------------------------------------------------------ - //
typedef float GlayNum;	// Number //
#define GLAY_0	0.0f
#define GLAY_1	1.0f
// - ------------------------------------------------------------------------------------------ - //
enum GlayNodeFlags {
	GLAY_LEFT =			0x1,
	GLAY_RIGHT = 		0x2,
	GLAY_CENTER =		GLAY_LEFT | GLAY_RIGHT,
			
	GLAY_TOP =			0x4,
	GLAY_BOTTOM	=		0x8,
	GLAY_MIDDLE =		GLAY_TOP | GLAY_BOTTOM,

	
	GLAY_DEFAULT =		GLAY_CENTER | GLAY_MIDDLE,
};
// - ------------------------------------------------------------------------------------------ - //
struct GlayRegion {
	GlayNum x,y,w,h;
	
	inline GlayRegion( const GlayNum _x = GLAY_0, const GlayNum _y = GLAY_0, const GlayNum _w = GLAY_1, const GlayNum _h = GLAY_1 ) :
		x(_x),
		y(_y),
		w(_w),
		h(_h)
	{
	}
	
public:
	inline void SetPos( const GlayNum _x, const GlayNum _y ) {
		x = _x;
		y = _y;
	}
	inline void SetShape( const GlayNum _w, const GlayNum _h ) {
		w = _w;
		h = _h;
	}
};
// - ------------------------------------------------------------------------------------------ - //

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

//// - ------------------------------------------------------------------------------------------ - //
//inline GlayNode* new_Child_GlayNode( GlayNode* Parent ) {
//	GlayNode* Node = new GlayNode;
//	Node->Region.x = 0;
//	Node->Region.y = 0;
//	Node->Region.w = 1;
//	Node->Region.h = 1;
//
//	Node->Flags = GLAY_DEFAULT;
//	
//	Node->Parent = Parent;
//	//Node->Child = 0;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void delete_GlayNode( GlayNode* Node ) {
//	for (std::list<GlayNode*>::const_iterator itr = intList.begin(); iterator != intList.end(); ++iterator) {
//	    std::cout << *iterator;
//	}
////	if ( Node->Child ) {
////		delete_GlayNode( Node->Child );
////	}
//	delete Node;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline GlayLayout* new_GlayLayout() {
//	GlayLayout* Layout = new GlayLayout;
//	Layout->Root = new_Child_GlayNode( 0 );
//	return Layout;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void delete_GlayLayout( GlayLayout* Layout ) {
//	if ( Layout->Root ) {
//		delete_GlayNode( Layout->Root );
//	}
//	delete Layout;
//}
// - ------------------------------------------------------------------------------------------ - //

//// - ------------------------------------------------------------------------------------------ - //
//inline void set_Region_GlayNode( GlayNode* Node, const GlayNum x, const GlayNum y, const GlayNum w, const GlayNum h ) {
//	Node->Region.x = x;
//	Node->Region.y = y;
//	Node->Region.w = w;
//	Node->Region.h = h;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void set_Pos_GlayNode( GlayNode* Node, const GlayNum x, const GlayNum y ) {
//	Node->Region.x = x;
//	Node->Region.y = y;
//}
//// - ------------------------------------------------------------------------------------------ - //
//inline void set_Shape_GlayNode( GlayNode* Node, const GlayNum w, const GlayNum h ) {
//	Node->Region.w = w;
//	Node->Region.h = h;
//}
//// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GLAYOUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
