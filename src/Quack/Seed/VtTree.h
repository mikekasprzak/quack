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
inline void Gen_VtTree( VtTree& Out, const st32 Segments = 13 ) {
	Out.Clear();
	Out.Reserve(Segments+1); // Any Resize will cause our Parent pointers to break //
	
	// Add Root Node //
	VtTreeNode* Node = Out.Add(0);
	Node->Length = 16;
	Node->Normal = Vector2D(0,1);
	Node->Angle = Node->Normal;
	Node->Radius = 7;
	Node->InvMass = Real::One / Real( Node->Length * Node->Radius );
	
	for ( st32 idx = 0; idx < Segments; idx++ ) {
		int ParentIndex = Out.Size()-1;
		
		Node = Out.Add( Node );
		VtTreeNode* Parent = &Out[ParentIndex]; // Because "Node->Parent" can potentially be wrong due to Resize //

		Node->Length = 15 - idx;
		Node->Radius = Parent->Radius - Real::Half;
		Node->InvMass = Real::One / Real( Node->Length * Node->Radius );

		Vector2D Twist(-5,10);
		Twist.Normalize();
		if ( idx >= 3 ) 
			Twist.x = -Twist.x;
		Matrix2x2 MatTwist(Twist.Tangent(),Twist);

		Node->Normal = Parent->Normal.ApplyMatrix( MatTwist );
		Node->Angle = Twist;
	}	
}
// - ------------------------------------------------------------------------------------------ - //
inline void Step_VtTree( VtTree& InOut ) {
	typedef typename VtTree::Type VertType;
	
	// Step //
	for ( st32 idx = 0; idx < InOut.Size(); idx++ ) {
		VertType& A = InOut[idx];
		
		Vector2D Velocity = A.Pos - A.Old;
		Velocity *= Real(0.998);
		Velocity += Vector2D(0,-0.03);
		
		A.Old = A.Pos;
		A.Pos += Velocity;// * Real(0.99);
	}
/*
	// Spring Constraint //
	for ( st32 idx = 1; idx < InOut.Size(); idx++ ) {
		VertType& A = *InOut[idx].Parent;
		VertType& B = InOut[idx];
		
		Vector2D Ray = B.Pos - A.Pos;
		Real Mag = Ray.NormalizeRet();
		
		Real NewLen = A.Length - Mag;
		
		Real Weight(0.5);
		
		A.Pos -= Ray * NewLen * Weight;
		B.Pos += Ray * NewLen * (Real::One - Weight);
		A.Normal = (B.Pos - A.Pos).Normal();
	}
*/		
	// Angle Constraint //
	for ( st32 idx = 1; idx < InOut.Size(); idx++ ) {
		VertType& A = *InOut[idx].Parent;
		VertType& B = InOut[idx];

		Real MassSum = A.InvMass + B.InvMass;

		if ( MassSum > Real::Zero ) {
			Vector2D TargetNormal = A.Angle;
			Matrix2x2 Mat( A.Normal.Tangent(), A.Normal );
			TargetNormal = TargetNormal.ApplyMatrix( Mat );
					
			Vector2D Ray = B.Pos - A.Pos;
			Vector2D Ray2 = (TargetNormal*A.Length);

			MassSum = Real::One / MassSum;
			Vector2D RayDiff = Ray2 - Ray;
			B.Pos += RayDiff * (B.InvMass * MassSum);// / MassSum);// * Real(0.5f);
			A.Pos -= RayDiff * (A.InvMass * MassSum);// / MassSum);// * Real(0.5f);
	
			B.Normal = (B.Pos - A.Pos).Normal();
		}
	}

	// Pin Constraint //
	InOut[0].Pos = Vector2D::Zero;
	InOut[1].Pos = InOut[0].Pos + (InOut[0].Angle * InOut[0].Length);
	InOut[0].Normal = (InOut[1].Pos - InOut[0].Pos).Normal();
	InOut[1].Normal = (InOut[2].Pos - InOut[1].Pos).Normal();
}
// - ------------------------------------------------------------------------------------------ - //
inline void Grow_VtTree( VtTree& InOut ) {
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __SEED_VTTREE_H__ //
// - ------------------------------------------------------------------------------------------ - //
