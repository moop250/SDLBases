#ifndef APPSTATE_CLASS_HPP
# define APPSTATE_CLASS_HPP

#include "main.hpp"
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <string>

class AppState  {
	private:
		SDL_Window		*window_;
		SDL_Renderer	*renderer_;
		SDL_Texture		*texture_;
		SDL_Surface		*screenSurface_;
		SDL_Surface		*imgSurface_;
		bool			destroyed_;
		int				windowHieght_;
		int				windowWidth_;
	
	public:
	/*  Constructors and Destructors  */
		AppState();
		AppState(const AppState &src);
		AppState& operator=(const AppState &src);
		~AppState();

		bool			init();
		bool			loadMedia(const std::string &path);
		SDL_Window		*getWindow();
		SDL_Renderer	*getRenderer();
		SDL_Texture		*getTexture();
		SDL_Surface		*getScreenSurface();
		SDL_Surface		*getImgSurface();
		void			destroyAppState();
};


#endif
