#pragma once
#include "ResourceManager.h"
class Texture;
class TextureManager : public ResourceManager
{
public:
	static void initialize();
	static void destroy();
	static TextureManager* getInstance();
	Texture* createTextureFromFile(const wchar_t* filePath);

private:
	static TextureManager* sharedInstance;

	TextureManager();
	~TextureManager();
	Resource* convertToResource(const wchar_t* filePath);

};