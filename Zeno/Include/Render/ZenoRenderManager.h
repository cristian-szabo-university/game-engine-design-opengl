#pragma once

#include "ZenoInterface.h"

#include "ZenoRenderData.h"

class RenderManager : public IRenderManager
{
public:
	virtual ~RenderManager();

	virtual bool vInit();

	virtual int vCreate(int nWndWidth, int nWndHeight, const char* pWndTitle);

	virtual void vAttach(IRenderListener* pListener, int nIndex);

	virtual void vMakeCurrent(int nIndex);

	virtual void vSwapBuffer(int nIndex);

	virtual void vOnEvent(SDL_WindowEvent* pEvent);

	virtual void vDestroy(int nIndex);

	virtual int vGetWndNum();

private:
	template<class T> friend class Global;

	std::map<int, IRenderListener*> m_mapListener;

	bool m_bReady;

	SDL_GLContext m_pContext;

	RenderManager();

};