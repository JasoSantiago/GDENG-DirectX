#include "ShaderLibrary.h"
#include "GraphicsEngine.h"
#include "VertexShader.h"
#include "PixelShader.h"

ShaderLibrary* ShaderLibrary::sharedInstance = NULL;

ShaderLibrary* ShaderLibrary::getInstance()
{
	return sharedInstance;
}

void ShaderLibrary::initialize()
{
	sharedInstance = new ShaderLibrary();
}

void ShaderLibrary::destroy()
{
	delete sharedInstance;
}

void ShaderLibrary::requestVertexShaderData(std::wstring vertexShaderName, void** shaderByteCode, size_t* sizeShader)
{
	GraphicsEngine::get()->compileVertexShader(vertexShaderName.c_str(), "vsmain", shaderByteCode, sizeShader);
}

VertexShader* ShaderLibrary::getVertexShader(std::wstring vertexShaderName)
{
	if(this->activeVertexShaders[vertexShaderName] == nullptr)
	{
		std::cout << "Vertex Shader does not exist";
	}
	return this->activeVertexShaders[vertexShaderName];
}

PixelShader* ShaderLibrary::getPixelShader(std::wstring pixelShaderName)
{

	if (this->activePixelShaders[pixelShaderName] == NULL) {
		std::cout << "Pixel Shader does not exist";
	}

	return this->activePixelShaders[pixelShaderName];
}

ShaderLibrary::ShaderLibrary()
{

	ShaderNames shaderNames;
	ShaderData shaderData;

	GraphicsEngine::get()->compileVertexShader(shaderNames.BASE_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME] = GraphicsEngine::get()->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	GraphicsEngine::get()->compilePixelShader(shaderNames.BASE_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME] = GraphicsEngine::get()->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	GraphicsEngine::get()->compileVertexShader(shaderNames.TEXTURED_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.TEXTURED_VERTEX_SHADER_NAME] = GraphicsEngine::get()->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	GraphicsEngine::get()->compilePixelShader(shaderNames.TEXTURED_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEXTURED_PIXEL_SHADER_NAME] = GraphicsEngine::get()->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	GraphicsEngine::get()->compileVertexShader(shaderNames.MESH_VERTEX_SHADER_NAME.c_str(), "vsmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activeVertexShaders[shaderNames.MESH_VERTEX_SHADER_NAME] = GraphicsEngine::get()->createVertexShader(shaderData.shaderByteCode, shaderData.sizeShader);

	GraphicsEngine::get()->compilePixelShader(shaderNames.TEAPOT_PIXEL_SHADER_NAME.c_str(), "psmain", &shaderData.shaderByteCode, &shaderData.sizeShader);
	this->activePixelShaders[shaderNames.TEAPOT_PIXEL_SHADER_NAME] = GraphicsEngine::get()->createPixelShader(shaderData.shaderByteCode, shaderData.sizeShader);

	std::cout << "Shader library initialized. \n";
}


ShaderLibrary::~ShaderLibrary()
{
	ShaderNames shaderNames;
	this->activeVertexShaders[shaderNames.BASE_VERTEX_SHADER_NAME]->release();
	this->activePixelShaders[shaderNames.BASE_PIXEL_SHADER_NAME]->release();

	this->activeVertexShaders.clear();
	this->activePixelShaders.clear();
}