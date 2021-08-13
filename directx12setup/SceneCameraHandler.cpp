#include "SceneCameraHandler.h"
#include "EngineTIme.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
    return sharedInstance;
}

void SceneCameraHandler::initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    delete sharedInstance;
}

Camera* SceneCameraHandler::getSceneCamera()
{
    return this->sceneCamera;
}

void SceneCameraHandler::update()
{
    this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getViewMatrix();
}

Matrix4x4 SceneCameraHandler::getProjectionViewMatrix()
{
    return  this->sceneCamera->getProjMatrix();
}

SceneCameraHandler::SceneCameraHandler()
{
   this->sceneCamera = new Camera("SceneCamera");
}
SceneCameraHandler::~SceneCameraHandler()
{
   delete this->sceneCamera;
}