#pragma once

#include <iostream>
#include <fstream>
#include "rapidjson\document.h"
#include "rapidjson\stringbuffer.h"
#include "Configuration.h"

class Loader
{
public:
	Loader();
	Loader(std::string configPath);
	~Loader();

private:
	bool loadAssets();
	bool loadVisualData();
	bool loadAudioData();
	std::string pullStringFromJSON(rapidjson::Document& doc, const char* value);
	std::map<std::string, std::string>* pullMapFromJSON(rapidjson::Document& doc);
	Configuration* parseConfiguration(std::string jsonStr);
	Configuration* config;
	std::string configPath;
};