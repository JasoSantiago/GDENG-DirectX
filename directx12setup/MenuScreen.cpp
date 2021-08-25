#include "MenuScreen.h"
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
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
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) { /* Do stuff */ }
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) {
			if (ImGui::MenuItem("Create Cube")) { this->OnCreateCubeClicked(); }
			if (ImGui::MenuItem("Create Sphere")) { this->OnCreateSphereClicked(); }
			if (ImGui::MenuItem("Create Plane")) { this->OnCreatePlaneClicked(); }
			if (ImGui::BeginMenu("Light")) {
				if (ImGui::MenuItem("Point Light")) { /* Do stuff */ }
				ImGui::EndMenu();
			}
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
	//initialize vertex for object
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
	//initialize vertex for object
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