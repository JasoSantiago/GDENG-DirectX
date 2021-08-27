
#pragma once
#include "Cube.h"
#include "Vector2D.h"

class TexturedCube : public Cube
{
public:
	TexturedCube(std::string name, void* shaderByteCode, size_t sizeShader);
	~TexturedCube();

	void draw(int width, int height, VertexShader* vertex_shader, PixelShader* pixel_shader) override;
private:
	struct Vertex {
		Vector3D position;
		Vector2D texCoord;
	};
	Texture* m_tex;
};
