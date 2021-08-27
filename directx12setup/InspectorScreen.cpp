#include "InspectorScreen.h"
#include "imGUI/imgui.h"
#include "GameObjectManager.h"
#include "UIManager.h"
#include "AGameObject.h"

InspectorScreen::InspectorScreen() : AUIScreen("InspectorScreen")
{
}

InspectorScreen::~InspectorScreen()
{
}

void InspectorScreen::drawUI()
{
	ImGui::Begin("Inspector Window");
	ImGui::SetWindowPos(ImVec2(UIManager::WINDOW_WIDTH - 275, 20));
	ImGui::SetWindowSize(ImVec2(225, UIManager::WINDOW_HEIGHT));
	this->selectedObject = GameObjectManager::getInstance()->getSelectedObject();
	if (this->selectedObject != NULL) {
		String name = this->selectedObject->getName();
		ImGui::Text("Selected Object: %s", name.c_str());

		this->updateTransformDisplays();
		if (ImGui::InputFloat3("Position", this->Displayposition)) { this->onTransformUpdate(); }
		if (ImGui::InputFloat3("Rotation", this->Displayrotation)) { this->onTransformUpdate(); }
		if (ImGui::InputFloat3("Scale", this->Displayscale)) { this->onTransformUpdate(); }

	}
	else {
		ImGui::Text("No object selected. Select an object first.");
	}
	ImGui::End();
}

void InspectorScreen::updateTransformDisplays()
{
	Vector3D m_pos = this->selectedObject->getLocalPosition();
	this->Displayposition[0] = m_pos.m_x;
	this->Displayposition[1] = m_pos.m_y;
	this->Displayposition[2] = m_pos.m_z;

	Vector3D m_rot = this->selectedObject->getRotation();
	this->Displayrotation[0] = m_rot.m_x;
	this->Displayrotation[1] = m_rot.m_y;
	this->Displayrotation[2] = m_rot.m_z;

	Vector3D m_scale = this->selectedObject->getLocalScale();
	this->Displayscale[0] = m_scale.m_x;
	this->Displayscale[1] = m_scale.m_y;
	this->Displayscale[2] = m_scale.m_z;
}

void InspectorScreen::onTransformUpdate()
{
	if (this->selectedObject != NULL) {
		this->selectedObject->setPosition(Vector3D(this->Displayposition[0], this->Displayposition[1], this->Displayposition[2]));
		this->selectedObject->setRotation(Vector3D(this->Displayrotation[0], this->Displayrotation[1], this->Displayrotation[2]));
		this->selectedObject->setScale(Vector3D(this->Displayscale[0], this->Displayscale[1], this->Displayscale[2]));
	}
}