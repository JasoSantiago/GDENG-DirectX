#pragma once
#include "Plane.h"
class PhysicsPlane: public Plane
{
public:
	PhysicsPlane(std::string name, bool skipinit);
	~PhysicsPlane();
	void draw(int width, int height) override;
};

