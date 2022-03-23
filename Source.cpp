#include "Header.h"
#include "SDL_rect.h"
#include "SDL_surface.h"
#include "paths.h"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <thread>
#include <type_traits>

SDL_Surface* sdl::Window::getWindowSurface() {
	return SDL_GetWindowSurface(window);
}

void sdl::Window::blit(const std::string& file)
{
	try {
		SDL_Surface* surfaceToBlit = this->loadBMP(file);
		SDL_BlitSurface(surfaceToBlit , NULL, currentSurface, NULL );
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void sdl::Window::blit(SDL_Surface* surfaceToBlit)
{
	try {
		SDL_BlitSurface(surfaceToBlit , NULL, currentSurface, NULL );
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void sdl::Window::optimalLoad(const std::string& file)
{
	try {
		SDL_Surface* surfaceToBlit = loadBMP(file);
		SDL_Surface* optimisedSurface = nullptr;

		optimisedSurface = SDL_ConvertSurface(surfaceToBlit, currentSurface->format, 0);

		SDL_Rect scretch;
		scretch.x = 0;
		scretch.y = 0;
		scretch.w = SCREEN_WIDTH;
		scretch.h = SCREEN_HEIGHT;
		SDL_BlitScaled(surfaceToBlit, NULL, currentSurface, &scretch);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void sdl::Window::optimise(SDL_Surface* surfaceToBlit, SDL_Rect* rect)
{
	try {
		SDL_Surface* optimisedSurface = nullptr;

		optimisedSurface = SDL_ConvertSurface(surfaceToBlit, currentSurface->format, 0);

		SDL_BlitScaled(surfaceToBlit, NULL, currentSurface, rect);
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}

void sdl::Window::changeSurface(KeyPressSurfaces key)
{
	SDL_BlitSurface(screenSurfaces[(int)key], NULL, currentSurface, NULL);
}

void sdl::Window::fill(const SDL_Rect* rectangle, std::optional<Uint32> color)
{
	currentSurface = getWindowSurface();
	//Fill the surface white
	Uint32 local = (color.has_value() ? color.value() : SDL_MapRGB( currentSurface->format, 0xFF, 0xFF, 0xFF ));
	SDL_FillRect( currentSurface, rectangle, local);
}

void sdl::Window::updateWindow()
{
	SDL_Delay(100); // without this it does not work leave it here
	SDL_UpdateWindowSurface(window);
}

SDL_Surface* sdl::Window::loadBMP(const std::string& file)
{
	auto created = SDL_LoadBMP(file.c_str());
	if( created == NULL) {
		throw std::runtime_error(file + ": " + SDL_GetError());
	}
	return created;
}

SDL_Surface* sdl::Window::loadPNG(const std::string& file)
{
    //The final optimized image
    SDL_Surface* optimizedSurface = nullptr;

	SDL_Surface* loadedSurface = IMG_Load( file.c_str() );
	if (loadedSurface == NULL)
		throw std::runtime_error(file + ": " + SDL_GetError());

    //Convert surface to screen format
    optimizedSurface = SDL_ConvertSurface( loadedSurface, currentSurface->format, 0 );
    if( optimizedSurface == NULL )
    	throw std::runtime_error( std::string("Unable to optimize image ") + file + " SDL Error: " + SDL_GetError() );

    //Get rid of old loaded surface
    SDL_FreeSurface( loadedSurface );

	return optimizedSurface;
}

sdl::Window::Window(const std::string& name, Inits initParam, IMGType type)
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		throw std::runtime_error(SDL_GetError());

	window = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL ) 
		throw std::runtime_error(std::string("Window could not be created! SDL_Error: ") + SDL_GetError());

	std::thread([&]{
	//Load default surface
	screenSurfaces.push_back(loadBMP( SDLPressBMP ));

	//Load up surface
	screenSurfaces.push_back(loadBMP( SDLUpBMP ));

	//Load down su.push_back(
	screenSurfaces.push_back(loadBMP( SDLDownBMP ));

	//Load left su.push_back(
	screenSurfaces.push_back(loadBMP( SDLLeftBMP ));

	//Load right s.push_back(
	screenSurfaces.push_back(loadBMP( SDLRightBMP ));

	screenSurfaces.push_back(loadBMP( SDLStretchBMP));
	}).detach();

	switch (initParam) {
		case Inits::IMG: {
			int imgFlags = (int)type;
			if ( !(IMG_Init( imgFlags) & imgFlags))
				throw std::runtime_error(std::string("SDL_image could not initialize! SDL_image Error: ") +  IMG_GetError());
		}
		break;
		case Inits::TTF:
		case Inits::MIXER:
		case Inits::EMPTY:
		break;
	}
	//Get window surface
	currentSurface = SDL_GetWindowSurface( window );
}

sdl::Window::Window(const std::string& name) : Window(name, sdl::Inits::EMPTY, sdl::IMGType::NUL){}

sdl::Window::~Window()
{
	//Destroy window
	SDL_DestroyWindow( window );

	for(auto surface : screenSurfaces)
	{
		SDL_FreeSurface(surface);
	}

	//Quit SDL subsystems
	SDL_Quit();
}

