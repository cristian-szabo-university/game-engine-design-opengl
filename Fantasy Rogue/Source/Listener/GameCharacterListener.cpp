#include "Listener/GameCharacterListener.h"

GameCharacterListener::GameCharacterListener()
{

}

GameCharacterListener::~GameCharacterListener()
{

}

void GameCharacterListener::vOnInit(void* pUserData)
{
	m_pThisLayer = vGetContext()->vFind("LayerGameCharacter");

	m_pArrow = dynamic_cast<Entity*>(m_pThisLayer->vFind("Arrow"));

	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	m_pArrow->setPosition(-50, 0);

	m_pOptions->createObjectStats(m_pThisLayer->vFind("PlayerAttack"), m_pThisLayer, 200, m_pOptions->vGetWndHeight() / 2 + 50);

	m_pOptions->createObjectStats(m_pThisLayer->vFind("PlayerDefense"), m_pThisLayer, 200, m_pOptions->vGetWndHeight() / 2 + 100);

	m_pOptions->createObjectStats(m_pThisLayer->vFind("PlayerNeutral"), m_pThisLayer, 200, m_pOptions->vGetWndHeight() / 2 + 150);
}

void GameCharacterListener::vOnUpdate(int nCurrentTime)
{
	
}

void GameCharacterListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		IEntity* pObject;

		if ((pObject = m_pThisLayer->vCheckMouseHover("PlayerAttack", nPosX, nPosY)) != NULL)
		{
			m_pArrow->setPosition(pObject->vGetPosX(), pObject->vGetPosY() - pObject->vGetHeight() - 10);

			m_szPlayerSelect.assign(pObject->vGetName());
		}

		if ((pObject = m_pThisLayer->vCheckMouseHover("PlayerDefense", nPosX, nPosY)) != NULL)
		{
			m_pArrow->setPosition(pObject->vGetPosX(), pObject->vGetPosY() - pObject->vGetHeight() - 10);

			m_szPlayerSelect.assign(pObject->vGetName());
		}

		if ((pObject = m_pThisLayer->vCheckMouseHover("PlayerNeutral", nPosX, nPosY)) != NULL)
		{
			m_pArrow->setPosition(pObject->vGetPosX(), pObject->vGetPosY() - pObject->vGetHeight() - 10);

			m_szPlayerSelect.assign(pObject->vGetName());
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonNext", nPosX, nPosY) &&
			!m_szPlayerSelect.empty())
		{
			ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameActive");

			tinyxml2::XMLElement* pElem = m_pOptions->createObject("Player", 400, 300, m_szPlayerSelect.c_str());

			IEntity* pNewObject = Global<EntityFactory>::getInst()->vCreate(pElem);

			if (pNewObject)
			{
				pNextLayer->vAttach(pNewObject);
			}
			
			vGetContext()->vChange("LayerGameActive", new int(1));
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonBack", nPosX, nPosY))
		{
			vGetContext()->vChange("LayerMainMenu");
		}
	}
}
