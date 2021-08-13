#pragma once
#include "Camera.h"

class SceneCameraHandler
{
public:
	static SceneCameraHandler* getInstance();
	static void initialize();
	static void destroy();
	Camera* getSceneCamera();
	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	Matrix4x4 getProjectionViewMatrix();
private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};           
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};  
	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera;

};