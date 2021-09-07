
#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Plane.h"
#include "AGameObject.h"
#include "PhysicsCube.h"
#include "PhysicsPlane.h"
#include "TexturedCube.h"

GameObjectManager* GameObjectManager::sharedInstance = NULL;

GameObjectManager* GameObjectManager::getInstance()
{
	return sharedInstance;
}

void GameObjectManager::initialize()
{
	sharedInstance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	sharedInstance->gameObjectMap.clear();
	sharedInstance->gameObjectList.clear();
	delete sharedInstance;
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	if (this->gameObjectMap[name] != nullptr) {
		return this->gameObjectMap[name];
	}
	else {
		std::cout << "Object does not exist";
		return nullptr;
	}
}

std::vector<AGameObject*>  GameObjectManager::getAllObjects()
{
	return this->gameObjectList;
}

int GameObjectManager::activeObjects()
{
	return this->gameObjectList.size();
}

void GameObjectManager::updateAllObjects()
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {
			this->gameObjectList[i]->update(EngineTime::getDeltaTime());

	}
}

void GameObjectManager::renderAllObjects(int width, int height)
{
	for (int i = 0; i < this->gameObjectList.size(); i++) {

			this->gameObjectList[i]->draw(width, height);

	}
}

void GameObjectManager::addObject(AGameObject* gameObject)
{
	//used to generate the name of the objects so that they don't overlap
	if (this->gameObjectMap[gameObject->getName()] != nullptr) {
		int number = 1;
		std::string newName = gameObject->getName() + std::to_string(number);
		while (this->gameObjectMap[newName] != nullptr) {
			number++;
			newName = gameObject->getName() + std::to_string(number);
		}
		gameObject->name = newName;
		this->gameObjectMap[newName] = gameObject;
	}
	else {
		this->gameObjectMap[gameObject->getName()] = gameObject;
	}
	this->gameObjectList.push_back(gameObject);
}

void GameObjectManager::createObject(PrimitiveType type)
{
	if (type == PrimitiveType::CUBE) {
		Cube* cube = new Cube("Cube");
		cube->setPosition(0.0f, 0.0f, 0.0f);
		cube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(cube);
	}

	if (type == PrimitiveType::PLANE) {
		Plane* plane = new Plane("Plane", false);
		plane->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(plane);
	}
	if(type == PrimitiveType::TEXTUREDCUBE)
	{
		TexturedCube* TCube = new TexturedCube("Textured Cube");
		TCube->setPosition(0.0f, 0.0f, 0.0f);
		TCube->setScale(1.0f, 1.0f, 1.0f);
		this->addObject(TCube);
	}
	if(type == PrimitiveType::PHYSICSCUBE)
	{
		for (int i = 0; i < 20; i++) {
			PhysicsCube* pCUbe = new PhysicsCube("pCube", false);
			this->addObject(pCUbe);
		}
	}
	if(type == PrimitiveType::PHYSICSPLANE)
	{
		PhysicsPlane* pPlane = new PhysicsPlane("pPlane", true);
		this->addObject(pPlane);
	}
}

void GameObjectManager::deleteObject(AGameObject* gameObject)
{
	this->gameObjectMap.erase(gameObject->getName());

	int index = -1;
	for (int i = 0; i < this->gameObjectList.size(); i++) {
		if (this->gameObjectList[i] == gameObject) {
			index = i;
			break;
		}
	}

	if (index != -1) {
		this->gameObjectList.erase(this->gameObjectList.begin() + index);
	}
	else
	{
		std::cout << "Game Object does not exist";
	}
	delete gameObject;
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = this->findObjectByName(name);

	if (object != nullptr ) {
		this->deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	if (this->gameObjectMap[name] != nullptr) {
		this->setSelectedObject(this->gameObjectMap[name]);
	}
}

void GameObjectManager::setSelectedObject(AGameObject* gameObject)
{
	this->selectedObject = gameObject;
}

void GameObjectManager::saveStates()
{
	for(int i = 0; i < gameObjectList.size(); i++)
	{
		if (this->gameObjectList[i]->stored == false) {
			this->gameObjectList[i]->stored = true;
			this->gameObjectList[i]->matrixchanged = true;
			this->gameObjectList[i]->saveState();
		}
	}
}

void GameObjectManager::restoreStates()
{
	for (int i = 0; i < gameObjectList.size(); i++)
	{
		this->gameObjectList[i]->restoreState();
		this->gameObjectList[i]->stored = false;
	}
}

void GameObjectManager::applyStorageValues(Storage* storage)
{
	AGameObject* objectChange = this->findObjectByName(storage->getOwnerName());
	if(objectChange != nullptr)
	{
		objectChange->setPosition(storage->getStoredPos());
		objectChange->setScale(storage->gettStoredScale());
		objectChange->setRotation(storage->getStoredRotation());
		objectChange->setLocalMatrix(storage->getStoredMatrix().getMatrix());
		
	}
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return this->selectedObject;
}

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}