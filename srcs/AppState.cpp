#include "../incl/AppState.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <iostream>

AppState::AppState() : destroyed_(false) {

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS)) {
		std::cerr << "SDL_Init error: " << SDL_GetError() << std::endl;
		exit(SDL_APP_FAILURE);
	}

	if (!SDL_CreateWindowAndRenderer("test", WINDOW_WIDTH, WINDOW_HIGHT, 0, &this->window_, &this->renderer_)) {
		std::cerr << "SDL_CreateWindowAndRenderer error: " << SDL_GetError() << std::endl;
		SDL_Quit();
	}

	this->texture_ = SDL_CreateTexture(this->renderer_, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HIGHT);
}

AppState::AppState(const AppState &src) :
	destroyed_(src.destroyed_), renderer_(src.renderer_), window_(src.window_) {}

AppState& AppState::operator=(const AppState &src) {
	if (&src != this) {
		this->destroyed_ = src.destroyed_;
		this->renderer_ = src.renderer_;
		this->window_ = src.window_;
	}
	return *this;
}

AppState::~AppState() {
	if (!this->destroyed_)
		destroyAppState();
	SDL_Quit();
}

/*  Getters and Setters  */

SDL_Window	*AppState::getWindow() {
	return this->window_;
}

SDL_Renderer	*AppState::getRenderer() {
	return this->renderer_;
}

SDL_Texture	*AppState::getTexture() {
	return this->texture_;
}

/*  Member Functions  */

void AppState::destroyAppState() {
	if (this->destroyed_)
		return ;
	SDL_DestroyRenderer(this->renderer_);
	SDL_DestroyWindow(this->window_);
	SDL_DestroyTexture(this->texture_);
	this->destroyed_ = true;
}
