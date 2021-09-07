#include "EngineBackEnd.h"
#include "GameObjectManager.h"

EngineBackEnd* EngineBackEnd::sharedInstance = nullptr;

EngineBackEnd* EngineBackEnd::getInstance()
{
	return sharedInstance;
}

void EngineBackEnd::initialize()
{
	sharedInstance = new EngineBackEnd();
}

void EngineBackEnd::destroy()
{
	delete sharedInstance;
}

void EngineBackEnd::setMode(EditorMode mode)
{
	this->editorMode = mode;
	if(this->editorMode == EditorMode::PLAY)
	{
		GameObjectManager::getInstance()->saveStates();
	}
	else if(this->editorMode == EditorMode::EDITOR)
	{
		GameObjectManager::getInstance()->restoreStates();
	}
}

void EngineBackEnd::startFrameStep()
{
	this->frameStepping = true;
}

void EngineBackEnd::endFrameStep()
{
	this->frameStepping = false;
}

bool EngineBackEnd::insideFrameStep()
{
	return this->frameStepping;
}

EngineBackEnd::EditorMode EngineBackEnd::getMode()
{
	return this->editorMode;
}

EngineBackEnd::EngineBackEnd()
{
}

EngineBackEnd::~EngineBackEnd()
{
}
