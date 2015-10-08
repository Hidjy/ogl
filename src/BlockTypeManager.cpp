#include "BlockTypeManager.hpp"

#include "BlockType.hpp"

#include <map>
#include <string>

BlockTypeManager::BlockTypeManager() {
	_blockTypes.clear();
}

BlockTypeManager::~BlockTypeManager() {
	for (auto it = _blockTypes.begin(); it != _blockTypes.end(); ++it)
		delete it->second;
}

void		BlockTypeManager::add(std::string name, BlockType *bt) {
	_blockTypes[name] = bt;
}

BlockType	*BlockTypeManager::operator[](const std::string& name) {
	auto it = _blockTypes.find(name);
	if (it != _blockTypes.end())
		return it->second;
	return nullptr;
}
