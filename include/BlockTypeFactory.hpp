#pragma once

#include "IBlockType.hpp"

#include <map>
#include <string>

class BlockTypeFactory {
public:
	IBlockType	*create(const std::string& name);
};
