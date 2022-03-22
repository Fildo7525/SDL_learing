#pragma once

#include "SDL_surface.h"
#include <exception>
#include <iostream>
#include <SDL2/SDL.h>
#include <optional>
#include <vector>

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class SDLWindow
{
public:
	operator bool() { return !(window == NULL);}
	SDLWindow() = default;
	SDLWindow(const std::string& name);

	void fill(const SDL_Rect* rectangle = NULL, std::optional<Uint32> color = std::optional<Uint32>());
	void updateWindow();

	void blit(const std::string& file);
	~SDLWindow();

private:
	SDL_Surface* getWindowSurface();
	SDL_Surface* loadBMP(const std::string& file);

private:
	SDL_Window *window;
	SDL_Surface* currentSurface;
	std::vector<SDL_Surface*> screenSurfaces;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

