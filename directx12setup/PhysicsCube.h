#pragma once
#include "Cube.h"

class PhysicsCube : public Cube
{
public:
	PhysicsCube(std::string name, bool skipinit);
	~PhysicsCube();

	void draw(int width, int height) override;
	void update(float deltaTime) override;
private:
	float mass = 3.0f;
};

