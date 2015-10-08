#pragma once

#include "Color.hpp"

class BlockType {
private:
	Color _color;

public:
	BlockType();

	void setColor(Color const &color);

	Color	getColor() const;
};
