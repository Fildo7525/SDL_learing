#include "Header.h"
#include "SDL_surface.h"
#include "paths.h"

SDL_Surface* SDLWindow::getWindowSurface() {
	return SDL_GetWindowSurface(window);
}

void SDLWindow::blit(const std::string& file)
{
	SDL_Surface* surfaceToBlit = this->loadBMP(file);
	SDL_BlitSurface(surfaceToBlit , NULL, currentSurface, NULL );
}

void SDLWindow::changeSurface(KeyPressSurfaces key)
{
	SDL_BlitSurface(screenSurfaces[(int)key], NULL, currentSurface, NULL);
}

void SDLWindow::fill(const SDL_Rect* rectangle, std::optional<Uint32> color)
{
	currentSurface = getWindowSurface();
	//Fill the surface white
	Uint32 local = (color.has_value() ? color.value() : SDL_MapRGB( currentSurface->format, 0xFF, 0xFF, 0xFF ));
	SDL_FillRect( currentSurface, rectangle, local);
}

void SDLWindow::updateWindow()
{
	SDL_Delay(45);
	SDL_UpdateWindowSurface(window);
}

SDL_Surface* SDLWindow::loadBMP(const std::string& file)
{
	auto created = SDL_LoadBMP(file.c_str());
	if( created == NULL) {
		throw std::runtime_error(file + ": " + SDL_GetError());
	}
	return created;
}

SDLWindow::SDLWindow(const std::string& name)
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
			currentSurface = SDL_GetWindowSurface( window );
		}
	}
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

}

SDLWindow::~SDLWindow()
{
	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();
}

