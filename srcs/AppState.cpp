#include "../incl/AppState.hpp"
#include <SDL3/SDL_error.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_video.h>
#include <cstdlib>
#include <iostream>

AppState::AppState() : destroyed_(false), windowWidth_(WINDOW_WIDTH), windowHieght_(WINDOW_HIGHT) {
}

AppState::AppState(const AppState &src) :
	destroyed_(src.destroyed_), renderer_(src.renderer_), window_(src.window_), windowWidth_(src.windowWidth_), windowHieght_(src.windowWidth_) {}

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

SDL_Surface	*AppState::getScreenSurface() {
	return this->screenSurface_;
}

SDL_Surface	*AppState::getImgSurface() {
	return this->imgSurface_;
}

/*  Member Functions  */

bool AppState::init() {
	bool success{true};

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_Log("SDL could nit initialize! SDL error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		if (this->window_ = SDL_CreateWindow("Watermelon", this->windowWidth_, this->windowHieght_, 0); this->window_ == nullptr) {
			SDL_Log("Window could nto be created! SDL error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			this->screenSurface_ = SDL_GetWindowSurface(this->window_);
		}
	}
	return success;
}

bool AppState::loadMedia(const std::string &path) {
	bool success{true};

	if (this->imgSurface_ = SDL_LoadBMP(path.c_str()); this->imgSurface_ == nullptr) {
		SDL_Log("Unable to load image %s! SDL Error %s\n", path.c_str(), SDL_GetError());
		success = false;
	}
	return success;

}

void AppState::destroyAppState() {
	if (this->destroyed_)
		return ;
	SDL_DestroySurface(this->imgSurface_);
	this->imgSurface_ = nullptr;

	SDL_DestroyWindow(this->window_);
	this->window_ = nullptr;
	this->screenSurface_ = nullptr;

	SDL_Quit();
	this->destroyed_ = true;
}
