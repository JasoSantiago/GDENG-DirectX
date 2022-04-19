#include "EditorUndoScreen.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "EngineBackend.h"
#include "ActionHistory.h"
#include "GameObjectManager.h"
#include "SceneReader.h"
#include "SceneWriter.h"

EditorUndoScreen::EditorUndoScreen() : AUIScreen("EditorUndoScreen")
{
}

EditorUndoScreen::~EditorUndoScreen()
{
}

void EditorUndoScreen::drawUI()
{
	if (EngineBackend::getInstance()->getMode() == EngineBackend::EditorMode::EDITOR)
	{
		ImGui::Begin("Actions");
		ImGui::SameLine();
		if (ImGui::Button("Save", ImVec2(100, 50)))
		{
			SceneWriter::getInstance()->writeToFile();
		}
		if (ImGui::Button("Load", ImVec2(100, 50)))
		{
			SceneReader::getInstance()->readFromFile();
		}
		ImGui::End();
	}
}
