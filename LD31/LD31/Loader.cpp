#include "Loader.h"


Loader::Loader()
{
	//Default constructor, load master config file from default location
	this->configPath = "MasterConfig.json";
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

std::string Loader::pullStringFromJSON(rapidjson::Document& doc, const char* value)
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

std::map<std::string, std::string>* Loader::pullMapFromJSON(rapidjson::Document& doc)
{
	//std::stringstream ss;

	if(!doc.IsObject())
	{
		fprintf(stdout, "[!] Cannot pull map from JSON as this isn't even an object!\n");
		return NULL;
	}
	//TODO: Iterate through JSON object members
	return NULL;
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
		tmpConfig->visualDataPath = pullStringFromJSON(configDoc, "visualData");
		tmpConfig->audioDataPath = pullStringFromJSON(configDoc, "audioData");
		tmpConfig->mapDataPath = pullStringFromJSON(configDoc, "mapData");
		//tmpConfig->options = pullMapFromJSON(configDoc["options"]);
		return tmpConfig;
	}
	catch(std::exception& ex)
	{
		fprintf(stdout, "[!] Caught exception trying to parse configuration file!\n");
		fprintf(stdout, ex.what());
		return NULL;
	}
}

bool Loader::loadAssets()
{
	//Find the config file, use that to determine what we need to load for each part
	//Then, call the appropriate load functions
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
	fprintf(stdout, "[=] Read our JSON into Memory:\n");
	
	//Parse the config file
	this->config = parseConfiguration(configJSON);
	if(!config)
	{
		throw std::exception("We couldn't parse the configuration file");
	}

	

	return true;
	
}