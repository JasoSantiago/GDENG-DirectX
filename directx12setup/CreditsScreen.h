#pragma once
#include "AUIScreen.h"
class CreditsScreen : public AUIScreen
{
private:
	CreditsScreen();
	~CreditsScreen();

	virtual void drawUI() override;
	friend class UIManager;

	bool isOpen = false;
};
