#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

constexpr int plat_n_coef_a = 100;
constexpr int plat_n_coef_b = 2;
constexpr int h = 200; //how many pixels from the top of the screen camera should start moving
constexpr int max_x_btw_plats = 15; //maximum distance between plats in the x axis. (actually: maximum + 1)
constexpr int distance_btw_scores = 3;
constexpr float falling_force = 0.08f;
constexpr int jump_power = -6;
constexpr int ability_cost = 0;
constexpr unsigned int ability_time = 20000u;
constexpr unsigned int fugacious_plat_time = 3000u;
constexpr int side_movement_power = 1;
constexpr int coin_probability = 100; //in fact, it is 1/<value>
constexpr int white_hole_probability = 200; //in fact, it is 1/<value>
constexpr int enemy_probability = 4; //in fact, it is 1/<value>
constexpr int fugacious_plat_probability = 2; //in fact, it is (1/<value>)*(1-1/enemy_probability)
constexpr int white_hole_power = 100;
constexpr int white_hole_power_range = 150;
constexpr int bullet_speed = 3;
#endif