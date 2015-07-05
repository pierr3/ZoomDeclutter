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
	ZoomData.clear();
	const char * raw_data;
	CString str;
	
	GetPlugIn()->SelectActiveSectorfile();

	// We loop through each entry in the ASR
	for (int i = 1; ; i++)
	{
		// variable name
		str.Format("ZOOM%d", i);

		// get it from ASR
		if ((raw_data = GetDataFromAsr(str)) == NULL)
			break;

		// Each line is formated this way "(ZOOM%ID):TYPE:NAME:LEVEL"
		vector<string> data = split(string(raw_data), ':');

		string type = data.at(0);
		string name = data.at(1);
		int level = atoi(data.at(2).c_str());

		int ElementType = EuroScopePlugIn::SECTOR_ELEMENT_ALL;

		if (startsWith("GEO", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_GEO;
		if (startsWith("AIRPORT", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_AIRPORT;
		if (startsWith("AIRSPACE", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_AIRSPACE;
		if (startsWith("ARTC", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_ARTC;
		if (startsWith("FIX", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_FIX;
		if (startsWith("FREETEXT", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_FREE_TEXT;
		if (startsWith("HIGHAIRWAY", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_HIGH_AIRWAY;
		if (startsWith("HIGHARTC", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_HIGH_ARTC;
		if (startsWith("INFO", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_INFO;
		if (startsWith("LOWAIRWAY", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_LOW_AIRWAY;
		if (startsWith("LOWARTC", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_LOW_ARTC;
		if (startsWith("NDB", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_NDB;
		if (startsWith("NUMBER", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_NUMBER;
		if (startsWith("POSITION", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_POSITION;
		if (startsWith("RADARS", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_RADARS;
		if (startsWith("REGIONS", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_REGIONS;
		if (startsWith("RUNWAY", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_RUNWAY;
		if (startsWith("SID", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_SID;
		if (startsWith("STAR", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_STAR;
		if (startsWith("VOR", type.c_str()))
			ElementType = EuroScopePlugIn::SECTOR_ELEMENT_VOR;
		
		CSectorElement element;
		for (element = GetPlugIn()->SectorFileElementSelectFirst(ElementType);
			element.IsValid();
			element = GetPlugIn()->SectorFileElementSelectNext(element, ElementType))
		{
			string t = element.GetName();
			if (t == name) {
				ZoomData.insert(std::make_pair(level, element));
				break;
			}
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

	GetPlugIn()->DisplayUserMessage("Message", "Zoom Clutter", t.c_str(), true, true, false, true, false);

	return true;
}

void CZoomClutterRadarScreen::OnRefresh(HDC hDC, int Phase) {

	if (Phase != REFRESH_PHASE_BEFORE_TAGS)
		return;

	CPosition bottomLeft, TopRight;
	GetDisplayArea(&bottomLeft, &TopRight);

	int currentLevel = (int)bottomLeft.DistanceTo(TopRight);

	if (currentLevel == saveLevel)
		return;

	saveLevel = currentLevel;

	bool needRefresh = false;

	for (auto it : ZoomData) {
		bool displayElement = false;

		CSectorElement Element = it.second;

		string elementString = Element.GetName();
		elementString.append(Element.GetComponentName(0));
		elementString.append(std::to_string(it.first));

		if (it.first >= currentLevel && 
			std::find(CurrentlyDrawn.begin(), CurrentlyDrawn.end(), elementString) == CurrentlyDrawn.end()) {
			displayElement = true;
			needRefresh = true;
			CurrentlyDrawn.push_back(elementString);
			ShowSectorFileElement(Element, Element.GetComponentName(0), displayElement);
		}

		if (currentLevel > it.first &&
			std::find(CurrentlyDrawn.begin(), CurrentlyDrawn.end(), elementString) != CurrentlyDrawn.end()) {
			displayElement = false;
			needRefresh = true;
			CurrentlyDrawn.erase(std::find(CurrentlyDrawn.begin(), CurrentlyDrawn.end(), elementString));
			ShowSectorFileElement(Element, Element.GetComponentName(0), displayElement);
		}

	}

	if (needRefresh)
		RefreshMapContent();
}

CZoomClutterRadarScreen::~CZoomClutterRadarScreen()
{
}
