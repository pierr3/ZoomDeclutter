#pragma once
#include <EuroScopePlugIn.h>
#include "ZoomClutterRadarScreen.h"

class CZoomDeclutterPlugin :
	public EuroScopePlugIn::CPlugIn
{
public:
	CZoomDeclutterPlugin();

	//---OnRadarScreenCreated------------------------------------------

	inline virtual EuroScopePlugIn::CRadarScreen * OnRadarScreenCreated(const char * sDisplayName,
		bool NeedRadarContent,
		bool GeoReferenced,
		bool CanBeSaved,
		bool CanBeCreated);

	virtual ~CZoomDeclutterPlugin();
};

