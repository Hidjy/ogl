#include "MessageManager.hpp"

#include <string>
#include <map>
#include <queue>

std::map<std::string, std::queue<void *>> MessageManager::_messages;

MessageManager::MessageManager() {
}

MessageManager::~MessageManager() {
}

void	MessageManager::add(std::string key, void *data) {
	if ( _messages.find(key) == _messages.end() )
		_messages[key] = std::queue<void *>();
	MessageManager::_messages[key].push(data);
}

void	*MessageManager::get(std::string key) {
	if ( _messages.find(key) == _messages.end() )
		return nullptr;
	std::queue<void *> q = _messages[key];
	if (q.empty())
		return nullptr;
	void *message = q.front();
	q.pop();
	return message;
}
