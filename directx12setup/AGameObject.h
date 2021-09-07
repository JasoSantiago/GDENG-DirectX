#pragma once
#include <string>
#include <vector>
#include <reactphysics3d/mathematics/Quaternion.h>

#include "AComponentSystem.h"
#include "Vector3D.h"
#include "Matrix4x4.h"


class GameObjectManager;
class VertexShader;
class PixelShader;
class AGameObject
{
public:
	struct Quaternion {
		float m_w = 0.0f;
		float m_x = 0.0f;
		float m_y = 0.0f;
		float m_z = 0.0f;
	};
	AGameObject(std::string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getRotation();

	bool isEnabled();
	void setEnabled(bool flag);
	std::string getName();

	float* getPhysicsLocalMatrix();
	void setLocalMatrix(float matrix[16]);

	void attachComponent(AComponentSystem* component);
	void detachComponent(AComponentSystem* component);
	AComponentSystem* findComponentOfType(AComponentSystem::ComponentType type, std::string name);

	Matrix4x4 getMatrix();
	friend class GameObjectManager;

	_declspec(align(16)) 
		struct CBData {
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		unsigned int m_time;
	};

	virtual void saveState();
	virtual void restoreState();

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;
	Vector3D storedPosition;
	Vector3D storedScale;
	Vector3D storedRotation;
	Matrix4x4 storedMatrix;
	std::vector<AComponentSystem*> componentList;
	Quaternion quaternion;
	bool matrixchanged = false;

private:
	bool enabled = true;
	bool stored = false;
};
