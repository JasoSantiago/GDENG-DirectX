#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Window.h"
#include "AUIScreen.h"

class UINames {
public:
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const std::string CREDITS_SCREEN = "CREDITS_SCREEN";
	const std::string COLOR_PICKER = "COLOR_PICKER";
	const std::string PLAY_SCREEN = "PLAY_SCREEN";
	const std::string REDO_UNDO_SCREEN = "REDO_UNDO_SCREEN";
};


class UIManager
{
public:
	typedef std::string String;
	typedef std::vector<AUIScreen*> UIList;
	typedef std::unordered_map<String, AUIScreen*> UITable;

	static UIManager* getInstance();
	static void initialize(HWND windowHandle);
	static void destroy();

	void drawAllUI();
	void createCredits();
	void createColorPicker();
	static const int WINDOW_WIDTH = 1440;
	static const int WINDOW_HEIGHT = 900;

private:
	UIManager(HWND windowHandle);
	~UIManager();
	static UIManager* sharedInstance;

	UIList uiList;
	UITable uiTable;
};
