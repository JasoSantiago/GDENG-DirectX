#pragma once
#include <Windows.h>
#include "EngineTIme.h"

class Window
{
public:
	
	Window();
	bool init();
	bool broadcast();
	bool release();
	bool isRun();
	//events
	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();
	
	~Window();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

protected:

	HWND m_hwnd;
	bool m_isrun;
};

