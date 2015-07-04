#include "stdafx.h"
#include "ZoomClutterRadarScreen.h"


CZoomClutterRadarScreen::CZoomClutterRadarScreen()
{
}

vector<string> &split(const string &s, char delim, vector<string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}
vector<string> split(const string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}

void CZoomClutterRadarScreen::OnAsrContentLoaded(bool Loaded) {
	if (!Loaded)
		return;

	ZoomData.clear();
	string base_name = "ZOOM";
	const char * raw_data;

	// We loop through each entry in the ASR
	for (int i = 1; ; ++i)
	{
		string item_name = base_name + std::to_string(i);

		if ((raw_data = GetDataFromAsr(item_name.c_str())) == NULL)
			break;

		// Each line is formated this way "(ZOOM%ID):TYPE;NAME;LEVEL"
		vector<string> data = split(string(raw_data), ';');

		string type = data.at(0);
		string name = data.at(1);
		int level = std::stoi(data.at(3));

		int ElementType = EuroScopePlugIn::SECTOR_ELEMENT_ALL;

		if (type.compare("GEO"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_GEO;
		if (type.compare("AIRPORT"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_AIRPORT;
		if (type.compare("AIRSPACE"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_AIRSPACE;
		if (type.compare("ARTC"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_ARTC;
		if (type.compare("FIX"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_FIX;
		if (type.compare("FREETEXT"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_FREE_TEXT;
		if (type.compare("HIGHAIRWAY"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_HIGH_AIRWAY;
		if (type.compare("HIGHARTC"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_HIGH_ARTC;
		if (type.compare("INFO"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_INFO;
		if (type.compare("LOWAIRWAY"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_LOW_AIRWAY;
		if (type.compare("LOWARTC"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_LOW_ARTC;
		if (type.compare("NDB"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_NDB;
		if (type.compare("NUMBER"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_NUMBER;
		if (type.compare("POSITION"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_POSITION;
		if (type.compare("RADARS"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_RADARS;
		if (type.compare("REGIONS"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_REGIONS;
		if (type.compare("RUNWAY"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_RUNWAY;
		if (type.compare("SID"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_SID;
		if (type.compare("STAR"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_STAR;
		if (type.compare("VOR"))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_VOR;

		CSectorElement element;
		for (element = GetPlugIn()->SectorFileElementSelectFirst(ElementType);
			element.IsValid();
			element = GetPlugIn()->SectorFileElementSelectNext(element, ElementType))
		{
			string element_name = element.GetComponentName(0);

			if (name.compare(element_name))
				ZoomData.insert(std::pair<int, CSectorElement>(level, element)); break;
		}
	}
}

bool CZoomClutterRadarScreen::OnCompileCommand(const char * sCommandLine) {
	if (strcmp(sCommandLine, ".zs") != 0)
		return false;

	CPosition bottomLeft, TopRight;
	GetDisplayArea(&bottomLeft, &TopRight);

	int currentLevel = (int)bottomLeft.DistanceTo(TopRight);

	string t = "Current zoom level ";
	t.append(std::to_string(currentLevel));

	GetPlugIn()->DisplayUserMessage("Messages", "Zoom Clutter", t.c_str(), true, true, false, true, false);

	return true;
}

void CZoomClutterRadarScreen::OnRefresh(HDC hDC, int Phase) {

	if (Phase != REFRESH_PHASE_BEFORE_TAGS)
		return;

	CPosition bottomLeft, TopRight;
	GetDisplayArea(&bottomLeft, &TopRight);

	if (bottomLeft.DistanceTo(saveBottomLeft) == 0.0)
		return;

	saveBottomLeft = bottomLeft;

	int currentLevel = (int)bottomLeft.DistanceTo(TopRight);

	for (multimap<int, CSectorElement>::iterator itr = ZoomData.begin(); itr != ZoomData.end();) {
		ShowSectorFileElement(itr->second, itr->second.GetComponentName(0), (itr->first >= currentLevel));
	}

	RefreshMapContent();
}

CZoomClutterRadarScreen::~CZoomClutterRadarScreen()
{
}
