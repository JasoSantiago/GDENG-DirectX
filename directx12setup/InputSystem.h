#pragma once
#include "InputListener.h"
#include <map>
#include "Point.h"



class InputSystem
{
public:
	static InputSystem* getInstance();
	static void initialize();
	static void destroy();

public:
	void update();
	void addListener(InputListener* inputListener);
	void removeListener(InputListener* inputListener);
private:
	std::map<InputListener*, InputListener*> m_map_listener;
	unsigned char m_keys_state[256] = {};
	unsigned char m_old_keys_state[256] = {};
	Point oldMousePos;
	bool firstCheck = true;
	static InputSystem* sharedInstance;


};