#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>

using namespace std;


class ConfigParser
{
public:
	ConfigParser(const char* config_path,const char * project);
	ConfigParser();
	~ConfigParser();

protected:
	string mstrPath;
	string mstrProject;
	map<string, string> mCfgMap;
	map<string, float[4]> mRoiArray;
	vector<string> mVecKeys;
	vector<float> mVecRoi;
	virtual int parse() = 0;
public:
	__inline vector<string> allKeys() { return mVecKeys; };
	__inline map<string, string> configMap() { return mCfgMap; };
	__inline map<string, float[4]> roiArrays() { return mRoiArray; };

	__inline void setPath(string path) { mstrPath = path; };
	__inline void setProject(string project) {  mstrProject = project; };

};

class JsonConfigParser : public ConfigParser
{
public:
	JsonConfigParser(const char* path, const char* project);
	~JsonConfigParser() {};

protected:
	virtual int parse() override;

};

