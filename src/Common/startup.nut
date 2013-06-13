// - -------------------------------------------------------------------------------------------------------------- - //
// COMMON //


const QK_DISPLAY_DEFAULT	= -1;

// CONTEXT TRANSFORM (formerly DISPLAY SCALING) //
const QK_CT_NONE			= 0;		// 1:1 positions to pixels (use your own matrix) //
const QK_CT_RIGID			= 1;		// Viewport is scaled up rigidly (pixels) to fit screen and aspect ratio //
const QK_CT_SMOOTH			= 2;		// Viewport is scaled up smoothly to fit the screen and aspect ratio //
const QK_CT_FILL			= 3;		// Unlikely what anyone wants, but Viewport scaled to fill entire screen //
// NOTE: Smiles style orientation change is probably not supported here? Wide Tall? //

// ENGINES //
const QK_ENGINE_NONE 		= 0;		// Linear script. Exits once the last script is executed. No Reloading supported. //
const QK_ENGINE_MAIN		= 1;		// Calls Main function, exits at end of it (manual gameloop and frameskipping) //
const QK_ENGINE_STEPDRAW	= 2;		// Step and Draw gameloop with frameskipping //
//const QK_ENGINE_PLATFORMER	= 2;	// Platformer game engine with messaging //

// RUNNERS (Not devices, unless it's a one-shot) //
const QK_RUNNER_NULL		= 0;
const QK_RUNNER_SDL			= 1;		// Windows, Linux, Mac
const QK_RUNNER_MARMALADE	= 2;		// iOS, Android, Blackberry
const QK_RUNNER_HTML5		= 3;		// Chrome, Firefox, IE11
const QK_RUNNER_WINRT		= 4;		// Windows 8, Windows RT, Windows Phone 8, Xbox One

const QK_RUNNER_3DS			= 16;
const QK_RUNNER_WII_U		= 17;
const QK_RUNNER_PS3			= 18;
const QK_RUNNER_PS_VITA		= 19;
const QK_RUNNER_PS4			= 20;
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function qkGetRunner() {
	return QK_RUNNER_NULL; // TODO //
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// Contexts are output displays. // 
// Typically there is only ever 1, but PC's can have multiple Windows/Screens, and browsers multiple contexts. //
// - -------------------------------------------------------------------------------------------------------------- - //
function qkGetDefaultContext() {
	return 0;
}
// - -------------------------------------------------------------------------------------------------------------- - //
function qkSetContext( ctx ) {
	// TODO //
}
function qkGetContext() {
	// TODO //
	return 0;
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
// Opens a new Window. Window can fill an entire screen. Can also specify an explicit screen (or default is the next) //
function qkNewContext( w, h, FullScreen = true, UseDisplay = QK_DISPLAY_DEFAULT ) {
	// Call Explicitly on PC Only! //
}
// - -------------------------------------------------------------------------------------------------------------- - //
// Attatch to an existing WebGL context //
function qkBindContext( id ) {
	// Call Explicitly on browser only! //
}
// - -------------------------------------------------------------------------------------------------------------- - //

error("Yes");
