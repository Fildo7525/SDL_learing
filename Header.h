#pragma once

#include "SDL_error.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "SDL_timer.h"
#include "SDL_video.h"
#include <exception>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <new>
#include <stdexcept>
#include <string>
#include <optional>

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

	void loadTexture(const std::string& newTexture);
	void blit(const std::string& file);
	~SDLWindow();

private:
	SDL_Surface* getWindowSurface();
	SDL_Surface* loadBMP(const std::string& file);

private:
	SDL_Window *window;
	SDL_Surface *screenSurface;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
};

inline SDL_Surface* SDLWindow::getWindowSurface() {
	return SDL_GetWindowSurface(window);
}

inline void SDLWindow::blit(const std::string& file)
{
	SDL_Surface* surfaceToBlit = this->loadBMP(file);
	SDL_BlitSurface(surfaceToBlit , NULL, screenSurface, NULL );
}

inline void SDLWindow::fill(const SDL_Rect* rectangle, std::optional<Uint32> color)
{
	screenSurface = getWindowSurface();
	//Fill the surface white
	Uint32 local = (color.has_value() ? color.value() : SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ));
	SDL_FillRect( screenSurface, rectangle, local);
}

inline void SDLWindow::updateWindow()
{
	SDL_Delay(45);
	SDL_UpdateWindowSurface(window);
}

inline SDL_Surface* SDLWindow::loadBMP(const std::string& file)
{
	auto created = SDL_LoadBMP(file.c_str());
	if( created == NULL) {
		throw std::runtime_error(SDL_GetError());
	}
	return created;
}

inline void SDLWindow::loadTexture(const std::string& newTexture)
{
	auto texture = IMG_LoadTexture(renderer, newTexture.c_str());
	
}

inline SDLWindow::SDLWindow(const std::string& name)
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		throw std::runtime_error(SDL_GetError());
	} else {
		window = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			throw std::runtime_error(SDL_GetError());
		} else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );
		}
	}
}

inline SDLWindow::~SDLWindow()
{
	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

