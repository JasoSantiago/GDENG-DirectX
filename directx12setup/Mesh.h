#pragma once
#include "Resource.h"
#include <d3d11.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

class Mesh: public Resource
{
public:
	Mesh(const wchar_t* fullPath);
	~Mesh();
	std::wstring getPath();
	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();
	void drawMesh(float witdh, float height);
private:
	friend class DeviceContext;
	VertexBuffer* vertexbuffer;
	IndexBuffer* indexbuffer;
};

