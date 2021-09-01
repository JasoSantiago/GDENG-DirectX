
#pragma once
#include "AUIScreen.h"
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;
	void OnCreateCubeClicked();
	void OnCreatePlaneClicked();
	void onCreateCreditsClicked();
	void onCreateColorPicker();
	void onCreateTexturedCubeClicked();
	void onCreatePhysicsCubeClicked();
	void onCreatePhysicsPlaneClicked();
	friend class UIManager;

	bool isOpen = false;
};
