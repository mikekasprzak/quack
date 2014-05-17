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
class GelLayoutNodeData {
	typedef GelLayoutNodeData thistype;
	typedef GlayNode<thistype> NodeType;
public:
	int Type;	// What kind of Node this is //
	
	GelAtlasPool::UID	AtlasUID;
	int 				ArtIndex;
	
	std::string			Text;
	GelColor			Color;
	GlayPoint			Scale;

	GelFontPool::UID	FontUID;		// NOTE: Could be merged with AtlasUID, if I really wanted //
	float				FontSize;
	int					FontAlign;
public:
	inline GelLayoutNodeData() :
		Type( Gel::GLO_NULL ),
		AtlasUID( 0 ),
		ArtIndex( 0 ),
		Scale(GLAY_1,GLAY_1),
		FontUID( 0 ),
		FontSize( 12 ),
		FontAlign( GEL_ALIGN_CENTER | GEL_ALIGN_MIDDLE ),
		Color( GEL_RGB_WHITE )
	{
	}
	
	inline GelLayoutNodeData( const int _Type, const char* const _Text = "" ) :
		Type( _Type ),
		AtlasUID( 0 ),
		ArtIndex( 0 ),
		Scale(GLAY_1,GLAY_1),
		Text( _Text ),
		FontUID( 0 ),
		FontSize( 12 ),
		FontAlign( GEL_ALIGN_CENTER | GEL_ALIGN_MIDDLE ),
		Color( GEL_RGB_WHITE )
	{	
		PostLoad();
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
	inline void SetScale( const GlayNum _SizeX = GLAY_1, const GlayNum _SizeY = GLAY_1 ) {
		Scale.x = _SizeX;
		Scale.y = _SizeY;
	}

	inline void SetFontSize( const float _Size ) {
		FontSize = _Size;
	}
	inline void SetFontAlign( const int _Align ) {
		FontAlign = _Align;
	}
	
	inline void SetText( const char* _Text ) {
		Text = _Text;
	}
	inline void SetArt( const char* _Art ) {
		Text = _Art;
	}
	
	
	inline void PostLoad() {
		switch ( Type ) {
			case Gel::GLO_IMAGE: {
				AtlasUID = Gel::AtlasPool.LoadAndIndex( Text.c_str(), &ArtIndex );
				break;
			}
//			case Gel::GLO_TEXT: {
//				Text = _Text;
//				break;
//			}
		}		
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
//				Matrix4x4 MyMat = Matrix4x4::ScalarMatrix( Vector2D(Node.GetShape().x, Node.GetShape().y) );
				Matrix4x4 MyMat = Matrix4x4::ScalarMatrix( Vector2D(Scale.x, Scale.y) );
				MyMat *= Matrix4x4::TranslationMatrix( Vector2D(Node.GetCenterPos().x, Node.GetCenterPos().y) );
				MyMat *= Mat;
				
				GelAtlas& Atlas = Gel::AtlasPool[AtlasUID];
				Atlas.Draw( MyMat, ArtIndex, Color );
				
				break;
			}
			case Gel::GLO_TEXT: {
				Gel::FontPool[FontUID].printf( 
					Mat, 
					Vector2D(Node.GetCenterPos().x, Node.GetCenterPos().y).ToVector3D(), 
					Real(FontSize), 
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
typedef GlayLayout<GelLayoutNodeData> GelLayout;
typedef GlayNode<GelLayoutNodeData> GelLayoutNode;
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GELLAYOUT_H__ //
// - ------------------------------------------------------------------------------------------ - //
