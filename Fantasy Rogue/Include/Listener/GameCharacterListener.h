#pragma once

#include "ZenoLibrary.h"

#include "GameOptions.h"

class GameCharacterListener : public SceneListener
{
public:
	GameCharacterListener();

	virtual ~GameCharacterListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnUpdate(int nCurrentTime);

	virtual void vOnMouse(int nButton, int nState, int nPosX, int nPosY);

private:
	ISceneLayer* m_pThisLayer;

	FantasyRogueOptions* m_pOptions;

	Entity* m_pArrow;

	std::string m_szPlayerSelect;

};

