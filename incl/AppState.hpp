#ifndef APPSTATE_CLASS_HPP
# define APPSTATE_CLASS_HPP

#include "main.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

class AppState  {
	private:
		SDL_Window		*window_;
		SDL_Renderer	*renderer_;
		SDL_Texture		*texture_;
		bool			destroyed_;
	
	public:
	/*  Constructors and Destructors  */
		AppState();
		AppState(const AppState &src);
		AppState& operator=(const AppState &src);
		~AppState();

		SDL_Window		*getWindow();
		SDL_Renderer	*getRenderer();
		SDL_Texture		*getTexture();
		void			destroyAppState();
};


#endif
