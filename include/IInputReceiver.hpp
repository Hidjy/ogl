#pragma once

class IInputReceiver {
public:
	virtual ~IInputReceiver() {};
	virtual void	onMouseMove(float mx, float my) = 0;
};
