#pragma once

#include "ZenoLibrary.h"

class IntroListener : public SceneListener
{
public:
	IntroListener();

	virtual ~IntroListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnUpdate(int nCurrentTime);

private:
	int m_nStartTime;

	SceneLayer* m_pLayer;

	SceneLayer* m_pNextLayer;

};