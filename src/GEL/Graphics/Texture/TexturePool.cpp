// - ------------------------------------------------------------------------------------------ - //
#ifdef PRODUCT_LEGACY_SMILES
// - ------------------------------------------------------------------------------------------ - //
#include <Debug/GelDebug.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Graphics/Graphics.h>
#include <Graphics/GelTexture.h>
#include "TexturePool.h"
// - ------------------------------------------------------------------------------------------ - //
#include <map>
#include <vector>
#include <string>
// - ------------------------------------------------------------------------------------------ - //
#include "Pool_String.h"
// - ------------------------------------------------------------------------------------------ - //
#include <Core/GelDirectory.h>
// - ------------------------------------------------------------------------------------------ - //
#include "PVRTexture_Load.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#ifdef _MSC_VER
#define TEXTURE_POOL_SLASH "\\"
#else // _MSC_VER //
#define TEXTURE_POOL_SLASH "/"
#endif // _MSC_VER //
// - ------------------------------------------------------------------------------------------ - //
#if !defined(USES_IOS) && !defined(USES_WINDOWSMOBILE)
extern char AppBaseDir[];
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL
extern void MessageLoop();
#endif // USES_SDL //
// - ------------------------------------------------------------------------------------------ - //

#ifdef PRODUCT_PALM
#define HACK_TEXTURE5_GLITCH
#endif // PRODUCT_PALM //

// - ------------------------------------------------------------------------------------------ - //
namespace TexturePool {
// - ------------------------------------------------------------------------------------------ - //
	int AllocCount;
	int AllocSum;

#ifdef HACK_TEXTURE5_GLITCH	
	unsigned int PalmGlitch;
#endif // HACK_TEXTURE5_GLITCH //

	// - -------------------------------------------------------------------------------------- - //
	class GelTexture_Instance {
	public:
		std::string FileName;
		GelTexture Texture;

	public:
		GelTexture_Instance()
		{
		}
		
		GelTexture_Instance( const char* _FileName ) :
			FileName( _FileName )
		{
			// Note: I did not pass anythnig to Texture, that would cause a load //
		}
		
		void Load( std::string Prefix ) {
			Prefix += FileName;
			Log( "* Caching %s...\n", Prefix.c_str() );
			Texture.Load( Prefix.c_str() );
		}

