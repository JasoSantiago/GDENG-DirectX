#pragma once
#include "AComponentSystem.h"
#include <reactphysics3d/reactphysics3d.h>
using namespace reactphysics3d;
class PhysicsComponent : public AComponentSystem
{
public:
	PhysicsComponent(std::string name, AGameObject* owner);
	~PhysicsComponent();
	void perform(float deltaTime) override;

	RigidBody* getRigidBody();

private:
	float mass = 1000.0f; //in kilograms
	RigidBody* rigidBody;
};