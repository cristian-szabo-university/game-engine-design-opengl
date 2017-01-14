#include <iostream>

#include "Game/ZenoGameManager.h"

GameManager::GameManager()
{
	m_bReady = false;

	m_nWndIndex = 0;
}

GameManager::~GameManager()
{
	ZENO_DELETE m_pGameOptions;

	ZENO_DELETE m_pSceneManager;

	ZENO_DELETE m_pEntityFactory;

	ZENO_DELETE m_pRenderManager;

	ZENO_DELETE m_pResourceManager;

	SDL_Quit();
}

bool GameManager::vInit(IGameOptions* pOptions)
{
	if (m_bReady == true)
	{
		return false;
	}
	
	if (SDL_Init(NULL) < 0)
	{
		return false;
	}
	
	m_pResourceManager = Global<ResourceManager>::getInst();

	if (m_pResourceManager->vInit() != true)
	{
		return false;
	}

	if (m_pResourceManager->vLoad(pOptions->vGetResourceFile()) != true)
	{
		return false;
	}

	m_pRenderManager = Global<RenderManager>::getInst();

	if (m_pRenderManager->vInit() != true)
	{
		return false;
	}

	m_nWndIndex = m_pRenderManager->vCreate(
		pOptions->vGetWndWidth(), pOptions->vGetWndHeight(), 
		pOptions->vGetWndTitle());

	if (!m_nWndIndex)
	{
		return false;
	}
	
	m_pEntityFactory = Global<EntityFactory>::getInst();

	if (m_pEntityFactory->vLoad(pOptions->vGetCategoryFile()) != true)
	{
		return false;
	}

	m_pEntityFactory->vRegister("Graphic", &createGraphicObject);

	m_pEntityFactory->vRegister("String", &createStringObject);

	m_pSceneManager = ZENO_NEW SceneManager;

	if (m_pSceneManager->vLoad(pOptions->vGetLayoutFile()) != true)
	{
		return false;
	}
	
	m_pGameOptions = pOptions;

	m_bReady = true;

	return true;
}

void GameManager::vPostInit()
{
	m_pSceneManager->vChange(m_pGameOptions->vGetFirstLayerName());
}

bool GameManager::vIsRunning()
{
	return (m_pRenderManager->vGetWndNum() > 0 && SDL_QuitRequested() != SDL_TRUE);
}

void GameManager::vAttachWindowListener(IRenderListener* pListener)
{
	RenderListener* pCastListener = dynamic_cast<RenderListener*>(pListener);

	if (pCastListener && m_pRenderManager)
	{
		pCastListener->m_pContext = m_pRenderManager;

		pCastListener->m_pOptions = m_pGameOptions;
		
		m_pRenderManager->vAttach(pCastListener, m_nWndIndex);
	}
}

void GameManager::vAttachLayerListener(ISceneListener* pListener, const char* pLayerName)
{
	SceneListener* pCastListener = dynamic_cast<SceneListener*>(pListener);

	if (pCastListener && m_pSceneManager)
	{
		pCastListener->m_pContext = m_pSceneManager;

		pCastListener->m_pOptions = m_pGameOptions;

		m_pSceneManager->vAttach(pCastListener, pLayerName);
	}
}

void GameManager::vTriggerEvents()
{
	while (SDL_PollEvent(&m_sEvent))
	{
		switch(m_sEvent.type) 
		{
		case SDL_WINDOWEVENT :
			{
				m_pRenderManager->vOnEvent(&m_sEvent.window);

				break;
			}
		case SDL_KEYDOWN :
		case SDL_KEYUP :
			{
				m_pSceneManager->vOnEvent(&m_sEvent.key);
				
				break;
			}
		case SDL_MOUSEBUTTONDOWN :
		case SDL_MOUSEBUTTONUP :
			{
				m_pSceneManager->vOnEvent(&m_sEvent.button);
				
				break;
			}
		case SDL_QUIT :
			{
				m_pRenderManager->vDestroy(m_nWndIndex);

				break;
			}
		}
	}
	
	m_pSceneManager->vUpdate();

	m_pSceneManager->vRender();
	
	m_pRenderManager->vSwapBuffer(m_nWndIndex);
}
