#pragma once
#include "Resource.h"
#include <d3d11.h>

class Texture : public Resource
{
public:
	Texture(const wchar_t* fullPath);
	~Texture();
	std::wstring getPath();
	ID3D11ShaderResourceView* getShaderResource();

private:
	ID3D11Resource* m_Texture = NULL;
	ID3D11ShaderResourceView* m_shaderResView = NULL;
	friend class DeviceContext;
};