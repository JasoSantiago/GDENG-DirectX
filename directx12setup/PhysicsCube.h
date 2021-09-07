#pragma once
#include "Cube.h"
#include "PhysicsComponent.h"

class PhysicsCube : public Cube
{
public:
	PhysicsCube(std::string name, bool skipinit);
	~PhysicsCube();

	void draw(int width, int height) override;
	void update(float deltaTime) override;
	void restoreState() override;
	void attachPhysicsComponent();
private:
	float mass = 3.0f;
	PhysicsComponent* component;
};

