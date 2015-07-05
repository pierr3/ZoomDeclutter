# Zoom Declutter Plugin
A EuroScope 3.2 zoom declutter plugin.

## What does it do?

Based on the current zoom level in EuroScope, it can display or hide sectors elements. The settings for the zoom are saved in the ASR, allowing you to have multiple configurations.

Example: Working on LFFF_CTR, an aircraft needs to intercept the LFPG ILS 09L, so you'd zoom in on LFPG, and the centerlines would appear, then just unzoom and back to the en-route view.

## How to use it

Load the plugin in EuroScope, and allow it to draw on the default EuroScope screen, plus all the screen types you want to use.

Zoom in to the first level you want elements to be displayed, then type in chat
```
.zs
```

It will give you in chat the current zoom level.

You'll then need to open your ASR file, and add the bottom of the a line like this:

```
PLUGIN:Zoom Declutter PlugIn:ZOOM1:FIX:RANUX:20
PLUGIN:Zoom Declutter PlugIn:ZOOM2:GEO:LFPB VPT 07:20
```

The format is as follows:
```
PLUGIN:Zoom Declutter PlugIn:ZOOMX:TYPE:NAME:LEVEL
```

ZOOMX: Replace the X with a number, starting from 1 and incrementing one by one

TYPE: It is the type of the element you want to have displayed, here are all element types available:

  * GEO
  * AIRPORT
  * AIRSPACE
  * ARTC
  * FIX
  * FREETEXT
  * HIGHAIRWAY
  * HIGHARTC
  * INFO
  * LOWAIRWAY
  * LOWARTC
  * NDB
  * NUMBER
  * POSITION
  * RADARS
  * REGIONS
  * RUNWAY
  * SID
  * STAR
  * VOR

NAME: The name of the item to display

LEVEL: The zoom level