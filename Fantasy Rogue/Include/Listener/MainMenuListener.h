#pragma once

#include "ZenoLibrary.h"

#include "GameOptions.h"

class MainMenuListener : public SceneListener
{
public:
	MainMenuListener();

	virtual ~MainMenuListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnUpdate(int nCurrentTime);

	virtual void vOnMouse(int nButton, int nState, int nPosX, int nPosY);

private:
	FantasyRogueOptions* m_pOptions;

	ISceneLayer* m_pThisLayer;

	bool m_bActive;

};