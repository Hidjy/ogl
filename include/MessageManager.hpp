#pragma once

#include <string>
#include <map>
#include <queue>

class MessageManager {
private:
	static std::map<std::string, std::queue<void *>> _messages;

public:
	MessageManager();
	~MessageManager();

	void	add(std::string key, void *data);
	void	*get(std::string key);
};
