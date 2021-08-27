#include "TextureManager.h"
#include "Texture.h"
#include <filesystem>

TextureManager* TextureManager::sharedInstance = NULL;

void TextureManager::initialize()
{
    sharedInstance = new TextureManager();
}

void TextureManager::destroy()
{
    delete sharedInstance;
}

TextureManager* TextureManager::getInstance()
{
	return sharedInstance;
}

Texture* TextureManager::createTextureFromFile(const wchar_t* filePath)
{
	std::wstring fullPath = filePath;

	this->resourceMap[fullPath] = this->convertToResource(filePath);

	return (Texture*)this->resourceMap[fullPath];
}

TextureManager::TextureManager():ResourceManager()
{

}

TextureManager::~TextureManager()
{
    ResourceManager::~ResourceManager();
}

Resource* TextureManager::convertToResource(const wchar_t* filePath)
{
	Texture* tex = nullptr;
	try
	{
		tex = new Texture(filePath);
	}
	catch (...) {}

	return tex;
}