#include "AUIScreen.h"


AUIScreen::AUIScreen(std::string name)
{
	this->name = name;
}

std::string AUIScreen::getName()
{
	return this->name;
}

AUIScreen::~AUIScreen()
{
}