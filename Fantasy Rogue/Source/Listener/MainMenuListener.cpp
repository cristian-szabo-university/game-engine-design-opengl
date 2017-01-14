#include "Listener/MainMenuListener.h"

#include <iostream>

MainMenuListener::MainMenuListener()
{
	m_bActive = true;
}

MainMenuListener::~MainMenuListener()
{

}

void MainMenuListener::vOnInit(void* pUserData)
{
	if (pUserData)
	{
		m_bActive = (*static_cast<int*>(pUserData) != 0) ? true : false;
	}

	if (m_bActive != false)
	{
		vGetContext()->vReset();

		if (vGetContext()->vLoad(vGetOptions()->vGetLayoutFile()) != true)
		{
			vGetContext()->vQuit();
		}
	}

	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	m_pThisLayer = vGetContext()->vFind("LayerMainMenu");
}

void MainMenuListener::vOnUpdate(int nCurrentTime)
{
	
}

void MainMenuListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		if (m_pThisLayer->vCheckMouseHover("ButtonStart", nPosX, nPosY))
		{
			vGetContext()->vChange("LayerGameCharacter");
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonLoad", nPosX, nPosY))
		{
			if (m_pOptions->checkFile(m_pOptions->getSaveFileName()))
			{
				vGetContext()->vReset();

				if (vGetContext()->vLoad(m_pOptions->getSaveFileName()) != true)
				{
					vGetContext()->vQuit();
				}
				else
				{
					vGetContext()->vChange("LayerGameActive", new int(1));

					m_pThisLayer = vGetContext()->vFind("LayerMainMenu");
				}
			}
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonCredits", nPosX, nPosY))
		{
			vGetContext()->vChange("LayerCredits");
		}

		if (m_pThisLayer->vCheckMouseHover("ButtonQuit", nPosX, nPosY))
		{
			vGetContext()->vQuit();
		}
	}
}
