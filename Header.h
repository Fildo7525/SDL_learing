#pragma once

#include "SDL_rect.h"
#include <iostream>
#include <exception>
#include <optional>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL_image.h>

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

enum class Inits {
	IMG,
	TTF,
	MIXER,
	EMPTY
};

enum class IMGType
{
	NUL = 0,
    JPG = 0x00000001,
    PNG = 0x00000002,
    TIF = 0x00000004,
    WEBP = 0x00000008,
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
	Window(const std::string& name, Inits initParam, IMGType type);

	void fill(const SDL_Rect* rectangle = NULL, std::optional<Uint32> color = std::optional<Uint32>());
	void updateWindow();

	void blit(const std::string& file);
	void blit(SDL_Surface* surfaceToBlit);
	void optimalLoad(const std::string& file);
	void optimise(SDL_Surface* surfaceToBlit, SDL_Rect* rect);
	void changeSurface(KeyPressSurfaces key);
	SDL_Surface* loadPNG(const std::string& file);
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
