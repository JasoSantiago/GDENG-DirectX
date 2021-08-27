#pragma once
#include <string>

class Resource
{
public:
	typedef std::wstring String;
	Resource(const wchar_t* fullPath);
	virtual ~Resource();
protected:
	String fullPath;
};