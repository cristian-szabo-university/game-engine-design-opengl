#include "Listener/GameActiveListener.h"

#include <iostream>

GameActiveListener::GameActiveListener()
{
	m_bStart = false;
}

GameActiveListener::~GameActiveListener()
{

}

void GameActiveListener::vOnInit(void* pUserData)
{
	if (pUserData)
	{
		m_bStart = !*static_cast<int*>(pUserData);
	}

	if (m_bStart != true)
	{
		m_pThisLayer = vGetContext()->vFind("LayerGameActive");

		m_pPlayer = dynamic_cast<Entity*>(m_pThisLayer->vFind("Player"));

		m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

		m_bFight = false;

		m_bStart = true;

		m_nLastTime = 0;
	}
}

void GameActiveListener::vOnUpdate(int nCurrentTime)
{
	IEntity* pObject = m_pThisLayer->vDetectCollision("Player");

	m_pOptions->createObjectStats(m_pPlayer, m_pThisLayer, 20, m_pOptions->vGetWndHeight() - 25);

	m_pOptions->createText((std::string("Render: ") + std::to_string(nCurrentTime - m_nLastTime) + std::string(" ms/frame")).c_str(), 
		"FPS", m_pThisLayer, m_pOptions->vGetWndWidth() - 150, 10);

	m_nLastTime = nCurrentTime;

	if (m_bFight == true)
	{
		m_pPlayer->setPosition(m_nLastPosX, m_nLastPosY);

		m_bFight = false;
	}

	if (pObject &&
		(_stricmp(pObject->vGetCategory(), "RaiderEnemy") == NULL ||
		_stricmp(pObject->vGetCategory(), "BruteEnemy") == NULL ||
		_stricmp(pObject->vGetCategory(), "FodderEnemy") == NULL))
	{
		m_pEnemy = dynamic_cast<Entity*>(pObject);

		ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameCombat");

		m_pEnemy->setName("Enemy");

		m_pEnemy->setPosition(560, 300);

		pNextLayer->vAttach(m_pEnemy);

		m_nLastPosX = m_pPlayer->vGetPosX();

		m_nLastPosY = m_pPlayer->vGetPosY();

		m_pPlayer->setPosition(200, 300);

		pNextLayer->vAttach(m_pPlayer);

		m_pThisLayer->vRemove(m_pPlayer->vGetName());

		m_pThisLayer->vRemove(m_pEnemy->vGetName());

		m_pEnemy = NULL;

		m_bFight = true;

		vGetContext()->vChange("LayerGameCombat");
	}

	if (pObject && _stricmp(pObject->vGetCategory(), "HealthPack") == NULL)
	{
		int nHealth = m_pPlayer->vGetComponent("Health")->vGet();

		int nMaxHealth = m_pPlayer->vGetComponent("MaxHealth")->vGet();

		if (nHealth < nMaxHealth)
		{
			m_pPlayer->vGetComponent("Health")->vSet(nMaxHealth);
		}
		else
		{
			m_pPlayer->vGetComponent("MaxHealth")->vChange(1);
		}

		m_pThisLayer->vErase(pObject->vGetName());

		pObject = NULL;
	}

	if (pObject && _stricmp(pObject->vGetCategory(), "CombatPack") == NULL)
	{
		m_pPlayer->vGetComponent("Speed")->vChange(pObject->vGetComponent("Bonus")->vGet());

		m_pThisLayer->vErase(pObject->vGetName());

		pObject = NULL;
	}

	if (pObject && _stricmp(pObject->vGetCategory(), "StimulantPack") == NULL)
	{
		m_pPlayer->vGetComponent("Strength")->vChange(pObject->vGetComponent("Bonus")->vGet());

		m_pThisLayer->vErase(pObject->vGetName());

		pObject = NULL;
	}

	if (pObject && _stricmp(pObject->vGetCategory(), "Shop") == NULL)
	{
		ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameShop");

		pNextLayer->vAttach(m_pPlayer);

		m_pThisLayer->vRemove(m_pPlayer->vGetName());

		vGetContext()->vChange("LayerGameShop");
	}
}

void GameActiveListener::vOnKeyboard(int nButton, int nState)
{
	if (nState == SDL_PRESSED)
	{
		switch (nButton)
		{
		case SDLK_LEFT :
			{
				m_pPlayer->setDirection(-5, 0);

				break;
			}
		case SDLK_RIGHT :
			{
				m_pPlayer->setDirection(5, 0);

				break;
			}
		case SDLK_UP :
			{
				m_pPlayer->setDirection(0, -5);

				break;
			}
		case SDLK_DOWN :
			{
				m_pPlayer->setDirection(0, 5);

				break;
			}
		case SDLK_ESCAPE :
			{
				vGetContext()->vChange("LayerGameMenu");

				break;
			}
		}
	}
}
