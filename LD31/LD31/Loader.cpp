#include "Loader.h"


Loader::Loader()
{
	//Default constructor, load master config file from default location
	this->configPath = "assets\\MasterConfig.json";
	try
	{
		if(this->loadAssets())
		{
			fprintf(stdout, "\n[=] Successfully loaded assets\n");
		}
		else
		{
			throw std::exception("Failed to load assets");
		}
	}
	catch(std::exception& ex)
	{
		fprintf(stdout, "\n[!] Wow, caught an exception loading assets!\n");
		fprintf(stdout, ex.what());
		exit(1);
	}
}

Loader::Loader(std::string configPath)
{
	try
	{
		if(this->loadAssets())
		{
			fprintf(stdout, "\n[=] Successfully loaded assets\n");
		}
	}
	catch(std::exception& ex)
	{
		fprintf(stdout, "\n[!] Wow, caught an exception loading assets!\n");
		fprintf(stdout, ex.what());
		exit(1);
	}
}

std::string Loader::pullStringFromJSON(const rapidjson::Document& doc, const char* value)
{
	std::stringstream ss;

	if(!doc.HasMember(value))
	{
		ss << "[!] " << value << " not found in JSON doc!\n";	
		throw std::exception(ss.str().c_str());
	}
	if(!doc[value].IsString())
	{
		ss << "[!] " << value << " not interpreted as string!\n";	
		throw std::exception(ss.str().c_str());
	}
	return doc[value].GetString();
}

std::map<std::string, std::string>* Loader::pullMapFromJSON(const rapidjson::Value& doc)
{
	std::stringstream ss;
	std::map<std::string, std::string>* tmpMap = new std::map<std::string, std::string>();

	if(!doc.IsObject())
	{
		fprintf(stdout, "[!] Cannot pull map from JSON as this isn't even an object!\n");
		return NULL;
	}
	for(rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
	{
		if(!itr->value.IsString())
		{
			ss << "[-] Parsing Options: Don't know what to do with " << itr->name.GetString() << " cuz it's not a string";
			fprintf(stdout, ss.str().c_str());
			continue;
		}
		
		(*tmpMap)[itr->name.GetString()] = itr->value.GetString();
	}
	return tmpMap;
}	

Configuration* Loader::parseConfiguration(std::string jsonStr)
{
	Configuration* tmpConfig = new Configuration();
	//We're assuming the configuration data is there and makes sense
	rapidjson::Document configDoc;
	if(configDoc.Parse<0>(jsonStr.c_str()).HasParseError())
	{
		//Malformed JSON maybe?
		fprintf(stdout, "[!] Error parsing JSON document into object!");
		return NULL;
	}
	if(!configDoc.IsObject())
	{
		//Root of our document isn't an object, and that's not OK
		fprintf(stdout, "[!] Root of our document isn't a JSON object!");
		return NULL;
	}
	try
	{
		tmpConfig->visualDataPath = pullStringFromJSON(configDoc, "entityData");
		tmpConfig->audioDataPath = pullStringFromJSON(configDoc, "audioData");
		tmpConfig->mapDataPath = pullStringFromJSON(configDoc, "mapData");
		if(configDoc.HasMember("options"))
		{
			tmpConfig->options = pullMapFromJSON(configDoc["options"]);
		}
		else
		{
			tmpConfig->options = NULL;
		}
		tmpConfig->isLoaded = true;
		return tmpConfig;
	}
	catch(std::exception& ex)
	{
		fprintf(stdout, "[!] Caught exception trying to parse configuration file!\n");
		fprintf(stdout, ex.what());
		return NULL;
	}
}

void Loader::parseEntityData(std::string jsonStr)
{
	std::stringstream ss;
	//EntityMap* tmpSuperMap = new EntityMap();

	rapidjson::Document compDoc;
	if(compDoc.Parse<0>(jsonStr.c_str()).HasParseError())
	{
		fprintf(stdout, "[!] Error parsing JSON document into object!");
		return;
	}

	//add component section for extendability
	if(!compDoc.HasMember("Entities"))
	{
		fprintf(stdout, "[!] No entity member found in component json!");
		return;
	}
	if(!compDoc["Entities"].IsObject())
	{
		fprintf(stdout, "[!] Expected entity member to be object, was something else");
		return;
	}

	const rapidjson::Value& compObj = compDoc["Entities"];
	//Each object element should be an object containing objects representing entities

	if(!compObj.HasMember("Towers") || !compObj["Towers"].IsObject())
	{
		fprintf(stdout, "[!] Expected Towers object member in the Entities object");
		return;
	}
	const rapidjson::Value& towerObj = compObj["Towers"];
	this->TowerEntityData = pullEntityMapFromObject(towerObj);

	if(!compObj.HasMember("Ammos") || !compObj["Ammos"].IsObject())
	{
		fprintf(stdout, "[!] Expected Ammos object member in the Entities object");
		return;
	}
	const rapidjson::Value& ammObj = compObj["Ammos"];
	this->AmmoEntityData = pullEntityMapFromObject(ammObj);

	if(!compObj.HasMember("Monsters") || !compObj["Monsters"].IsObject())
	{
		fprintf(stdout, "[!] Expected Monsters object member in the Entities object");
		return;
	}
	const rapidjson::Value& monObj = compObj["Monsters"];
	this->EnemyEntityData = pullEntityMapFromObject(monObj);
}

EntityMap* Loader::pullEntityMapFromObject(const rapidjson::Value& doc)
{
	std::stringstream ss;
	EntityMap* tmpSuperMap = new EntityMap();

	for(rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); itr++)
	{
		if(!itr->value.IsObject())
		{
			ss << "[-] expected " << itr->name.GetString() << " to be an object, was something else";
			continue;
		}

		(*tmpSuperMap)[itr->name.GetString()] = this->pullMapFromJSON((rapidjson::Value&)itr->value);

	}

	return tmpSuperMap;
}

