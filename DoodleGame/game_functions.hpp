#ifndef GAME_FUNCTIONS_HPP
#define GAME_FUNCTIONS_HPP

#include <string.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "constants.hpp"
#include "objects_and_variables.hpp"
//#include <chrono>

void fresh_start() {
	distance = 0;
	plats_passed = 0;
	my_coins = 0;
	ability = false;
	hero_x = 0;
	hero_y = height_arg - hero_sprite_height - plat_sprite_height;
	dx = 0;
	dy = 0;
	hero_left = basic_hero_left;
	hero_front = basic_hero_front;
	hero_right = basic_hero_right;
	hero_sprite = hero_front;
	plats[0].x = 0;
	plats[0].y = height_arg - plat_sprite_height;
	plats[0].enemy = false; //for restarting the game
	plats[0].fugacious = false;
	plats[0].existence = true;
	int interval = plats[0].y / (plat_N - 1);
	for (int i = 1; i < plat_N; i++)
	{
		plats[i].x = rand() % 2 ?
			plats[i - 1].x - (rand() % max_x_btw_plats + plat_sprite_width) :
			(plats[i - 1].x + plat_sprite_width + (rand() % max_x_btw_plats)) % (width_arg - plat_sprite_width);
		if (plats[i].x < 0) {
			plats[i].x = width_arg - plat_sprite_width + plats[i].x;
		}
		plats[i].y = plats[0].y - i * interval + (rand() % (interval - plat_sprite_height));
		plats[i].enemy = false; //for restarting the game
		plats[i].fugacious = false;
		plats[i].existence = true;
	}
	bullets.clear();
	coins.clear();
	white_holes.clear();
}

void print_stats(int stats, int place, Sprite* icon) {
	float stats_temp = stats / 10.f;
	int stats_digits = 1;
	while (stats_temp >= 1) {
		stats_digits++;
		stats_temp = stats_temp / 10.f;
	}
	int index = stats % 10;
	int coef = 1;
	icon->draw_sprite(0, place * (scores_sprite_height + distance_btw_scores));
	scores_sprites[index]->draw_sprite((stats_digits - 1) * scores_sprite_width + scores_sprite_width, place * (scores_sprite_height + distance_btw_scores));
	for (int i = 1; i < stats_digits; i++) {
		coef = coef * 10;
		index = (stats / coef) % 10;
		scores_sprites[index]->draw_sprite((stats_digits - i) * scores_sprite_width, place * (scores_sprite_height + distance_btw_scores));
		//drawSprite(scores_sprites[index], (stats_digits - (i + 1)) * scores_sprite_width, place * (scores_sprite_height + distance_btw_scores));
	}
}

void get_screen_size(int& width, int& height)
{
	SDL_Rect viewport;
	SDL_RenderGetViewport(renderer, &viewport);
	width = viewport.w;
	height = viewport.h;
}

void set_screen_size(int& width, int& height, bool& fullscreen)
{
	width = width_arg;
	height = height_arg;
	fullscreen = fullscreen_arg;
}

