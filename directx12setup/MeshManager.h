#pragma once
#include "ResourceManager.h"

class Mesh;

class MeshManager : public ResourceManager
{
public:
	static void initialize();
	static void destroy();
	static MeshManager* getInstance();
	Mesh* createMeshFromFile(const wchar_t* filePath);

private:
	static MeshManager* sharedInstance;

	MeshManager();
	~MeshManager();
	Resource* convertToResource(const wchar_t* filePath);
};

