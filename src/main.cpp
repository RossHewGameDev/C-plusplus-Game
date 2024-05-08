#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "b2_api.h"
#include "b2_world.h"

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Utils.hpp"

// using namespace std; (removed to keep "vector" more obvious as not a vector2)

///
/// Credit to Codergopher for the tutorial on getting a good SDL2 setup.
///

int main(int argc, char* args[]) //arguments for SDL
{

	if (SDL_Init(SDL_INIT_VIDEO) > 0){ 

		std::cout << "SDL _Init HAS FAILED. SDL_ERROR : " << SDL_GetError() << std::endl;
	}


	if (!(IMG_Init(IMG_INIT_PNG))){

		std::cout  << "IMG_Init has failed. ERROR: " << SDL_GetError() << std::endl;
	}

	RenderWindow window("GAME v1.0", 1280, 720);

//INIT COMPLETE ...
//----------------------------
	SDL_Texture* grassTexture = window.LoadTexture("res/gfx/ground_grass_1.png");

	// Entity Construction
	std::vector<Entity> entities = {Entity(Vector2f(0,0), grassTexture),
									Entity(Vector2f(32,0), grassTexture),
									Entity(Vector2f(64,0), grassTexture),
									Entity(Vector2f(96,0), grassTexture)
						 			};
	// Memory Scope example.
	{
		Entity wilson(Vector2f(128,0), grassTexture);
		// Deletes wilson memory after scope ends.
		entities.push_back(wilson);
		// wilson still added to entities so is not lost.
	}




	bool gameRunning = true;
	SDL_Event event;
//----------------------------
// GAME LOOP ...

	const float deltaTime = 0.01f;
	float accumulator = 0.0f;
	float currentTime = utils::hireTimeInSeconds();

	while(gameRunning) 
	{
		int startTicks = SDL_GetTicks();

		float newTime = utils::hireTimeInSeconds();
		float frameTime = newTime - currentTime;

		currentTime = newTime;

		accumulator += frameTime;

		while(accumulator >= deltaTime)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
				{
					gameRunning = false;
				}
			}

			accumulator -= deltaTime;
		}

		//const float alpha = accumulator / deltaTime; 

		window.clear();

		//for every entity in entities:
		for (Entity& e : entities)
		{
			window.render(e);
		}
		// ------------------

		std::cout << utils::hireTimeInSeconds() << std::endl;




		window.display();

		int frameTicks = SDL_GetTicks() - startTicks;

		if (frameTicks < 1000 / window.getRefreshRate())
			SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
 
	}
// GAME LOOP ...



	window.cleanUp();
	SDL_Quit();

	return 0; // SDL requirement
}