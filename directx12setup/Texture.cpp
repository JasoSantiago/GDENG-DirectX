#include "Texture.h"
#include <iostream>
#include <DirectXTex.h>
#include "GraphicsEngine.h"
#include <filesystem>

Texture::Texture(const wchar_t* fullPath) : Resource(fullPath)
{
	DirectX::ScratchImage imageData;
	HRESULT res = DirectX::LoadFromWICFile(fullPath, DirectX::WIC_FLAGS_NONE, nullptr, imageData);
	if (SUCCEEDED(res)) {
		res = DirectX::CreateTexture(GraphicsEngine::get()->getDevice(), imageData.GetImages(),
			imageData.GetImageCount(), imageData.GetMetadata(), &this->m_Texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = imageData.GetMetadata().format;
		desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = (UINT)imageData.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		GraphicsEngine::get()->getDevice()->CreateShaderResourceView(this->m_Texture, &desc, &this->m_shaderResView);
	}
	else {
		std::cout << "Texture not created successfully. \n";
	}
}

Texture::~Texture()
{
	Resource::~Resource();
	this->m_shaderResView->Release();
	this->m_Texture->Release();
}

Resource::String Texture::getPath()
{
	return this->fullPath;
}

ID3D11ShaderResourceView* Texture::getShaderResource()
{
	return this->m_shaderResView;
} 