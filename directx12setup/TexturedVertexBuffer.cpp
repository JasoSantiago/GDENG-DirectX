#include "TexturedVertexBuffer.h"
#include "GraphicsEngine.h"
#include <iostream>

TexturedVertexBuffer::TexturedVertexBuffer() : VertexBuffer()
{
}

TexturedVertexBuffer::~TexturedVertexBuffer()
{
	VertexBuffer::~VertexBuffer();
}

bool TexturedVertexBuffer::loadQuad(void* vertexList, UINT vertexSize, UINT listSize, void* shader_byte_code, UINT size_byte_shader)
{
	this->m_buffer->Release();
	this->m_layout->Release();


	D3D11_BUFFER_DESC buff_desc = {};
	buff_desc.Usage = D3D11_USAGE_DEFAULT;
	buff_desc.ByteWidth = vertexSize * listSize;
	buff_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	buff_desc.CPUAccessFlags = 0;
	buff_desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA init_data = {};
	init_data.pSysMem = vertexList;

	this->m_size_list = vertexSize;
	this->m_size_list = listSize;

	ID3D11Device* Device = GraphicsEngine::get()->getDevice();
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateBuffer(&buff_desc, &init_data, &m_buffer)))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	UINT size_layout = ARRAYSIZE(layout);
	HRESULT layoutResult = Device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &this->m_layout);
	if (FAILED(GraphicsEngine::get()->m_d3d_device->CreateInputLayout(layout, size_layout, shader_byte_code, size_byte_shader, &m_layout)))
	{
		return false;
	}
}