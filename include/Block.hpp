#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Block {
private:
	bool		_active;
	int			_type;

public:
	Block();
	Block(Block const &src);
	~Block();

	bool 		isActive() const;
	int			getType() const;

	void 		setActive(bool active);

	Block	&operator=(Block const &src);
};
