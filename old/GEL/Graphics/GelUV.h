// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_GRAPHICS_GELUV_H__
#define __GEL_GRAPHICS_GELUV_H__
// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_GEL) && !defined(NO_PLATFORM_H)
#include "../Platform.h"
#endif // USES_GEL && NO_PLATFORM_H //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#if defined(USES_OPENGL) || defined(USES_OPENGLES)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/OpenGL/GelUV.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_D3D9)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/D3D9/UV.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PSP)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/PSP/UV.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_PS3)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/PS3/UV.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_WII)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/Wii/UV.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_DSI)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/DSi/UV.h"
// - ------------------------------------------------------------------------------------------ - //
#elif defined(USES_3DS)
// - ------------------------------------------------------------------------------------------ - //
#include "Native/3DS/UV.h"
// - ------------------------------------------------------------------------------------------ - //
#endif // USES //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_GRAPHICS_GELUV__ //
// - ------------------------------------------------------------------------------------------ - //
