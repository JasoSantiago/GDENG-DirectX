#pragma once
#include "AUIScreen.h"
#include "SceneWriter.h"

class EditorUndoScreen : public AUIScreen
{
public:
	EditorUndoScreen();
	~EditorUndoScreen();

	virtual void drawUI() override;

};

