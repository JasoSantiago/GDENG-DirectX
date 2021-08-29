#include "MenuScreen.h"
#include "imGUI/imgui.h"
#include <iostream>
#include "GameObjectManager.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "CreditsScreen.h"
#include "UIManager.h"

MenuScreen::MenuScreen() : AUIScreen("MenuScreen")
{

}

MenuScreen::~MenuScreen()
{
}

void MenuScreen::drawUI()
{

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) { this->OnCreateCubeClicked(); }
			if (ImGui::MenuItem("Create Plane")) { this->OnCreatePlaneClicked(); }
			if(ImGui::MenuItem("Create Color Picker")) { this->onCreateColorPicker(); }
			if (ImGui::MenuItem("Create Textured Cube")) { this->onCreateTexturedCubeClicked(); }
			ImGui::EndMenu();
		}
		if(ImGui::BeginMenu("About"))
		{
			if (ImGui::MenuItem("Credits")) { this->onCreateCreditsClicked(); }
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void MenuScreen::OnCreateCubeClicked()
{
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::CUBE);
	std::cout << "cube Created \n";
}

void MenuScreen::OnCreatePlaneClicked()
{

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PLANE);
	std::cout << "creating Plane\n";
}

void MenuScreen::onCreateCreditsClicked()
{
	UIManager::getInstance()->createCredits();
}

void MenuScreen::onCreateColorPicker()
{
	UIManager::getInstance()->createColorPicker();
}

void MenuScreen::onCreateTexturedCubeClicked()
{
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::TEXTUREDCUBE);
}
