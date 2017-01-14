#include "Game/ZenoGameData.h"

#include "Render/ZenoRenderData.h"

#include "ZenoTemplate.h"
#include "Resource/ZenoResourceManager.h"

IRenderTarget* createStringObject(tinyxml2::XMLElement* pElement)
{
	const char* pText = pElement->Attribute("Text");

	StringObject* pObject = ZENO_NEW StringObject;

	pObject->setText(pText);

	return pObject;
}

IRenderTarget* createGraphicObject(tinyxml2::XMLElement* pElement)
{
	return ZENO_NEW GraphicObject;
}

GameOptions::GameOptions()
{

}

GameOptions::~GameOptions()
{

}

const char* GameOptions::vGetWndTitle()
{
	return "Unknown";
}

int GameOptions::vGetWndWidth()
{
	return 600;
}

int GameOptions::vGetWndHeight()
{
	return 480;
}

const char* GameOptions::vGetResourceFile()
{
	return "Resource/AssetTree.xml";
}

const char* GameOptions::vGetLayoutFile()
{
	return "Resource/LayoutTree.xml";
}

const char* GameOptions::vGetCategoryFile()
{
	return "Resource/CategoryTree.xml";
}

const char* GameOptions::vGetFirstLayerName()
{
	return "LayerBegin";
}