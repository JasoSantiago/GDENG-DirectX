#pragma once
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
struct vec3
{
	float x, y, z;
};


struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

class Quad
{
public:
	Quad();
	~Quad();
	static void createQuad(vertex list[], VertexBuffer* mq_vb, void* shader_byte_code, size_t size_shader, UINT sizeList);
	static void onUpdate(VertexBuffer* mq_vb);
};

