#define INCLUDE_GFX_IMPLEMENTATION 1
#include "gfx.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

void DisplayImageData(color_t* pixels, int32_t w, int32_t h);

int main(int argc, char** argv) {
	int32_t w = 800, h = 600;
	color_t* pixels = (color_t*) malloc(w * h * sizeof(color_t));
	gfx_clear(pixels, 0xFFFFFFFF, w, h);
	int32_t rw = w/2;
	int32_t rh = h/2;
	gfx_rect(pixels, 0xFF0000FF, w, h, w/2 - rw/2, h/2 - rh/2, rw, rh);

	DisplayImageData(pixels, w, h);
	free(pixels);
	return 0;
}

void DisplayImageData(color_t* pixels, int32_t width, int32_t height) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) { printf("SDL_Init failed: %s\n", SDL_GetError()); return; }

	SDL_Window* window = SDL_CreateWindow("gfx demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (window == NULL) { printf("SDL_CreateWindow returned NULL: %s\n", SDL_GetError()); return; }

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_SOFTWARE);
	if (renderer == NULL) { printf("SDL_CreateRenderer returned NULL: %s\n", SDL_GetError()); return; }

	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
	if (texture == NULL) { printf("SDL_CreateTexture returned NULL: %s\n", SDL_GetError()); return; }

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	if (SDL_UpdateTexture(texture, NULL, pixels, width * sizeof(color_t)) != 0) { printf("SDL_UpdateTexture failed: %s\n", SDL_GetError()); return; }
	if (SDL_RenderCopy(renderer, texture, NULL, NULL) != 0) { printf("SDL_RenderCopy failed: %s\n", SDL_GetError()); return; }

	SDL_RenderPresent(renderer);

	uint32_t frameStart, frameTime;
	const uint32_t frameDelay = 1000 / 30;
	int32_t ShouldClose = 0;
	while (!ShouldClose) {
		frameStart = SDL_GetTicks();

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					ShouldClose = 1;
					break;
				case SDL_WINDOWEVENT:
					if (event.window.event == SDL_WINDOWEVENT_CLOSE) ShouldClose = 1;
					break;
				default:
					break;
			}
		}

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
		frameStart = SDL_GetTicks();
	}

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