void create_the_game() {
	get_screen_size(width_arg, height_arg);
	SDL_ShowCursor(1);
	highest_distance = 0;
	plat_N = height_arg / plat_n_coef_a + plat_n_coef_b;
	plats = new Plat[plat_N];
	basic_hero_left = create_sprite("./data/jungle-left.png");
	basic_hero_front = create_sprite("./data/jungle-puca.png");
	basic_hero_right = create_sprite("./data/jungle-right.png");
	ability_hero_left = create_sprite("./data/space-left.png");
	ability_hero_front = create_sprite("./data/space-puca.png");
	ability_hero_right = create_sprite("./data/space-right.png");
	plat_sprite = create_sprite("./data/hs-friends.png");
	fugacious_plat_sprite = create_sprite("./data/hs-friends-on.png");
	bullet_sprite = create_sprite("./data/news-close.png");
	enemy_sprite = create_sprite("./data/underwater-left.png");
	scores_sprites[0] = create_sprite("./data/0.png");
	scores_sprites[1] = create_sprite("./data/1.png");
	scores_sprites[2] = create_sprite("./data/2.png");
	scores_sprites[3] = create_sprite("./data/3.png");
	scores_sprites[4] = create_sprite("./data/4.png");
	scores_sprites[5] = create_sprite("./data/5.png");
	scores_sprites[6] = create_sprite("./data/6.png");
	scores_sprites[7] = create_sprite("./data/7.png");
	scores_sprites[8] = create_sprite("./data/8.png");
	scores_sprites[9] = create_sprite("./data/9.png");
	coin_sprite = create_sprite("./data/ach-spring.png");
	white_hole_sprite = create_sprite("./data/ice-snow-16.png");
	white_hole_sprite->width = 48;
	white_hole_sprite->height = 48;
	background = create_sprite("./data/hop-bck.png");
	background->width = width_arg;
	background->height = height_arg;

	//let's assume every hero sprite has the same size and every scores sprite has the same size, and plat = fugacious_plat
	hero_sprite_width = basic_hero_front->width;
	hero_sprite_height = basic_hero_front->height;
	plat_sprite_width = plat_sprite->width;
	plat_sprite_height = plat_sprite->height;
	bullet_sprite_width = bullet_sprite->width;
	bullet_sprite_height = bullet_sprite->height;
	coin_sprite_width = coin_sprite->width;
	coin_sprite_height = coin_sprite->height;
	scores_sprite_width = scores_sprites[0]->width;
	scores_sprite_height = scores_sprites[0]->height;
	white_hole_sprite_width = white_hole_sprite->width;
	white_hole_sprite_height = white_hole_sprite->height;

	distance_icon = create_sprite("./data/hs-local.png");
	distance_icon->width = scores_sprite_width;
	distance_icon->height = scores_sprite_width;
	highest_distance_icon = create_sprite("./data/hs-global.png");
	highest_distance_icon->width = scores_sprite_width;
	highest_distance_icon->height = scores_sprite_width;
	plats_icon = create_sprite("./data/friends-button-on.png");
	plats_icon->width = scores_sprite_width;
	plats_icon->height = scores_sprite_width;
	coins_icon = create_sprite("./data/ach-spring.png");
	coins_icon->width = scores_sprite_width;
	coins_icon->height = scores_sprite_width;

	fresh_start();
}

void destroy_the_game() {
	delete[] plats;
	destroy_sprite(basic_hero_left);
	destroy_sprite(basic_hero_front);
	destroy_sprite(basic_hero_right);
	destroy_sprite(ability_hero_left);
	destroy_sprite(ability_hero_front);
	destroy_sprite(ability_hero_right);
	destroy_sprite(plat_sprite);
	destroy_sprite(fugacious_plat_sprite);
	destroy_sprite(bullet_sprite);
	destroy_sprite(enemy_sprite);
	destroy_sprite(scores_sprites[0]);
	destroy_sprite(scores_sprites[1]);
	destroy_sprite(scores_sprites[2]);
	destroy_sprite(scores_sprites[3]);
	destroy_sprite(scores_sprites[4]);
	destroy_sprite(scores_sprites[5]);
	destroy_sprite(scores_sprites[6]);
	destroy_sprite(scores_sprites[7]);
	destroy_sprite(scores_sprites[8]);
	destroy_sprite(scores_sprites[9]);
	destroy_sprite(coin_sprite);
	destroy_sprite(white_hole_sprite);
	destroy_sprite(background);
}

