#pragma once

#include "ZenoInterface.h"

#include "ZenoGameData.h"

#include "ZenoTemplate.h"
#include "Render/ZenoRenderManager.h"
#include "Entity/ZenoEntityFactory.h"
#include "Resource/ZenoResourceManager.h"
#include "Scene/ZenoSceneManager.h"

class GameManager : public IGameManager
{
public:
	virtual ~GameManager();

	virtual bool vInit(IGameOptions* pOptions);

	virtual void vPostInit();

	virtual bool vIsRunning();

	virtual void vAttachWindowListener(IRenderListener* pListener);

	virtual void vAttachLayerListener(ISceneListener* pListener, const char* pLayerName);

	virtual void vTriggerEvents();

private:
	template<class T> friend class Global;

	bool m_bReady;

	int m_nWndIndex;

	SDL_Event m_sEvent;

	IGameOptions* m_pGameOptions;

	IRenderManager* m_pRenderManager;

	IResourceManager* m_pResourceManager;

	IEntityFactory* m_pEntityFactory;

	ISceneManager* m_pSceneManager;

	GameManager();

};
