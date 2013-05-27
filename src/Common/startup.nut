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
const QK_ENGINE_NONE 		= 0;		// Normal linear script (manual gameloop and frameskipping) //
const QK_ENGINE_STEPDRAW	= 1;		// Init, Step, Draw gameloop with frameskipping //
//const QK_ENGINE_PLATFORMER	= 2;	// Platformer game engine with messaging //
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
