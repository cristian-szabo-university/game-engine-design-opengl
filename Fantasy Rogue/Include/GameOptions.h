#pragma once

#include "ZenoLibrary.h"

class FantasyRogueOptions : public IGameOptions
{
public:
	FantasyRogueOptions();

	virtual ~FantasyRogueOptions();

	virtual const char* vGetWndTitle();

	virtual int vGetWndWidth();

	virtual int vGetWndHeight();

	virtual const char* vGetResourceFile();

	virtual const char* vGetLayoutFile();

	virtual const char* vGetCategoryFile();

	virtual const char* vGetFirstLayerName();

	const char* getSaveFileName();

	tinyxml2::XMLElement* createObject(const char* pName, int nPosX, int nPosY, const char* pCategory);

	tinyxml2::XMLElement* createObject(const char* pName, int nPosX, int nPosY, const char* pText, const char* pCategory);

	void createObjectStats(IEntity* pObject, ISceneLayer* pLayer, int nPosX, int nPosY);

	void createItemStats(IEntity* pObject, ISceneLayer* pLayer, int nPosX, int nPosY);

	void createText(const char* pText, const char* pName, ISceneLayer* pLayer, int nPosX, int nPosY, const char* pCategory = "Text");

	bool checkFile(const char*pFileName);

private:
	tinyxml2::XMLDocument m_XMLDoc;

};