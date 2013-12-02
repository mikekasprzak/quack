// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_SYSTEM_GELSCREEN_GELSCREENS_INTERNAL_SDL_NATIVESCREEN_H__
#define __GEL_SYSTEM_GELSCREEN_GELSCREENS_INTERNAL_SDL_NATIVESCREEN_H__
// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#include <API/API_SDL2.h>
#include <API/API_OpenGL.h>
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <Main/Main_Product.h>
// - ------------------------------------------------------------------------------------------ - //
#include "GelScreens.h"
// - ------------------------------------------------------------------------------------------ - //
class GelNativeScreen {
	int Index;					// Stored Index... it's either this or pass it in always //
public:
	SDL_Rect DisplayBounds;		// x,y,w,h of the Actual Display //
	SDL_Rect Bounds;			// x,y,w,h of the Window //
	SDL_Window* pWindow;		// Opaque. No direct access to members. //
	SDL_GLContext GLContext;	// (void*) //
	
	inline GelNativeScreen() :
		Index( 0 ),
		pWindow( 0 ),
		GLContext( 0 )
	{
	}
	
public:
	// Outside Interface. Call these only after creating a Window. //
	inline const int GetWidth() const {
		return Bounds.w;
	}
	inline const int GetHeight() const {
		return Bounds.h;
	}
	inline const int GetX() const {
		return Bounds.x;
	}
	inline const int GetY() const {
		return Bounds.y;
	}
	
	inline const float GetAspectRatio() const {
		return (float)Bounds.h / (float)Bounds.w;
	}


	inline const int GetActualWidth() const {
		return DisplayBounds.w;
	}
	inline const int GetActualHeight() const {
		return DisplayBounds.h;
	}
	inline const int GetActualX() const {
		return DisplayBounds.x;
	}
	inline const int GetActualY() const {
		return DisplayBounds.y;
	}
	
	inline const float GetActualAspectRatio() const {
		return (float)DisplayBounds.h / (float)DisplayBounds.w;
	}
	
	// TODO: Some sort of "IsAvailable" //

public:	
	// Call when you just want the NativeScreen to know it's own bounds //
	inline GelError Init( const int _Index ) {
		Index = _Index;
		
		return_if( GetDisplayBounds() );
		
		return GEL_OK;
	}
	
	// Call when you want to create a Window and Context for this screen //
	inline GelError InitWindow( const int _Index ) {
		Index = _Index;
		
		return_if( GetDisplayBounds() );
		
		if ( NewWindow() ) {
			// This means we failed to create a Window with MSAA //
			Log( "* Trying to create Window again, without MSAA Buffers..." );

			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
			
			return_if( NewWindow() );
		}

		if ( NewGLContext() ) {
			// This means we failed to create a context with MSAA //
			Log( "* Trying to create GLContext again, without MSAA Buffers..." );

			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
			SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);

			// Android doesn't create standalone contexts, so window must be disposed of. //
			return_if( NewWindow() );
			return_if( NewGLContext() );
		}
		
		return GEL_OK;
	}
		
	inline GelError Destroy() {
		return_if( DeleteGLContext() );
		return_if( DeleteWindow() );
		return GEL_OK;
	}
	
	inline const int GetIndex() const {
		return Index;
	}
	
	inline GelError MakeCurrent() { // const?
		return SDL_GL_MakeCurrent( pWindow, GLContext );
	}

	inline GelError Swap() { // const?
		if ( pWindow ) {
			SDL_GL_SwapWindow( pWindow );
		}
		return GEL_OK;
	}
	
	inline GelError UpdateViewport() const {
		glViewport( 0, 0, Bounds.w, Bounds.h );
		
		return GEL_OK;
	}

	inline bool HasWindow() const {
		return pWindow;
	}
	inline bool HasGLContext() const {
		return GLContext;
	}
	
	// Call me inside Resize and Move events so the Bounds are updated correctly //
	inline GelError UpdateBounds() {
		if ( HasWindow() ) {
			SDL_GetWindowPosition( pWindow, &Bounds.x, &Bounds.y );
			SDL_GetWindowSize( pWindow, &Bounds.w, &Bounds.h );
			
			VLog( "** Window %i [%i] Bounds Updated: (%i, %i) (%i, %i)", Index, SDL_GetWindowID(pWindow), Bounds.x, Bounds.y, Bounds.w, Bounds.h );
			return GEL_OK;
		}
		return GEL_ERROR;
	}
		
