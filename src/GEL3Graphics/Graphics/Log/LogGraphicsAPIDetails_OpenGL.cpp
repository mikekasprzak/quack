// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_OPENGL_LIB
// - ------------------------------------------------------------------------------------------ - //
#include <Lib/Lib.h>
#include <API/API_OpenGL.h>
#include <Graphics/Graphics.h>
// - ------------------------------------------------------------------------------------------ - //
// TODO: Create a list of all extensions that match OpenGL ES 2 and 3, and do a check of the current GPU Vs. //
//  ... though it may not be necessary, as any computer newer than this one will match the spec. //
// - ------------------------------------------------------------------------------------------ - //
// Extensions Found in OpenGL ES 2.0 //
const char* const OpenGLES2Extensions[] = {
	"",
	0
};
// - ------------------------------------------------------------------------------------------ - //
// Extensions Found in OpenGL ES 3.0 //
const char* const OpenGLES3Extensions[] = {
	"",
	0
};
// - ------------------------------------------------------------------------------------------ - //
void gelLogGraphicsAPIDetails() {
	Log( "" );
	Log( "-=- Khronos Libraries -=-" );

	#ifdef USES_GLEE
	Log( "* Using GLEE" );
	#endif // USES_GLEE //
	#ifdef USES_GLEE
	Log( "* Using GLEW" );
	#endif // USES_GLEW //

	Log( "" );
	
	#ifdef USES_WGL
	{
		Log( "-=- WGL -=-" );
		PROC wglGetExtString = wglGetProcAddress("wglGetExtensionsStringARB");
		if ( wglGetExtString ) {
			char* Extensions = ((char*(__stdcall*)(HDC))wglGetExtString)( wglGetCurrentDC() );
			Log( "WGL Extensions (ARB):\n%s", Extensions );
		}
		else {
			PROC wglGetExtString2 = wglGetProcAddress("wglGetExtensionsStringEXT");
			if ( wglGetExtString2 ) {
				char* Extensions = ((char*(__stdcall*)(HDC))wglGetExtString2)( wglGetCurrentDC() );
				Log( "WGL Extensions (EXT, no ARB):\n%s", Extensions );
			}
		}
		Log( "" );
	}
	#endif // USES_WGL //

//	#ifdef USES_GLX
//	{
//		Log( "-=- GLX -=-" );
//		Log( "" );
//	}
//	#endif // USES_GLX //
//
//	#ifdef USES_CGL
//	{
//		Log( "-=- CGL -=-" );
//		Log( "" );
//	}
//	#endif // USES_CGL //

//	#ifdef USES_EGL
//	{
//		Log( "-=- EGL -=-" );
//		// TODO: The following will not work (old EGLProxy code) //
//		//		 To fix this, I'm going to need an SDL way of querying EGL vars. //
//		extern EGLDisplay g_eglDisplay;
//		Log( "EGL Version: %s", eglQueryString(g_eglDisplay, EGL_VERSION) );
//		Log( "Driver Vendor: %s", eglQueryString(g_eglDisplay, EGL_VENDOR) );
//		Log( "Client APIs: %s", eglQueryString(g_eglDisplay, EGL_CLIENT_APIS) );
//		Log( "Extensions: %s", eglQueryString(g_eglDisplay, EGL_EXTENSIONS) );
//		Log( "" );
//	}
//	#endif // USES_EGL //
	
	// Get OpenGL Information Strings //
	const char* OpenGLVendor = (const char*)glGetString( GL_VENDOR );
	const char* OpenGLRenderer = (const char*)glGetString( GL_RENDERER );
	const char* OpenGLVersion = (const char*)glGetString( GL_VERSION );
	const char* OpenGLExtensions = (const char*)glGetString( GL_EXTENSIONS );		

	Log( "-=- OpenGL -=-" );
	Log( "OpenGL Vendor: %s", OpenGLVendor );
	Log( "OpenGL Renderer: %s", OpenGLRenderer );
	Log( "OpenGL Version: %s", OpenGLVersion );
#ifdef USES_SHADERS
	Log( "OpenGL Shading Language Version: %s", glGetString( GL_SHADING_LANGUAGE_VERSION ) );
#endif // USES_SHADERS //
	Log( "OpenGL Extensions:\n%s", OpenGLExtensions );
	Log( "" );
	
//	if ( find_String( "GL_ARB_half_float_vertex", OpenGLExtensions ) || find_String( "GL_OES_vertex_half_float", OpenGLExtensions ) ) {
//		Log( "* Half Float Extension Available!" );
//	}
//	else {
//		Log( "! WARNING! Half Float Extension Unavailable!" );
//	}
//
//	Log( "" );
	
	{
		int Dummy;	// Dummy Value for things we don't want to remember //
			
		// GL Environment Settings //
		Dummy = 0;
		glGetIntegerv( GL_DEPTH_BITS, (GLint*)&Dummy );
		Log( "GL_DEPTH_BITS: %i", Dummy );
	
		Dummy = 0;
		glGetIntegerv( GL_STENCIL_BITS, (GLint*)&Dummy );
		Log( "GL_STENCIL_BITS: %i", Dummy );
		
		Log( "" );
	
		{
			int Dummy2[2];
			Dummy2[0] = 0;
			Dummy2[1] = 0;
			glGetIntegerv( GL_MAX_VIEWPORT_DIMS, (GLint*)Dummy2 );
			Log( "GL_MAX_VIEWPORT_DIMS: %i, %i", Dummy2[0], Dummy2[1] );
		}
	
		Dummy = 0;
		glGetIntegerv( GL_MAX_RENDERBUFFER_SIZE, (GLint*)&Dummy );
		Log( "GL_MAX_RENDERBUFFER_SIZE: %i", Dummy );
	
		Dummy = 0;
		glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&Dummy );
		Log( "GL_MAX_TEXTURE_SIZE: %i", Dummy );
	
		Dummy = 0;
		glGetIntegerv( GL_MAX_CUBE_MAP_TEXTURE_SIZE, (GLint*)&Dummy );
		Log( "GL_MAX_CUBE_MAP_TEXTURE_SIZE: %i", Dummy );
	
		Dummy = 0;
		glGetIntegerv( GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*)&Dummy );
		Log( "GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS: %i", Dummy );
			
		Log( "" );
		Log( "TERMS:" );
		Log( "* Attributes are Vertex Streams." );
		Log( "* Varyings are interpolated values from VS to FS." );
		Log( "* Uniforms are global variables/constants." );
		Log( "" );
	
		// TODO: Log more data. http://www.opengl.org/sdk/docs/man/xhtml/glGet.xml	
		Dummy = 0;
		glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, (GLint*)&Dummy );
		Log( "GL_MAX_VERTEX_ATTRIBS: %i    (Max number of generic 4 component Vertex Attributes. [Minimum 8])", Dummy );
	
		#ifdef USES_OPENGL_3_FAMILY
		Dummy = 0;
		glGetIntegerv( GL_MAX_VARYING_VECTORS, (GLint*)&Dummy );
		if ( Dummy == 0 ) {
			glGetIntegerv( GL_MAX_VARYING_COMPONENTS, (GLint*)&Dummy );
			Log( "GL_MAX_VARYING_COMPONENTS: %i [%i]    (Max number of interpolated fp values. [Minimum 8])", Dummy, Dummy / 4 );
		}
		else
			Log( "GL_MAX_VARYING_VECTORS: %i    (Max number of 4 element interpolated fp values. [Minimum 8])", Dummy );
		#endif // USES_OPENGL_3_FAMILY //
	
		#ifdef USES_OPENGL_3_FAMILY
		Dummy = 0;
		glGetIntegerv( GL_MAX_VERTEX_UNIFORM_VECTORS, (GLint*)&Dummy );
		if ( Dummy == 0 ) {
			glGetIntegerv( GL_MAX_VERTEX_UNIFORM_COMPONENTS, (GLint*)&Dummy );
			Log( "GL_MAX_VERTEX_UNIFORM_COMPONENTS: %i [%i]    (Max number of fp, int, bool values. [Minimum 128])", Dummy, Dummy / 4 );
		}
		else 
			Log( "GL_MAX_VERTEX_UNIFORM_VECTORS: %i    (Max number of 4 element fp, int, bool values. [Minimum 128])", Dummy );
		#endif // USES_OPENGL_3_FAMILY //
	
	
		#ifdef USES_OPENGL_3_FAMILY
			// http://www.opengl.org/wiki/Uniform_Buffer_Object
			Dummy = 0;
			glGetIntegerv( GL_MAX_VERTEX_UNIFORM_BLOCKS, (GLint*)&Dummy );
			Log( "GL_MAX_VERTEX_UNIFORM_BLOCKS: %i    (Max number of Uniform Blocks per Vertex Shader. [Minimum 12])", Dummy );
		#endif // USES_OPENGL_3_FAMILY //
	
		Dummy = 0;
		glGetIntegerv( GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, (GLint*)&Dummy );
		Log( "GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS: %i    (Max number of TUs accessable from Vertex Shaders. [Minimum 0])", Dummy );
	
		Log( "" );
		
		#ifdef USES_OPENGL_3_FAMILY
		Dummy = 0;
		glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_VECTORS, (GLint*)&Dummy );
		if ( Dummy == 0 ) {
			glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, (GLint*)&Dummy );
			Log( "GL_MAX_FRAGMENT_UNIFORM_COMPONENTS: %i [%i]    (Max number of fp, int, bool values. [Minimum 16])", Dummy, Dummy / 4 );
		}
		else
			Log( "GL_MAX_FRAGMENT_UNIFORM_VECTORS: %i    (Max number of 4 element fp, int, bool values. [Minimum 16])", Dummy );
		#endif // USES_OPENGL_3_FAMILY //
	
		#if defined(USES_OPENGL3) || defined(USES_OPENGL_ES3)
			// http://www.opengl.org/wiki/Uniform_Buffer_Object
			Dummy = 0;
			glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_BLOCKS, (GLint*)&Dummy );
			Log( "GL_MAX_FRAGMENT_UNIFORM_BLOCKS: %i    (Max number of Uniform Blocks per Fragment Shader. [Minimum 12])", Dummy );
		#endif // defined(USES_OPENGL3) || defined(USES_OPENGLES3) //
	
		Dummy = 0;
		glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&Dummy );
		Log( "GL_MAX_TEXTURE_IMAGE_UNITS: %i    (Max number of TUs accessable from Fragment Shaders. [Minimum 8])", Dummy );
	
		Log( "" );
		
		// TODO: Detect PowerVR based Intel GPUs //
		// TODO: Detect CPUs //

