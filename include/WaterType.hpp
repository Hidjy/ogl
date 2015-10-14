#pragma once

#include "IBlockType.hpp"

class WaterType : public IBlockType {
public:
	void	getRGBA(float &r, float &g, float &b, float &a) const;
};
