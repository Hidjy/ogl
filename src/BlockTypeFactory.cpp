#include "BlockTypeFactory.hpp"

#include <string>
#include <exception>

#include "StoneType.hpp"
#include "DirtType.hpp"
#include "WaterType.hpp"
#include "SandType.hpp"

IBlockType	*BlockTypeFactory::create(const std::string& name) {
	if (name == "Stone")
		return new StoneType();
	if (name == "Dirt")
		return new DirtType();
	if (name == "Water")
		return new WaterType();
	if (name == "Sand")
		return new SandType();
	throw std::exception();
	return nullptr;
}
