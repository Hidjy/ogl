#pragma once

#include "BlockType.hpp"

#include <map>
#include <string>

class BlockTypeManager {
private:
	std::map<std::string, BlockType *> _blockTypes;

public:
	BlockTypeManager();
	~BlockTypeManager();

	void add(std::string name, BlockType *bt);
	BlockType	*operator[](const std::string& name);
};
