#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
    if (this->resourceMap.size() != 0) {
        this->resourceMap.clear();
    }
}
