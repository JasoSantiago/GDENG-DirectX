
#pragma once
#include "AUIScreen.h"
class MenuScreen : public AUIScreen
{
private:
	MenuScreen();
	~MenuScreen();

	virtual void drawUI() override;
	void OnCreateCubeClicked();
	void OnCreateSphereClicked();
	void OnCreatePlaneClicked();
	void onCreateCreditsClicked();
	void onCreateColorPicker();
	friend class UIManager;

	bool isOpen = false;
};
