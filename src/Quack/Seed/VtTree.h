// - ------------------------------------------------------------------------------------------ - //
#ifndef __SEED_VTTREE_H__
#define __SEED_VTTREE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Vert/Vert.h>
// - ------------------------------------------------------------------------------------------ - //
struct VtTreeNode {
	VtTreeNode* Parent;
	enum { MAX_CHILDREN = 4 };
	VtTreeNode* Child[MAX_CHILDREN];

//	GenTree_Leaf* Leaf;

	// Values that Change //	
	Vector2D Pos;
	Vector2D Old;		// Verlet //
	Vector2D Normal;	// Direction Pointing //
	
	// Values that stay the same //
	Vector2D Angle;		// Angular Constraint //
	Real Length;		// Spring Constraint //
	Real InvMass;
	Real Radius;

public:
	typedef Vector2D Type;
	
	inline VtTreeNode( VtTreeNode* _Parent = 0 ) :
		Parent( _Parent ),
		Normal( Vector2D(0,1) ),
		Angle( Vector2D(0,1) ),
		Length( Real::One ),
		InvMass( Real::One ),
		Radius( Real::One )
	{
		// Clear Children Pointers //
		for ( st idx = 0; idx < MAX_CHILDREN; idx++ ) {
			Child[idx] = 0;
		}

		// If we have a parent, use it to determin our position //		
		if ( Parent )
			Pos = Parent->Pos + (Parent->Normal * Parent->Length);
		else
			Pos = Vector2D::Zero;

		Old = Pos;
	}

	inline st32 Size() const {
		st32 Ret = 0;
		for ( st idx = 0; idx < MAX_CHILDREN; idx++ ) {
			if ( Child[idx] == 0 )
				return idx;
			Ret++;
		}
		return Ret;
	}
	
	inline st32 MaxSize() const {
		return MAX_CHILDREN;
	}

	inline int NextIndex() const {
		for ( int idx = 0; idx < MAX_CHILDREN; idx++ ) {
			if ( Child[idx] == 0 ) {
				return idx;
			}
		}
		return -1;
	}
};
// - ------------------------------------------------------------------------------------------ - //
typedef GelTree<VtTreeNode> VtTree;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline void Gen_VtTree( VtTree& Out, const st32 Segments = 12 ) {
	Out.Clear();
	Out.Reserve(Segments+1);
	
	// Add Root Node //
	VtTreeNode* Root = Out.Add(0);
	VtTreeNode* Node = Root;
	Node->Length = 16;
	Node->Normal = Vector2D(0,1);
	Node->Radius = 8;
	
	for ( st32 idx = 0; idx < Segments; idx++ ) {
		Node = Out.Add( Node );
		Node->Length = 16 - (Segments>>1);
		Node->Radius = Node->Parent->Radius - Real::Half;

		Node->Normal = Node->Parent->Normal;
		Vector2D Twist(1,10);
		if ( idx >= 3 ) 
			Twist.x = -Twist.x;
		Twist.Normalize();
		Matrix2x2 MatTwist(Twist.Tangent(),Twist);
		Node->Normal = Node->Normal.ApplyMatrix( MatTwist );
	}
}
// - ------------------------------------------------------------------------------------------ - //
inline void Step_VtTree( VtTree& InOut ) {
}
// - ------------------------------------------------------------------------------------------ - //
inline void Grow_VtTree( VtTree& InOut ) {
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_VTTREE_H__ //
// - ------------------------------------------------------------------------------------------ - //
