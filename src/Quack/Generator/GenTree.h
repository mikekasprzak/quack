// - ------------------------------------------------------------------------------------------ - //
#ifndef __GENERATOR_GENTREE_H__
#define __GENERATOR_GENTREE_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Vert/Vert.h>
// - ------------------------------------------------------------------------------------------ - //
enum {
	GT_MAX_CHILDREN = 4
};
// - ------------------------------------------------------------------------------------------ - //
struct GenTreeNode {
	GenTreeNode* Parent;
	GenTreeNode* Child[GT_MAX_CHILDREN];
//	GenTree_Leaf* Leaf;
	
	Vector2D Pos;
	Vector2D Old;
	
	Vector2D Angle;		// Angular Constraint //
	Real Length;		// Spring Constraint //
	Real InvMass;
//	Real Radius;

public:
	inline GenTreeNode( GenTreeNode* _Parent = 0, const Vector2D& _Pos = Vector2D::Zero, const Vector2D& _Angle = Vector2D(0,1), const Real _Length = Real::One, const Real _InvMass = Real::One ) :
		Parent( _Parent ),
		Pos( _Pos ),
		Old( _Pos ),
		Angle( _Angle ),
		Length( _Length ),
		InvMass( _InvMass )
	{
		// Clear Children Pointers //
		for ( st idx = 0; idx < GT_MAX_CHILDREN; idx++ ) {
			Child[idx] = 0;
		}
	}
	
	inline st32 Size() const {
		st32 Ret = 0;
		for ( st idx = 0; idx < GT_MAX_CHILDREN; idx++ ) {
			if ( Child[idx] ) {
				Ret++;
			}
			else {
				break;
			}
		}
		return Ret;
	}
	
	inline st32 MaxSize() const {
		return GT_MAX_CHILDREN;
	}

	inline int NextIndex() const {
		for ( int idx = 0; idx < GT_MAX_CHILDREN; idx++ ) {
			if ( Child[idx] == 0 ) {
				return idx;
			}
		}
		return -1;
	}

public:
	inline void AddChild( const Vector2D& _Pos = Vector2D::Zero, const Vector2D& _Angle = Vector2D(0,1), const Real _InvMass = Real::One ) {
		int Index = NextIndex();
		if ( Index >= 0 ) {
			Child[Index] = new GenTreeNode( this, _Pos, _Angle, (_Pos-Pos).Magnitude(), _InvMass );
		}
	}
};

// - ------------------------------------------------------------------------------------------ - //
struct GenTree {
	GenTreeNode* Root;
	
public:
	inline GenTree() :
		Root( 0 )
	{
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
inline GenTree new_GenTree() {
	GenTree Ret;
	
	Ret.Root = new GenTreeNode( 0, Vector2D(-120,0) );
	GenTreeNode* Node = Ret.Root;
	for ( int idx = 0; idx < 6; idx++ ) {
		Node->AddChild( Vector2D(-120,10+((10-idx)*idx)) );
		Node = Node->Child[0];
	}
	
	return Ret;
}
// - ------------------------------------------------------------------------------------------ - //
inline void delete_GenTreeNode( GenTreeNode* Node ) {
	if ( Node ) {
		for ( int idx = 0; idx < Node->MaxSize(); idx++ ) {
			if ( Node->Child[idx] ) {
				// Recursive -- Delete My Child's Children //
				delete_GenTreeNode( Node->Child[idx] );
				// Delete Child //
				delete Node->Child[idx];
				Node->Child[idx] = 0;
			}
		}
	}
}

// - ------------------------------------------------------------------------------------------ - //
inline void delete_GenTree( GenTree& Tree ) {
	delete_GenTreeNode( Tree.Root );
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GENERATOR_GENTREE_H__ //
// - ------------------------------------------------------------------------------------------ - //
