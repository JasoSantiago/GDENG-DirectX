#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"


class GameObjectManager;
class VertexShader;
class PixelShader;
class AGameObject
{
public:
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
	friend class GameObjectManager;

	_declspec(align(16)) 
		struct CBData {
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		unsigned int m_time;
	};

protected:
	std::string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

private:
	bool enabled = true;

};
