#pragma once

#include <iostream>
#include <fstream>
#include "rapidjson\document.h"
#include "rapidjson\prettywriter.h"
#include "Configuration.h"

class Loader
{
public:
	Loader();
	Loader(std::string configPath);
	~Loader();

private:
	bool loadAssets();
	Configuration* parseConfiguration();
	std::string configPath;
};