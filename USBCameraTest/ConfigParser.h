#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <regex>


using namespace std;

using TUPLE_POS = tuple<double, double, double, double, double, double, double, double>;
using TUPLE_RECT = tuple<double, double, double, double>;

class Draw_ROI
{
public:
	Draw_ROI(double x, double y, double w_ratio, double h_ratio);
	Draw_ROI(double x,double y,int roi_w, double roi_h,int width,int height);
	Draw_ROI(double LT_x, double LT_y, double RT_x, double RT_y, double RB_x, double RB_y, double LB_x, double LB_y);
	~Draw_ROI();

	TUPLE_POS pos();
	TUPLE_RECT rect();

	const static int ROI_POS = 8;
	const static int ROI_RECT = 4;


private:

	double mf_startX = 0.0f;
	double mf_startY = 0.0f;
	double mf_wr = 0.0f;
	double mf_hr = 0.0f;

	unsigned int muiWidth = 0;
	unsigned int muiHeight = 0;
	unsigned int muiRectWidth = 0;
	unsigned int muiRectHeight = 0;

	double mLT_x = 0.0f;
	double mLT_y = 0.0f;

	double mRT_x = 0.0f;
	double mRT_y = 0.0f;

	double mRB_x = 0.0f;
	double mRB_y = 0.0f;

	double mLB_x = 0.0f;
	double mLB_y = 0.0f;
};


class ConfigParser
{
public:
	ConfigParser(const char* config_path,const char * project);
	ConfigParser();
	~ConfigParser();

	static int write(const char* path, const char* project, string resolution, map<string, Draw_ROI*> roiMap);


	int updateItem(const char* key, int val);
	int updateItem(const char* key, string val);
	int updateItem(const char* key, double* arr, int size = 4);

protected:
	string mstrPath;
	string mstrProject;
	map<string, string> mCfgMap;
	map<string, Draw_ROI*> mRoiMap;

	vector<string> mVecKeys;
	vector<Draw_ROI*> mVecRoi;
	virtual int parse() = 0;

	std::shared_ptr<Draw_ROI> mspRoi = nullptr;

public:
	__inline vector<string> allKeys() { return mVecKeys; };
	__inline map<string, string> configMap() { return mCfgMap; };

	__inline vector<Draw_ROI*> roiList() { return mVecRoi; };
	__inline map<string, Draw_ROI*> roiMap() { return mRoiMap; };

	__inline void setPath(string path) { mstrPath = path; };
	__inline void setProject(string project) {  mstrProject = project; };

	__inline static std::vector<std::string> stringSplit(const std::string& str, string delim) {
		std::regex reg(delim);
		std::vector<std::string> elems(std::sregex_token_iterator(str.begin(), str.end(), reg, -1),
			std::sregex_token_iterator());
		return elems;
	}
};

class JsonConfigParser : public ConfigParser
{
public:
	JsonConfigParser(const char* path, const char* project);
	~JsonConfigParser() {};

protected:
	virtual int parse() override;

};

