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
};	
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GelUINode {
	typedef GelUINode thistype;
	typedef GlayNode<thistype> NodeType;
public:
	int Type;
	
public:
	inline GelUINode() :
		Type( Gel::UI_NULL )
	{
	}
	
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
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELUI_H__ //
// - ------------------------------------------------------------------------------------------ - //
