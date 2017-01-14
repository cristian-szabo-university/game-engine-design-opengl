#pragma once

#include "ZenoInterface.h"

#include "ZenoSceneData.h"

class SceneManager : public ISceneManager
{
public:
	SceneManager();

	virtual ~SceneManager();

	virtual bool vLoad(const char* pFileName);

	virtual void vSave(const char* pFileName);

	virtual void vChange(const char* pLayerName, void* pUserData = NULL);

	virtual ISceneLayer* vFind(const char* pName);

	virtual void vRemove(const char* pName);

	virtual void vAttach(ISceneListener* pListener, const char* pLayerName);

	virtual void vOnEvent(SDL_KeyboardEvent* pEvent);

	virtual void vOnEvent(SDL_MouseButtonEvent* pEvent);

	virtual void vUpdate();

	virtual void vRender();

	virtual void vReset();

	virtual void vQuit();

private:
	int m_nCurrentTime;

	ISceneLayer* m_pCurrentLayer;

	std::list<ISceneLayer*> m_listLayer;

	std::map<std::string, ISceneListener*> m_mapListener;

};