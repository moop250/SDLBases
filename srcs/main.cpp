

#include "../incl/main.hpp"
#include "../incl/AppState.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <cstdio>
#include <string>


int	main(void) {
	int exitCode{0};
	AppState app;

	if (!app.init()) {
		SDL_Log("Unable to initialize program!\n");
		exitCode = 1;
	}
	else {
		if (!app.loadMedia(const_cast<char *>("req/thing.bmp"))) {
			SDL_Log("Unable to load media!\n");
			exitCode = 2;
		}
		bool quit{false};

		SDL_Event e;
		SDL_zero(e);
		while (quit == false) {
			while (SDL_PollEvent(&e)) {
				if(e.type == SDL_EVENT_QUIT)
					quit = true;
			}
			SDL_FillSurfaceRect(app.getScreenSurface(), nullptr, SDL_MapSurfaceRGB(app.getScreenSurface(), 0xff, 0xff, 0xff));

			SDL_BlitSurface(app.getImgSurface(), nullptr, app.getScreenSurface(), nullptr);

			SDL_UpdateWindowSurface(app.getWindow());
		}
	}
	app.destroyAppState();

	return exitCode;
}

