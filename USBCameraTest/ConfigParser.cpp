#include "ConfigParser.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iomanip>
//#include <Windows.h>

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

tuple<string,string> ConfigParser::latest_project()
{
	wchar_t pathBuff[512];
	wchar_t *rz = _wgetcwd(pathBuff, 512 - 1);
	wstring path(pathBuff);

	path += L"\\mtf_roi.json";
	
	ifstream ifs(path);
	if (!ifs.is_open()) return { "" ,""};
	json json_data = json::parse(ifs);
	ifs.close();
	string project = json_data.items().begin().key();
	return { to_string(path),project };
}

int ConfigParser::write(const char* path, const char* project, string resolution, map<string, Draw_ROI*> roiMap)
{
	 unsigned int width =  stoi(stringSplit(resolution, "x")[0].c_str());
	 unsigned int height =  stoi(stringSplit(resolution, "x")[1].c_str());
	
	json j;
	j[project]["width"] = width;
	j[project]["height"] = height;



	for each (auto var in roiMap)
	{
		auto [x, y, w, h] = var.second->rect();


		j[project][var.first.c_str()][0] = x;
		j[project][var.first.c_str()][1] = y;
		j[project][var.first.c_str()][2] = w;
		j[project][var.first.c_str()][3] = h;

	}

	ofstream out(path);
	
	if (!out.is_open())
	{
		return -1;
	}

	out << setw(4) << setprecision(3) << j << endl;
	out.close();
	return 0;
}

vector<string> ConfigParser::allProjects(const char* path)
{
	vector<string> keysVec;

	fstream ifs(path);
	if (!ifs.is_open()) return vector<string>();
	json json_data = json::parse(ifs);
	ifs.close();

	try
	{
		for each (auto item in json_data.items())
		{
			keysVec.push_back(item.key());
		}
	}
	catch (const std::exception&)
	{
		return vector<string>();
	}


	return keysVec;
}

int ConfigParser::addItem(const char* project, string resolution, map<string, Draw_ROI*> roiMap)
{
	fstream ifs(mstrPath);
	if (!ifs.is_open()) return -1;
	json json_data = json::parse(ifs);
	ifs.close();

	unsigned int width = stoi(stringSplit(resolution, "x")[0].c_str());
	unsigned int height = stoi(stringSplit(resolution, "x")[1].c_str());

	json_data[project]["width"] = width;
	json_data[project]["height"] = height;

	for each (auto var in roiMap)
	{
		auto [x, y, w, h] = var.second->rect();


		json_data[project][var.first.c_str()][0] = x;
		json_data[project][var.first.c_str()][1] = y;
		json_data[project][var.first.c_str()][2] = w;
		json_data[project][var.first.c_str()][3] = h;

	}

	ofstream out(mstrPath);

	if (!out.is_open())
	{
		return -1;
	}

	out << setw(4) << json_data << endl;
	out.close();


	return 0;
}

int ConfigParser::updateItem(const char* key, int val)
{
	fstream ifs(mstrPath);
	if (!ifs.is_open()) return -1;
	json json_data = json::parse(ifs);
	ifs.close();

	json_data[mstrProject][key] = val;

	ofstream out(mstrPath);
	if (!out.is_open())
	{
		return -1;
	}

	out << setw(4) << setprecision(3) << json_data << endl;
	out.close();
	return 0;
}

int ConfigParser::updateItem(const char* key, string val)
{
	fstream ifs(mstrPath);
	if (!ifs.is_open()) return -1;
	json json_data = json::parse(ifs);
	ifs.close();

	json_data[mstrProject][key] = val;

	ofstream out(mstrPath);
	if (!out.is_open())
	{
		return -1;
	}

	out << setw(4) << setprecision(3) << json_data << endl;
	out.close();
	return 0;
}

int ConfigParser::updateItem(const char* key, double* arr, int size)
{
	fstream ifs(mstrPath);
	if (!ifs.is_open()) return -1;
	json json_data = json::parse(ifs);
	ifs.close();

	//json_data[mstrProject][key] = val;

	for (size_t i = 0; i < size; i++)
	{
		json_data[mstrProject][key][i] = arr[i];
	}


	ofstream out(mstrPath);
	if (!out.is_open())
	{
		return -1;
	}

	out << setw(4) << setprecision(3) << json_data << endl;
	out.close();
	return 0;
}

string ConfigParser::to_string(const wstring& str, const locale& loc)
{
	vector<char>buf(str.size());
	use_facet<ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '*', buf.data());
	return string(buf.data(), buf.size());
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
			int n = item.value().size();
			string curKey = item.key();


			if (n == Draw_ROI::ROI_RECT)
			{
				Draw_ROI * roi = new Draw_ROI(item.value().at(0), item.value().at(1), item.value().at(2), item.value().at(3));
				mVecRoi.push_back(roi);
				mRoiMap[curKey] = roi;
			}
			else if(n == Draw_ROI::ROI_POS)
			{
				Draw_ROI* roi = new Draw_ROI(item.value().at(0), item.value().at(1), item.value().at(2), item.value().at(3), \
					item.value().at(4), item.value().at(5), item.value().at(6), item.value().at(7));
				mVecRoi.push_back(roi);
				mRoiMap[curKey] = roi;
			}
			mVecKeys.push_back(curKey);
		}
	}
	catch (const std::exception&)
	{
		return -1;
	}

	return 0;
}

Draw_ROI::Draw_ROI(double x, double y, double w_ratio, double h_ratio) :\
mf_startX(x), mf_startY(y), mf_wr(w_ratio), mf_hr(h_ratio)
{
	mLT_x = mf_startX;
	mLT_y = mf_startY;

	mRT_x = mf_startX + mf_wr * 2;
	mRT_y = mf_startY;

	mRB_x = mf_startX + mf_wr * 2;
	mRB_y = mf_startY - mf_hr * 2;

	mLB_x = mf_startX;
	mLB_y = mf_startY - mf_hr * 2;


}

Draw_ROI::Draw_ROI(double x, double y, int roi_w, double roi_h, int width, int height) :\
mf_startX(x), mf_startY(y), muiRectWidth(roi_w), muiRectHeight(roi_h), muiWidth(width), muiHeight(height)
{
	mf_wr = double(muiRectWidth) / double(muiRectWidth);
	mf_wr = double(muiRectHeight) / double(muiRectHeight);

	mLT_x = mf_startX;
	mLT_y = mf_startY;

	mRT_x = mf_startX + mf_wr;
	mRT_y = mf_startY;

	mRB_x = mf_startX + mf_wr;
	mRB_y = mf_startY - mf_hr;

	mLB_x = mf_startX;
	mLB_y = mf_startY - mf_hr;


}

Draw_ROI::Draw_ROI(double LT_x, double LT_y, double RT_x, double RT_y, double RB_x, double RB_y, double LB_x, double LB_y):\
mLT_x(LT_x), mLT_y(LT_y), mRT_x(RT_x), mRT_y(RT_y), mRB_x(RB_x), mRB_y(RB_y), mLB_x(LB_x), mLB_y(LB_y)
{
	mf_startX = mLT_x;
	mf_startY = mLT_y;

	mf_wr = (mRT_x - mLT_x) / 2;
	mf_hr = (mRT_x - mRB_x) / 2;

}

Draw_ROI::~Draw_ROI()
{
}

TUPLE_POS Draw_ROI::pos()
{
	return {mLT_x, mLT_y, mRT_x, mRT_y, mRB_x, mRB_y, mLB_x, mLB_y};
}

TUPLE_RECT Draw_ROI::rect()
{
	return {mf_startX, mf_startY, mf_wr, mf_hr};
}