std::string* Loader::loadJSONStringFromFile(std::string path)
{
	std::ifstream ifstr(path);
	std::string* json = new std::string();
	if(!ifstr.good())
	{
		std::stringstream ss;
		ss << "We couldn't open config file: " << path;
		throw std::exception(ss.str().c_str());
	}
	ifstr.seekg(0, std::ios::end);
	(*json).reserve(ifstr.tellg());
	ifstr.seekg(0, std::ios::beg);

	(*json).assign((std::istreambuf_iterator<char>(ifstr)), (std::istreambuf_iterator<char>()));

	return json;
}

bool Loader::loadAssets()
{
	//Find the config file, use that to determine what we need to load for each part
	//Then, call the appropriate load functions
	/*
	std::ifstream ifstr(this->configPath);
	std::string configJSON;
	if(!ifstr.good())
	{
		std::stringstream ss;
		ss << "We couldn't open config file: " << configPath;
		throw std::exception(ss.str().c_str());
	}
	ifstr.seekg(0, std::ios::end);
	configJSON.reserve(ifstr.tellg());
	ifstr.seekg(0, std::ios::beg);

	configJSON.assign((std::istreambuf_iterator<char>(ifstr)), (std::istreambuf_iterator<char>()));
	*/
	std::string configJSON((*loadJSONStringFromFile(this->configPath)));
	fprintf(stdout, "[=] Read our JSON into Memory:\n");
	
	//Parse the config file
	this->config = parseConfiguration(configJSON);
	if(!config)
	{
		throw std::exception("We couldn't parse the configuration file");
	}

	//now we have the configuration asset path, parse that.
	std::string componentJSON((*loadJSONStringFromFile(this->config->visualDataPath)));
	this->parseEntityData(componentJSON);

	if(!TowerEntityData || !AmmoEntityData || !EnemyEntityData)
	{
		fprintf(stdout, "[-] Something horrible during asset loading happened");
		return false;
	}

	return true;
	
}