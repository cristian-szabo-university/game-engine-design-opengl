// Windows.h required for Win32 API and ctime header for randomizing
#include <Windows.h>

// Import Zeno library header files
#include "ZenoLibrary.h"

#include "GameOptions.h"

#include "Listener/GameWindowListener.h"

#include "Listener/IntroListener.h"
#include "Listener/MainMenuListener.h"
#include "Listener/GameMenuListener.h"
#include "Listener/GameCharacterListener.h"
#include "Listener/GameActiveListener.h"
#include "Listener/GameCombatListener.h"
#include "Listener/GameOverListener.h"
#include "Listener/GameShopListener.h"
#include "Listener/CreditsListener.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpCmdShow, int nCmdLine)
{
	// Activate console for debug purposes
	/*
	AllocConsole();

	FILE* pConOutput;

	freopen_s(&pConOutput, "conout$", "w", stdout);
	*/
	IGameManager* pMyGameManager = Global<GameManager>::getInst();

	if (pMyGameManager->vInit(ZENO_NEW FantasyRogueOptions) != true)
	{
		return 1;
	}

	pMyGameManager->vAttachWindowListener(ZENO_NEW GameWindowListener);

	pMyGameManager->vAttachLayerListener(ZENO_NEW IntroListener, "LayerIntro");

	pMyGameManager->vAttachLayerListener(ZENO_NEW MainMenuListener, "LayerMainMenu");

	pMyGameManager->vAttachLayerListener(ZENO_NEW GameMenuListener, "LayerGameMenu");

	pMyGameManager->vAttachLayerListener(ZENO_NEW GameCharacterListener, "LayerGameCharacter");

	pMyGameManager->vAttachLayerListener(ZENO_NEW GameActiveListener, "LayerGameActive");

	pMyGameManager->vAttachLayerListener(ZENO_NEW GameCombatListener, "LayerGameCombat");

	pMyGameManager->vAttachLayerListener(ZENO_NEW GameOverListener, "LayerGameOver");

	pMyGameManager->vAttachLayerListener(ZENO_NEW GameShopListener, "LayerGameShop");

	pMyGameManager->vAttachLayerListener(ZENO_NEW CreditsListener, "LayerCredits");

	pMyGameManager->vPostInit();

	while (pMyGameManager->vIsRunning() == true)
	{
		pMyGameManager->vTriggerEvents();
	}

	ZENO_DELETE pMyGameManager;
	
	// Release the allocated console
	// FreeConsole();

	return 0;
}