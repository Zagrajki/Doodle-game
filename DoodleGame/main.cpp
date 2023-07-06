#include "game_functions.hpp"

#undef main //as "main" is defined as a macro in SDL2, but it is better to use original "main" here
int main(int argc, char* argv[])
{
	fullscreen_arg = false;
	bool window_specified = false;
	if (argc >= 3 && strcmp(argv[1], "-window") == 0) {
		char* p = strchr(argv[2], 'x');
		if (p) {
			*p = 0;
			if (strspn(argv[2], "0123456789") + 1 == sizeof(argv[2]) && strspn(p + 1, "0123456789") + 1 == sizeof(p + 1)) {
				char* output;
				width_arg = strtol(argv[2], &output, 10);
				height_arg = strtol(p + 1, &output, 10);
				if (width_arg < 300 || height_arg < 500) {
					std::cout << "Width must not be smaller than 300 and height must not be smaller than 500" << std::endl;
					window_specified = false;
				}
				else {
					window_specified = true;
				}
			}
		}
	}
	else if (argc >= 2 && strcmp(argv[1], "-fullscreen") == 0) {
		fullscreen_arg = true;
	}
	if (!window_specified) {
		width_arg = 600;
		height_arg = 600;
	}
	return launch();
}
