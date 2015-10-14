#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

#include "IBlockType.hpp"

class Block {
private:
	bool		_active;
	IBlockType	*_type;

public:
	static const int RENDER_SIZE = 1;

public:
	Block();
	Block(Block const &src);
	~Block();

	bool 		isActive() const;
	IBlockType	*getType() const;

	void 		setActive(bool active);
	void 		setType(IBlockType *type);

	Block	&operator=(Block const &src);
};
