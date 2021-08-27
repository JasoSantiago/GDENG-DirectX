#pragma once
#include <d3d11.h>

class GraphicsEngine;
class DeviceContext;
class VertexShader
{
public:
	VertexShader();
	void release();
	~VertexShader();
private:
	bool init(void* shader_BYTE_code, size_t BYTE_code_size);

private:
	ID3D11VertexShader* m_vs;

private:
	friend class GraphicsEngine;
	friend class DeviceContext;
};

