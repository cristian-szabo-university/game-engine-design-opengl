#include "Listener/IntroListener.h"

IntroListener::IntroListener()
{

}

IntroListener::~IntroListener()
{

}

void IntroListener::vOnInit(void* pUserData)
{
	m_nStartTime = SDL_GetTicks();
}

void IntroListener::vOnUpdate(int nCurrentTime)
{
	if (m_nStartTime + 1000 < nCurrentTime)
	{
		vGetContext()->vChange("LayerMainMenu");
	}
}
