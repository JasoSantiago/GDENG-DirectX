#include "MenuScreen.h"

#include "Capsule.h"
#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_dx11.h"
#include "IMGUI/imgui_impl_win32.h"
#include "GameObjectManager.h"
#include "Cube.h"
#include "Plane.h"
#include "LoadedMeshObject.h"
#include "Sphere.h"
#include "SceneReader.h"
#include "SceneWriter.h"
#include "Cylinder.h"

MenuScreen::MenuScreen() : AUIScreen("Menu")
{
	this->openSceneDialog = new ImGui::FileBrowser();
	this->openSceneDialog->SetTitle("Open Scene");
	this->openSceneDialog->SetTypeFilters({ ".level" });

	this->saveSceneDialog = new ImGui::FileBrowser(ImGuiFileBrowserFlags_EnterNewFilename);
	this->saveSceneDialog->SetTitle("Save Scene");
	this->saveSceneDialog->SetTypeFilters({ ".level" });

	SceneReader::initialize();
	SceneWriter::initialize();
}

MenuScreen::~MenuScreen()
{
	delete this->openSceneDialog;
	delete this->saveSceneDialog;
}

void MenuScreen::drawUI()
{
	if (ImGui::BeginMainMenuBar()) 
	{
		if (ImGui::BeginMenu("File")) 
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) 
			{
				this->openSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save", "Ctrl+S")) 
			{
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S")) 
			{
				this->saveSceneDialog->Open();
			}
			if (ImGui::MenuItem("Exit Editor", "Ctrl+W")) {/*Do something */ }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Game Object")) 
		{
			if (ImGui::MenuItem("Cube")) 
			{ 
				GameObjectManager::getInstance()->addGameObject(new Cube("Cube", Vector3D(), Vector3D(1, 1, 1), Vector3D(), Vector3D(), true)); 
			}
			if (ImGui::MenuItem("Plane")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Plane("Plane", Vector3D(0,-2,0), Vector3D(15, 1, 15), Vector3D(), Vector3D())); 
			}
			if (ImGui::MenuItem("Sphere")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Sphere("Sphere", Vector3D(), 1, 5, true)); 
			}
			if (ImGui::MenuItem("Cylinder")) 
			{
				GameObjectManager::getInstance()->addGameObject(new Cylinder("Cylinder", 3.0, 1.0, 32, true, Vector3D(), Vector3D(1,1,1), Vector3D())); 
			}
			if (ImGui::MenuItem("CubeBatch")) 
			{
				srand(time(0));

				for (int i = 0; i < 50; i++)
				{
					Vector3D positionRand = Vector3D(rand() % 10 - 5, rand() % 10, rand() % 10 - 5);
					AGameObject* obj = new Cube("Cube", positionRand, Vector3D(1, 1, 1), Vector3D(), Vector3D(), true);
					GameObjectManager::getInstance()->addGameObject(obj);
				}
			}
			if (ImGui::MenuItem("Capsule")) 
			{
				GameObjectManager::getInstance()->addGameObject(new LoadedMeshObject("Capsule", Vector3D(), Vector3D(1, 1, 1), Vector3D(), L"Assets\\Meshes\\capsule.obj"));
			}
			

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	this->openSceneDialog->Display();
	this->saveSceneDialog->Display();

	if (this->saveSceneDialog->HasSelected())
	{
		SceneWriter::getInstance()->setDirectory(this->saveSceneDialog->GetSelected().string());
		SceneWriter::getInstance()->writeToFile();

		this->saveSceneDialog->ClearSelected();
		this->saveSceneDialog->Close();
	}

	else if (this->openSceneDialog->HasSelected()) 
	{
		SceneReader::getInstance()->setDirectory(this->openSceneDialog->GetSelected().string());
		SceneReader::getInstance()->readFromFile();

		this->openSceneDialog->ClearSelected();
		this->openSceneDialog->Close();
	}
}
