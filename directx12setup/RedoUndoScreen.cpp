#include "RedoUndoScreen.h"

#include "EngineBackEnd.h"
#include "GameObjectManager.h"
#include "History.h"
#include "imGUI/imgui.h"

RedoUndoScreen::RedoUndoScreen(): AUIScreen("Redo-Undo Screen")
{
}

RedoUndoScreen::~RedoUndoScreen()
{
	AUIScreen::~AUIScreen();
}

void RedoUndoScreen::drawUI()
{
	ImGui::Begin("Redo Undo", 0, ImGuiWindowFlags_NoResize);
	ImGui::SetWindowSize(ImVec2(205, 100));

	if (EngineBackEnd::getInstance()->getMode() == EngineBackEnd::EditorMode::EDITOR)
	{
		if (ImGui::Button("Redo") && History::getInstance()->hasRemainingRedoActions())
		{
			History::getInstance()->recordHistory(GameObjectManager::getInstance()->getSelectedObject());
			GameObjectManager::getInstance()->applyStorageValues(History::getInstance()->redoAction());
		}
		if (ImGui::Button("Undo") && History::getInstance()->hasRemainingUndoActions())
		{
			History::getInstance()->recordUndoHistory(GameObjectManager::getInstance()->getSelectedObject());
			GameObjectManager::getInstance()->applyStorageValues(History::getInstance()->undoAction());
		}

	}
	ImGui::End();
}
