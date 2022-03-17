#include "Header.h"
#include <exception>

int main( int argc, char* args[] )
{
	try {
	SDLWindow window("SDL_tutorial");
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else {
		//Create window
		if( !window ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {
			window.blit("hello_world.bmp");
			window.updateWindow();

			//Wait two seconds
			SDL_Delay( 5000 );
		}
	}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