		void Free() {
			Texture.Free();
		}
	};
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Members //
	std::string FilePrefix;	
	std::vector< GelTexture_Instance > TextureInfo;
	std::map<std::string, GelTextureID> TextureLookup;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	void Init( const char* BaseDirectory ) {		
		GelTexture::Init();
		
#ifdef HACK_TEXTURE5_GLITCH
		PalmGlitch = 0;
#endif // HACK_TEXTURE5_GLITCH //
		
		// Create a string containing the base filename directory //
		{
			// If an empty string (i.e. first character is terminator) //
			if ( BaseDirectory[0] == 0 )
				FilePrefix = AppBaseDir;
			else
				FilePrefix = std::string( AppBaseDir ) + BaseDirectory;

			// Store the prefix (without trailing slash.  Slash will be part of search strings) //

			VVLog("FilePrefix: %s\n", FilePrefix.c_str());
		}
		
		{
			// Initalize the TextureInfo //
			TextureInfo.clear();
			TextureInfo.push_back( GelTexture_Instance() );	// Dummy //
			
			// Initalize the TextureLookup //
			TextureLookup.clear();
		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void AddDirectory( const char* Directory ) {
		// TODO: Be sure to include a beginning "/" in the populated filenames //
		// TODO: Be sure to remove file extensions in the search query //
		std::string ReadDir = FilePrefix;
		if ( Directory[0] != 0 ) {
			ReadDir += Directory;
		}
		//ReadDir += TEXTURE_POOL_SLASH;
		
		GelDirectory* Dir = new_GelDirectory( ReadDir.c_str() );
		Log( "Adding Directory \"%s\" (%i Total)\n", ReadDir.c_str(), size_GelDirectory( Dir ) );
		
		for( size_t idx = 0; idx < size_GelDirectory( Dir ); idx++ ) {
			std::string SlashString = TEXTURE_POOL_SLASH;
			SlashString += index_GelDirectory( Dir, idx );
			TextureInfo.push_back( GelTexture_Instance( (std::string(Directory) + SlashString).c_str() ) );
			
			std::string NoExt = NoExtensions( SlashString );
			TextureLookup[ NoExt.c_str() ] = TextureInfo.size() - 1;
			
			VLog( "* %s (%i) [Pattern: %s]\n", SlashString.c_str(), idx, NoExt.c_str() );
		}
		
		delete_GelDirectory( Dir );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	GelTextureID FindID( const char* FileName ) {
		// Search the map for the specific pattern //
		std::map<std::string, GelTextureID>::iterator SearchIterator = TextureLookup.find( FileName );
		Log( "+ Searching for %s\n", FileName );
		
		// If it was found, return the Id //
		if ( SearchIterator != TextureLookup.end() ) {
			Log( "- %s found in lookup cache!\n", FileName );
			return SearchIterator->second;
		}

		// Linear pattern matching search (if it contains the pattern, instead of exact match) //
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			// Linear test strings if they contain the pattern passed //
			if ( TextureInfo[idx].FileName.find( FileName ) != std::string::npos ) {
				Log( "- Found %s!\n", FileName );
				return idx;
			}
		}
		Log( "- %s not found!!\n", FileName );
		
		// Otherwise, no file was found.  Return the dummy Id (0). //
		return 0;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	void Set( const GelTextureID Texture ) {
		TextureInfo[ Texture ].Texture.Bind( 0 );
		
//		glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].Texture.Handle );
////		if ( Texture != 0 ) {
////			if ( TextureInfo[ Texture ].Texture.Handle == 0 ) {
////				LoadTexture( Texture );
////			}
////			
////			glBindTexture( GL_TEXTURE_2D, TextureInfo[ Texture ].Texture.Handle );
////		}
////		else {
////			glBindTexture( GL_TEXTURE_2D, 0 );
////		}
	}
	// - -------------------------------------------------------------------------------------- - //
	void LoadTexture( const GelTextureID Texture ) {
		// Bail if the dummy texture //
		if ( Texture == 0 )
			return;
		
		// If GL Texture is set, activate it //
		if ( TextureInfo[ Texture ].Texture.Handle ) {
			Set( Texture );		
			return;
		}
						
		// TODO: If there is uncompressed data, load it in to memory //
		// TODO: If there is compressed data, decompress it, then load in to memory //
		
		// If there is only a filename, load it //
		{
			TextureInfo[ Texture ].Load( FilePrefix );

#ifdef HACK_TEXTURE5_GLITCH
			if ( TextureInfo[ Texture ].Texture.Handle == 5 ) {
				Log( "** WebOS! ** : Working around 'Texture 5' glitch...\n" );
				PalmGlitch = TextureInfo[ Texture ].Texture.Handle;				
				TextureInfo[ Texture ].Load( FilePrefix );
			}
#endif // HACK_TEXTURE5_GLITCH //
		}
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	GelTextureID Load( const char* FileName ) {
#ifdef USES_SDL
		MessageLoop();
#endif // USES_SDL //

		// Bail if we're in the middle of shutting down //
		if ( System::ShutdownGame || System::CloseButtonPressed ) {
			Log( "* Shutdown Detected!  Aborting Texture Load...\n");
			return 0;
		}

		// Search for ID based on input string //
		GelTextureID Texture = FindID( FileName );
		
		// Loaded, so cache the texture in memory //
		LoadTexture( Texture );
		
		// Return the Id //
		return Texture;	
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Free( const GelTextureID Texture ) {
		TextureInfo[ Texture ].Free();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	void Exit() {
		GelTexture::LogAllocations();
		
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			//Free( idx );
			TextureInfo[ idx ].Free();
		}
		
#ifdef HACK_TEXTURE5_GLITCH
		if ( PalmGlitch != 0 ) {
			glDeleteTextures( 1, (const GLuint*)&PalmGlitch );
		}
#endif // HACK_TEXTURE5_GLITCH //
		
		GelTexture::Exit();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Free textures so we can reload them in to the new/current OpenGL Context //
	void ReleaseTextures() {
		Exit();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Reload all the previously released textures //
	void ReloadTextures() {
		for ( size_t idx = 0; idx < TextureInfo.size(); idx++ ) {
			LoadTexture( idx );
		}
	}
// - ------------------------------------------------------------------------------------------ - //
#undef TEXTURE_POOL_SLASH
// - ------------------------------------------------------------------------------------------ - //
}; // namespace TexturePool //
// - ------------------------------------------------------------------------------------------ - //
#endif // PRODUCT_LEGACY_SMILES //
// - ------------------------------------------------------------------------------------------ - //
