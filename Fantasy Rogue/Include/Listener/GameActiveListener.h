#pragma once

#include "ZenoLibrary.h"

#include "GameOptions.h"

class GameActiveListener : public SceneListener
{
public:
	GameActiveListener();

	virtual ~GameActiveListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnUpdate(int nCurrentTime);

	virtual void vOnKeyboard(int nButton, int nState);

private:
	bool m_bStart;

	FantasyRogueOptions* m_pOptions;

	ISceneLayer* m_pThisLayer;

	Entity* m_pPlayer;

	Entity* m_pEnemy;

	int m_nLastPosX;

	int m_nLastPosY;

	bool m_bFight;

	int m_nLastTime;

};