public:
	inline GelError GetDisplayBounds() {
		return_if( SDL_GetDisplayBounds( Index, &DisplayBounds ) );
		return GEL_OK;
	}
	
	inline GelError NewWindow( const int Width, const int Height ) {
		return_if( DeleteWindow() );
		
		bool FullScreen = (Gel::ScreenScalar == 1.0f);

		pWindow = SDL_CreateWindow(
			FullProductName, 						// Window Title //
			SDL_WINDOWPOS_CENTERED_DISPLAY(Index),	// Window Position X //
			SDL_WINDOWPOS_CENTERED_DISPLAY(Index),	// Window Position Y //
			Width, Height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | (FullScreen ? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_RESIZABLE) | ((FullScreen && (Index==0)) ? SDL_WINDOW_INPUT_GRABBED : 0)
			);
		
		// SDL_WINDOW_BORDERLESS, SDL_WINDOW_RESIZABLE
		
		if ( FullScreen ) {
			return_if_Log( !HasWindow(), "! Error Creating Full Screen Window[%i]: %s", Index, SDL_GetError() );
			Log( "* Full Screen Window %i with ID %i Created (%i,%i)", Index, SDL_GetWindowID( pWindow ), Width, Height );
		}
		else {
			return_if_Log( !HasWindow(), "! Error Creating Window[%i]: %s", Index, SDL_GetError() );
			Log( "* Window %i with ID %i Created (%i,%i)", Index, SDL_GetWindowID( pWindow ), Width, Height );
		}

		return_if( UpdateBounds() );		

//		return_if( MakeCurrent() );
//		return_if( UpdateViewport() );
			
		return GEL_OK;
	}

	// Creates a Window based on the knowledge of the DisplayBounds //
	inline GelError NewWindow() {
		float Scalar = Gel::ScreenScalar;

		return NewWindow( 
			(int)((float)DisplayBounds.w * Scalar),
			(int)((float)DisplayBounds.h * Scalar)
			);
	}

	inline GelError DeleteWindow() {
		if ( HasWindow() ) {
			Log( "* Window %i with ID %i Destroyed", Index, SDL_GetWindowID( pWindow ) );
			SDL_DestroyWindow( pWindow );
			pWindow = 0;
		}
		return (GelError)pWindow; // Should always be zero //
	}
	
	inline GelError NewGLContext() {
		return_if( DeleteGLContext() );
		
		Assert( pWindow == 0, "Window not created before SDL_GL_CreateContext called" );
		
		GLContext = SDL_GL_CreateContext( pWindow );
		
		return_if_Log( GLContext == NULL, "! Error Creating GLContext %i: %i", Index, GLContext );
		Log( "* GLContext %i Created: %i", Index, GLContext );
		
		return_if( MakeCurrent() );
		return_if( UpdateViewport() );
		
		return GEL_OK;
	}
	
	inline GelError DeleteGLContext() {
		if ( HasGLContext() ) {
			Log( "* GLContext %i Destroyed: %i", Index, GLContext );
			SDL_GL_DeleteContext( GLContext );
			GLContext = 0;
		}
		return (GelError)GLContext;	// Should always be zero //
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_SYSTEM_GELSCREEN_GELSCREENS_INTERNAL_SDL_NATIVESCREEN_H__ //
// - ------------------------------------------------------------------------------------------ - //
