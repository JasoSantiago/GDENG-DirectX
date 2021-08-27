#include "VertexShader.h"
#include <iostream>
#include "GraphicsEngine.h"


VertexShader::VertexShader()
{
}

void VertexShader::release()
{
	m_vs->Release();
	delete this;
}

bool VertexShader::init(void* shader_byte_code, size_t byte_code_size)
{
	ID3D11Device* directXDevice = GraphicsEngine::get()->m_d3d_device;
	HRESULT vertexResult = directXDevice->CreateVertexShader(shader_byte_code, byte_code_size, NULL, &this->m_vs);

	if (!SUCCEEDED(GraphicsEngine::get()->m_d3d_device->CreateVertexShader(shader_byte_code, byte_code_size, nullptr, &m_vs))){
		return false;
	}
	return true;
}



VertexShader::~VertexShader()
{
}
