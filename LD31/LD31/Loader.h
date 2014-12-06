#pragma once

#include <iostream>
#include <fstream>
#include "rapidjson\document.h"
#include "Configuration.h"

class Loader
{
public:
	Loader();
	Loader(std::string configPath);
	~Loader();
	std::map<std::string, std::map<std::string, std::string>> getComponentData(std::string componentName);

private:
	bool loadAssets();
	bool loadVisualData();
	bool loadAudioData();
	std::string pullStringFromJSON(rapidjson::Document& doc, const char* value);
	std::map<std::string, std::string>* pullMapFromJSON(rapidjson::Value& doc);
	std::map<std::string, std::map<std::string, std::string>*>* componentData;
	Configuration* parseConfiguration(std::string jsonStr);
	std::string* Loader::loadJSONStringFromFile(std::string path);
	std::map<std::string, std::map<std::string, std::string>*>* parseComponentData(std::string jsonStr);
	Configuration* config;
	std::string configPath;
};