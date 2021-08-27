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
			if (ImGui::MenuItem("Create Sphere")) { this->OnCreateSphereClicked(); }
			if (ImGui::MenuItem("Create Plane")) { this->OnCreatePlaneClicked(); }
			if(ImGui::MenuItem("Create Color Picker")) { this->onCreateColorPicker(); }
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
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	VertexShader* vertexShader = graphEngine->createVertexShader(shaderByteCode, sizeShader);
	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::CUBE, shaderByteCode, sizeShader);
	vertexShader->release();
	std::cout << "cube Created \n";
}

void MenuScreen::OnCreateSphereClicked()
{
	std::cout << "Creating sphere placeholder. \n";
}

void MenuScreen::OnCreatePlaneClicked()
{
	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
	GraphicsEngine* graphEngine = GraphicsEngine::get();
	graphEngine->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shaderByteCode, &sizeShader);
	VertexShader* vertexShader = graphEngine->createVertexShader(shaderByteCode, sizeShader);

	GameObjectManager::getInstance()->createObject(GameObjectManager::PrimitiveType::PLANE, shaderByteCode, sizeShader);

	vertexShader->release();
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
