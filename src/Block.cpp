#include "Block.hpp"

#include "BlockType.hpp"

Block::Block() : _active(false), _type(0) {
}

Block::Block(Block const &src) : _active(src.isActive()), _type(src.getType()) {
}

Block::~Block() {
}

bool 		Block::isActive() const {
	return _active;
}

BlockType	*Block::getType() const {
	return _type;
}

void 		Block::setActive(bool active) {
	_active = active;
}

void 		Block::setType(BlockType *type) {
	_type = type;
}

Block		&Block::operator=(Block const &src) {
	_active = src.isActive();
	_type = src.getType();
	return *this;
}
