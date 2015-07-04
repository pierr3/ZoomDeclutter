#include "stdafx.h"
#include "ZoomDeclutterPlugin.h"

#define MY_PLUGIN_NAME      "Zoom Declutter PlugIn"
#define MY_PLUGIN_VERSION   "1.0"
#define MY_PLUGIN_DEVELOPER "Pierre Ferran"
#define MY_PLUGIN_COPYRIGHT "MIT License (c) 2015"

CZoomDeclutterPlugin::CZoomDeclutterPlugin(void) : CPlugIn(EuroScopePlugIn::COMPATIBILITY_CODE,
	MY_PLUGIN_NAME,
	MY_PLUGIN_VERSION,
	MY_PLUGIN_DEVELOPER,
	MY_PLUGIN_COPYRIGHT)
{

}

//---OnRadarScreenCreated------------------------------------------

EuroScopePlugIn::CRadarScreen * CZoomDeclutterPlugin::OnRadarScreenCreated(const char * sDisplayName,
                                                                           bool NeedRadarContent,
                                                                           bool GeoReferenced,
                                                                           bool CanBeSaved,
                                                                           bool CanBeCreated)
{
        return new CZoomClutterRadarScreen;
}


CZoomDeclutterPlugin::~CZoomDeclutterPlugin()
{
}
