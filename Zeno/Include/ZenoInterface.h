#pragma once

#include <malloc.h>
#include <iostream>
#include <fstream>

#include <string>
#include <vector>
#include <list>
#include <map>

#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "TinyXML2\TinyXML2.h"

/* ------------------------------------------------------------------------- */

struct MemoryData
{
	int nSize;

	std::string szFileName;

	int nLineNum;

	std::string szFuncName;
};

class MemoryTracker
{
public:
	static MemoryTracker* getInst();

	~MemoryTracker();

	void record(void* ptr, MemoryData data);

	void release(void* ptr);

private:
	std::map<void*, MemoryData> m_mapData;

	int m_nTotalMemAlloc;

	MemoryTracker();

};

class MemoryObject
{
public:
	virtual ~MemoryObject();

	void* operator new(size_t sz, const char* file, int line, const char* func);

	void operator delete(void* pPointer, const char* pFileName, int nLineNum, const char* pFuncName);

	void operator delete(void* pPointer);
};

#define ZENO_NEW new (__FILE__, __LINE__, __FUNCTION__)
#define ZENO_DELETE delete

/* ------------------------------------------------------------------------- */

class IGameManager;
class IGameOptions;
class IResourceManager;
class IResource;
class IRenderTarget;
class IRenderListener;
class IRenderManager;
class ISceneLayer;
class ISceneListener;
class ISceneManager;
class IEntity;
class IEntityCategory;
class IEntityComponent;
class IEntityFactory;

/* ------------------------------------------------------------------------- */

class IGameOptions : public MemoryObject
{
public:
	virtual ~IGameOptions();

	virtual const char* vGetWndTitle() = 0;

	virtual int vGetWndWidth() = 0;

	virtual int vGetWndHeight() = 0;

	virtual const char* vGetResourceFile() = 0;

	virtual const char* vGetLayoutFile() = 0;

	virtual const char* vGetCategoryFile() = 0;

	virtual const char* vGetFirstLayerName() = 0;

};

class IGameManager : public MemoryObject
{
public:
	virtual ~IGameManager();

	virtual bool vInit(IGameOptions* pOptions) = 0;

	virtual void vPostInit() = 0;

	virtual bool vIsRunning() = 0;

	virtual void vAttachWindowListener(IRenderListener* pListener) = 0;

	virtual void vAttachLayerListener(ISceneListener* pListener, const char* pLayerName) = 0;

	virtual void vTriggerEvents() = 0;

};

/* ------------------------------------------------------------------------- */

class IRenderTarget : public MemoryObject
{
public:
	virtual ~IRenderTarget();

	virtual bool vSetup(IResource* pResource) = 0;

	virtual void vRender(int nPosX, int nPosY) = 0;

	virtual void vClean() = 0;

	virtual int vGetWidth() = 0;

	virtual int vGetHeight() = 0;

};

class IRenderListener : public MemoryObject
{
public:
	virtual ~IRenderListener();

	virtual void vOnClose() = 0;

	virtual void vOnResize(int nWidth, int nHegiht) = 0;

	virtual IRenderManager* vGetContext() = 0;

	virtual IGameOptions* vGetOption() = 0;

};

class IRenderManager : public MemoryObject
{
public:
	virtual ~IRenderManager();

	virtual bool vInit() = 0;

	virtual int vCreate(int nWndWidth, int nWndHeight, const char* pWndTitle) = 0;

	virtual void vAttach(IRenderListener* pListener, int nIndex) = 0;

	virtual void vMakeCurrent(int nWindowIndex) = 0;

	virtual void vSwapBuffer(int nWindowIndex) = 0;

	virtual void vOnEvent(SDL_WindowEvent* pEvent) = 0;

	virtual void vDestroy(int nWindowIndex) = 0;

	virtual int vGetWndNum() = 0;
};

/* ------------------------------------------------------------------------- */

class IEntity : public MemoryObject
{
public:
	virtual ~IEntity();

	virtual void vUpdate() = 0;

	virtual void vRender() = 0;

	virtual tinyxml2::XMLElement* vToXML(tinyxml2::XMLDocument* pDoc) = 0;

	virtual const char* vGetName() = 0;

	virtual const char* vGetCategory() = 0;

	virtual int vGetWidth() = 0;

