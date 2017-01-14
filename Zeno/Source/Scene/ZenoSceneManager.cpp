#include "Scene/ZenoSceneManager.h"

#include "ZenoTemplate.h"
#include "Resource/ZenoResourceManager.h"
#include "Entity/ZenoENtityFactory.h"

SceneManager::SceneManager()
{
	
}

SceneManager::~SceneManager()
{
	vReset();

	for (auto iterListener = m_mapListener.begin();
		iterListener != m_mapListener.end();
		iterListener++)
    {
		ZENO_DELETE iterListener->second;
	}

	m_mapListener.clear();
}

bool SceneManager::vLoad(const char* pFileName)
{
	std::string szFileName(pFileName);

	if (szFileName.empty() || !szFileName.find(".xml"))
	{
		return false;
	}

	tinyxml2::XMLDocument pDocument;

	if (pDocument.LoadFile(szFileName.c_str()) == tinyxml2::XML_ERROR_FILE_NOT_FOUND)
	{
		return false;
	}

	tinyxml2::XMLElement* pRoot = pDocument.FirstChildElement("Layouts");

	if (!pRoot)
	{
		return false;
	}

	for (tinyxml2::XMLNode* pLayerNode = pRoot->FirstChild();
		pLayerNode;
		pLayerNode = pLayerNode->NextSibling())
	{
		tinyxml2::XMLElement* pLayerElement = pLayerNode->ToElement();

		if (!pLayerElement ||
			_stricmp(pLayerElement->Name(), "Layer") != NULL)
		{
			continue;
		}

		const char* pName = pLayerElement->Attribute("Name");

		if (!pName)
		{
			continue;
		}

		ISceneLayer* pLayer = ZENO_NEW SceneLayer(pName);

		for (auto iterLayer = m_listLayer.begin();
			iterLayer != m_listLayer.end();
			iterLayer++)
		{
			if (_stricmp((*iterLayer)->vGetName(), pLayer->vGetName()) == NULL)
			{
				m_listLayer.erase(iterLayer);

				break;
			}
		}

		for (tinyxml2::XMLNode* pObjectNode = pLayerElement->FirstChild();
			pObjectNode;
			pObjectNode = pObjectNode->NextSibling())
		{
			tinyxml2::XMLElement* pObjectElement = pObjectNode->ToElement();

			if (!pObjectElement ||
				_stricmp(pObjectElement->Name(), "Object") != NULL)
			{
				continue;
			}

			IEntity* pObject = Global<EntityFactory>::getInst()->vCreate(pObjectElement);

			if (pObject)
			{
				pLayer->vAttach(pObject);
			}
		}

		m_listLayer.push_back(pLayer);
	}

	return true;
}

void SceneManager::vSave(const char* pFileName)
{
	tinyxml2::XMLDocument pDocument;

	tinyxml2::XMLElement* pElemLayout = pDocument.NewElement("Layouts");

	for (auto iterLayer = m_listLayer.begin();
		iterLayer != m_listLayer.end();
		iterLayer++)
    {
		tinyxml2::XMLElement* pElemLayer = (*iterLayer)->vToXML(&pDocument);

		pElemLayout->LinkEndChild(pElemLayer);
    }

	pDocument.LinkEndChild(pElemLayout);

	pDocument.SaveFile(pFileName);
}

void SceneManager::vChange(const char* pLayerName, void* pUserData)
{
	auto iterLayout = m_mapListener.find(pLayerName);

	if (iterLayout != m_mapListener.end())
	{
		iterLayout->second->vOnInit(pUserData);
	}

	ISceneLayer* pLayer = vFind(pLayerName);

	if (pLayer)
	{
		m_pCurrentLayer = pLayer;
	}
}

ISceneLayer* SceneManager::vFind(const char* pName)
{
    for(auto iterLayer = m_listLayer.begin();
		iterLayer != m_listLayer.end();
		iterLayer++)
    {
		if(_stricmp((*iterLayer)->vGetName(), pName) == NULL)
		{
            return (*iterLayer);
		}
    }

    return NULL;
}

void SceneManager::vRemove(const char* pName)
{
	auto iterLayer = m_listLayer.begin();

	while (iterLayer != m_listLayer.end())
    {
		if(_stricmp((*iterLayer)->vGetName(), pName) == NULL)
		{
            iterLayer = m_listLayer.erase(iterLayer);
		}

		iterLayer++;
    }
}

void SceneManager::vAttach(ISceneListener* pListener, const char* pLayerName)
{
	m_mapListener.insert(std::make_pair(std::string(pLayerName), pListener));
}

void SceneManager::vOnEvent(SDL_KeyboardEvent* pEvent)
{
	switch(pEvent->type)
	{
	case SDL_KEYDOWN :
	case SDL_KEYUP :
		{
			auto iterLayout = m_mapListener.find(m_pCurrentLayer->vGetName());

			if (iterLayout != m_mapListener.end())
			{
				iterLayout->second->vOnKeyboard(pEvent->keysym.sym, pEvent->state);
			}

			break;
		}
	}
}

void SceneManager::vOnEvent(SDL_MouseButtonEvent* pEvent)
{
	switch(pEvent->type)
	{
	case SDL_MOUSEBUTTONDOWN :
	case SDL_MOUSEBUTTONUP :
		{
			auto iterLayout = m_mapListener.find(m_pCurrentLayer->vGetName());

			if (iterLayout != m_mapListener.end())
			{
				iterLayout->second->vOnMouse(pEvent->button, pEvent->state, 
					pEvent->x, pEvent->y);
			}

			break;
		}
	}
}

void SceneManager::vUpdate()
{
	m_nCurrentTime = SDL_GetTicks();

	if (m_pCurrentLayer)
	{
		m_pCurrentLayer->vUpdate();

		auto iterLayout = m_mapListener.find(m_pCurrentLayer->vGetName());

		if (iterLayout != m_mapListener.end())
		{
			iterLayout->second->vOnUpdate(m_nCurrentTime);
		}
	}
}

void SceneManager::vRender()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	if (m_pCurrentLayer)
	{
		m_pCurrentLayer->vRender();
	}
}

void SceneManager::vReset()
{
	m_pCurrentLayer = NULL;

	for (auto iterLayer = m_listLayer.begin();
		iterLayer != m_listLayer.end();
		iterLayer++)
    {
		ZENO_DELETE (*iterLayer);	
    }

	m_listLayer.clear();
}

void SceneManager::vQuit()
{
	SDL_Event sEvent;

	sEvent.type = SDL_QUIT;

	SDL_PushEvent(&sEvent);
}