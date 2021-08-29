#include "MeshManager.h"
#include "Mesh.h"

MeshManager* MeshManager::sharedInstance = NULL;

void MeshManager::initialize()
{
	sharedInstance = new MeshManager();
}

void MeshManager::destroy()
{
	delete sharedInstance;
}

MeshManager* MeshManager::getInstance()
{
	return sharedInstance;
}

Mesh* MeshManager::createMeshFromFile(const wchar_t* filePath)
{
	std::wstring fullPath = filePath;

	this->resourceMap[fullPath] = this->convertToResource(filePath);

	return (Mesh*)this->resourceMap[fullPath];
}

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

Resource* MeshManager::convertToResource(const wchar_t* filePath)
{
	Mesh* mesh = nullptr;

	try
	{

		mesh = new Mesh(filePath);

	}
	catch (...) {}

	return mesh;
}
