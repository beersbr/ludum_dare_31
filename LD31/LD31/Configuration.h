#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>

class Configuration
{
public:
	Configuration(void);
	~Configuration(void);
	std::string visualDataPath;
	std::string mapDataPath;
	std::string audioDataPath;
	std::map<std::string, std::string>* options;
	bool isLoaded;
};

