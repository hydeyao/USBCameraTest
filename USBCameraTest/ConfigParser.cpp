#include "ConfigParser.h"
#include <nlohmann/json.hpp>
#include <fstream>

using json = nlohmann::json;

ConfigParser::ConfigParser(const char* config_path, const char* project) : mstrPath(config_path), mstrProject(project)
{
}

ConfigParser::ConfigParser()
{
}

ConfigParser::~ConfigParser()
{
}

JsonConfigParser::JsonConfigParser(const char* path, const char* project) : ConfigParser(path, project)
{
	parse();
}

int JsonConfigParser::parse()
{
	fstream ifs(mstrPath);
	if (!ifs.is_open()) return -1;
	json json_data = json::parse(ifs);
	ifs.close();

	try
	{
		auto items = json_data[mstrProject].items();
		for each (auto item in items)
		{
			for each (auto ele in item.value().items())
			{
				cout << ele.value() << endl;
			}
		}
	}
	catch (const std::exception&)
	{

	}



	return -1;
}


