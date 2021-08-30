#include "AComponentSystem.h"

AComponentSystem::AComponentSystem(std::string name, ComponentType type, AGameObject* owner)
{
	this->name = name;
	this->type = type;
	this->owner = owner;
}

AComponentSystem::~AComponentSystem()
{
	this->owner = nullptr;
	this->type = NotSet;
}

void AComponentSystem::attachOwner(AGameObject* owner)
{
	this->owner = owner;
}

void AComponentSystem::detachOwner()
{
	this->owner = nullptr;
	delete this;
	//deletion has to happen for component so that it dose not return a null when running 
}

AGameObject* AComponentSystem::getOwner()
{
	return this->owner;
}

AComponentSystem::ComponentType AComponentSystem::getType()
{
	return this->type;
}

std::string AComponentSystem::getName()
{
	return this->name;
}

void AComponentSystem::perform(float deltaTime)
{
}
