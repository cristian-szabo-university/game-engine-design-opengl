#pragma once

#include "ZenoInterface.h"

#include "Entity\ZenoEntityData.h"

class SceneListener : public ISceneListener
{
public:
	SceneListener();

	virtual ~SceneListener();

	virtual void vOnInit(void* pUserData);

	virtual void vOnMouse(int nButton, int nState, int nPosX, int nPosY);

	virtual void vOnKeyboard(SDL_Keycode nKeyn, int nState);

	virtual ISceneManager* vGetContext();

	virtual IGameOptions* vGetOptions();

	virtual void vOnClose();

private:
	friend class GameManager;

	friend class SceneManager;

	ISceneManager* m_pContext;

	IGameOptions* m_pOptions;

};

class SceneLayer : public ISceneLayer
{
public:
	SceneLayer(const char* pName);

	virtual ~SceneLayer();

	virtual void vAttach(IEntity* pObject);

	virtual IEntity* vFind(const char* pName);

	virtual void vRemove(const char* pName);

	virtual void vErase(const char* pName);

	virtual IEntity* vDetectCollision(const char* pName);

	virtual IEntity* vCheckMouseHover(const char* pName, int nMousePosX, int nMousePosY);

	virtual void vUpdate();

	virtual void vRender();

	virtual tinyxml2::XMLElement* vToXML(tinyxml2::XMLDocument* pDoc);

	virtual const char* vGetName();

private:
	std::vector<IEntity*> m_vecEntity;

	std::string m_szName;

};
