#pragma once
#include "VertexBuffer.h"
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "Vector3D.h"

struct vertex
{
	Vector3D position;
	Vector3D position1;
	Vector3D color;
	Vector3D color1;
};

class Quad
{
public:
	Quad();
	~Quad();
	static void createQuad(vertex list[], VertexBuffer* mq_vb, void* shader_byte_code, size_t size_shader, UINT sizeList);
	static void onUpdate(VertexBuffer* mq_vb);
};

