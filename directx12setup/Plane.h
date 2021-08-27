#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Quad.h"

class Plane: public AGameObject
{
public:
	Plane(std::string name, void* shaderByteCode, size_t sizeShader);
	~Plane();
	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;

private:
	VertexBuffer* vertex_buffer;
	IndexBuffer* index_buffer;
	ConstantBuffer* cosntant_buffer;

	float ticks = 0.0f;
	float deltaPos = 0.0f;
	float deltaTime = 0.0f;
	float speed = 10.0f;
	float rot_x = 0.0f;
	float rot_y = 0.0f;
	struct Vertex {
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};
};



