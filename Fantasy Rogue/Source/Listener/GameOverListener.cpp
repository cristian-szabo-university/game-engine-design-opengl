#include "Listener/GameOverListener.h"

GameOverListener::GameOverListener()
{

}

GameOverListener::~GameOverListener()
{

}

void GameOverListener::vOnInit(void* pUserData)
{
	m_pThisLayer = vGetContext()->vFind("LayerGameOver");

	m_pPlayer = dynamic_cast<Entity*>(m_pThisLayer->vFind("Player"));

	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	m_pPlayer->setPosition(m_pOptions->vGetWndWidth() / 2 - 20, m_pOptions->vGetWndHeight() / 2);

	if (m_pPlayer->vGetComponent("Health")->vGet() <= 0)
	{
		m_pOptions->createText("You Lost! ", "Defeat", m_pThisLayer, 300, 230, "Title");
	}
	else
	{
		m_pOptions->createText("You Win!", "Victory", m_pThisLayer, 300, 230, "Title");
	}
}

void GameOverListener::vOnUpdate(int nCurrentTime)
{

}

void GameOverListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		if (m_pThisLayer->vCheckMouseHover("ButtonExit", nPosX, nPosY))
		{
			m_pThisLayer->vErase("Player");

			vGetContext()->vChange("LayerMainMenu", new int(1));
		}
	}
}
