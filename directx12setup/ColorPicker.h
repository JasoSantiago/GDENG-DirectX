#pragma once
#include "AUIScreen.h"
#include "ImGui/imgui.h"
class ColorPicker: public AUIScreen
{
	ColorPicker();
	~ColorPicker();

	virtual void drawUI() override;
	friend class UIManager;
	ImColor my_color;
	bool isOpen = false;
};

