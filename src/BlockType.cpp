#include "BlockType.hpp"

#include "Color.hpp"

BlockType::BlockType() {
}

void BlockType::setColor(Color const &color) {
	_color.r = color.r;
	_color.g = color.g;
	_color.b = color.b;
	_color.a = color.a;
}

Color	BlockType::getColor() const {
	return _color;
}