bool tick() {
	bool game_over = false;
	hero_x += dx;
	int hero_center_x = hero_x + hero_sprite_width / 2;
	int hero_center_y = hero_y + hero_sprite_height / 2;
	if (hero_center_x > width_arg) {//sprite's center decides about passing to the other side
		hero_x = -hero_sprite_width / 2;
	}
	else if (hero_center_x < 0) {
		hero_x = width_arg + hero_x;
	}
	dy += falling_force;
	if (static_cast<int>(dy) == 0 && dy < 0) {//to not stand still in the air
		dy = -dy;
	}
	hero_y += static_cast<int>(dy);
	//if (ability && std::chrono::duration_cast<std::chrono::seconds>
	//	(std::chrono::high_resolution_clock::now() - ability_start).count() > 20) {
	if (ability && SDL_GetTicks() - ability_start > ability_time) {
		ability = false;
		hero_left = basic_hero_left;
		hero_front = basic_hero_front;
		hero_right = basic_hero_right;
		if (dx == -side_movement_power) {
			hero_sprite = hero_left;
		}
		else if (dx == 0) {
			hero_sprite = hero_front;
		}
		else if (dx == side_movement_power) {
			hero_sprite = hero_right;
		}
	}
	if (hero_y + hero_sprite_height >= height_arg + dy) {
		if (ability) dy = jump_power; else game_over = true;
	}

	if (hero_y < h)
	{
		hero_y = h;
		distance -= static_cast<int>(dy);
		std::for_each(bullets.begin(), bullets.end(), [](Bullet& bullet) {
			bullet.y -= dy;
			});
		std::for_each(coins.begin(), coins.end(), [](Coods& coin) {
			coin.y -= static_cast<int>(dy);
			});
		std::for_each(white_holes.begin(), white_holes.end(), [](Coods& white_hole) {
			white_hole.y -= static_cast<int>(dy);
			});
		if (rand() % coin_probability == 0) {
			coins.push_back(Coods(rand() % (width_arg - coin_sprite_width), 0));
		}
		if (rand() % white_hole_probability == 0) {
			white_holes.push_back(Coods(rand() % (width_arg - white_hole_sprite_width), 0));
		}
		for (int i = 0; i < plat_N; i++)
		{
			plats[i].y -= static_cast<int>(dy);
			if (plats[i].y > height_arg)
			{
				plats_passed++;
				plats[i].enemy = false;
				plats[i].fugacious = false;
				plats[i].y = 0;
				plats[i].x = rand() % 2 ?
					plats[(i + plat_N - 1) % plat_N].x - (rand() % max_x_btw_plats + plat_sprite_width) :
					(plats[(i + plat_N - 1) % plat_N].x + plat_sprite_width + (rand() % max_x_btw_plats)) % (width_arg - plat_sprite_width);
				if (plats[i].x < 0) {
					plats[i].x = width_arg - plat_sprite_width + plats[i].x;
				}
				if (rand() % enemy_probability == 0) {
					plats[i].enemy = true;
					plats[i].enemy_x = plats[i].x + rand() % (plat_sprite_width - hero_sprite_width);
				}
				else if (rand() % fugacious_plat_probability == 0) {
					plats[i].fugacious = true;
					plats[i].fugacious_start = SDL_GetTicks(); //::chrono::high_resolution_clock::now();
				}
				plats[i].existence = true;
			}
		}
	}

	for (int i = 0; i < plat_N; i++) {
		//if (plats[i].fugacious && std::chrono::duration_cast<std::chrono::seconds>
		//	(std::chrono::high_resolution_clock::now() - plats[i].fugacious_start).count() > 3) {
		if (plats[i].fugacious && SDL_GetTicks() - plats[i].fugacious_start > fugacious_plat_time) {
			plats[i].existence = false;
		}
		if (plats[i].existence && (hero_x + hero_sprite_width * 4 / 5 > plats[i].x) && (hero_x + hero_sprite_width / 5 < plats[i].x + plat_sprite_width) &&
			(hero_y + hero_sprite_height >= plats[i].y) && (hero_y + hero_sprite_height <= plats[i].y + dy) &&
			dy > 0) {
			dy = jump_power;
		}
		if (plats[i].enemy && hero_x + hero_sprite_width * 4 / 5 >= plats[i].enemy_x + hero_sprite_width / 5 &&
			hero_x + hero_sprite_width / 5 <= plats[i].enemy_x + hero_sprite_width * 4 / 5 &&
			hero_y + hero_sprite_height >= plats[i].y - hero_sprite_height && hero_y <= plats[i].y) {
			if (hero_y + hero_sprite_height <= plats[i].y - hero_sprite_height + dy) {
				plats[i].enemy = false;
			}
			else {
				game_over = true;
			}
		}
	}
	for (unsigned int it = 0; it < bullets.size(); it++) {
		bullets[it].x += bullets[it].dx;
		float bullet_center_x = bullets[it].x + bullet_sprite_width / 2;
		if (bullet_center_x > width_arg) {//sprite's center decides about passing to the other side
			bullets[it].x = static_cast<float>(-bullet_sprite_width / 2);
		}
		else if (bullet_center_x < 0) {
			bullets[it].x = static_cast<float>(width_arg - bullet_sprite_width / 2);
		}

		bullets[it].y += bullets[it].dy;
		if (bullets[it].y < 0 || bullets[it].y > height_arg) {
			bullets.erase(bullets.begin() + it);
			it--;
			break;
		}
		for (int i = 0; i < plat_N; i++) {
			if (plats[i].enemy && bullets[it].x + bullet_sprite_width >= plats[i].enemy_x + hero_sprite_width / 5 &&
				bullets[it].x <= plats[i].enemy_x + hero_sprite_width * 4 / 5 &&
				bullets[it].y + bullet_sprite_height >= plats[i].y - hero_sprite_height && bullets[it].y <= plats[i].y) {
				plats[i].enemy = false;
				bullets.erase(bullets.begin() + it);
				it--;
				break;
			}
		}
	}

	for (unsigned int it = 0; it < coins.size(); it++) {//if-else-if for clarity
		if (hero_x + hero_sprite_width * 4 / 5 >= coins[it].x && hero_x + hero_sprite_width / 5 <= coins[it].x + coin_sprite_width &&
			hero_y + hero_sprite_height >= coins[it].y - coin_sprite_height && hero_y <= coins[it].y) {
			coins.erase(coins.begin() + it);
			it--;
			my_coins++;
			break;
		}
		else if (coins[it].y > height_arg) {
			coins.erase(coins.begin() + it);
			it--;
			break;
		}
	}

	for (unsigned int it = 0; it < white_holes.size(); it++) {
		int white_hole_center_x = white_holes[it].x + white_hole_sprite_width / 2;
		int white_hole_center_y = white_holes[it].y + white_hole_sprite_height / 2;
		float c = static_cast<float>(std::sqrt((white_hole_center_x - hero_center_x) * (white_hole_center_x - hero_center_x)
			+ (white_hole_center_y - hero_center_y) * (white_hole_center_y - hero_center_y)));
		if (c == 0) break;
		if (c <= white_hole_power_range) {
			float power = white_hole_power / c;
			hero_x -= static_cast<int>(power * ((white_hole_center_x - hero_center_x) / c));//power * cos
			hero_y -= static_cast<int>(power * ((white_hole_center_y - hero_center_y) / c));//power * sin
		}
		if (white_holes[it].y > height_arg) {
			white_holes.erase(white_holes.begin() + it);
			it--;
			break;
		}
	}
	if (game_over) fresh_start();

	//draw_test_background();// to keep slow speed of the game (such a hack)
	//SDL_Delay(5);
	background->draw_sprite(0, 0);
	hero_sprite->draw_sprite(hero_x, hero_y);
	for (int i = 0; i < plat_N; i++)
	{
		if (plats[i].existence) {
			if (plats[i].fugacious) {
				fugacious_plat_sprite->draw_sprite(plats[i].x, plats[i].y);
			}
			else {
				plat_sprite->draw_sprite(plats[i].x, plats[i].y);
			}
		}
		if (plats[i].enemy) {
			enemy_sprite->draw_sprite(plats[i].enemy_x, plats[i].y - hero_sprite_height);
		}
	}
	std::for_each(bullets.begin(), bullets.end(), [](Bullet bullet) {
		bullet_sprite->draw_sprite(static_cast<int>(bullet.x), static_cast<int>(bullet.y));
		});
	std::for_each(coins.begin(), coins.end(), [](Coods coin) {
		coin_sprite->draw_sprite(coin.x, coin.y);
		});
	std::for_each(white_holes.begin(), white_holes.end(), [](Coods white_holes) {
		white_hole_sprite->draw_sprite(white_holes.x, white_holes.y);
		});

	if (distance > highest_distance) {
		highest_distance = distance;
	}

	print_stats(distance, 0, distance_icon);
	print_stats(highest_distance, 1, highest_distance_icon);
	print_stats(plats_passed, 2, plats_icon);
	print_stats(my_coins, 3, coins_icon);

	return false;
}

