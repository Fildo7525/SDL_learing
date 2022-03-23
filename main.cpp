#include "Header.h"
#include "SDL_events.h"
#include "SDL_keycode.h"
#include "paths.h"

using sdl::KeyPressSurfaces;

int main( int argc, char* args[] )
{
	try {
		bool quit = false;
		sdl::Window window("SDL_tutorial");
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
			if (SDL_WaitEvent(&event) != 0)
			{
				if (event.type == SDL_QUIT) {
					quit = true;
					window.blit(SDLXoutBMP);
					window.updateWindow();
					SDL_Delay(1000);
				}else if (event.type == SDL_KEYDOWN) {
					sdl::KeyPressSurfaces key;
					switch (event.key.keysym.sym) {
						case SDLK_LEFT:
							key = KeyPressSurfaces::LEFT;
							break;
						case SDLK_RIGHT:
							key = KeyPressSurfaces::RIGHT;
							break;
						case SDLK_DOWN:
							key = KeyPressSurfaces::DOWN;
							break;
						case SDLK_UP:
							key = KeyPressSurfaces::UP;
							break;
						case SDLK_s:
							key = KeyPressSurfaces::STRETCH;
							break;
						default:
							key = KeyPressSurfaces::DEFAULT;
					}

					if (key == KeyPressSurfaces::STRETCH) {
						window.optimalLoad(SDLStretchBMP);
					} else {
						window.changeSurface(key);
					}

					window.updateWindow();
				}
			}
		}
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}
