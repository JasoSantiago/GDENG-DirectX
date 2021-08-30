#include "PhysicsSystem.h"

#include "EngineTIme.h"
#include "PhysicsComponent.h"

PhysicsSystem::PhysicsSystem()
{
	this->physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings WorldSettings;
	WorldSettings.defaultVelocitySolverNbIterations = 50;
	WorldSettings.gravity = Vector3(0, -9.8, 0);
	this->physicsWorld = this->physicsCommon->createPhysicsWorld(WorldSettings);
}

PhysicsSystem::~PhysicsSystem()
{
	delete this->physicsCommon;
}

void PhysicsSystem::registerComponent(PhysicsComponent* phyComp)
{
	this->componentTable[phyComp->getName()] = phyComp;
	this->componentList.push_back(phyComp);
}

void PhysicsSystem::unregisterComponent(PhysicsComponent* phyComp)
{
	if(this->componentTable[phyComp->getName()] != nullptr)
	{
		this->componentTable.erase(phyComp->getName());
		int index = -1;
		for(int i = 0; i<this->componentList.size(); i++)
		{
			if(this->componentList[i] == phyComp)
			{
				index = i;
				break;
			}
		}

		if(index != -1)
		{
			this->componentList.erase(this->componentList.begin() + index);
		}
	}
	else
	{
		std::cout << "Component does not exist";
	}
}

void PhysicsSystem::unregisterComponentByName(std::string name)
{
	if(this->componentTable[name] != nullptr)
	{
		this->unregisterComponent(this->componentTable[name]);
	}
	else
	{
		std::cout << "Failed to unregister Component";
	}
}

PhysicsComponent* PhysicsSystem::findComponentByName(std::string name)
{
	if (this->componentTable[name] != nullptr) {
		return this->componentTable[name];
	}
	else {
		std::cout << "Component does not exist";
		return nullptr;
	}
}

std::vector<PhysicsComponent*> PhysicsSystem::getAllComponents()
{
	return this->componentList;
}

void PhysicsSystem::updateAllComponents()
{
	this->physicsWorld->update(EngineTime::getDeltaTime());
	for(int i = 0; i < componentList.size(); i++)
	{
		this->componentList[i]->perform(EngineTime::getDeltaTime());
	}
}

PhysicsWorld* PhysicsSystem::getPhysicsWorld()
{
	return this->physicsWorld;
}

PhysicsCommon* PhysicsSystem::getPhysicsCommon()
{
	return this->physicsCommon;
}
