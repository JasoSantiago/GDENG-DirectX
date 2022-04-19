#pragma once
#include <string>

#include "ConstantBuffer.h"
#include "PhysicsComponent.h"
#include "Vector3D.h"
#include "AGameObject.h"

class Capsule: public AGameObject
{
public:
	Capsule (std::string name, Vector3D pos, Vector3D scale, Vector3D color, Vector3D rot, bool hasPhysics);
	~Capsule();

	void setColors(Vector3D color);
	virtual void update(float deltaTime) override;
	virtual void draw(ConstantBuffer* cb) override;

	virtual void setPosition(float x, float y, float z) override;
	virtual void setPosition(Vector3D pos) override;

	virtual void setScale(float x, float y, float z) override;
	virtual void setScale(Vector3D scale) override;

	virtual void setRotation(float x, float y, float z) override;
	virtual void setRotation(Vector3D rot) override;

	Vector3D* getVertexWorldPositions();

	void attachPhysicsComponent();
	float checkRaycast(Vector3D rayOrigin, Vector3D rayDirection);

private:
	virtual void updateVertexLocations() override;

	float rot_x = 0;
	float rot_y = 0;
	float speed = 1;

	Vector3D edges[8];
	PhysicsComponent* component;
	class VertexBuffer* m_vb;
	class VertexShader* m_vs;
	class PixelShader* m_ps;
	class IndexBuffer* m_ib;

	class BoundingBox* collisionBox;

	class Texture* m_default_tex;

	class Mesh* m_mesh;
};

