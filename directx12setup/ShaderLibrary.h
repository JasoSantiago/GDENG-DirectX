#pragma once
#include <iostream>
#include <unordered_map>
#include <string>


class VertexShader;
class PixelShader;

class ShaderNames {
public:

	const std::wstring BASE_VERTEX_SHADER_NAME = L"VertexShader.hlsl";
	const std::wstring TEXTURED_VERTEX_SHADER_NAME = L"TextureVertexShader.hlsl";
	const std::wstring MESH_VERTEX_SHADER_NAME = L"VertexMeshLayoutShader.hlsl";

	const std::wstring BASE_PIXEL_SHADER_NAME = L"PixelShader.hlsl";
	const std::wstring TEXTURED_PIXEL_SHADER_NAME = L"TexturedPixelShader.hlsl";
	const std::wstring TEAPOT_PIXEL_SHADER_NAME = L"TeapotPixelShader.hlsl";
};
class ShaderLibrary
{
public:
	class ShaderData {
	public:
		void* shaderByteCode = NULL;
		size_t sizeShader = 0;
	};

	static ShaderLibrary* getInstance();
	static void initialize();
	static void destroy();

	void requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader); 
	VertexShader* getVertexShader(std::wstring vertexShaderName);
	PixelShader* getPixelShader(std::wstring pixelShaderName);

private:
	ShaderLibrary();
	~ShaderLibrary();
	static ShaderLibrary* sharedInstance;

	std::unordered_map<std::wstring, VertexShader*> activeVertexShaders;
	std::unordered_map<std::wstring, PixelShader*> activePixelShaders;
};