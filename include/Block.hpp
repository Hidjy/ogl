#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "BlockType.hpp"

class Block {
private:
	bool		_active;
	BlockType	*_type;

public:
	static const int RENDER_SIZE = 1;

public:
	Block();
	Block(Block const &src);
	~Block();

	bool 		isActive() const;
	BlockType	*getType() const;

	void 		setActive(bool active);
	void 		setType(BlockType *type);

	Block	&operator=(Block const &src);
};
