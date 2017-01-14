#pragma once

#include "ZenoLibrary.h"

#include "GameOptions.h"

class GameCombatListener : public SceneListener
{
public:
	GameCombatListener();

	virtual ~GameCombatListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnUpdate(int nCurrentTime);

	virtual void vOnMouse(int nButton, int nState, int nPosX, int nPosY);

private:
	const int MIN_DAMAGE;

	FantasyRogueOptions* m_pOptions;

	ISceneLayer* m_pThisLayer;

	IEntity* m_pPlayer;

	IEntity* m_pEnemy;

	bool m_bTurn;

	int m_nTotalDamage;

	int m_nItemDropCount;

	int m_nLastSpwanPosY;

	int battle(IEntity* pAttacker, IEntity* pDefender);

	void drop(IEntity* pObject, ISceneLayer* pLayer, int nPosX, int nPosY);

};

