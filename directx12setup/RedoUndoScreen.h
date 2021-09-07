#pragma once
#include "AUIScreen.h"

class RedoUndoScreen : public AUIScreen
{
public:
	RedoUndoScreen();
	~RedoUndoScreen();

	virtual void drawUI() override;
	friend class UIManager;
};

