#pragma once
#include <Bounce2.h>

class Button
{
public:
	Button();
	Button(int pin);
	~Button();
	virtual void tick();
	bool fell();
private:
	Bounce button;
	int buttonPin;
	bool pressed;
};