	virtual int vGetHeight() = 0;

	virtual int vGetPosX() = 0;

	virtual int vGetPosY() = 0;

	virtual IEntityComponent* vGetComponent(const char* pName) = 0;

};

class IEntityCategory : public MemoryObject
{
public:
	virtual ~IEntityCategory();

	virtual const char* vGetName() = 0;

	virtual const char* vGetType() = 0;

	virtual int vGetResourceIndex() = 0;

};

class IEntityComponent : public MemoryObject
{
public:
	virtual ~IEntityComponent();

	virtual void vChange(int nValue) = 0;

	virtual void vSet(int nValue) = 0;;

	virtual const char* vGetName() = 0;

	virtual int vGet() = 0;
};

class IEntityFactory : public MemoryObject
{
public:
	typedef IRenderTarget* (*CreateFunc)(tinyxml2::XMLElement* pElement);

	virtual ~IEntityFactory();

	virtual bool vLoad(const char* pFileName) = 0;

	virtual IEntityComponent* vFind(const char* pCategory, const char* pComponent) = 0;

	virtual void vRegister(const char* pCategory, CreateFunc pFunc) = 0;

	virtual IEntity* vCreate(tinyxml2::XMLElement* pElement) = 0;

};

/* ------------------------------------------------------------------------- */

class ISceneLayer : public MemoryObject
{
public:
	virtual ~ISceneLayer();

	virtual void vAttach(IEntity* pObject) = 0;

	virtual IEntity* vFind(const char* pName) = 0;

	virtual void vRemove(const char* pName) = 0;

	virtual void vErase(const char* pName) = 0;

	virtual IEntity* vDetectCollision(const char* pName) = 0;

	virtual IEntity* vCheckMouseHover(const char* pName, int nMousePosX, int nMousePosY) = 0;

	virtual void vUpdate() = 0;

	virtual void vRender() = 0;

	virtual tinyxml2::XMLElement* vToXML(tinyxml2::XMLDocument* pDoc) = 0;

	virtual const char* vGetName() = 0;

};

class ISceneListener : public MemoryObject
{
public:
	virtual ~ISceneListener();

	virtual void vOnInit(void* pUserData) = 0;

	virtual void vOnUpdate(int nCurrentTime) = 0;

	virtual void vOnMouse(int nButton, int nState, int nPosX, int nPosY) = 0;

	virtual void vOnKeyboard(SDL_Keycode nKeyn, int nState) = 0;

	virtual ISceneManager* vGetContext() = 0;

	virtual IGameOptions* vGetOptions() = 0;

};

class ISceneManager : public MemoryObject
{
public:
	virtual ~ISceneManager();

	virtual bool vLoad(const char* pFileName) = 0;

	virtual void vSave(const char* pFileName) = 0;

	virtual void vChange(const char* pName, void* pUserData = NULL) = 0;

	virtual ISceneLayer* vFind(const char* pName) = 0;

	virtual void vRemove(const char* pName) = 0;

	virtual void vAttach(ISceneListener* pListener, const char* pLayerName) = 0;

	virtual void vOnEvent(SDL_KeyboardEvent* pEvent) = 0;

	virtual void vOnEvent(SDL_MouseButtonEvent* pEvent) = 0;

	virtual void vUpdate() = 0;

	virtual void vRender() = 0;

	virtual void vReset() = 0;

	virtual void vQuit() = 0;

};

/* ------------------------------------------------------------------------- */

const enum ResourceType
{
	RESOURCE_INVALID,
	RESOURCE_GRAPHIC,
	RESOURCE_AUDIO,
	RESOURCE_FONT,
	RESOURCE_TYPE_MAX
};

class IResource : public MemoryObject
{
public:
	virtual ~IResource();

	virtual void vLoad() = 0;

	virtual void vClean() = 0;

	virtual bool vIsLoaded() = 0;

	virtual const char* vGetFileName() = 0;

	virtual ResourceType vGetType() = 0;

	virtual int vGetIndex() = 0;

};

class IResourceManager : public MemoryObject
{
public:
	virtual ~IResourceManager();

	virtual bool vInit() = 0;

	virtual bool vLoad(const char* pFileName) = 0;

	virtual IResource* vFind(int nIndex) = 0;

};

/* ------------------------------------------------------------------------- */
