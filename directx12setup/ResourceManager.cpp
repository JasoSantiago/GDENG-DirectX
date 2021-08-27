#include "ResourceManager.h"
#include <filesystem>

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    if (this->resourceMap.size() != 0) {
        this->resourceMap.clear();
    }
}
