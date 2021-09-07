#pragma once
class EngineBackEnd
{
public:
	static EngineBackEnd* getInstance();
	static void initialize();
	static void destroy();

	enum EditorMode
	{
		EDITOR = 0,
		PLAY = 1,
		PAUSED = 2
	};

	void setMode(EditorMode mode);
	void startFrameStep();
	void endFrameStep();
	bool insideFrameStep();
	EditorMode getMode();

private:
	EngineBackEnd();
	~EngineBackEnd();
	EngineBackEnd(EngineBackEnd const&){};
	EngineBackEnd& operator = (EngineBackEnd const&) {};

	static EngineBackEnd* sharedInstance;

	EditorMode editorMode = EditorMode::EDITOR;

	bool frameStepping = false;
};

