#pragma once

#include <iostream>
#include <fstream>
#include "rapidjson\document.h"
#include "Configuration.h"
#include "Entity.h"

typedef std::map<std::string, std::map<std::string, std::string>*> EntityMap;

class Loader
{
public:
	Loader();
	Loader(std::string configPath);
	~Loader();
	std::map<std::string, std::string>* getTowerEntityProps(std::string entityName);
	std::map<std::string, std::string>* getAmmoEntityProps(std::string entityName);
	std::map<std::string, std::string>* getEnemyEntityProps(std::string entityName);
	

private:
	bool loadAssets();
	bool loadVisualData();
	bool loadAudioData();
	std::map<std::string, std::string>* getEntity(std::string entName, ENTITY_TYPE ent);
	std::string pullStringFromJSON(const rapidjson::Document& doc, const char* value);
	std::map<std::string, std::string>* pullMapFromJSON(const rapidjson::Value& doc);
	EntityMap* pullEntityMapFromObject(const rapidjson::Value& doc);
	EntityMap* TowerEntityData;
	EntityMap* AmmoEntityData;
	EntityMap* EnemyEntityData;
	Configuration* parseConfiguration(std::string jsonStr);
	std::string* Loader::loadJSONStringFromFile(std::string path);
	void parseEntityData(std::string jsonStr);
	Configuration* config;
	std::string configPath;
};