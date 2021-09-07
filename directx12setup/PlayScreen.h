#pragma once
#include "AUIScreen.h"


class PlayScreen : public AUIScreen
{
	PlayScreen();
	~PlayScreen();

	virtual void drawUI() override;
	friend class UIManager;
};

