#include "InputSystem.h"
#include <Windows.h>

InputSystem* InputSystem::sharedInstance = NULL;

InputSystem* InputSystem::getInstance()
{
	return sharedInstance;
}

void InputSystem::initialize()
{
	sharedInstance = new InputSystem();
}

void InputSystem::destroy()
{
	if (sharedInstance != NULL) {
		delete sharedInstance;
	}
}

void InputSystem::update()
{
	POINT currentMousePos = {};
	::GetCursorPos(&currentMousePos);

	if (firstCheck)
	{
		oldMousePos = Point(currentMousePos.x, currentMousePos.y);
		firstCheck = false;
	}

	if (currentMousePos.x != oldMousePos.m_x || currentMousePos.y != oldMousePos.m_y)
	{
		std::map<InputListener*, InputListener*>::iterator it = m_map_listener.begin();

		while (it != m_map_listener.end())
		{
			it->second->onMouseMove(Point(currentMousePos.x - oldMousePos.m_x, currentMousePos.y - oldMousePos.m_y));
			++it;
		}
	}
	oldMousePos = Point(currentMousePos.x, currentMousePos.y);

	if (::GetKeyboardState(m_keys_state))
	{
		for (unsigned int i = 0; i < 256; i++)
		{
			if (m_keys_state[i] & 0x80)
			{
				std::map<InputListener*, InputListener*>::iterator it = m_map_listener.begin();

				while (it != m_map_listener.end())
				{
					if (i == VK_LBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							it->second->onLeftMouseDown(Point(currentMousePos.x, currentMousePos.y));
						}
					}
					if (i == VK_RBUTTON)
					{
						if (m_keys_state[i] != m_old_keys_state[i])
						{
							it->second->onRightMouseDown(Point(currentMousePos.x, currentMousePos.y));
						}
					}
					else
						it->second->onKeyDown(i);
					++it;
				}
			}
			else
			{
				if (m_keys_state[i] != m_old_keys_state[i])
				{
					std::map<InputListener*, InputListener*>::iterator it = m_map_listener.begin();

					while (it != m_map_listener.end())
					{
						if (i == VK_LBUTTON)
							it->second->onLeftMouseUp(Point(currentMousePos.x, currentMousePos.y));
						else if (i == VK_RBUTTON)
							it->second->onRightMouseUp(Point(currentMousePos.x, currentMousePos.y));
						else
							it->second->onKeyUp(i);
						++it;
					}
				}
			}
		}
		::memcpy(m_old_keys_state, m_keys_state, sizeof(unsigned char) * 256);
	}
}

void InputSystem::addListener(InputListener* inputListener)
{
	m_map_listener.insert(std::make_pair<InputListener*, InputListener*>(std::forward<InputListener*>(inputListener), std::forward<InputListener*>(inputListener)));
}

void InputSystem::removeListener(InputListener* inputListener)
{
	std::map<InputListener*, InputListener*>::iterator it = m_map_listener.find(inputListener);

	if (it != m_map_listener.end())
	{
		m_map_listener.erase(it);
	}
}