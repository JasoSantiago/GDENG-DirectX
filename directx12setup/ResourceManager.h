#pragma once
#include <iostream>
#include <unordered_map>
#include <string>

class Resource;
class ResourceManager
{

public:
	ResourceManager();
	~ResourceManager();
protected:
	std::unordered_map<std::wstring, Resource*>  resourceMap;
private:
	ResourceManager(ResourceManager const&) {};             
	ResourceManager& operator=(ResourceManager const&) {}; 
};