#include "Color.hpp"

Color::Color() {
	// ff00ff power
	r = 1.0f;
	g = 0.0f;
	b = 1.0f;
	a = 1.0f;
}

Color::Color(float red, float green, float blue) : r(red), g(green), b(blue), a(1.0f) {
}
