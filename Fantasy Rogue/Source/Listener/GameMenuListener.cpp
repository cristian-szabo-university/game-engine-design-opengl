#include "Listener/GameMenuListener.h"

GameMenuListener::GameMenuListener()
{

}

GameMenuListener::~GameMenuListener()
{

}

void GameMenuListener::vOnInit(void* pUserData)
{
	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	m_pThisLayer = vGetContext()->vFind("LayerGameMenu");
}

void GameMenuListener::vOnUpdate(int nCurrentTime)
{

}

void GameMenuListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		if (m_pThisLayer->vCheckMouseHover("ButtonContinue", nPosX, nPosY))
		{
			vGetContext()->vChange("LayerGameActive");
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonSave", nPosX, nPosY))
		{
			vGetContext()->vSave(m_pOptions->getSaveFileName());
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonExit", nPosX, nPosY))
		{
			vGetContext()->vChange("LayerMainMenu", new int(1));
		}
	}
}