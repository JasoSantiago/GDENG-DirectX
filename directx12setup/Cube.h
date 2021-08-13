#pragma once
#include "AGameObject.h"
#include "GraphicsEngine.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"
#include "Quad.h"


class Cube: public AGameObject
{
public:
	Cube(string name, void* shaderByteCode, size_t sizeShader);
	~Cube();

	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
	void setAnimSpeed(float speed);
	void rotateCubex(float value, float deltaTime); 
	void rotateCubey(float value, float deltaTime);
	
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
};

