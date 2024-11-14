#include "includes.h"

SColor::SColor(std::vector<float>& color) : SColor(color[0], color[1], color[2], color[3]) {}

SColor::SColor(float r, float g, float b, float a)
	: red(r), green(g), blue(b), alpha(a) {}

