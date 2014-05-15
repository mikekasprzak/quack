// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELUI_H__
#define __GEL_GELUI_H__
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Glayout/Glayout.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	UI_NULL = 0,
	
	UI_BOX,					// Box Test //
	UI_IMAGE,				// Static Image //
};	
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GelUINode {
	typedef GelUINode thistype;
	typedef GlayNode<thistype> NodeType;
public:
	int Type;	// What kind of Node this is //
	
	GelAtlasPool::UID	AtlasUID;
	int 				ArtIndex; 
public:
	inline GelUINode() :
		Type( Gel::UI_NULL ),
		AtlasUID( 0 ),
		ArtIndex( 0 )
	{
	}
	
	inline GelUINode( const int _Type, const char* const AtlasName ) :
		Type( _Type )
	{	
		Log( "T: %i", Type );
		
		AtlasUID = Gel::AtlasPool.Load( AtlasName );
		ArtIndex = 0;
	}

public:	
	inline void SetType( const int _Type ) {
		Type = _Type;
	}
	
	inline void Draw( const Matrix4x4& Mat, const NodeType& Node ) const {
		switch ( Type ) {
			case Gel::UI_BOX: {
				const st32 VertCount = 4;
				Vector3D Verts[ VertCount ];
				Verts[0].x = Node.GetPos().x;
				Verts[0].y = Node.GetPos().y;
				Verts[1].x = Node.GetPos().x + Node.GetShape().x;
				Verts[1].y = Node.GetPos().y;
				Verts[2].x = Node.GetPos().x + Node.GetShape().x;
				Verts[2].y = Node.GetPos().y + Node.GetShape().y;
				Verts[3].x = Node.GetPos().x;
				Verts[3].y = Node.GetPos().y + Node.GetShape().y;
			
				Gel::RenderFlat( GEL_LINE_LOOP, Mat, GEL_RGB_WHITE, Verts, VertCount );
			
				break;
			}
			case Gel::UI_IMAGE: {				
				Matrix4x4 MyMat = Matrix4x4::ScalarMatrix( Vector2D(Node.GetShape().x, Node.GetShape().y) );
				MyMat *= Matrix4x4::TranslationMatrix( Vector2D(Node.GetCenterPos().x, Node.GetCenterPos().y) );
				MyMat *= Mat;
				
				GelAtlas& Atlas = Gel::AtlasPool[AtlasUID];
				Atlas.Draw( MyMat, ArtIndex );
				
				break;
			}
		}
		
		{
			const st32 VertCount = 4;
			Vector3D Verts[ VertCount ];
			Verts[0].x = Node.GetPos().x;
			Verts[0].y = Node.GetPos().y;
			Verts[1].x = Node.GetPos().x + Node.GetShape().x;
			Verts[1].y = Node.GetPos().y;
			Verts[2].x = Node.GetPos().x + Node.GetShape().x;
			Verts[2].y = Node.GetPos().y + Node.GetShape().y;
			Verts[3].x = Node.GetPos().x;
			Verts[3].y = Node.GetPos().y + Node.GetShape().y;
		
			Gel::RenderFlat( GEL_LINE_LOOP, Mat, GEL_RGBA(128,128,0,128), Verts, VertCount );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELUI_H__ //
// - ------------------------------------------------------------------------------------------ - //
