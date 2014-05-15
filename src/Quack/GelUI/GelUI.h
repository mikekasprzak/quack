// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELUI_H__
#define __GEL_GELUI_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Glayout/Glayout.h>
#include <Render/GelDraw.h>
#include <Font/Font.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	UI_NULL = 0,
	
	UI_BOX,					// Box Test //
	UI_IMAGE,				// Static Image //
	UI_TEXT,				// Text Box (line) //
};	
// - ------------------------------------------------------------------------------------------ - //
}; // namespace Gel //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
namespace App {
	extern bool Debug;	
}; // namespace App //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
class GelUINode {
	typedef GelUINode thistype;
	typedef GlayNode<thistype> NodeType;
public:
	int Type;	// What kind of Node this is //
	
	GelAtlasPool::UID	AtlasUID;
	int 				ArtIndex;
	
	std::string			Text;
	GelFontPool::UID	FontUID;		// NOTE: Could be merged with AtlasUID, if I really wanted //
		
	GelColor			Color;
public:
	inline GelUINode() :
		Type( Gel::UI_NULL ),
		AtlasUID( 0 ),
		ArtIndex( 0 ),
		FontUID( 0 ),
		Color( GEL_RGB_WHITE )
	{
	}
	
	inline GelUINode( const int _Type, const char* const _Text ) :
		Type( _Type )
	{	
		switch ( Type ) {
			case Gel::UI_IMAGE: {
				AtlasUID = Gel::AtlasPool.LoadAndIndex( _Text, &ArtIndex );
				break;
			}
			case Gel::UI_TEXT: {
				Text = _Text;
				break;
			}
		}
	}

public:	
	inline void SetType( const int _Type ) {
		Type = _Type;
	}
	inline void SetFont( const char* const FontName ) {
		FontUID = Gel::FontPool.Load( FontName );
	}
	inline void SetColor( const GelColor& _Color ) {
		Color = _Color;
	}

public:	
	inline void Draw( const Matrix4x4& Mat, const NodeType& Node ) const {
		switch ( Type ) {
			case Gel::UI_BOX: {
				gelDrawRect( 
					Mat,
					Vector2D(Node.GetPos().x,Node.GetPos().y).ToVector3D(), 
					Vector2D(Node.GetShape().x, Node.GetShape().y), 
					GEL_RGB_WHITE
				);

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
			case Gel::UI_TEXT: {
				Gel::FontPool[FontUID].printf( 
					Mat, 
					Vector2D(Node.GetCenterPos().x, Node.GetCenterPos().y).ToVector3D(), 
					Real(1), // FontSize, 
					Color,
					GEL_ALIGN_DEFAULT,
					Text.c_str()
				);
				
				break;
			}
		}
		
		if ( App::Debug ) {
			gelDrawRect( 
				Mat,
				Vector2D(Node.GetPos().x,Node.GetPos().y).ToVector3D(), 
				Vector2D(Node.GetShape().x, Node.GetShape().y), 
				GEL_RGBA(128,128,0,128)
			);
			gelDrawCross( 
				Mat, 
				Vector2D(Node.GetCenterPos().x,Node.GetCenterPos().y).ToVector3D(), 
				Vector2D(2,2), 
				GEL_RGBA(128,128,0,128) 
			);
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELUI_H__ //
// - ------------------------------------------------------------------------------------------ - //