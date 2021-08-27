
#pragma once
#include "Cube.h"
#include "Vector2D.h"

class TexturedCube : public AGameObject
{
public:
	TexturedCube(std::string name, void* shaderByteCode, size_t sizeShader);
	~TexturedCube();
	void update(float deltaTime) override;
	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};
	Texture* m_tex;
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
