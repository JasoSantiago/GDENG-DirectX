#pragma once
#include <string>

class AGameObject;
class AComponentSystem
{
public:
	enum ComponentType { NotSet = -1, Script = 0, Renderer = 1, Input = 2, Physics = 3 };
	AComponentSystem(std::string name, ComponentType type, AGameObject* owner);
	~AComponentSystem();

	void attachOwner(AGameObject* owner);
	void detachOwner();
	AGameObject* getOwner();
	ComponentType getType();
	std::string getName();

	virtual void perform(float deltaTime);

protected:
	AGameObject* owner;
	ComponentType type;
	std::string name;
};