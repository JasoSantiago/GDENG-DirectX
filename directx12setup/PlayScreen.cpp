#include "PlayScreen.h"
#include "imGUI/imgui.h"
#include "EngineBackEnd.h"

PlayScreen::PlayScreen(): AUIScreen("Play Screen")
{

}

PlayScreen::~PlayScreen()
{
	AUIScreen::~AUIScreen();
}

void PlayScreen::drawUI()
{
	ImGui::Begin("Scene Control", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 100));

	if(EngineBackEnd::getInstance()->getMode() == EngineBackEnd::EditorMode::EDITOR)
	{
		if (ImGui::Button("Play")) { EngineBackEnd::getInstance()->setMode(EngineBackEnd::EditorMode::PLAY); }
	}

	if (EngineBackEnd::getInstance()->getMode() != EngineBackEnd::EditorMode::EDITOR) {
		if (ImGui::Button("Stop")) { EngineBackEnd::getInstance()->setMode(EngineBackEnd::EditorMode::EDITOR); }
	}

	if (EngineBackEnd::getInstance()->getMode() == EngineBackEnd::EditorMode::PLAY) {
		if (ImGui::Button("Pause")) { EngineBackEnd::getInstance()->setMode(EngineBackEnd::EditorMode::PAUSED); }
	}
	if (EngineBackEnd::getInstance()->getMode() == EngineBackEnd::EditorMode::PAUSED) {
		if (ImGui::Button("Resume")) { EngineBackEnd::getInstance()->setMode(EngineBackEnd::EditorMode::PLAY); }
		if( ImGui::Button("Frame Step")) { EngineBackEnd::getInstance()->startFrameStep(); }
	}
	ImGui::End();

}
