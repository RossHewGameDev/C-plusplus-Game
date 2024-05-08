#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include"Entity.hpp"

class RenderWindow
{
public:
	RenderWindow(const char* p_title, int p_w, int p_h);
	SDL_Texture* LoadTexture(const char* p_filePath);

	int getRefreshRate();

	void cleanUp();
	void clear();
	void render(Entity& p_entity);
	void display();
private:
	SDL_Window* window; // create pointer for window
	SDL_Renderer* renderer; // create pointer for renderer
};