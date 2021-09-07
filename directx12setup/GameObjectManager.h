#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "AGameObject.h"
#include "Storage.h"

class GameObjectManager
{
public:

	enum PrimitiveType {
		CUBE,
		PLANE,
		TEXTUREDCUBE,
		PHYSICSCUBE,
		PHYSICSPLANE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*>  getAllObjects();
	int activeObjects();
	void updateAllObjects();
	void renderAllObjects(int width, int height);
	void addObject(AGameObject* gameObject);
	void createObject(PrimitiveType type);
	void deleteObject(AGameObject* gameObject);
	void deleteObjectByName(std::string name);
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* gameObject);
	void saveStates();
	void restoreStates();
	void applyStorageValues( Storage* storage);
	AGameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

	std::unordered_map<std::string, AGameObject*> gameObjectMap;
	std::vector<AGameObject*> gameObjectList;

	AGameObject* selectedObject = NULL;
};
