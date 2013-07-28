// - ------------------------------------------------------------------------------------------ - //
#ifdef USES_SDL2
// - ------------------------------------------------------------------------------------------ - //
#ifndef __GEL_EXTENSIONS_SDL2_H__
#define __GEL_EXTENSIONS_SDL2_H__
// - ------------------------------------------------------------------------------------------ - //
inline const char* SDL_WindowEventName( Uint8 EventName ) {
	switch( EventName ) {
		case SDL_WINDOWEVENT_NONE:			return "SDL_WINDOWEVENT_NONE";
		case SDL_WINDOWEVENT_SHOWN:			return "SDL_WINDOWEVENT_SHOWN";
		case SDL_WINDOWEVENT_HIDDEN:		return "SDL_WINDOWEVENT_HIDDEN";
		case SDL_WINDOWEVENT_EXPOSED:		return "SDL_WINDOWEVENT_EXPOSED";
		case SDL_WINDOWEVENT_MOVED:			return "SDL_WINDOWEVENT_MOVED";
		case SDL_WINDOWEVENT_RESIZED:		return "SDL_WINDOWEVENT_RESIZED";
		case SDL_WINDOWEVENT_SIZE_CHANGED:	return "SDL_WINDOWEVENT_SIZE_CHANGED";
		case SDL_WINDOWEVENT_MINIMIZED:		return "SDL_WINDOWEVENT_MINIMIZED";
		case SDL_WINDOWEVENT_MAXIMIZED:		return "SDL_WINDOWEVENT_MAXIMIZED";
		case SDL_WINDOWEVENT_RESTORED:		return "SDL_WINDOWEVENT_RESTORED";
		case SDL_WINDOWEVENT_ENTER:			return "SDL_WINDOWEVENT_ENTER";
		case SDL_WINDOWEVENT_LEAVE:			return "SDL_WINDOWEVENT_LEAVE";
		case SDL_WINDOWEVENT_FOCUS_GAINED:	return "SDL_WINDOWEVENT_FOCUS_GAINED";
		case SDL_WINDOWEVENT_FOCUS_LOST:	return "SDL_WINDOWEVENT_FOCUS_LOST";
		case SDL_WINDOWEVENT_CLOSE:			return "SDL_WINDOWEVENT_CLOSE";
	};
	return "SDL_WINDOWEVENT_???";
}
// - ------------------------------------------------------------------------------------------ - //
#endif // __GEL_EXTENSIONS_SDL2_H__ //
// - ------------------------------------------------------------------------------------------ - //
#endif // USES_SDL2 //
// - ------------------------------------------------------------------------------------------ - //
