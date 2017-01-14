#include "Listener/GameShopListener.h"

GameShopListener::GameShopListener()
{
	
}

GameShopListener::~GameShopListener()
{

}

void GameShopListener::vOnInit(void* pUserData)
{
	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	m_pThisLayer = vGetContext()->vFind("LayerGameShop");

	m_pArrow = dynamic_cast<Entity*>(m_pThisLayer->vFind("Arrow"));

	m_pArrow->setPosition(-50, 0);

	m_pPlayer = dynamic_cast<Entity*>(m_pThisLayer->vFind("Player"));

	m_pPlayer->setPosition(380, 130);

	m_szPlayerSelect.clear();

	m_nLastSpwanPosY = 150;

	m_pOptions->createItemStats(m_pThisLayer->vFind("HealthPack"), m_pThisLayer, 280, m_pOptions->vGetWndHeight() / 2 + 50);

	m_pOptions->createItemStats(m_pThisLayer->vFind("StimulantPack"), m_pThisLayer, 280, m_pOptions->vGetWndHeight() / 2 + 100);

	m_pOptions->createItemStats(m_pThisLayer->vFind("CombatPack"), m_pThisLayer, 280, m_pOptions->vGetWndHeight() / 2 + 150);
}

void GameShopListener::vOnUpdate(int nCurrentTime)
{
	m_pOptions->createObjectStats(m_pPlayer, m_pThisLayer, 200, 200);
}

void GameShopListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		IEntity* pObject;

		if ((pObject = m_pThisLayer->vCheckMouseHover("HealthPack", nPosX, nPosY)) != NULL)
		{
			m_pArrow->setPosition(pObject->vGetPosX() - 10, pObject->vGetPosY() - pObject->vGetHeight() - 25);

			m_szPlayerSelect.assign(pObject->vGetName());
		}

		if ((pObject = m_pThisLayer->vCheckMouseHover("StimulantPack", nPosX, nPosY)) != NULL)
		{
			m_pArrow->setPosition(pObject->vGetPosX() - 10, pObject->vGetPosY() - pObject->vGetHeight() - 25);

			m_szPlayerSelect.assign(pObject->vGetName());
		}

		if ((pObject = m_pThisLayer->vCheckMouseHover("CombatPack", nPosX, nPosY)) != NULL)
		{
			m_pArrow->setPosition(pObject->vGetPosX() - 10, pObject->vGetPosY() - pObject->vGetHeight() - 25);

			m_szPlayerSelect.assign(pObject->vGetName());
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonBuy", nPosX, nPosY) && !m_szPlayerSelect.empty())
		{
			int nItemPrice = m_pThisLayer->vFind(m_szPlayerSelect.c_str())->vGetComponent("Price")->vGet();

			if (m_pPlayer->vGetComponent("Money")->vGet() >= nItemPrice)
			{
				m_pPlayer->vGetComponent("Money")->vChange(-nItemPrice);

				ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameActive");

				tinyxml2::XMLElement* pElem = m_pOptions->createObject(
					(std::string("ItemPack") + std::to_string(rand() % 2013)).c_str(), 
					750, m_nLastSpwanPosY, 
					m_szPlayerSelect.c_str());

				IEntity* pNewObject = Global<EntityFactory>::getInst()->vCreate(pElem);

				m_nLastSpwanPosY += pNewObject->vGetHeight() + 15;

				if (pNewObject)
				{
					pNextLayer->vAttach(pNewObject);
				}
			}
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonBack", nPosX, nPosY))
		{
			ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameActive");

			IEntity* pShop = pNextLayer->vFind("Shop");

			m_pPlayer->setPosition(pShop->vGetPosX() - m_pPlayer->vGetWidth() - 10, pShop->vGetPosY());

			pNextLayer->vAttach(m_pPlayer);

			m_pThisLayer->vRemove(m_pPlayer->vGetName());

			vGetContext()->vChange("LayerGameActive");
		}
	}
}
