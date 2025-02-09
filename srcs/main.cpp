

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

void	render(Uint64 aTicks, int *frameBuff) {
	for (int i = 0, c = 0; i < WINDOW_HIGHT; i++) {
		for (int j = 0; j < WINDOW_WIDTH; j++, c++) {
			frameBuff[c] = (int)(i * i + j * j + aTicks | 0xff000000);
		}
	}
}

/*
void	putPixel(int x, int y, int color, int *frameBuff) {
	if (x < 0 ||
	 	y < 0 ||
	 	x >= WINDOW_WIDTH ||
	 	y >= WINDOW_HIGHT)
	{
		return;
	}
	frameBuff[y * WINDOW_WIDTH + x] = color;
}
*/

bool	update(AppState *ap, int *frameBuff) {
	SDL_Event e;
	
	if (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
	}

	char	*pix;
	int		pitch;

	SDL_LockTexture(ap->getTexture(), NULL, (void**)&pix, &pitch);
	for (int i = 0, sp = 0, dp = 0; i < WINDOW_HIGHT; i++, dp += WINDOW_WIDTH, sp += pitch)
		memcpy(pix + sp, frameBuff + dp, WINDOW_WIDTH * 4);

	SDL_UnlockTexture(ap->getTexture());
	SDL_RenderTexture(ap->getRenderer(), ap->getTexture(), NULL, NULL);
	SDL_RenderPresent(ap->getRenderer());
	SDL_Delay(1);

	return true;
}

int	main(void) {
	bool		running = true;
	AppState	*ap = new AppState();
	int			*frameBuff = new int[WINDOW_WIDTH * WINDOW_HIGHT];

	while (running) {
		if (!update(ap, frameBuff))
			running = false;
		else {
		//	putPixel(int x, int y, int color, int *frameBuff)
			render(SDL_GetTicks(), frameBuff);
		}
	}

	delete ap;
	return (0);
}

