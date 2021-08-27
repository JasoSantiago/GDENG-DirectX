#pragma once
#include "AUIScreen.h"

class AGameObject;
class InspectorScreen : public AUIScreen
{
private:
	InspectorScreen();
	~InspectorScreen();

	void onTransformUpdate();
	virtual void drawUI() override;
	void updateTransformDisplays();
	friend class UIManager;

	float Displayposition[3] = { 0.0f, 0.0f, 0.0f };
	float Displayrotation[3] = { 0.0f, 0.0f, 0.0f };
	float Displayscale[3] = { 1.0f, 1.0f, 1.0f };

	AGameObject* selectedObject = NULL;
};
