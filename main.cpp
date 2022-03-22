#include "Header.h"
#include "paths.h"

int main( int argc, char* args[] )
{
	try {
		bool quit = false;
		SDLWindow window("SDL_tutorial");
		//Create window
		if( !window ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		} else {
			window.blit(SDLHelloWorldBMP);
			window.updateWindow();

			//Wait five seconds
			SDL_Delay( 5000 );
		}

		SDL_Event event;

		while (!quit) {
			if (SDL_PollEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT)
				{
					quit = true;
					window.blit(SDLXoutBMP);
					window.updateWindow();
					SDL_Delay(1000);
				}
			}
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
