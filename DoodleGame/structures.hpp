#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
SDL_Renderer* renderer;

struct Coods {
	int x;
	int y;
	Coods(int x, int y) : x(x), y(y) {}
	Coods() : x(0), y(0) {}
};

struct Bullet {
	float x;
	float y;
	float dx;
	float dy;
	Bullet(float x, float y, float dx, float dy) : x(x), y(y), dx(dx), dy(dy) {}
};

struct Plat : Coods {
	bool enemy;
	int enemy_x;
	bool existence;
	bool fugacious;
	unsigned int fugacious_start;
	//std::chrono::steady_clock::time_point fugacious_start;//no need of initialization with any specific value
	Plat() : enemy(false), enemy_x(0), existence(true), fugacious(false), fugacious_start(0) {}
	//fugacious_start(std::chrono::high_resolution_clock::now())
};

struct Sprite {
	SDL_Texture* texture;
	int width, height;
	Sprite() : texture(nullptr), width(0), height(0) {}
	void draw_sprite(int x, int y)
	{
		SDL_Rect rect;
		rect.w = this->width;
		rect.h = this->height;
		rect.x = x;
		rect.y = y;
		SDL_RenderCopy(renderer, this->texture, NULL, &rect);
	}
};

Sprite* create_sprite(const char* path)
{
	Sprite* sprite = new Sprite();
	SDL_Texture* texture = IMG_LoadTexture(renderer, path);
	SDL_QueryTexture(texture, NULL, NULL, &sprite->width, &sprite->height);
	sprite->texture = texture;
	return sprite;
}

void destroy_sprite(Sprite* sprite)
{
	if (sprite->texture)
	{
		SDL_DestroyTexture(sprite->texture);
	}

	delete sprite;
}
#endif