#pragma once

#include "ZenoLibrary.h"

#include "GameOptions.h"

class GameShopListener : public SceneListener
{
public:
	GameShopListener();

	virtual ~GameShopListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnUpdate(int nCurrentTime);

	virtual void vOnMouse(int nButton, int nState, int nPosX, int nPosY);

private:
	FantasyRogueOptions* m_pOptions;

	ISceneLayer* m_pThisLayer;

	Entity* m_pArrow;

	Entity* m_pPlayer;

	std::string m_szPlayerSelect;

	int m_nLastSpwanPosY;

};