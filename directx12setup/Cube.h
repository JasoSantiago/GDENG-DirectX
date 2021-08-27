#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Quad.h"
#include "SceneCameraHandler.h"


class Cube: public AGameObject
{
public:
	Cube(std::string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
	void setAnimSpeed(float speed);
	void rotateCubex(float value, float deltaTime); 
	void rotateCubey(float value, float deltaTime);
	
protected:
	VertexBuffer* vertex_buffer;
	IndexBuffer* index_buffer;
	ConstantBuffer* cosntant_buffer;
	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
	float rot_x = 0.0f;
	float rot_y = 0.0f;
private:
	struct Vertex {
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};
};

