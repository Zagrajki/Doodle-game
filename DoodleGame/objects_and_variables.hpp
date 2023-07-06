#ifndef OBJECTS_AND_VARIABLES_HPP
#define OBJECTS_AND_VARIABLES_HPP

#include <vector>
#include "structures.hpp"

int width_arg;
int height_arg;
bool fullscreen_arg;
int plat_N;

Sprite* hero_sprite;
Sprite* hero_left;
Sprite* hero_front;
Sprite* hero_right;

Sprite* basic_hero_left;
Sprite* basic_hero_front;
Sprite* basic_hero_right;

Sprite* ability_hero_left;
Sprite* ability_hero_front;
Sprite* ability_hero_right;

int hero_x;
int hero_y;
int dx;
float dy;
int hero_sprite_width;
int hero_sprite_height;

Sprite* plat_sprite;
Sprite* fugacious_plat_sprite;
Plat* plats;
int plat_sprite_width;
int plat_sprite_height;

Sprite* bullet_sprite;
std::vector<Bullet> bullets;
int bullet_sprite_width;
int bullet_sprite_height;

Sprite* enemy_sprite;
Sprite* scores_sprites[10];
int scores_sprite_width;
int scores_sprite_height;

Sprite* white_hole_sprite;
std::vector<Coods> white_holes;
int white_hole_sprite_width;
int white_hole_sprite_height;

Sprite* coin_sprite;
std::vector<Coods> coins;
int my_coins;
int coin_sprite_width;
int coin_sprite_height;

bool ability;
unsigned int ability_start;
//std::chrono::steady_clock::time_point ability_start;
//The "chrono" library can be used instead of the SDL's tick.
int mouse_x;
int mouse_y;
int distance;
int highest_distance;
int plats_passed;

Sprite* background;

Sprite* distance_icon;
Sprite* highest_distance_icon;
Sprite* plats_icon;
Sprite* coins_icon;
#endif