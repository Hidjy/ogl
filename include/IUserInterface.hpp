#pragma once

class IUserInterface {
public:
	virtual void	update(float dt) = 0;
	virtual void	render() = 0;
};
