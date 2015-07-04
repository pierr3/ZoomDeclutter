#pragma once
#include <map>
#include <string>
#include <sstream>
#include <vector>
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

	inline virtual void OnAsrContentToBeClosed(void) {
		delete this;
	};

protected:

	multimap<int, CSectorElement> ZoomData;

	CPosition saveBottomLeft;

};

