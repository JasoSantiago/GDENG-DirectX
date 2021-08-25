#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"

using namespace std;

class GameObjectManager;
class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader);

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
	string getName();
	friend class GameObjectManager;

	struct Vertex {
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};

	_declspec(align(16)) //make CBData a size of 16-bytes.
		struct CBData {
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_proj;
		unsigned int m_time;
	};

protected:
	string name;
	Vector3D localPosition;
	Vector3D localScale;
	Vector3D localRotation;
	Matrix4x4 localMatrix;

private:
	bool enabled = true;

};