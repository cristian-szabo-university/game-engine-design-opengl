#pragma once

#include "ZenoInterface.h"

IRenderTarget* createStringObject(tinyxml2::XMLElement* pElement);

IRenderTarget* createGraphicObject(tinyxml2::XMLElement* pElement);

class GameOptions : public IGameOptions
{
public:
	GameOptions();

	virtual ~GameOptions();

	virtual const char* vGetWndTitle();

	virtual int vGetWndWidth();

	virtual int vGetWndHeight();

	virtual const char* vGetResourceFile();

	virtual const char* vGetLayoutFile();

	virtual const char* vGetCategoryFile();

	virtual const char* vGetFirstLayerName();

};