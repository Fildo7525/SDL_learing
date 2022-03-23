#pragma once

#include "SDL_pixels.h"
#include "SDL_surface.h"
#include <exception>
#include <iostream>
#include <SDL2/SDL.h>
#include <optional>
#include <vector>


namespace sdl
{
//Key press surfaces constants
enum class KeyPressSurfaces
{
    DEFAULT,
    UP,
    DOWN,
    LEFT,
    RIGHT,
	STRETCH,
    TOTAL
};

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class Window
{
public:
	operator bool() { return !(window == NULL);}
	Window() = default;
	Window(const std::string& name);

	void fill(const SDL_Rect* rectangle = NULL, std::optional<Uint32> color = std::optional<Uint32>());
	void updateWindow();

	void blit(const std::string& file);
	void optimalLoad(const std::string& file);
	void changeSurface(KeyPressSurfaces key);
	~Window();

private:
	SDL_Surface* getWindowSurface();
	SDL_Surface* loadBMP(const std::string& file);
	SDL_Surface* convert(SDL_Surface* toConvert, const SDL_PixelFormat* windowFormat);

private:
	SDL_Window *window;
	SDL_Surface* currentSurface;
	std::vector<SDL_Surface*> screenSurfaces;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};
}
