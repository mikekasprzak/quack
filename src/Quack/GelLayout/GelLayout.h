// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GELLAYOUT_H__
#define __GEL_GELLAYOUT_H__
// - ------------------------------------------------------------------------------------------ - //
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Math/Math.h>
#include <Geometry/Rect.h>

#include <Glayout/Glayout.h>

#include <Render/GelDraw.h>
#include <Atlas/Atlas.h>
#include <Font/Font.h>
// - ------------------------------------------------------------------------------------------ - //
namespace Gel {
// - ------------------------------------------------------------------------------------------ - //
enum {
	GLO_NULL = 0,
	
	GLO_BOX,				// Box Test //
	GLO_IMAGE,				// Static Image //
	GLO_TEXT,				// Text Box (line) //
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
class GelLayoutNode {
	typedef GelLayoutNode thistype;
	typedef GlayNode<thistype> NodeType;
public:
	int Type;	// What kind of Node this is //
	
	GelAtlasPool::UID	AtlasUID;
	int 				ArtIndex;
	
	std::string			Text;
	GelFontPool::UID	FontUID;		// NOTE: Could be merged with AtlasUID, if I really wanted //
		
	GelColor			Color;
	Real				FontSize;
	int					FontAlign;
public:
	inline GelLayoutNode() :
		Type( Gel::GLO_NULL ),
		AtlasUID( 0 ),
		ArtIndex( 0 ),
		FontUID( 0 ),
		FontSize( 12 ),
		FontAlign( GEL_ALIGN_CENTER | GEL_ALIGN_MIDDLE ),
		Color( GEL_RGB_WHITE )
	{
	}
	
	inline GelLayoutNode( const int _Type, const char* const _Text = "" ) :
		Type( _Type ),
		AtlasUID( 0 ),
		ArtIndex( 0 ),
		FontUID( 0 ),
		FontSize( 12 ),
		FontAlign( GEL_ALIGN_CENTER | GEL_ALIGN_MIDDLE ),
		Color( GEL_RGB_WHITE )
	{	
		switch ( Type ) {
			case Gel::GLO_IMAGE: {
				AtlasUID = Gel::AtlasPool.LoadAndIndex( _Text, &ArtIndex );
				break;
			}
			case Gel::GLO_TEXT: {
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
	inline void SetFontSize( const Real _Size ) {
		FontSize = _Size;
	}
	inline void SetFontAlign( const int _Align ) {
		FontAlign = _Align;
	}

public:	
	inline void Draw( const Matrix4x4& Mat, const NodeType& Node ) const {
		switch ( Type ) {
			case Gel::GLO_BOX: {
				gelDrawRectFill( 
					Mat,
					Vector2D(Node.GetPos().x,Node.GetPos().y).ToVector3D(), 
					Vector2D(Node.GetShape().x, Node.GetShape().y), 
					Color
				);

				break;
			}
			case Gel::GLO_IMAGE: {
				Matrix4x4 MyMat = Matrix4x4::ScalarMatrix( Vector2D(Node.GetShape().x, Node.GetShape().y) );
				MyMat *= Matrix4x4::TranslationMatrix( Vector2D(Node.GetCenterPos().x, Node.GetCenterPos().y) );
				MyMat *= Mat;
				
				GelAtlas& Atlas = Gel::AtlasPool[AtlasUID];
				Atlas.Draw( MyMat, ArtIndex );
				
				break;
			}
			case Gel::GLO_TEXT: {
				Gel::FontPool[FontUID].printf( 
					Mat, 
					Vector2D(Node.GetCenterPos().x, Node.GetCenterPos().y).ToVector3D(), 
					FontSize, 
					Color,
					FontAlign,
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

// - ------------------------------------------------------------------------------------------ - //
typedef GlayLayout<GelLayoutNode> GelLayout;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELLAYOUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
