#include "GameOptions.h"

FantasyRogueOptions::FantasyRogueOptions()
{
	
}

FantasyRogueOptions::~FantasyRogueOptions()
{
	
}

const char* FantasyRogueOptions::vGetWndTitle()
{
	return "Fantasy Rogue";
}

int FantasyRogueOptions::vGetWndWidth()
{
	return 800;
}

int FantasyRogueOptions::vGetWndHeight()
{
	return 600;
}

const char* FantasyRogueOptions::vGetResourceFile()
{
	return "Resources/ResourceTree.xml";
}

const char* FantasyRogueOptions::vGetLayoutFile()
{
	return "Resources/LayoutTree.xml";
}

const char* FantasyRogueOptions::vGetCategoryFile()
{
	return "Resources/CategoryTree.xml";
}

const char* FantasyRogueOptions::vGetFirstLayerName()
{
	return "LayerIntro";
}

const char* FantasyRogueOptions::getSaveFileName()
{
	return "GameSaved.xml";
}

tinyxml2::XMLElement* FantasyRogueOptions::createObject(const char* pName, int nPosX, int nPosY, const char* pCategory)
{
	tinyxml2::XMLElement* pElem = m_XMLDoc.NewElement("Object");

	pElem->SetAttribute("Name", pName);

	pElem->SetAttribute("PosX", nPosX);

	pElem->SetAttribute("PosY", nPosY);

	pElem->SetAttribute("Category", pCategory);

	m_XMLDoc.LinkEndChild(pElem);

	return pElem;
}

tinyxml2::XMLElement* FantasyRogueOptions::createObject(const char* pName, int nPosX, int nPosY, const char* pText, const char* pCategory)
{
	tinyxml2::XMLElement* pElem = createObject(pName, nPosX, nPosY, pCategory);

	pElem->SetAttribute("Text", pText);

	return pElem;
}

void FantasyRogueOptions::createObjectStats(IEntity* pObject, ISceneLayer* pLayer, int nPosX, int nPosY)
{
	std::string szPlayerStats;

	szPlayerStats += std::string(pObject->vGetName()) + std::string(" -> Health: ") + std::to_string(pObject->vGetComponent("Health")->vGet());

	szPlayerStats += std::string(" | Strength: ") + std::to_string(pObject->vGetComponent("Strength")->vGet());

	szPlayerStats += std::string(" | Speed: ") + std::to_string(pObject->vGetComponent("Speed")->vGet());

	szPlayerStats += std::string(" | Money: ") + std::to_string(pObject->vGetComponent("Money")->vGet());

	createText(szPlayerStats.c_str(), (std::string(pObject->vGetName()) + std::string("Stats")).c_str(), pLayer, nPosX, nPosY);
}

void FantasyRogueOptions::createItemStats(IEntity* pObject, ISceneLayer* pLayer, int nPosX, int nPosY)
{
	std::string szPlayerStats;

	szPlayerStats += std::string(pObject->vGetName()) + std::string(" -> Price: ") + std::to_string(pObject->vGetComponent("Price")->vGet());

	szPlayerStats += std::string(" | Bonus +") + std::to_string(pObject->vGetComponent("Bonus")->vGet());

	createText(szPlayerStats.c_str(), (std::string(pObject->vGetName()) + std::string("Stats")).c_str(), pLayer, nPosX, nPosY);
}

void FantasyRogueOptions::createText(const char* pText, const char* pName, ISceneLayer* pLayer, int nPosX, int nPosY, const char* pCategory)
{
	std::string szName(std::string("Text") + std::string(pName));

	pLayer->vErase(szName.c_str());

	tinyxml2::XMLElement* pElem = createObject(szName.c_str(), nPosX, nPosY, pText, pCategory);	

	IEntity* pNewObject = Global<EntityFactory>::getInst()->vCreate(pElem);

	if (pNewObject)
	{
		pLayer->vAttach(pNewObject);
	}
}

bool FantasyRogueOptions::checkFile(const char*pFileName)
{
	bool bState;

	std::ofstream file;

	file.open(pFileName, std::ofstream::in);

	bState = file.is_open();

	file.close();

	return bState;
}
