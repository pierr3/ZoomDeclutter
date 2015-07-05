#pragma once
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <EuroScopePlugIn.h>

using namespace EuroScopePlugIn;
using namespace std;

class CZoomClutterRadarScreen :
	public EuroScopePlugIn::CRadarScreen
{
public:
	CZoomClutterRadarScreen();
	virtual ~CZoomClutterRadarScreen();

	//---OnAsrContentLoaded--------------------------------------------

	inline virtual void OnAsrContentLoaded(bool Loaded);

	//---OnRefresh------------------------------------------------------

	inline virtual void OnRefresh(HDC hDC, int Phase);

	//---OnCompileCommand------------------------------------------------------

	inline virtual bool OnCompileCommand(const char * sCommandLine);

	//---startsWith-----------------------------------------

	inline virtual bool startsWith(const char *pre, const char *str)
	{
		size_t lenpre = strlen(pre), lenstr = strlen(str);
		return lenstr < lenpre ? false : strncmp(pre, str, lenpre) == 0;
	};

	inline virtual void OnAsrContentToBeClosed(void) {
		delete this;
	};

	multimap<int, CSectorElement> ZoomData;
	vector<string> CurrentlyDrawn;
	int saveLevel = 0;
};

