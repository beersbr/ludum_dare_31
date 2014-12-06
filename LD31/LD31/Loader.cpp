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
	fprintf(stdout, "================================\n");
	fprintf(stdout, "%s", configJSON.c_str());
	return true;
	
}