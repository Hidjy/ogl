#pragma once

#include "Color.hpp"

class IBlockType {
public:
	virtual ~IBlockType() {};
	virtual void	getRGBA(float &r, float &g, float &b, float &a) const = 0;
};