int launch()
{
	bool end = false;
	SDL_Window* window;
	SDL_Event event;

	bool is_fullscreen;
	int window_width;
	int window_height;
	set_screen_size(window_width, window_height, is_fullscreen);

	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		std::cerr << "SDL_Init(SDL_INIT_VIDEO) failed: " << SDL_GetError() << std::endl;
		return(-1);
	}

	if (SDL_CreateWindowAndRenderer(0, 0, is_fullscreen ? SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN : SDL_WINDOW_HIDDEN,
		&window, &renderer) < 0) {
		std::cerr << "SDL_CreateWindowAndRenderer() failed: " << SDL_GetError() << std::endl;
		return(-1);
	}

	SDL_SetWindowTitle(window, "Game");
	SDL_SetWindowSize(window, window_width, window_height);
	SDL_ShowWindow(window);

	create_the_game();

	while (!end) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYUP:
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
				{
					if (dx == side_movement_power) {
						dx = 0;
						hero_sprite = hero_front;
					}
					break;
				}
				case SDLK_LEFT:
				{
					if (dx == -side_movement_power) {
						dx = 0;
						hero_sprite = hero_front;
					}
					break;
				}
				case SDLK_ESCAPE:
					end = true;
					break;
				default:
					break;
				}
				break;
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_RIGHT:
				{
					dx = side_movement_power;
					hero_sprite = hero_right;
					break;
				}
				case SDLK_LEFT:
				{
					dx = -side_movement_power;
					hero_sprite = hero_left;
					break;
				}
				default:
					break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch (event.button.button) {
				case SDL_BUTTON_RIGHT:
				{
					if (my_coins >= ability_cost) {
						my_coins -= ability_cost;
						ability = true;
						ability_start = SDL_GetTicks();// std::chrono::high_resolution_clock::now();
						hero_left = ability_hero_left;
						hero_front = ability_hero_front;
						hero_right = ability_hero_right;
						if (dx == -side_movement_power) {
							hero_sprite = hero_left;
						}
						else if (dx == 0) {
							hero_sprite = hero_front;
						}
						else if (dx == side_movement_power) {
							hero_sprite = hero_right;
						}
					}
					break;
				}
				case SDL_BUTTON_LEFT:
				{
					float x = static_cast<float>(hero_x + hero_sprite_width / 2);
					float y = static_cast<float>(hero_y + hero_sprite_height / 2);
					float c = static_cast<float>(std::sqrt((mouse_x - x) * (mouse_x - x) + (mouse_y - y) * (mouse_y - y)));
					if (c == 0) break;
					bullets.push_back(Bullet(x - bullet_sprite_width / 2, y - bullet_sprite_height / 2,
						bullet_speed * (mouse_x - x) / c, bullet_speed * (mouse_y - y) / c));
					//"- bullet_sprite_height/2" to make a center of the bullet starting from the center of the hero
					//[dx, dy] = [cos(a), sin(a)], so its length is: sqrt((cos(a))^2 + (sin(a))^2) = sqrt(1) = 1
					//bullet_speed*[dx, dy] = [bullet_speed*cos(a), bullet_speed*sin(a)], so its length is: 
					//sqrt(bullet_speed^2*(cos(a))^2 + bullet_speed^2*(sin(a))^2) = 
					//sqrt(bullet_speed^2*((cos(a))^2 + (sin(a))^2)) = bullet_speed*sqrt((cos(a))^2 + (sin(a))^2) = bullet_speed
					break;
				}
				default:
					break;
				}
				break;
			case SDL_MOUSEMOTION:
				mouse_x = event.motion.x;
				mouse_y = event.motion.y;
				break;
			case SDL_QUIT:
				end = true;
				break;
			default:
				break;
			}
		}

		end |= tick() ? true : false;

		SDL_RenderPresent(renderer);

		SDL_Delay(5);
	}

	destroy_the_game();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return(0);
}
#endif