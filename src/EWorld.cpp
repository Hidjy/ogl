#include "EWorld.hpp"

EWorld::EWorld(const std::string message) {
	msg = message.c_str();
}

const char* EWorld::what() const throw() {
	return msg;
}
