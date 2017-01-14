#include "Listener/CreditsListener.h"

CreditsListener::CreditsListener()
{

}

CreditsListener::~CreditsListener()
{

}

void CreditsListener::vOnInit(void* pUserData)
{
	m_pOptions = dynamic_cast<FantasyRogueOptions*>(vGetOptions());

	m_pThisLayer = vGetContext()->vFind("LayerCredits");

	m_pOptions->createText("Designed by Cristian Szabo @ VideoGameLab", "TextHelp1", m_pThisLayer, 250, 200, "Text");

	m_pOptions->createText("Found at www.videogamelab.co.uk or cristiszabo93@gmail.com", "TextHelp2", m_pThisLayer, 170, 250, "Text");

	m_pOptions->createText("Thanks to Daniel Livingstone's tutorials for the", "TextHelp3", m_pThisLayer, 230, 300, "Text");

	m_pOptions->createText("Game Engine Design module at UWS 2013/2014", "TextHelp4", m_pThisLayer, 230, 350, "Text");
}


void CreditsListener::vOnUpdate(int nCurrentTime)
{

}

void CreditsListener::vOnMouse(int nButton, int nState, int nPosX, int nPosY)
{
	if (nButton == SDL_BUTTON_LEFT && nState == SDL_PRESSED)
	{
		if (m_pThisLayer->vCheckMouseHover("ButtonBack", nPosX, nPosY))
		{
			vGetContext()->vChange("LayerMainMenu");
		}
	}
}