#pragma once
#include "Point.h"



class InputListener
{
public:
	InputListener()
	{
		
	}
	~InputListener()
	{
		
	}
	//KeyBoard
	virtual void onKeyDown(int key) = 0;
	virtual void onKeyUp(int key) = 0;

	//Mouse

	virtual void onMouseMove(const Point& delta_mouse_pos) = 0;
	
	virtual void onLeftMouseDown(const Point& mousepos) = 0;
	virtual void onLeftMouseUp(const Point& mousepos) = 0;
	
	virtual void onRightMouseDown(const Point& mousepos) = 0;
	virtual void onRightMouseUp(const Point& mousepos) = 0;
	
};