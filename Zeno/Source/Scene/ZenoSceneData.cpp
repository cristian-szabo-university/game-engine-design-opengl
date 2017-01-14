#include <iostream>

#include "Scene/ZenoSceneData.h"

SceneListener::SceneListener()
{
	m_pContext = NULL;

	m_pOptions = NULL;
}

SceneListener::~SceneListener()
{

}

void SceneListener::vOnInit(void* pUserData)
{

}

void SceneListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	
}

void SceneListener::vOnKeyboard(SDL_Keycode nKeyn, int nState)
{

}

ISceneManager* SceneListener::vGetContext()
{
	return m_pContext;
}

IGameOptions* SceneListener::vGetOptions()
{
	return m_pOptions;
}

void SceneListener::vOnClose()
{

}

SceneLayer::SceneLayer(const char* pName)
{
	if (pName)
	{
		m_szName.assign(pName);
	}
	else
	{
		m_szName.assign("Unknown");
	}
}

SceneLayer::~SceneLayer()
{
	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		ZENO_DELETE (*iterObject);
	}

	m_vecEntity.clear();
}

void SceneLayer::vAttach(IEntity* pObject)
{
	m_vecEntity.push_back(pObject);
}

const char* SceneLayer::vGetName()
{
	return m_szName.c_str();
}

bool checkCollision(IEntity* pTargetObject, IEntity* pEnemyObject) 
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	left1 = pTargetObject->vGetPosX();
	left2 = pEnemyObject->vGetPosX();

	right1 = pTargetObject->vGetPosX() + pTargetObject->vGetWidth();
	right2 = pEnemyObject->vGetPosX() + pEnemyObject->vGetWidth();

	top1 = pTargetObject->vGetPosY();
	top2 = pEnemyObject->vGetPosY();

	bottom1 = pTargetObject->vGetPosY() + pTargetObject->vGetHeight();
	bottom2 = pEnemyObject->vGetPosY() + pEnemyObject->vGetHeight();

	if (bottom1 < top2) return false;
	if (top1 > bottom2) return false;

	if (right1 < left2) return false;
	if (left1 > right2) return false;

	return true;
};

IEntity* SceneLayer::vDetectCollision(const char* pName)
{
	IEntity* pObject = vFind(pName);

	if (!pObject)
	{
		return NULL;
	}

	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		if ((*iterObject) != pObject)
		{
			if (checkCollision(pObject, (*iterObject)))
			{
				return (*iterObject);
			}	
		}
	}

	return NULL;
}

IEntity* SceneLayer::vCheckMouseHover(const char* pName, int nMousePosX, int nMousePosY)
{
	IEntity* pObject = vFind(pName);

	if (nMousePosX > pObject->vGetPosX() && nMousePosX < (pObject->vGetPosX() + pObject->vGetWidth()))
	{
		if (nMousePosY > pObject->vGetPosY() && nMousePosY < (pObject->vGetPosY() + pObject->vGetHeight()))
		{
			return pObject;
		}
	}

	return NULL;
}

void SceneLayer::vUpdate()
{
	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		(*iterObject)->vUpdate();
	}
}

void SceneLayer::vRender()
{
	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		(*iterObject)->vRender();
	}
}

tinyxml2::XMLElement* SceneLayer::vToXML(tinyxml2::XMLDocument* pDoc)
{
	tinyxml2::XMLElement* pElem = pDoc->NewElement("Layer");

	pElem->SetAttribute("Name", m_szName.c_str());

	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		tinyxml2::XMLElement* pObject = (*iterObject)->vToXML(pDoc);

		pElem->LinkEndChild(pObject);
	}

	return pElem;
}

IEntity* SceneLayer::vFind(const char* pName)
{
	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		if (_stricmp((*iterObject)->vGetName(), pName) == NULL)
		{
			return (*iterObject);
		}
	}

	return NULL;
}

void SceneLayer::vRemove(const char* pName)
{
	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		if (_stricmp((*iterObject)->vGetName(), pName) == NULL)
		{
			iterObject = m_vecEntity.erase(iterObject);

			break;
		}
	}
}

void SceneLayer::vErase(const char* pName)
{
	for (auto iterObject = m_vecEntity.begin();
		iterObject != m_vecEntity.end();
		iterObject++)
	{
		if (_stricmp((*iterObject)->vGetName(), pName) == NULL)
		{
			ZENO_DELETE (*iterObject);

			iterObject = m_vecEntity.erase(iterObject);

			break;
		}
	}
};