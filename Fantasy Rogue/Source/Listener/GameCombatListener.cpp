#include <iostream>

#include "Listener/GameCombatListener.h"

GameCombatListener::GameCombatListener() : MIN_DAMAGE(2)
{
	m_nItemDropCount = 0;

	m_nLastSpwanPosY = 150;
}

GameCombatListener::~GameCombatListener()
{

}

void GameCombatListener::vOnInit(void* pUserData)
{
	m_pThisLayer = vGetContext()->vFind("LayerGameCombat");

	m_pPlayer = m_pThisLayer->vFind("Player");

	m_pEnemy = m_pThisLayer->vFind("Enemy");

	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	if (m_pPlayer->vGetComponent("Speed")->vGet() > m_pEnemy->vGetComponent("Speed")->vGet())
	{
		m_bTurn = true;
	}
	else
	{
		if (m_pPlayer->vGetComponent("Speed")->vGet() < m_pEnemy->vGetComponent("Speed")->vGet())
		{
			m_bTurn = false;
		}
		else
		{
			m_bTurn = ((rand() % 2) == 1) ? true : false;
		}
	}

	m_nTotalDamage = 0;
}

void GameCombatListener::vOnUpdate(int nCurrentTime)
{
	m_pOptions->createObjectStats(m_pPlayer, m_pThisLayer, 200, 150);

	m_pOptions->createObjectStats(m_pEnemy, m_pThisLayer, 200, 200);

	if (m_pPlayer->vGetComponent("Health")->vGet() <= 0)
	{
		ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameOver");

		pNextLayer->vAttach(m_pPlayer);

		m_pThisLayer->vRemove(m_pPlayer->vGetName());

		m_pThisLayer->vErase(m_pEnemy->vGetName());

		m_pEnemy = NULL;

		vGetContext()->vChange("LayerGameOver");
	}

	if (m_pEnemy->vGetComponent("Health")->vGet() <= 0)
	{
		ISceneLayer* pNextLayer = vGetContext()->vFind("LayerGameActive");

		m_pPlayer->vGetComponent("Money")->vChange(m_pEnemy->vGetComponent("Money")->vGet());

		int nAddHealth = m_nTotalDamage / 2;

		if ((m_pPlayer->vGetComponent("Health")->vGet() + nAddHealth) <= 
			m_pPlayer->vGetComponent("MaxHealth")->vGet())
		{
			m_pPlayer->vGetComponent("Health")->vChange(nAddHealth);
		}
		else
		{
			m_pPlayer->vGetComponent("Health")->vSet(
			
			m_pPlayer->vGetComponent("MaxHealth")->vGet());
		}

		pNextLayer->vAttach(m_pPlayer);

		m_pThisLayer->vRemove(m_pPlayer->vGetName());

		drop(m_pEnemy, pNextLayer, 750, m_nLastSpwanPosY);

		m_nLastSpwanPosY += 50;

		m_pThisLayer->vErase(m_pEnemy->vGetName());

		m_pEnemy = NULL;

		vGetContext()->vChange("LayerGameActive");
	}
}

void GameCombatListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		if (m_pThisLayer->vCheckMouseHover("ButtonBattle", nPosX, nPosY))
		{
			if (m_bTurn)
			{
				m_nTotalDamage += battle(m_pPlayer, m_pEnemy);

				m_bTurn = false;
			}
			else
			{
				m_nTotalDamage += battle(m_pEnemy, m_pPlayer);

				m_bTurn = true;
			}
		}
	}
}

int GameCombatListener::battle(IEntity* pAttacker, IEntity* pDefender)
{
	int nDamage = (rand() % (pAttacker->vGetComponent("Strength")->vGet() - MIN_DAMAGE)) + MIN_DAMAGE;

	pDefender->vGetComponent("Health")->vChange(-nDamage);

	return nDamage;
}

void GameCombatListener::drop(IEntity* pObject, ISceneLayer* pLayer, int nPosX, int nPosY)
{
	int nRandNum = rand() % 100 + 1;

	int nDropRate, nItemRate;

	nDropRate = pObject->vGetComponent("Drop")->vGet();

	if (nRandNum <= nDropRate)
	{
		std::string szItems[3] = {"HealthPack", "CombatPack", "StimulantPack"};

		int nItemIndex = 0;

		while (nItemIndex < 3)
		{
			nRandNum = rand() % 100 + 1;

			nItemRate = Global<EntityFactory>::getInst()->vFind(szItems[nItemIndex].c_str(), "Drop")->vGet();

			if (nRandNum <= nItemRate)
			{	
				m_nItemDropCount++;

				std::string szItems[3] = {"HealthPack", "CombatPack", "StimulantPack"};
				
				tinyxml2::XMLElement* pElem = m_pOptions->createObject((std::string("PackDrop") + std::to_string(m_nItemDropCount)).c_str(),
					nPosX, nPosY, szItems[nItemIndex].c_str());

				IEntity* pNewObject = Global<EntityFactory>::getInst()->vCreate(pElem);

				if (pNewObject)
				{
					pLayer->vAttach(pNewObject);
				}

				break;
			}

			nItemIndex++;
		}
	}
}
