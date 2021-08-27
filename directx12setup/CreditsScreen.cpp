#include "CreditsScreen.h"
#include "ImGui/imgui.h"
#include <iostream>

CreditsScreen::CreditsScreen() : AUIScreen("MenuScreen")
{

}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::drawUI()
{
	ImGui::Begin("Credits");
	ImGui::Text("Scene Editor v0.69\n");
	ImGui::Text("by Jaso Santiago\n");
	ImGui::Text("Acknowledgments:\n");
	ImGui::Text("Pardcode\n");
	ImGui::Text("Sir Neil\n");
	ImGui::End();
}