//	// Check both the Vendor and the Renderer, since Intel subcontracted the Linux driver to Tungsten. //
//	// Intel GMA 950's have only enough texture cache for 1024x1024 textures, so making that the limit //
//	if ( find_String( "Intel", OpenGLVendor ) || find_String( "Intel", OpenGLRenderer ) ) {
//		Log( "* Found Intel GPU..." );
//		System::GPUVendor = System::GPU_INTEL;
//#ifndef PRODUCT_NO_INTEL_FIX
//		if ( System::MaxTextureSize == 2048 ) {
//			Log( "* Limiting textures to 1024x1024 (was %i) -- GMA Fix", System::MaxTextureSize );
//			System::MaxTextureSize = 1024;
//		}
//#endif // PRODUCT_NO_INTEL_FIX //
//	}
//	else if ( find_String( "Imagination", OpenGLVendor ) || find_String( "PowerVR", OpenGLRenderer ) ) {
//		Log( "* Found PowerVR (Imagination Technology) GPU..." );
//		System::GPUVendor = System::GPU_POWERVR;
//	}
//	else if ( find_String( "ARM", OpenGLVendor ) || find_String( "Mali", OpenGLRenderer ) ) {
//		Log( "* Found ARM GPU..." );
//		System::GPUVendor = System::GPU_ARM;
//		if_Log( find_String( "200", OpenGLRenderer ), "! Warning! Mali 200 devices do not support GL_OES_VERTEX_HALF_FLOAT" );
//		if_Log( find_String( "400", OpenGLRenderer ), "! Warning! Mali 400 devices do not support GL_OES_VERTEX_HALF_FLOAT" );
//	}
//	else if ( find_String( "NVIDIA", OpenGLVendor ) || find_String( "NVIDIA", OpenGLRenderer ) ) {
//		Log( "* Found NVIDIA GPU..." );
//		System::GPUVendor = System::GPU_NVIDIA;
//	}
//	else if ( find_String( "ATI", OpenGLVendor ) || find_String( "ATI", OpenGLRenderer ) ) {
//		Log( "* Found ATI (AMD) GPU..." );
//		System::GPUVendor = System::GPU_ATI;
//	}
//	else if ( find_String( "AMD", OpenGLVendor ) || find_String( "AMD", OpenGLRenderer ) ) {
//		Log( "* Found AMD (ATI) GPU..." );
//		System::GPUVendor = System::GPU_AMD;
//	}
//	else if ( find_String( "Qualcomm", OpenGLVendor ) || find_String( "Adreno", OpenGLRenderer ) ) {
//		Log( "* Found Qualcomm GPU..." );
//		System::GPUVendor = System::GPU_QUALCOMM;
//	}
//	else if ( find_String( "Vivante", OpenGLVendor ) || find_String( "GC", OpenGLRenderer ) ) {
//		Log( "* Found Vivante GPU..." );
//		System::GPUVendor = System::GPU_VIVANTE;
//	}
//	else if ( find_String( "Hisilicon", OpenGLVendor ) || find_String( "Immersion", OpenGLRenderer ) ) {
//		Log( "* Found HiSilicon Technologies (Huawei) GPU..." );
//		System::GPUVendor = System::GPU_HISILICON;
//	}
//	else if ( find_String( "Broadcom", OpenGLVendor ) || find_String( "VideoCore", OpenGLRenderer ) ) {
//		Log( "* Found Broadcom GPU..." );
//		System::GPUVendor = System::GPU_BROADCOM;
//	}
//	else if ( find_String( "ZiiLABS", OpenGLVendor ) || find_String( "ZMS", OpenGLRenderer ) ) {
//		Log( "* Found ZiiLABS GPU..." );
//		System::GPUVendor = System::GPU_ZIILABS;
//		Log( "! Warning! ZiiLABS devices do not support GL_OES_VERTEX_HALF_FLOAT" );
//	}
//	else if ( find_String( "Advanced", OpenGLVendor ) || find_String( "S", OpenGLRenderer ) ) {
//		// Last, because their company name and GPU names are too generic (S5 Multicore) //
//		Log( "* Found Advanced Graphics Corporation GPU..." );
//		System::GPUVendor = System::GPU_AGC;
//	}
//	else {
//		Log( "* Warning! Unknown GPU Vendor! (%s - %s)", OpenGLVendor, OpenGLRenderer );
//		System::GPUVendor = System::GPU_UNKNOWN;
//	}
//	
//	Log( "" );


		// TODO: Compare versus OpenGL ES 2 and ES 3 spec, the available extensions //
	}
}
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_OPENGL_LIB //
// - ------------------------------------------------------------------------------------------ - //
