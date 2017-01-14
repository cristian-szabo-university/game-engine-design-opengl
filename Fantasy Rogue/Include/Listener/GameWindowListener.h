#pragma once

#include "ZenoLibrary.h"

class GameWindowListener : public RenderListener
{
public:
	GameWindowListener();

	virtual ~GameWindowListener();

	virtual void vOnClose();

};

