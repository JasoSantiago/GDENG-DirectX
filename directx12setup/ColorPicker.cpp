#include "ColorPicker.h"

#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include <iostream>

ColorPicker::ColorPicker(): AUIScreen("ColorPicker")
{
}

ColorPicker::~ColorPicker()
{
}

void ColorPicker::drawUI()
{
	ImGui::Begin("Color Picker");

	ImGui::ColorEdit4("Color", (float*)&my_color);

	// Plot some values
	const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));
	ImGui::End();

}
